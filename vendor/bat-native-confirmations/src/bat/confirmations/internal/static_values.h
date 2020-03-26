/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BAT_CONFIRMATIONS_INTERNAL_STATIC_VALUES_H_
#define BAT_CONFIRMATIONS_INTERNAL_STATIC_VALUES_H_

#include <stdint.h>
#include <map>
#include <string>

#include "base/time/time.h"

namespace confirmations {

#define BAT_ADS_PRODUCTION_SERVER "https://ads-serve.brave.com"
#define BAT_ADS_STAGING_SERVER "https://ads-serve.bravesoftware.com"
#define BAT_ADS_DEVELOPMENT_SERVER "https://ads-serve.brave.software"

#define BAT_LEDGER_PRODUCTION_SERVER "https://ledger.mercury.basicattentiontoken.org"  // NOLINT
#define BAT_LEDGER_STAGING_SERVER "https://ledger-staging.mercury.basicattentiontoken.org"  // NOLINT
#define BAT_LEDGER_DEVELOPMENT_SERVER "https://ledger.rewards.brave.software"  // NOLINT

const int kNextPaymentDay = 5;

const int kMinimumUnblindedTokens = 20;
const int kMaximumUnblindedTokens = 50;

const uint64_t kRetryGettingRefillSignedTokensAfterSeconds = 15;

const uint64_t kNextTokenRedemptionAfterSeconds =
    24 * base::Time::kSecondsPerHour;
const uint64_t kDebugNextTokenRedemptionAfterSeconds =
    25 * base::Time::kSecondsPerMinute;

const uint64_t kRetryFailedConfirmationsAfterSeconds =
    5 * base::Time::kSecondsPerMinute;

const std::map<std::string, bool> kLargeAnonymityCountryCodes = {
  { "US", true  },  // United States of America
  { "CA", true  },  // Canada
  { "GB", true  },  // United Kingdom (Great Britain and Northern Ireland)
  { "DE", true  },  // Germany
  { "FR", true  },  // France
  { "AU", true  },  // Australia
  { "NZ", true  },  // New Zealand
  { "IE", true  },  // Ireland
  { "AR", true  },  // Argentina
  { "AT", true  },  // Austria
  { "BR", true  },  // Brazil
  { "CH", true  },  // Switzerland
  { "CL", true  },  // Chile
  { "CO", true  },  // Colombia
  { "DK", true  },  // Denmark
  { "EC", true  },  // Ecuador
  { "IL", true  },  // Israel
  { "IN", true  },  // India
  { "IT", true  },  // Italy
  { "JP", true  },  // Japan
  { "KR", true  },  // Korea
  { "MX", true  },  // Mexico
  { "NL", true  },  // Netherlands
  { "PE", true  },  // Peru
  { "PH", true  },  // Philippines
  { "PL", true  },  // Poland
  { "SE", true  },  // Sweden
  { "SG", true  },  // Singapore
  { "VE", true  },  // Venezuela
  { "ZA", true  },  // South Africa
  { "KY", false },  // Cayman Islands
  { "AE", true  },  // United Arab Emirates
  { "AL", true  },  // Albania
  { "AZ", true  },  // Azerbaijan
  { "BD", true  },  // Bangladesh
  { "BE", true  },  // Belgium
  { "BG", true  },  // Bulgaria
  { "CN", true  },  // China
  { "CZ", true  },  // Czechia
  { "DZ", true  },  // Algeria
  { "EG", true  },  // Egypt
  { "ES", true  },  // Spain
  { "FI", true  },  // Finland
  { "GR", true  },  // Greece
  { "HK", true  },  // Hong Kong
  { "HR", true  },  // Croatia
  { "HU", true  },  // Hungary
  { "ID", true  },  // Indonesia
  { "IQ", true  },  // Iraq
  { "KH", true  },  // Cambodia
  { "LT", true  },  // Lithuania
  { "MA", true  },  // Morocco
  { "MY", true  },  // Malaysia
  { "NG", true  },  // Nigeria
  { "NO", true  },  // Norway
  { "PK", true  },  // Pakistan
  { "PT", true  },  // Portugal
  { "RO", true  },  // Romania
  { "RS", true  },  // Serbia
  { "RU", true  },  // Russian Federation
  { "SA", true  },  // Saudi Arabia
  { "SI", true  },  // Slovenia
  { "SK", true  },  // Slovakia
  { "TH", true  },  // Thailand
  { "TR", true  },  // Turkey
  { "TW", true  },  // Taiwan
  { "UA", true  },  // Ukraine
  { "VN", true  }   // Vietnam
};

const std::map<std::string, bool> kPrivacyCountryCodes = {
};

}  // namespace confirmations

#endif  // BAT_CONFIRMATIONS_INTERNAL_STATIC_VALUES_H_
