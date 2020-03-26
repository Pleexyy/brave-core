/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BAT_CONFIRMATIONS_INTERNAL_PLATFORM_HELPER_LINUX_H_
#define BAT_CONFIRMATIONS_INTERNAL_PLATFORM_HELPER_LINUX_H_

#include <string>

#include "bat/confirmations/internal/platform_helper.h"

namespace confirmations {

class PlatformHelperLinux : public PlatformHelper {
 public:
  static PlatformHelperLinux* GetInstanceImpl();

 private:
  PlatformHelperLinux();
  ~PlatformHelperLinux() override;

  // PlatformHelper impl
  std::string GetPlatform() const override;

  friend struct base::DefaultSingletonTraits<PlatformHelperLinux>;
  DISALLOW_COPY_AND_ASSIGN(PlatformHelperLinux);
};

}  // namespace confirmations

#endif  // BAT_CONFIRMATIONS_INTERNAL_PLATFORM_HELPER_LINUX_H_
