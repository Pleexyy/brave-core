pipeline {
    agent {
        node { label "master" }
    }
    options {
        timeout(time: 6, unit: "HOURS")
        timestamps()
    }
    parameters {
        choice(name: "BUILD_TYPE", choices: ["Release", "Debug"], description: "")
        choice(name: "CHANNEL", choices: ["nightly", "dev", "beta", "release", "development"], description: "")
        string(name: "SLACK_BUILDS_CHANNEL", defaultValue: "#build-downloads-bot", description: "The Slack channel to send the list of artifact download links to. Leave blank to skip sending the message.")
        booleanParam(name: "SKIP_SIGNING", defaultValue: true, description: "")
        booleanParam(name: "WIPE_WORKSPACE", defaultValue: false, description: "")
        booleanParam(name: "SKIP_INIT", defaultValue: false, description: "")
        booleanParam(name: "DISABLE_SCCACHE", defaultValue: false, description: "")
        booleanParam(name: "DCHECK_ALWAYS_ON", defaultValue: true, description: "")
        booleanParam(name: "DEBUG", defaultValue: false, description: "")
    }
    environment {
        GITHUB_API = "https://api.github.com/repos/brave"
        GITHUB_CREDENTIAL_ID = "brave-builds-github-token-for-pr-builder"
        GITHUB_AUTH = credentials("${GITHUB_CREDENTIAL_ID}")
        BB_REPO = "https://${GITHUB_AUTH}@github.com/brave/brave-browser"
    }
    stages {
        stage("env") {
            steps {
                withCredentials([usernamePassword(credentialsId: "${GITHUB_CREDENTIAL_ID}", usernameVariable: "PR_BUILDER_USER", passwordVariable: "PR_BUILDER_TOKEN")]) {
                    script {
                        BUILD_TYPE = params.BUILD_TYPE
                        CHANNEL = params.CHANNEL
                        SLACK_BUILDS_CHANNEL = params.SLACK_BUILDS_CHANNEL
                        SKIP_SIGNING = params.SKIP_SIGNING
                        WIPE_WORKSPACE = params.WIPE_WORKSPACE
                        SKIP_INIT = params.SKIP_INIT
                        DISABLE_SCCACHE = params.DISABLE_SCCACHE
                        DCHECK_ALWAYS_ON = params.DCHECK_ALWAYS_ON
                        DEBUG = params.DEBUG
                        SKIP = false
                        BRANCH = env.BRANCH_NAME
                        TARGET_BRANCH = "master"
                        if (env.CHANGE_BRANCH) {
                            BRANCH = env.CHANGE_BRANCH
                            TARGET_BRANCH = env.CHANGE_TARGET
                            def bcPrDetails = readJSON(text: httpRequest(url: GITHUB_API + "/brave-core/pulls?head=brave:" + BRANCH, customHeaders: [[name: "Authorization", value: "token ${PR_BUILDER_TOKEN}"]], quiet: !DEBUG).content)[0]
                            if (bcPrDetails) {
                                bcPrDetails = readJSON(text: httpRequest(url: GITHUB_API + "/brave-core/pulls/" + bcPrDetails.number, customHeaders: [[name: "Authorization", value: "token ${PR_BUILDER_TOKEN}"]], quiet: !DEBUG).content)
                                SKIP = SKIP || bcPrDetails.mergeable_state.equals("draft") || bcPrDetails.labels.count { label -> label.name.equalsIgnoreCase("CI/skip") }.equals(1)
                            }
                        }
                        BRANCH_EXISTS_IN_BB = httpRequest(url: GITHUB_API + "/brave-browser/branches/" + BRANCH, validResponseCodes: "100:499", customHeaders: [[name: "Authorization", value: "token ${PR_BUILDER_TOKEN}"]], quiet: !DEBUG).status.equals(200)
                        if (BRANCH_EXISTS_IN_BB) {
                            def bbPrDetails = readJSON(text: httpRequest(url: GITHUB_API + "/brave-browser/pulls?head=brave:" + BRANCH, customHeaders: [[name: "Authorization", value: "token ${PR_BUILDER_TOKEN}"]], quiet: !DEBUG).content)[0]
                            if (bbPrDetails) {
                                bbPrDetails = readJSON(text: httpRequest(url: GITHUB_API + "/brave-browser/pulls/" + bbPrDetails.number, customHeaders: [[name: "Authorization", value: "token ${PR_BUILDER_TOKEN}"]], quiet: !DEBUG).content)
                                SKIP = SKIP || bbPrDetails.mergeable_state.equals("draft") || bbPrDetails.labels.count { label -> label.name.equalsIgnoreCase("CI/skip") }.equals(1)
                            }
                        }
                        buildName env.BUILD_NUMBER + "-" + BRANCH + "-" + env.GIT_COMMIT.substring(0, 7)
                    }
                }
            }
        }
        stage("abort") {
            steps {
                script {
                    if (SKIP) {
                        echo "Aborting build as PR is in draft or has \"CI/skip\" label"
                        stopCurrentBuild()
                    }
                    for (build in getBuilds()) {
                        if (build.isBuilding() && build.getNumber() < env.BUILD_NUMBER.toInteger()) {
                            echo "Aborting older running build " + build
                            build.doStop()
                        }
                    }
                }
            }
        }
        stage("checkout") {
            when {
                expression { !SKIP }
            }
            steps {
                sh """
                    set -e

                    if [ -d brave-browser ]; then
                        rm -rf brave-browser
                    fi

                    git clone --branch ${TARGET_BRANCH} ${BB_REPO} || git clone ${BB_REPO}

                    cd brave-browser
                    git config user.name brave-builds
                    git config user.email devops@brave.com
                    git config push.default simple
                """
            }
        }
        stage("branch") {
            when {
                allOf {
                    expression { !SKIP }
                    expression { !BRANCH_EXISTS_IN_BB }
                }
            }
            steps {
                sh """
                    set -e

                    cd brave-browser
                    git checkout -b ${BRANCH}

                    echo "Creating CI branch"
                    git commit --allow-empty -m "created CI branch"

                    echo "Pushing"
                    git push ${BB_REPO}
                """
            }
        }
        stage("build") {
            when {
                expression { !SKIP }
            }
            steps {
                withCredentials([usernamePassword(credentialsId: "${GITHUB_CREDENTIAL_ID}", usernameVariable: "PR_BUILDER_USER", passwordVariable: "PR_BUILDER_TOKEN")]) {
                    script {
                        try {
                            startBraveBrowserBuild()
                        }
                        catch (hudson.AbortException ex) {
                            echo "Sleeping 6m so new branch is discovered or associated PR created in brave-browser"
                            sleep(time: 6, unit: "MINUTES")
                            startBraveBrowserBuild()
                        }
                    }
                }
            }
        }
    }
}

@NonCPS
def stopCurrentBuild() {
    Jenkins.instance.getItemByFullName(env.JOB_NAME).getLastBuild().doStop()
}

@NonCPS
def getBuilds() {
    return Jenkins.instance.getItemByFullName(env.JOB_NAME).builds
}

def startBraveBrowserBuild() {
    def prDetails = readJSON(text: httpRequest(url: GITHUB_API + "/brave-browser/pulls?head=brave:" + BRANCH, customHeaders: [[name: "Authorization", value: "token ${PR_BUILDER_TOKEN}"]], quiet: !DEBUG).content)[0]
    def prNumber = prDetails ? prDetails.number : ""
    def refToBuild = prNumber ? "PR-" + prNumber : URLEncoder.encode(BRANCH, "UTF-8")
    params = [
        string(name: "BUILD_TYPE", value: BUILD_TYPE),
        string(name: "CHANNEL", value: CHANNEL),
        string(name: "SLACK_BUILDS_CHANNEL", value: SLACK_BUILDS_CHANNEL),
        booleanParam(name: "SKIP_SIGNING", value: SKIP_SIGNING),
        booleanParam(name: "WIPE_WORKSPACE", value: WIPE_WORKSPACE),
        booleanParam(name: "SKIP_INIT", value: SKIP_INIT),
        booleanParam(name: "DISABLE_SCCACHE", value: DISABLE_SCCACHE),
        booleanParam(name: "DCHECK_ALWAYS_ON", value: DCHECK_ALWAYS_ON),
        booleanParam(name: "DEBUG", value: DEBUG)
    ]
    currentBuild.result = build(job: "brave-browser-build-pr/" + refToBuild, parameters: params, propagate: false).result
}
