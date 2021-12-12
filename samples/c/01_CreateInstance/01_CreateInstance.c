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

#include <string.h>

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
    if (VulkanDynamicGetLoaderDispatch(loader, &loaderDispatch) != VK_SUCCESS)
    {
        return -1;
    }

    // Create Instance
    uint32_t instanceVersion = VK_API_VERSION_1_0;
    loaderDispatch.EnumerateInstanceVersion && loaderDispatch.EnumerateInstanceVersion(&instanceVersion);

    VkApplicationInfo applicationInfo;
    memset(&applicationInfo, 0u, sizeof(VkApplicationInfo));
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
    if (VulkanDynamicGetInstanceDispatch(instance, &loaderDispatch, &instanceDispatch) != VK_SUCCESS)
    {
        return -1;
    }

    // Destroy Instance
    instanceDispatch.DestroyInstance(instance, NULL);

    // Shutdown Vulkan Loader
    VulkanDynamicDestroyLoader(loader);

    return 0;
}
