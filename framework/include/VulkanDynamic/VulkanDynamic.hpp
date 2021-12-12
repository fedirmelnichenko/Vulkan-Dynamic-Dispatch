// Copyright 2021 Fedir Melnichenko
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//     http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef __VULKANDYNAMIC_HPP__
#define __VULKANDYNAMIC_HPP__

#include "VulkanDynamic.h"

#include <utility>

namespace VulkanDynamic
{
    //------------------------------------------------------------------------------------
    // Loader
    //------------------------------------------------------------------------------------

    class Loader
    {
    public:
        explicit Loader(::VulkanDynamicLoader loader) noexcept : loader_{ loader }
        {
        }

        Loader(::std::nullptr_t) noexcept : loader_{ nullptr }
        {
        }

        Loader(const Loader&) noexcept = delete;

        Loader(Loader&& src) noexcept : loader_{ src.loader_ }
        {
            src.loader_ = nullptr;
        }

        Loader() noexcept : loader_{ nullptr }
        {
        }

        ~Loader() noexcept
        {
            if (loader_)
            {
                ::VulkanDynamicDestroyLoader(loader_);
            }
        }

        Loader& operator=(const Loader&) noexcept = delete;

        Loader& operator=(Loader&& other) noexcept
        {
            Loader{ ::std::move(other) }.Swap(*this);
            return *this;
        }

        explicit operator bool() const noexcept
        {
            return loader_ != nullptr;
        }

        operator ::VulkanDynamicLoader() const noexcept
        {
            return loader_;
        }

    private:
        void Swap(Loader& other) noexcept
        {
            auto copy = loader_;
            loader_ = other.loader_;
            other.loader_ = copy;
        }

    private:
        ::VulkanDynamicLoader loader_{ nullptr };
    };

    inline Loader CreateLoader(::VkResult& result) noexcept
    {
        ::VulkanDynamicLoader loader = nullptr;
        ::VulkanDynamicCreateLoader(&loader);

        return Loader{ loader };
    }

    inline Loader CreateLoader() noexcept
    {
        ::VkResult _;
        return CreateLoader(_);
    }

    struct LoaderDispatch : ::VulkanDynamicLoaderDispatch
    {
        explicit LoaderDispatch(const Loader& loader, ::VkResult& result) noexcept : LoaderDispatch{}
        {
            result = ::VulkanDynamicGetLoaderDispatch(loader, this);
        }

        explicit LoaderDispatch(const Loader& loader) noexcept : LoaderDispatch{}
        {
            ::VulkanDynamicGetLoaderDispatch(loader, this);
        }

        LoaderDispatch() noexcept = default;
    };

    //------------------------------------------------------------------------------------
    // Instance
    //------------------------------------------------------------------------------------

    struct InstanceDispatch : ::VulkanDynamicInstanceDispatch
    {
        explicit InstanceDispatch(::VkInstance instance, const LoaderDispatch& loaderDispatch, ::VkResult& result) noexcept : InstanceDispatch{}
        {
            result = ::VulkanDynamicGetInstanceDispatch(instance, &loaderDispatch, this);
        }

        explicit InstanceDispatch(::VkInstance instance, const LoaderDispatch& loaderDispatch) noexcept : InstanceDispatch{}
        {
            ::VulkanDynamicGetInstanceDispatch(instance, &loaderDispatch, this);
        }

        InstanceDispatch() noexcept = default;
    };

    //------------------------------------------------------------------------------------
    // Device
    //------------------------------------------------------------------------------------

    struct DeviceDispatch : ::VulkanDynamicDeviceDispatch
    {
        explicit DeviceDispatch(::VkDevice device, const InstanceDispatch& instanceDispatch, ::VkResult& result) noexcept : DeviceDispatch{}
        {
            result = ::VulkanDynamicGetDeviceDispatch(device, &instanceDispatch, this);
        }

        explicit DeviceDispatch(::VkDevice device, const InstanceDispatch& instanceDispatch) noexcept : DeviceDispatch{}
        {
            ::VulkanDynamicGetDeviceDispatch(device, &instanceDispatch, this);
        }

        DeviceDispatch() noexcept = default;
    };
} // namespace VulkanDynamic

#endif // __VULKANDYNAMIC_HPP__
