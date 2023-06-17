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

template <typename T> using UniquePtr = std::unique_ptr<T>;
template <typename T> class Releaser;
template <typename T> using UniqueReleaserPtr = std::unique_ptr<T, Releaser<T>>;
template <typename T> using SharedPtr = std::shared_ptr<T>;
template <typename T> using WeakPtr = std::weak_ptr<T>;
template <typename T, typename... Args> inline SharedPtr<T> MakeShared(Args &&...args)
{
    return std::make_shared<T, Args...>(std::forward<Args>(args)...);
}
template <typename T, typename... Args> inline UniquePtr<T> MakeUnique(Args &&...args)
{
    return std::make_unique<T, Args...>(std::forward<Args>(args)...);
}

} // namespace chronicle