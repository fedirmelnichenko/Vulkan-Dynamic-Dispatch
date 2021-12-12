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

#include <VulkanDynamic/VulkanDynamic.hpp>

#include <iostream>
#include <vector>

namespace
{
    void Print(std::ostream& os, const ::VkPhysicalDeviceProperties& properties)
    {
        os << "VkPhysicalDeviceProperties:\n";
        os << "  Device name: " << properties.deviceName << "\n\n";
    }

    void Print(std::ostream& os, const ::VkPhysicalDeviceDriverProperties& properties)
    {
        os << "VkPhysicalDeviceDriverProperties:\n";
        os << "  Driver name: " << properties.driverName << "\n";
        os << "  Driver info: " << properties.driverInfo << "\n\n";
    }
}

int main()
{
    ::VkResult result{ ::VK_SUCCESS };

    ::VulkanDynamic::Loader loader = ::VulkanDynamic::CreateLoader(result);
    if (!loader)
    {
        return -1;
    }

    const ::VulkanDynamic::LoaderDispatch loaderDispatch{ loader, result };

    ::VkApplicationInfo applicationInfo{ ::VK_STRUCTURE_TYPE_APPLICATION_INFO };
    applicationInfo.apiVersion = VK_API_VERSION_1_0;
    
    const char* requiredInstanceExtensions[] = { VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME };

    ::VkInstanceCreateInfo instanceCreateInfo{ ::VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO };
    instanceCreateInfo.pApplicationInfo = &applicationInfo;
    instanceCreateInfo.enabledExtensionCount = 1;
    instanceCreateInfo.ppEnabledExtensionNames = requiredInstanceExtensions;

    ::VkInstance instance = nullptr;
    if (loaderDispatch.CreateInstance(&instanceCreateInfo, nullptr, &instance) != VK_SUCCESS)
    {
        return -1;
    }

    const ::VulkanDynamic::InstanceDispatch instanceDispatch{ instance, loaderDispatch, result };

    uint32_t physicalDeviceCount{};
    instanceDispatch.EnumeratePhysicalDevices(instance, &physicalDeviceCount, nullptr);
    std::vector<::VkPhysicalDevice> physicalDevices{ physicalDeviceCount };
    instanceDispatch.EnumeratePhysicalDevices(instance, &physicalDeviceCount, physicalDevices.data());

    for (auto physicalDevice : physicalDevices)
    {
        ::VkPhysicalDeviceDriverProperties driverProperties{ ::VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DRIVER_PROPERTIES };
        ::VkPhysicalDeviceProperties2 physicalDeviceProperties{ ::VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2, &driverProperties };
        instanceDispatch.GetPhysicalDeviceProperties2KHR(physicalDevice, &physicalDeviceProperties);

        Print(std::cout, physicalDeviceProperties.properties);
        Print(std::cout, driverProperties);
    }

    instanceDispatch.DestroyInstance(instance, nullptr);

    return 0;
}
