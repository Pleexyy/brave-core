/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "bat/confirmations/internal/platform_helper_ios.h"

#import <Cocoa/Cocoa.h>

namespace confirmations {

PlatformHelperIOS::PlatformHelperIOS() = default;

PlatformHelperIOS::~PlatformHelperIOS() = default;

std::string PlatformHelperIOS::GetPlatformName() const {
  return "ios";
}

PlatformHelperIOS* PlatformHelperIOS::GetInstanceImpl() {
  return base::Singleton<PlatformHelperIOS>::get();
}

PlatformHelper* PlatformHelper::GetInstanceImpl() {
  return PlatformHelperIOS::GetInstanceImpl();
}

}  // namespace confirmations
