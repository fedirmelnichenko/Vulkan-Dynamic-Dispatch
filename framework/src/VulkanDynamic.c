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
#include <Platform/SharedLibrary.h>

#define VULKANDYNAMIC_GET_SYMBOL(loader, dispatch, entryPoint, function) dispatch->function = (PFN_vk##function)dispatch->entryPoint(loader, "vk"#function)
#define VULKANDYNAMIC_GET_LOADER_SYMBOL(dispatch, function) VULKANDYNAMIC_GET_SYMBOL(VK_NULL_HANDLE, dispatch, GetInstanceProcAddr, function)
#define VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, dispatch, function) VULKANDYNAMIC_GET_SYMBOL(instance, dispatch, GetInstanceProcAddr, function)
#define VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, dispatch, function) VULKANDYNAMIC_GET_SYMBOL(device, dispatch, GetDeviceProcAddr, function)

//------------------------------------------------------------------------------------
// Loader
//------------------------------------------------------------------------------------

VKAPI_ATTR VkResult VKAPI_CALL VulkanDynamicCreateLoader(VulkanDynamicLoader* loader)
{
    if (!loader)
    {
        return VK_ERROR_OUT_OF_HOST_MEMORY;
    }

#if defined(_WIN32)
    const char* vulkanLibraryName = "vulkan-1.dll";
#elif __APPLE__
    const char* vulkanLibraryName = "libMoltenVK.dylib";
#elif __UNIX__
    const char* vulkanLibraryName = "libvulkan.so;libvulkan.so.1";
#else
    #error "Target platform undefined"
#endif

    VulkanDynamicLoader vulkanLoader = (VulkanDynamicLoader)SharedLibraryLoad(vulkanLibraryName);
    if (!vulkanLoader)
    {
        return VK_ERROR_INCOMPATIBLE_DRIVER;
    }

    *loader = vulkanLoader;

    return VK_SUCCESS;
}

VKAPI_ATTR void VKAPI_CALL VulkanDynamicDestroyLoader(VulkanDynamicLoader loader)
{
    SharedLibraryFree((SharedLibrary)loader);
}

VKAPI_ATTR VkResult VKAPI_CALL VulkanDynamicGetLoaderDispatch(const VulkanDynamicLoader loader, VulkanDynamicLoaderDispatch* loaderDispatch)
{
    if (!loader || !loaderDispatch)
    {
        return VK_ERROR_OUT_OF_HOST_MEMORY;
    }

    loaderDispatch->GetInstanceProcAddr = SharedLibraryGetSymbol((SharedLibrary)loader, "vkGetInstanceProcAddr");
    if (!loaderDispatch->GetInstanceProcAddr)
    {
        return VK_ERROR_INCOMPATIBLE_DRIVER;
    }

    // Vulkan Core 1.0
    VULKANDYNAMIC_GET_LOADER_SYMBOL(loaderDispatch, CreateInstance);
    VULKANDYNAMIC_GET_LOADER_SYMBOL(loaderDispatch, EnumerateInstanceExtensionProperties);
    VULKANDYNAMIC_GET_LOADER_SYMBOL(loaderDispatch, EnumerateInstanceLayerProperties);

    // Vulkan Core 1.1
    VULKANDYNAMIC_GET_LOADER_SYMBOL(loaderDispatch, EnumerateInstanceVersion);

    return VK_SUCCESS;
}

//------------------------------------------------------------------------------------
// Instance
//------------------------------------------------------------------------------------

VKAPI_ATTR VkResult VKAPI_CALL VulkanDynamicGetInstanceDispatch(VkInstance instance, const VulkanDynamicLoaderDispatch* loaderDispatch, VulkanDynamicInstanceDispatch* instanceDispatch)
{
    if (!instance || !loaderDispatch || !instanceDispatch)
    {
        return VK_ERROR_OUT_OF_HOST_MEMORY;
    }

    instanceDispatch->GetInstanceProcAddr = loaderDispatch->GetInstanceProcAddr;
    if (!instanceDispatch->GetInstanceProcAddr)
    {
        return VK_ERROR_INCOMPATIBLE_DRIVER;
    }

    // Vulkan Core 1.0
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, GetInstanceProcAddr);
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, GetDeviceProcAddr);
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, DestroyInstance);
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, EnumeratePhysicalDevices);
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, GetPhysicalDeviceFeatures);
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, GetPhysicalDeviceFormatProperties);
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, GetPhysicalDeviceImageFormatProperties);
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, GetPhysicalDeviceProperties);
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, GetPhysicalDeviceQueueFamilyProperties);
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, GetPhysicalDeviceMemoryProperties);
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, CreateDevice);
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, EnumerateDeviceExtensionProperties);
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, EnumerateDeviceLayerProperties);
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, GetPhysicalDeviceSparseImageFormatProperties);

    // Vulkan Core 1.1
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, EnumeratePhysicalDeviceGroups);
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, GetPhysicalDeviceFeatures2);
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, GetPhysicalDeviceProperties2);
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, GetPhysicalDeviceFormatProperties2);
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, GetPhysicalDeviceImageFormatProperties2);
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, GetPhysicalDeviceQueueFamilyProperties2);
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, GetPhysicalDeviceMemoryProperties2);
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, GetPhysicalDeviceSparseImageFormatProperties2);
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, GetPhysicalDeviceExternalBufferProperties);
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, GetPhysicalDeviceExternalFenceProperties);
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, GetPhysicalDeviceExternalSemaphoreProperties);

#if defined(VK_KHR_surface)
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, DestroySurfaceKHR);
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, GetPhysicalDeviceSurfaceSupportKHR);
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, GetPhysicalDeviceSurfaceCapabilitiesKHR);
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, GetPhysicalDeviceSurfaceFormatsKHR);
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, GetPhysicalDeviceSurfacePresentModesKHR);
#endif // VK_KHR_surface

#if defined(VK_KHR_display)
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, GetPhysicalDeviceDisplayPropertiesKHR);
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, GetPhysicalDeviceDisplayPlanePropertiesKHR);
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, GetDisplayPlaneSupportedDisplaysKHR);
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, GetDisplayModePropertiesKHR);
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, CreateDisplayModeKHR);
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, GetDisplayPlaneCapabilitiesKHR);
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, CreateDisplayPlaneSurfaceKHR);
#endif // VK_KHR_display

#if defined(VK_KHR_xlib_surface)
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, CreateXlibSurfaceKHR);
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, GetPhysicalDeviceXlibPresentationSupportKHR);
#endif // VK_KHR_xlib_surface

#if defined(VK_KHR_xcb_surface)
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, CreateXcbSurfaceKHR);
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, GetPhysicalDeviceXcbPresentationSupportKHR);
#endif // VK_KHR_xcb_surface

#if defined(VK_KHR_wayland_surface)
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, CreateWaylandSurfaceKHR);
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, GetPhysicalDeviceWaylandPresentationSupportKHR);
#endif // VK_KHR_wayland_surface

#if defined(VK_KHR_android_surface)
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, CreateAndroidSurfaceKHR);
#endif // VK_KHR_android_surface

#if defined(VK_KHR_win32_surface)
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, CreateWin32SurfaceKHR);
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, GetPhysicalDeviceWin32PresentationSupportKHR);
#endif // VK_KHR_win32_surface

#if defined(VK_EXT_debug_report)
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, CreateDebugReportCallbackEXT);
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, DestroyDebugReportCallbackEXT);
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, DebugReportMessageEXT);
#endif // VK_EXT_debug_report

#if defined(VK_GGP_stream_descriptor_surface)
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, CreateStreamDescriptorSurfaceGGP);
#endif // VK_GGP_stream_descriptor_surface

#if defined(VK_NV_external_memory_capabilities)
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, GetPhysicalDeviceExternalImageFormatPropertiesNV);
#endif // VK_NV_external_memory_capabilities

#if defined(VK_KHR_get_physical_device_properties2)
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, GetPhysicalDeviceFeatures2KHR);
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, GetPhysicalDeviceProperties2KHR);
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, GetPhysicalDeviceFormatProperties2KHR);
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, GetPhysicalDeviceImageFormatProperties2KHR);
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, GetPhysicalDeviceQueueFamilyProperties2KHR);
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, GetPhysicalDeviceMemoryProperties2KHR);
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, GetPhysicalDeviceSparseImageFormatProperties2KHR);
#endif // VK_KHR_get_physical_device_properties2

#if defined(VK_NN_vi_surface)
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, CreateViSurfaceNN);
#endif // VK_NN_vi_surface

#if defined(VK_KHR_device_group_creation)
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, EnumeratePhysicalDeviceGroupsKHR);
#endif // VK_KHR_device_group_creation

#if defined(VK_KHR_external_memory_capabilities)
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, GetPhysicalDeviceExternalBufferPropertiesKHR);
#endif // VK_KHR_external_memory_capabilities

#if defined(VK_KHR_external_semaphore_capabilities)
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, GetPhysicalDeviceExternalSemaphorePropertiesKHR);
#endif // VK_KHR_external_semaphore_capabilities

#if defined(VK_EXT_direct_mode_display)
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, ReleaseDisplayEXT);
#endif // VK_EXT_direct_mode_display

#if defined(VK_EXT_acquire_xlib_display)
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, AcquireXlibDisplayEXT);
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, GetRandROutputDisplayEXT);
#endif // VK_EXT_acquire_xlib_display

#if defined(VK_EXT_display_surface_counter)
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, GetPhysicalDeviceSurfaceCapabilities2EXT);
#endif // VK_EXT_display_surface_counter

#if defined(VK_KHR_external_fence_capabilities)
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, GetPhysicalDeviceExternalFencePropertiesKHR);
#endif // VK_KHR_external_fence_capabilities

#if defined(VK_KHR_get_surface_capabilities2)
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, GetPhysicalDeviceSurfaceCapabilities2KHR);
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, GetPhysicalDeviceSurfaceFormats2KHR);
#endif // VK_KHR_get_surface_capabilities2

#if defined(VK_KHR_get_display_properties2)
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, GetPhysicalDeviceDisplayProperties2KHR);
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, GetPhysicalDeviceDisplayPlaneProperties2KHR);
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, GetDisplayModeProperties2KHR);
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, GetDisplayPlaneCapabilities2KHR);
#endif // VK_KHR_get_display_properties2

#if defined(VK_MVK_ios_surface)
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, CreateIOSSurfaceMVK);
#endif // VK_MVK_ios_surface

#if defined(VK_MVK_macos_surface)
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, CreateMacOSSurfaceMVK);
#endif // VK_MVK_macos_surface

#if defined(VK_EXT_debug_utils)
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, SetDebugUtilsObjectNameEXT);
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, SetDebugUtilsObjectTagEXT);
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, QueueBeginDebugUtilsLabelEXT);
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, QueueEndDebugUtilsLabelEXT);
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, QueueInsertDebugUtilsLabelEXT);
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, CmdBeginDebugUtilsLabelEXT);
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, CmdEndDebugUtilsLabelEXT);
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, CmdInsertDebugUtilsLabelEXT);
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, CreateDebugUtilsMessengerEXT);
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, DestroyDebugUtilsMessengerEXT);
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, SubmitDebugUtilsMessageEXT);
#endif // VK_EXT_debug_utils

#if defined(VK_FUCHSIA_imagepipe_surface)
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, CreateImagePipeSurfaceFUCHSIA);
#endif // VK_FUCHSIA_imagepipe_surface

#if defined(VK_EXT_metal_surface)
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, CreateMetalSurfaceEXT);
#endif // VK_EXT_metal_surface

#if defined(VK_EXT_headless_surface)
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, CreateHeadlessSurfaceEXT);
#endif // VK_EXT_headless_surface

#if defined(VK_EXT_acquire_drm_display)
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, AcquireDrmDisplayEXT);
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, GetDrmDisplayEXT);
#endif // VK_EXT_acquire_drm_display

#if defined(VK_EXT_directfb_surface)
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, CreateDirectFBSurfaceEXT);
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, GetPhysicalDeviceDirectFBPresentationSupportEXT);
#endif // VK_EXT_directfb_surface

#if defined(VK_QNX_screen_surface)
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, CreateScreenSurfaceQNX);
    VULKANDYNAMIC_GET_INSTANCE_SYMBOL(instance, instanceDispatch, GetPhysicalDeviceScreenPresentationSupportQNX);
#endif // VK_QNX_screen_surface

    return VK_SUCCESS;
}

//------------------------------------------------------------------------------------
// Device
//------------------------------------------------------------------------------------

VKAPI_ATTR VkResult VKAPI_CALL VulkanDynamicGetDeviceDispatch(VkDevice device, const VulkanDynamicInstanceDispatch* instanceDispatch, VulkanDynamicDeviceDispatch* deviceDispatch)
{
    if (!device || !instanceDispatch || !deviceDispatch)
    {
        return VK_ERROR_OUT_OF_HOST_MEMORY;
    }

    deviceDispatch->GetDeviceProcAddr = instanceDispatch->GetDeviceProcAddr;
    if (!deviceDispatch->GetDeviceProcAddr)
    {
        return VK_ERROR_INCOMPATIBLE_DRIVER;
    }

    // Vulkan Core 1.0
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetDeviceProcAddr);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, DestroyDevice);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetDeviceQueue);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, QueueSubmit);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, QueueWaitIdle);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, DeviceWaitIdle);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, AllocateMemory);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, FreeMemory);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, MapMemory);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, UnmapMemory);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, FlushMappedMemoryRanges);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, InvalidateMappedMemoryRanges);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetDeviceMemoryCommitment);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, BindBufferMemory);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, BindImageMemory);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetBufferMemoryRequirements);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetImageMemoryRequirements);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetImageSparseMemoryRequirements);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, QueueBindSparse);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CreateFence);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, DestroyFence);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, ResetFences);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetFenceStatus);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, WaitForFences);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CreateSemaphore);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, DestroySemaphore);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CreateEvent);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, DestroyEvent);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetEventStatus);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, SetEvent);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, ResetEvent);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CreateQueryPool);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, DestroyQueryPool);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetQueryPoolResults);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CreateBuffer);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, DestroyBuffer);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CreateBufferView);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, DestroyBufferView);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CreateImage);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, DestroyImage);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetImageSubresourceLayout);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CreateImageView);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, DestroyImageView);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CreateShaderModule);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, DestroyShaderModule);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CreatePipelineCache);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, DestroyPipelineCache);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetPipelineCacheData);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, MergePipelineCaches);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CreateGraphicsPipelines);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CreateComputePipelines);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, DestroyPipeline);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CreatePipelineLayout);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, DestroyPipelineLayout);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CreateSampler);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, DestroySampler);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CreateDescriptorSetLayout);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, DestroyDescriptorSetLayout);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CreateDescriptorPool);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, DestroyDescriptorPool);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, ResetDescriptorPool);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, AllocateDescriptorSets);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, FreeDescriptorSets);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, UpdateDescriptorSets);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CreateFramebuffer);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, DestroyFramebuffer);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CreateRenderPass);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, DestroyRenderPass);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetRenderAreaGranularity);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CreateCommandPool);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, DestroyCommandPool);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, ResetCommandPool);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, AllocateCommandBuffers);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, FreeCommandBuffers);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, BeginCommandBuffer);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, EndCommandBuffer);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, ResetCommandBuffer);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdBindPipeline);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdSetViewport);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdSetScissor);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdSetLineWidth);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdSetDepthBias);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdSetBlendConstants);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdSetDepthBounds);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdSetStencilCompareMask);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdSetStencilWriteMask);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdSetStencilReference);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdBindDescriptorSets);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdBindIndexBuffer);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdBindVertexBuffers);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdDraw);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdDrawIndexed);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdDrawIndirect);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdDrawIndexedIndirect);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdDispatch);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdDispatchIndirect);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdCopyBuffer);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdCopyImage);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdBlitImage);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdCopyBufferToImage);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdCopyImageToBuffer);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdUpdateBuffer);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdFillBuffer);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdClearColorImage);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdClearDepthStencilImage);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdClearAttachments);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdResolveImage);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdSetEvent);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdResetEvent);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdWaitEvents);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdPipelineBarrier);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdBeginQuery);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdEndQuery);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdResetQueryPool);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdWriteTimestamp);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdCopyQueryPoolResults);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdPushConstants);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdBeginRenderPass);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdNextSubpass);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdEndRenderPass);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdExecuteCommands);

    // Vulkan Core 1.1
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, BindBufferMemory2);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, BindImageMemory2);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetDeviceGroupPeerMemoryFeatures);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdSetDeviceMask);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdDispatchBase);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetImageMemoryRequirements2);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetBufferMemoryRequirements2);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetImageSparseMemoryRequirements2);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, TrimCommandPool);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetDeviceQueue2);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CreateSamplerYcbcrConversion);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, DestroySamplerYcbcrConversion);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CreateDescriptorUpdateTemplate);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, DestroyDescriptorUpdateTemplate);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, UpdateDescriptorSetWithTemplate);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetDescriptorSetLayoutSupport);

    // Vulkan Core 1.2
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdDrawIndirectCount);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdDrawIndexedIndirectCount);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CreateRenderPass2);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdBeginRenderPass2);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdNextSubpass2);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdEndRenderPass2);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, ResetQueryPool);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetSemaphoreCounterValue);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, WaitSemaphores);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, SignalSemaphore);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetBufferDeviceAddress);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetBufferOpaqueCaptureAddress);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetDeviceMemoryOpaqueCaptureAddress);

#if defined(VK_KHR_swapchain)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CreateSwapchainKHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, DestroySwapchainKHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetSwapchainImagesKHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, AcquireNextImageKHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, QueuePresentKHR);
#endif // VK_KHR_swapchain

#if defined(VK_KHR_display_swapchain)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CreateSharedSwapchainsKHR);
#endif // VK_KHR_display_swapchain

#if defined(VK_EXT_debug_marker)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, DebugMarkerSetObjectTagEXT);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, DebugMarkerSetObjectNameEXT);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdDebugMarkerBeginEXT);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdDebugMarkerEndEXT);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdDebugMarkerInsertEXT);
#endif // VK_EXT_debug_marker

#if defined(VK_KHR_video_queue)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetPhysicalDeviceVideoCapabilitiesKHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetPhysicalDeviceVideoFormatPropertiesKHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CreateVideoSessionKHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, DestroyVideoSessionKHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetVideoSessionMemoryRequirementsKHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, BindVideoSessionMemoryKHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CreateVideoSessionParametersKHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, UpdateVideoSessionParametersKHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, DestroyVideoSessionParametersKHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdBeginVideoCodingKHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdEndVideoCodingKHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdControlVideoCodingKHR);
#endif // VK_KHR_video_queue

#if defined(VK_KHR_video_decode_queue)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdDecodeVideoKHR);
#endif // VK_KHR_video_decode_queue

#if defined(VK_EXT_transform_feedback)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdBindTransformFeedbackBuffersEXT);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdBeginTransformFeedbackEXT);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdEndTransformFeedbackEXT);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdBeginQueryIndexedEXT);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdEndQueryIndexedEXT);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdDrawIndirectByteCountEXT);
#endif // VK_EXT_transform_feedback

#if defined(VK_NVX_binary_import)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CreateCuModuleNVX);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CreateCuFunctionNVX);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, DestroyCuModuleNVX);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, DestroyCuFunctionNVX);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdCuLaunchKernelNVX);
#endif // VK_NVX_binary_import

#if defined(VK_NVX_image_view_handle)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetImageViewHandleNVX);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetImageViewAddressNVX);
#endif // VK_NVX_image_view_handle

#if defined(VK_AMD_draw_indirect_count)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdDrawIndirectCountAMD);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdDrawIndexedIndirectCountAMD);
#endif // VK_AMD_draw_indirect_count

#if defined(VK_AMD_shader_info)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetShaderInfoAMD);
#endif // VK_AMD_shader_info

#if defined(VK_NV_external_memory_win32)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetMemoryWin32HandleNV);
#endif // VK_NV_external_memory_win32

#if defined(VK_KHR_device_group)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetDeviceGroupPeerMemoryFeaturesKHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdSetDeviceMaskKHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdDispatchBaseKHR);
#endif // VK_KHR_device_group

#if defined(VK_KHR_maintenance1)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, TrimCommandPoolKHR);
#endif // VK_KHR_maintenance1

#if defined(VK_KHR_external_memory_win32)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetMemoryWin32HandleKHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetMemoryWin32HandlePropertiesKHR);
#endif // VK_KHR_external_memory_win32

#if defined(VK_KHR_external_memory_fd)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetMemoryFdKHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetMemoryFdPropertiesKHR);
#endif // VK_KHR_external_memory_fd

#if defined(VK_KHR_external_semaphore_win32)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, ImportSemaphoreWin32HandleKHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetSemaphoreWin32HandleKHR);
#endif // VK_KHR_external_semaphore_win32

#if defined(VK_KHR_external_semaphore_fd)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, ImportSemaphoreFdKHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetSemaphoreFdKHR);
#endif // VK_KHR_external_semaphore_fd

#if defined(VK_KHR_push_descriptor)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdPushDescriptorSetKHR);
#endif // VK_KHR_push_descriptor

#if defined(VK_EXT_conditional_rendering)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdBeginConditionalRenderingEXT);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdEndConditionalRenderingEXT);
#endif // VK_EXT_conditional_rendering

#if defined(VK_KHR_descriptor_update_template)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CreateDescriptorUpdateTemplateKHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, DestroyDescriptorUpdateTemplateKHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, UpdateDescriptorSetWithTemplateKHR);
#endif // VK_KHR_descriptor_update_template

#if defined(VK_NV_clip_space_w_scaling)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdSetViewportWScalingNV);
#endif // VK_NV_clip_space_w_scaling

#if defined(VK_EXT_display_control)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, DisplayPowerControlEXT);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, RegisterDeviceEventEXT);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, RegisterDisplayEventEXT);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetSwapchainCounterEXT);
#endif // VK_EXT_display_control

#if defined(VK_GOOGLE_display_timing)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetRefreshCycleDurationGOOGLE);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetPastPresentationTimingGOOGLE);
#endif // VK_GOOGLE_display_timing

#if defined(VK_EXT_discard_rectangles)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdSetDiscardRectangleEXT);
#endif // VK_EXT_discard_rectangles

#if defined(VK_EXT_hdr_metadata)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, SetHdrMetadataEXT);
#endif // VK_EXT_hdr_metadata

#if defined(VK_KHR_create_renderpass2)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CreateRenderPass2KHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdBeginRenderPass2KHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdNextSubpass2KHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdEndRenderPass2KHR);
#endif // VK_KHR_create_renderpass2

#if defined(VK_KHR_shared_presentable_image)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetSwapchainStatusKHR);
#endif // VK_KHR_shared_presentable_image

#if defined(VK_KHR_external_fence_win32)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, ImportFenceWin32HandleKHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetFenceWin32HandleKHR);
#endif // VK_KHR_external_fence_win32

#if defined(VK_KHR_external_fence_fd)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, ImportFenceFdKHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetFenceFdKHR);
#endif // VK_KHR_external_fence_fd

#if defined(VK_KHR_performance_query)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, EnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, AcquireProfilingLockKHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, ReleaseProfilingLockKHR);
#endif // VK_KHR_performance_query

#if defined(VK_ANDROID_external_memory_android_hardware_buffer)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetAndroidHardwareBufferPropertiesANDROID);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetMemoryAndroidHardwareBufferANDROID);
#endif // VK_ANDROID_external_memory_android_hardware_buffer

#if defined(VK_EXT_sample_locations)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdSetSampleLocationsEXT);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetPhysicalDeviceMultisamplePropertiesEXT);
#endif // VK_EXT_sample_locations

#if defined(VK_KHR_get_memory_requirements2)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetImageMemoryRequirements2KHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetBufferMemoryRequirements2KHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetImageSparseMemoryRequirements2KHR);
#endif // VK_KHR_get_memory_requirements2

#if defined(VK_KHR_acceleration_structure)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CreateAccelerationStructureKHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, DestroyAccelerationStructureKHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdBuildAccelerationStructuresKHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdBuildAccelerationStructuresIndirectKHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, BuildAccelerationStructuresKHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CopyAccelerationStructureKHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CopyAccelerationStructureToMemoryKHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CopyMemoryToAccelerationStructureKHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, WriteAccelerationStructuresPropertiesKHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdCopyAccelerationStructureKHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdCopyAccelerationStructureToMemoryKHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdCopyMemoryToAccelerationStructureKHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetAccelerationStructureDeviceAddressKHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdWriteAccelerationStructuresPropertiesKHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetDeviceAccelerationStructureCompatibilityKHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetAccelerationStructureBuildSizesKHR);
#endif // VK_KHR_acceleration_structure

#if defined(VK_KHR_ray_tracing_pipeline)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdTraceRaysKHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CreateRayTracingPipelinesKHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetRayTracingShaderGroupHandlesKHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetRayTracingCaptureReplayShaderGroupHandlesKHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdTraceRaysIndirectKHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetRayTracingShaderGroupStackSizeKHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdSetRayTracingPipelineStackSizeKHR);
#endif // VK_KHR_ray_tracing_pipeline

#if defined(VK_KHR_sampler_ycbcr_conversion)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CreateSamplerYcbcrConversionKHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, DestroySamplerYcbcrConversionKHR);
#endif // VK_KHR_sampler_ycbcr_conversion

#if defined(VK_KHR_bind_memory2)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, BindBufferMemory2KHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, BindImageMemory2KHR);
#endif // VK_KHR_bind_memory2

#if defined(VK_EXT_image_drm_format_modifier)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetImageDrmFormatModifierPropertiesEXT);
#endif // VK_EXT_image_drm_format_modifier

#if defined(VK_EXT_validation_cache)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CreateValidationCacheEXT);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, DestroyValidationCacheEXT);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, MergeValidationCachesEXT);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetValidationCacheDataEXT);
#endif // VK_EXT_validation_cache

#if defined(VK_NV_shading_rate_image)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdBindShadingRateImageNV);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdSetViewportShadingRatePaletteNV);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdSetCoarseSampleOrderNV);
#endif // VK_NV_shading_rate_image

#if defined(VK_NV_ray_tracing)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CreateAccelerationStructureNV);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, DestroyAccelerationStructureNV);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetAccelerationStructureMemoryRequirementsNV);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, BindAccelerationStructureMemoryNV);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdBuildAccelerationStructureNV);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdCopyAccelerationStructureNV);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdTraceRaysNV);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CreateRayTracingPipelinesNV);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetRayTracingShaderGroupHandlesNV);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetAccelerationStructureHandleNV);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdWriteAccelerationStructuresPropertiesNV);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CompileDeferredNV);
#endif // VK_NV_ray_tracing

#if defined(VK_KHR_maintenance3)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetDescriptorSetLayoutSupportKHR);
#endif // VK_KHR_maintenance3

#if defined(VK_KHR_draw_indirect_count)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdDrawIndirectCountKHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdDrawIndexedIndirectCountKHR);
#endif // VK_KHR_draw_indirect_count

#if defined(VK_EXT_external_memory_host)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetMemoryHostPointerPropertiesEXT);
#endif // VK_EXT_external_memory_host

#if defined(VK_AMD_buffer_marker)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdWriteBufferMarkerAMD);
#endif // VK_AMD_buffer_marker

#if defined(VK_EXT_calibrated_timestamps)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetPhysicalDeviceCalibrateableTimeDomainsEXT);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetCalibratedTimestampsEXT);
#endif // VK_EXT_calibrated_timestamps

#if defined(VK_NV_mesh_shader)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdDrawMeshTasksNV);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdDrawMeshTasksIndirectNV);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdDrawMeshTasksIndirectCountNV);
#endif // VK_NV_mesh_shader

#if defined(VK_NV_scissor_exclusive)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdSetExclusiveScissorNV);
#endif // VK_NV_scissor_exclusive

#if defined(VK_NV_device_diagnostic_checkpoints)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdSetCheckpointNV);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetQueueCheckpointDataNV);
#endif // VK_NV_device_diagnostic_checkpoints

#if defined(VK_KHR_timeline_semaphore)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetSemaphoreCounterValueKHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, WaitSemaphoresKHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, SignalSemaphoreKHR);
#endif // VK_KHR_timeline_semaphore

#if defined(VK_INTEL_performance_query)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, InitializePerformanceApiINTEL);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, UninitializePerformanceApiINTEL);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdSetPerformanceMarkerINTEL);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdSetPerformanceStreamMarkerINTEL);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdSetPerformanceOverrideINTEL);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, AcquirePerformanceConfigurationINTEL);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, ReleasePerformanceConfigurationINTEL);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, QueueSetPerformanceConfigurationINTEL);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetPerformanceParameterINTEL);
#endif // VK_INTEL_performance_query

#if defined(VK_AMD_display_native_hdr)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, SetLocalDimmingAMD);
#endif // VK_AMD_display_native_hdr

#if defined(VK_KHR_fragment_shading_rate)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetPhysicalDeviceFragmentShadingRatesKHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdSetFragmentShadingRateKHR);
#endif // VK_KHR_fragment_shading_rate

#if defined(VK_EXT_buffer_device_address)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetBufferDeviceAddressEXT);
#endif // VK_EXT_buffer_device_address

#if defined(VK_EXT_tooling_info)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetPhysicalDeviceToolPropertiesEXT);
#endif // VK_EXT_tooling_info

#if defined(VK_KHR_present_wait)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, WaitForPresentKHR);
#endif // VK_KHR_present_wait

#if defined(VK_NV_cooperative_matrix)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetPhysicalDeviceCooperativeMatrixPropertiesNV);
#endif // VK_NV_cooperative_matrix

#if defined(VK_NV_coverage_reduction_mode)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV);
#endif // VK_NV_coverage_reduction_mode

#if defined(VK_EXT_full_screen_exclusive)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetPhysicalDeviceSurfacePresentModes2EXT);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, AcquireFullScreenExclusiveModeEXT);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, ReleaseFullScreenExclusiveModeEXT);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetDeviceGroupSurfacePresentModes2EXT);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetDeviceGroupSurfacePresentModes2EXT);
#endif // VK_EXT_full_screen_exclusive

#if defined(VK_KHR_buffer_device_address)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetBufferDeviceAddressKHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetBufferOpaqueCaptureAddressKHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetDeviceMemoryOpaqueCaptureAddressKHR);
#endif // VK_KHR_buffer_device_address

#if defined(VK_EXT_line_rasterization)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdSetLineStippleEXT);
#endif // VK_EXT_line_rasterization

#if defined(VK_EXT_host_query_reset)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, ResetQueryPoolEXT);
#endif // VK_EXT_host_query_reset

#if defined(VK_EXT_extended_dynamic_state)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdSetCullModeEXT);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdSetFrontFaceEXT);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdSetPrimitiveTopologyEXT);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdSetViewportWithCountEXT);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdSetScissorWithCountEXT);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdBindVertexBuffers2EXT);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdSetDepthTestEnableEXT);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdSetDepthWriteEnableEXT);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdSetDepthCompareOpEXT);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdSetDepthBoundsTestEnableEXT);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdSetStencilTestEnableEXT);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdSetStencilOpEXT);
#endif // VK_EXT_extended_dynamic_state

#if defined(VK_KHR_deferred_host_operations)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CreateDeferredOperationKHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, DestroyDeferredOperationKHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetDeferredOperationMaxConcurrencyKHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetDeferredOperationResultKHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, DeferredOperationJoinKHR);
#endif // VK_KHR_deferred_host_operations

#if defined(VK_KHR_pipeline_executable_properties)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetPipelineExecutablePropertiesKHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetPipelineExecutableStatisticsKHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetPipelineExecutableInternalRepresentationsKHR);
#endif // VK_KHR_pipeline_executable_properties

#if defined(VK_NV_device_generated_commands)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetGeneratedCommandsMemoryRequirementsNV);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdPreprocessGeneratedCommandsNV);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdExecuteGeneratedCommandsNV);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdBindPipelineShaderGroupNV);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CreateIndirectCommandsLayoutNV);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, DestroyIndirectCommandsLayoutNV);
#endif // VK_NV_device_generated_commands

#if defined(VK_EXT_private_data)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CreatePrivateDataSlotEXT);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, DestroyPrivateDataSlotEXT);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, SetPrivateDataEXT);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetPrivateDataEXT);
#endif // VK_EXT_private_data

#if defined(VK_KHR_video_encode_queue)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdEncodeVideoKHR);
#endif // VK_KHR_video_encode_queue

#if defined(VK_KHR_synchronization2)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdSetEvent2KHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdResetEvent2KHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdWaitEvents2KHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdPipelineBarrier2KHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdWriteTimestamp2KHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, QueueSubmit2KHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdWriteBufferMarker2AMD);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetQueueCheckpointData2NV);
#endif // VK_KHR_synchronization2

#if defined(VK_NV_fragment_shading_rate_enums)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdSetFragmentShadingRateEnumNV);
#endif // VK_NV_fragment_shading_rate_enums

#if defined(VK_KHR_copy_commands2)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdCopyBuffer2KHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdCopyImage2KHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdCopyBufferToImage2KHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdCopyImageToBuffer2KHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdBlitImage2KHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdResolveImage2KHR);
#endif // VK_KHR_copy_commands2

#if defined(VK_NV_acquire_winrt_display)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, AcquireWinrtDisplayNV);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetWinrtDisplayNV);
#endif // VK_NV_acquire_winrt_display

#if defined(VK_EXT_vertex_input_dynamic_state)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdSetVertexInputEXT);
#endif // VK_EXT_vertex_input_dynamic_state

#if defined(VK_FUCHSIA_external_memory)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetMemoryZirconHandleFUCHSIA);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetMemoryZirconHandlePropertiesFUCHSIA);
#endif // VK_FUCHSIA_external_memory

#if defined(VK_FUCHSIA_external_semaphore)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, ImportSemaphoreZirconHandleFUCHSIA);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetSemaphoreZirconHandleFUCHSIA);
#endif // VK_FUCHSIA_external_semaphore

#if defined(VK_HUAWEI_subpass_shading)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdSubpassShadingHUAWEI);
#endif // VK_HUAWEI_subpass_shading

#if defined(VK_HUAWEI_invocation_mask)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdBindInvocationMaskHUAWEI);
#endif // VK_HUAWEI_invocation_mask

#if defined(VK_NV_external_memory_rdma)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetMemoryRemoteAddressNV);
#endif // VK_NV_external_memory_rdma

#if defined(VK_EXT_extended_dynamic_state2)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdSetPatchControlPointsEXT);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdSetRasterizerDiscardEnableEXT);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdSetDepthBiasEnableEXT);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdSetLogicOpEXT);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdSetPrimitiveRestartEnableEXT);
#endif // VK_EXT_extended_dynamic_state2

#if defined(VK_EXT_color_write_enable)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdSetColorWriteEnableEXT);
#endif // VK_EXT_color_write_enable

#if defined(VK_EXT_multi_draw)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdDrawMultiEXT);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdDrawMultiIndexedEXT);
#endif // VK_EXT_multi_draw

#if defined(VK_EXT_pageable_device_local_memory)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, SetDeviceMemoryPriorityEXT);
#endif // VK_EXT_pageable_device_local_memory

#if defined(VK_KHR_device_group) || defined(VK_KHR_swapchain)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetDeviceGroupPresentCapabilitiesKHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetDeviceGroupSurfacePresentModesKHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, GetPhysicalDevicePresentRectanglesKHR);
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, AcquireNextImage2KHR);
#endif // VK_KHR_device_group || VK_KHR_swapchain

#if defined(VK_KHR_push_descriptor) || defined(VK_KHR_descriptor_update_template)
    VULKANDYNAMIC_GET_DEVICE_SYMBOL(device, deviceDispatch, CmdPushDescriptorSetWithTemplateKHR);
#endif // VK_KHR_push_descriptor || VK_KHR_descriptor_update_template

    return VK_SUCCESS;
}
