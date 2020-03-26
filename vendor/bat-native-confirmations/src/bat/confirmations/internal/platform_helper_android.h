/* Copyright (c) 202- The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BAT_CONFIRMATIONS_INTERNAL_PLATFORM_HELPER_LINUX_ANDROID_H_
#define BAT_CONFIRMATIONS_INTERNAL_PLATFORM_HELPER_LINUX_ANDROID_H_

#include <string>

#include "bat/confirmations/internal/platform_helper.h"

namespace confirmations {

class PlatformHelperAndroid : public PlatformHelper {
 public:
  static PlatformHelperAndroid* GetInstanceImpl();

 private:
  PlatformHelperAndroid() = default;
  ~PlatformHelperAndroid() override = default;

  // PlatformHelper impl
  std::string GetPlatformName() const override;

  friend struct base::DefaultSingletonTraits<PlatformHelperAndroid>;
  DISALLOW_COPY_AND_ASSIGN(PlatformHelperAndroid);
};

}  // namespace confirmations

#endif  // BAT_CONFIRMATIONS_INTERNAL_PLATFORM_HELPER_LINUX_ANDROID_H_
