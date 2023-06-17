// Copyright (c) 2023 Sandro Cavazzoni
// This code is licensed under MIT license (see LICENSE.txt for details)

#pragma once

#include <cassert>
#include <functional>
#include <memory>
#include <optional>
#include <set>
#include <stdexcept>
#include <string>

#include <magic_enum.hpp>

#include "Log.h"

namespace chronicle
{

template <class T> using Unique = std::unique_ptr<T>;
template <class T> using Ref = std::shared_ptr<T>;

} // namespace chronicle