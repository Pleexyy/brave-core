/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BAT_CONFIRMATIONS_INTERNAL_PLATFORM_HELPER_H_
#define BAT_CONFIRMATIONS_INTERNAL_PLATFORM_HELPER_H_

#include <string>

#include "base/macros.h"
#include "base/memory/singleton.h"
#include "build/build_config.h"

namespace confirmations {

class PlatformHelper {
 public:
  static PlatformHelper* GetInstance();

  void set_for_testing(
      PlatformHelper* platform_helper);

  // Should return the platform
  virtual std::string GetPlatformName() const;

 protected:
  PlatformHelper();
  virtual ~PlatformHelper();

  static PlatformHelper* GetInstanceImpl();

 private:
  friend struct base::DefaultSingletonTraits<PlatformHelper>;
  DISALLOW_COPY_AND_ASSIGN(PlatformHelper);
};

}  // namespace confirmations

#endif  // BAT_CONFIRMATIONS_INTERNAL_PLATFORM_HELPER_H_
