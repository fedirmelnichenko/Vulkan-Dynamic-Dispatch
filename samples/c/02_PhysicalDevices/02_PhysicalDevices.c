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

#include <VulkanDynamic/VulkanDynamic.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void PrintProperties(const VkPhysicalDeviceProperties* properties)
{
    if (properties)
    {
        printf("VkPhysicalDeviceProperties:\n  Device name: %s\n\n", properties->deviceName);
    }
}

static void PrintDriverProperties(const VkPhysicalDeviceDriverProperties* properties)
{
    if (properties)
    {
        printf("VkPhysicalDeviceDriverProperties:\n  Driver name: %s\n  Driver info: %s\n\n", properties->driverName, properties->driverName);
    }
}

int main()
{
    // Initialize Vulkan (Runtime) Loader
    VulkanDynamicLoader loader = VK_NULL_HANDLE;
    if (VulkanDynamicCreateLoader(&loader) != VK_SUCCESS)
    {
        return -1;
    }

    // Create Loader dispatch 
    VulkanDynamicLoaderDispatch loaderDispatch;
    VulkanDynamicGetLoaderDispatch(loader, &loaderDispatch);

    // Create Instance
    uint32_t instanceVersion = VK_API_VERSION_1_0;
    loaderDispatch.EnumerateInstanceVersion&& loaderDispatch.EnumerateInstanceVersion(&instanceVersion);

    VkApplicationInfo applicationInfo;
    memset(&applicationInfo, 0, sizeof(VkApplicationInfo));
    applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    applicationInfo.apiVersion = instanceVersion;

    VkInstanceCreateInfo instanceCreateInfo;
    memset(&instanceCreateInfo, 0u, sizeof(VkInstanceCreateInfo));
    instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instanceCreateInfo.pApplicationInfo = &applicationInfo;

    VkInstance instance = VK_NULL_HANDLE;
    if (loaderDispatch.CreateInstance(&instanceCreateInfo, NULL, &instance) != VK_SUCCESS)
    {
        return -1;
    }

    // Create Instance dispatch 
    VulkanDynamicInstanceDispatch instanceDispatch;
    VulkanDynamicGetInstanceDispatch(instance, &loaderDispatch, &instanceDispatch);

    uint32_t physicalDeviceCount = 0;
    instanceDispatch.EnumeratePhysicalDevices(instance, &physicalDeviceCount, NULL);
    VkPhysicalDevice* physicalDevices = (VkPhysicalDevice*)malloc(sizeof(VkPhysicalDevice) * physicalDeviceCount);
    instanceDispatch.EnumeratePhysicalDevices(instance, &physicalDeviceCount, physicalDevices);

    for (uint32_t index = 0; index != physicalDeviceCount; ++index)
    {
        VkPhysicalDeviceDriverProperties driverProperties;
        driverProperties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DRIVER_PROPERTIES;
        driverProperties.pNext = NULL;

        VkPhysicalDeviceProperties2 physicalDeviceProperties;
        physicalDeviceProperties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2;
        physicalDeviceProperties.pNext = &driverProperties;

        instanceDispatch.GetPhysicalDeviceProperties2(physicalDevices[index], &physicalDeviceProperties);

        PrintProperties(&physicalDeviceProperties.properties);
        PrintDriverProperties(&driverProperties);
    }

    instanceDispatch.DestroyInstance(instance, NULL);

    // Shutdown Vulkan Loader
    VulkanDynamicDestroyLoader(loader);

    return 0;
}
