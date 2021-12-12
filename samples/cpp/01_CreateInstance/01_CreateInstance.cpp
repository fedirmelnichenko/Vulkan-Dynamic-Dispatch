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

int main()
{
    ::VkResult result{ ::VK_SUCCESS };

    // Initialize Vulkan (Runtime) Loader
    ::VulkanDynamic::Loader loader = ::VulkanDynamic::CreateLoader(result);
    if (!loader)
    {
        return -1;
    }

    // Create Loader dispatch 
    const ::VulkanDynamic::LoaderDispatch loaderDispatch{ loader, result };

    // Create Instance
    uint32_t instanceVersion = VK_API_VERSION_1_0;
    loaderDispatch.EnumerateInstanceVersion && loaderDispatch.EnumerateInstanceVersion(&instanceVersion);

    ::VkApplicationInfo applicationInfo{ ::VK_STRUCTURE_TYPE_APPLICATION_INFO };
    applicationInfo.apiVersion = instanceVersion;

    ::VkInstanceCreateInfo instanceCreateInfo{ ::VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO };
    instanceCreateInfo.pApplicationInfo = &applicationInfo;

    ::VkInstance instance = nullptr;
    if (loaderDispatch.CreateInstance(&instanceCreateInfo, nullptr, &instance) != VK_SUCCESS)
    {
        return -1;
    }

    // Create Instance dispatch 
    const ::VulkanDynamic::InstanceDispatch instanceDispatch{ instance, loaderDispatch, result };

    // Destroy Instance
    instanceDispatch.DestroyInstance(instance, nullptr);

    return 0;
}
