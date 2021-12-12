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

#ifndef __VULKANDYNAMIC_H__
#define __VULKANDYNAMIC_H__

#ifndef VK_NO_PROTOTYPES
    #define VK_NO_PROTOTYPES 
#endif // VK_NO_PROTOTYPES

#include <vulkan/vulkan.h>

#if defined(WIN32)
    #undef CreateSemaphore
    #undef CreateEvent
#endif // WIN32

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

#define VULKANDYNAMIC_DECLARE_FUNCTION(function) PFN_vk##function function

//---------------------------------------------------------------------------------------
// Loader
//---------------------------------------------------------------------------------------

VK_DEFINE_HANDLE(VulkanDynamicLoader);

VKAPI_ATTR VkResult VKAPI_CALL VulkanDynamicCreateLoader(VulkanDynamicLoader* loader);
VKAPI_ATTR void VKAPI_CALL VulkanDynamicDestroyLoader(VulkanDynamicLoader loader);

typedef struct VulkanDynamicLoaderDispatch
{
    // Vulkan Core 1.0
    VULKANDYNAMIC_DECLARE_FUNCTION(GetInstanceProcAddr);
    VULKANDYNAMIC_DECLARE_FUNCTION(CreateInstance);
    VULKANDYNAMIC_DECLARE_FUNCTION(EnumerateInstanceExtensionProperties);
    VULKANDYNAMIC_DECLARE_FUNCTION(EnumerateInstanceLayerProperties);

    // Vulkan Core 1.1
    VULKANDYNAMIC_DECLARE_FUNCTION(EnumerateInstanceVersion);

} VulkanDynamicLoaderDispatch;

VKAPI_ATTR VkResult VKAPI_CALL VulkanDynamicGetLoaderDispatch(const VulkanDynamicLoader loader, VulkanDynamicLoaderDispatch* loaderDispatch);

//---------------------------------------------------------------------------------------
// Instance
//---------------------------------------------------------------------------------------

typedef struct VulkanDynamicInstanceDispatch
{
    // Vulkan Core 1.0
    VULKANDYNAMIC_DECLARE_FUNCTION(GetInstanceProcAddr);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetDeviceProcAddr);
    VULKANDYNAMIC_DECLARE_FUNCTION(DestroyInstance);
    VULKANDYNAMIC_DECLARE_FUNCTION(EnumeratePhysicalDevices);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetPhysicalDeviceFeatures);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetPhysicalDeviceFormatProperties);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetPhysicalDeviceImageFormatProperties);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetPhysicalDeviceProperties);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetPhysicalDeviceQueueFamilyProperties);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetPhysicalDeviceMemoryProperties);
    VULKANDYNAMIC_DECLARE_FUNCTION(CreateDevice);
    VULKANDYNAMIC_DECLARE_FUNCTION(EnumerateDeviceExtensionProperties);
    VULKANDYNAMIC_DECLARE_FUNCTION(EnumerateDeviceLayerProperties);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetPhysicalDeviceSparseImageFormatProperties);

    // Vulkan Core 1.1
    VULKANDYNAMIC_DECLARE_FUNCTION(EnumeratePhysicalDeviceGroups);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetPhysicalDeviceFeatures2);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetPhysicalDeviceProperties2);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetPhysicalDeviceFormatProperties2);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetPhysicalDeviceImageFormatProperties2);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetPhysicalDeviceQueueFamilyProperties2);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetPhysicalDeviceMemoryProperties2);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetPhysicalDeviceSparseImageFormatProperties2);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetPhysicalDeviceExternalBufferProperties);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetPhysicalDeviceExternalFenceProperties);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetPhysicalDeviceExternalSemaphoreProperties);

#if defined(VK_KHR_surface)
    VULKANDYNAMIC_DECLARE_FUNCTION(DestroySurfaceKHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetPhysicalDeviceSurfaceSupportKHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetPhysicalDeviceSurfaceCapabilitiesKHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetPhysicalDeviceSurfaceFormatsKHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetPhysicalDeviceSurfacePresentModesKHR);
#endif // VK_KHR_surface

#if defined(VK_KHR_display)
    VULKANDYNAMIC_DECLARE_FUNCTION(GetPhysicalDeviceDisplayPropertiesKHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetPhysicalDeviceDisplayPlanePropertiesKHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetDisplayPlaneSupportedDisplaysKHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetDisplayModePropertiesKHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(CreateDisplayModeKHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetDisplayPlaneCapabilitiesKHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(CreateDisplayPlaneSurfaceKHR);
#endif // VK_KHR_display

#if defined(VK_KHR_xlib_surface)
    VULKANDYNAMIC_DECLARE_FUNCTION(CreateXlibSurfaceKHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetPhysicalDeviceXlibPresentationSupportKHR);
#endif // VK_KHR_xlib_surface

#if defined(VK_KHR_xcb_surface)
    VULKANDYNAMIC_DECLARE_FUNCTION(CreateXcbSurfaceKHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetPhysicalDeviceXcbPresentationSupportKHR);
#endif // VK_KHR_xcb_surface

#if defined(VK_KHR_wayland_surface)
    VULKANDYNAMIC_DECLARE_FUNCTION(CreateWaylandSurfaceKHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetPhysicalDeviceWaylandPresentationSupportKHR);
#endif // VK_KHR_wayland_surface

#if defined(VK_KHR_android_surface)
    VULKANDYNAMIC_DECLARE_FUNCTION(CreateAndroidSurfaceKHR);
#endif // VK_KHR_android_surface

#if defined(VK_KHR_win32_surface)
    VULKANDYNAMIC_DECLARE_FUNCTION(CreateWin32SurfaceKHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetPhysicalDeviceWin32PresentationSupportKHR);
#endif // VK_KHR_win32_surface

#if defined(VK_EXT_debug_report)
    VULKANDYNAMIC_DECLARE_FUNCTION(CreateDebugReportCallbackEXT);
    VULKANDYNAMIC_DECLARE_FUNCTION(DestroyDebugReportCallbackEXT);
    VULKANDYNAMIC_DECLARE_FUNCTION(DebugReportMessageEXT);
#endif // VK_EXT_debug_report

#if defined(VK_GGP_stream_descriptor_surface)
    VULKANDYNAMIC_DECLARE_FUNCTION(CreateStreamDescriptorSurfaceGGP);
#endif // VK_GGP_stream_descriptor_surface

#if defined(VK_NV_external_memory_capabilities)
    VULKANDYNAMIC_DECLARE_FUNCTION(GetPhysicalDeviceExternalImageFormatPropertiesNV);
#endif // VK_NV_external_memory_capabilities

#if defined(VK_KHR_get_physical_device_properties2)
    VULKANDYNAMIC_DECLARE_FUNCTION(GetPhysicalDeviceFeatures2KHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetPhysicalDeviceProperties2KHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetPhysicalDeviceFormatProperties2KHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetPhysicalDeviceImageFormatProperties2KHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetPhysicalDeviceQueueFamilyProperties2KHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetPhysicalDeviceMemoryProperties2KHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetPhysicalDeviceSparseImageFormatProperties2KHR);
#endif // VK_KHR_get_physical_device_properties2

#if defined(VK_NN_vi_surface)
    VULKANDYNAMIC_DECLARE_FUNCTION(CreateViSurfaceNN);
#endif // VK_NN_vi_surface

#if defined(VK_KHR_device_group_creation)
    VULKANDYNAMIC_DECLARE_FUNCTION(EnumeratePhysicalDeviceGroupsKHR);
#endif // VK_KHR_device_group_creation

#if defined(VK_KHR_external_memory_capabilities)
    VULKANDYNAMIC_DECLARE_FUNCTION(GetPhysicalDeviceExternalBufferPropertiesKHR);
#endif // VK_KHR_external_memory_capabilities

#if defined(VK_KHR_external_semaphore_capabilities)
    VULKANDYNAMIC_DECLARE_FUNCTION(GetPhysicalDeviceExternalSemaphorePropertiesKHR);
#endif // VK_KHR_external_semaphore_capabilities

#if defined(VK_EXT_direct_mode_display)
    VULKANDYNAMIC_DECLARE_FUNCTION(ReleaseDisplayEXT);
#endif // VK_EXT_direct_mode_display

#if defined(VK_EXT_acquire_xlib_display)
    VULKANDYNAMIC_DECLARE_FUNCTION(AcquireXlibDisplayEXT);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetRandROutputDisplayEXT);
#endif // VK_EXT_acquire_xlib_display

#if defined(VK_EXT_display_surface_counter)
    VULKANDYNAMIC_DECLARE_FUNCTION(GetPhysicalDeviceSurfaceCapabilities2EXT);
#endif // VK_EXT_display_surface_counter

#if defined(VK_KHR_external_fence_capabilities)
    VULKANDYNAMIC_DECLARE_FUNCTION(GetPhysicalDeviceExternalFencePropertiesKHR);
#endif // VK_KHR_external_fence_capabilities

#if defined(VK_KHR_get_surface_capabilities2)
    VULKANDYNAMIC_DECLARE_FUNCTION(GetPhysicalDeviceSurfaceCapabilities2KHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetPhysicalDeviceSurfaceFormats2KHR);
#endif // VK_KHR_get_surface_capabilities2

#if defined(VK_KHR_get_display_properties2)
    VULKANDYNAMIC_DECLARE_FUNCTION(GetPhysicalDeviceDisplayProperties2KHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetPhysicalDeviceDisplayPlaneProperties2KHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetDisplayModeProperties2KHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetDisplayPlaneCapabilities2KHR);
#endif // VK_KHR_get_display_properties2

#if defined(VK_MVK_ios_surface)
    VULKANDYNAMIC_DECLARE_FUNCTION(CreateIOSSurfaceMVK);
#endif // VK_MVK_ios_surface

#if defined(VK_MVK_macos_surface)
    VULKANDYNAMIC_DECLARE_FUNCTION(CreateMacOSSurfaceMVK);
#endif // VK_MVK_macos_surface

#if defined(VK_EXT_debug_utils)
    VULKANDYNAMIC_DECLARE_FUNCTION(SetDebugUtilsObjectNameEXT);
    VULKANDYNAMIC_DECLARE_FUNCTION(SetDebugUtilsObjectTagEXT);
    VULKANDYNAMIC_DECLARE_FUNCTION(QueueBeginDebugUtilsLabelEXT);
    VULKANDYNAMIC_DECLARE_FUNCTION(QueueEndDebugUtilsLabelEXT);
    VULKANDYNAMIC_DECLARE_FUNCTION(QueueInsertDebugUtilsLabelEXT);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdBeginDebugUtilsLabelEXT);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdEndDebugUtilsLabelEXT);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdInsertDebugUtilsLabelEXT);
    VULKANDYNAMIC_DECLARE_FUNCTION(CreateDebugUtilsMessengerEXT);
    VULKANDYNAMIC_DECLARE_FUNCTION(DestroyDebugUtilsMessengerEXT);
    VULKANDYNAMIC_DECLARE_FUNCTION(SubmitDebugUtilsMessageEXT);
#endif // VK_EXT_debug_utils

#if defined(VK_FUCHSIA_imagepipe_surface)
    VULKANDYNAMIC_DECLARE_FUNCTION(CreateImagePipeSurfaceFUCHSIA);
#endif // VK_FUCHSIA_imagepipe_surface

#if defined(VK_EXT_metal_surface)
    VULKANDYNAMIC_DECLARE_FUNCTION(CreateMetalSurfaceEXT);
#endif // VK_EXT_metal_surface

#if defined(VK_EXT_headless_surface)
    VULKANDYNAMIC_DECLARE_FUNCTION(CreateHeadlessSurfaceEXT);
#endif // VK_EXT_headless_surface

#if defined(VK_EXT_acquire_drm_display)
    VULKANDYNAMIC_DECLARE_FUNCTION(AcquireDrmDisplayEXT);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetDrmDisplayEXT);
#endif // VK_EXT_acquire_drm_display

#if defined(VK_EXT_directfb_surface)
    VULKANDYNAMIC_DECLARE_FUNCTION(CreateDirectFBSurfaceEXT);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetPhysicalDeviceDirectFBPresentationSupportEXT);
#endif // VK_EXT_directfb_surface

#if defined(VK_QNX_screen_surface)
    VULKANDYNAMIC_DECLARE_FUNCTION(CreateScreenSurfaceQNX);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetPhysicalDeviceScreenPresentationSupportQNX);
#endif // VK_QNX_screen_surface
} VulkanDynamicInstanceDispatch;

VKAPI_ATTR VkResult VKAPI_CALL VulkanDynamicGetInstanceDispatch(VkInstance instance, const VulkanDynamicLoaderDispatch* loaderDispatch, VulkanDynamicInstanceDispatch* instanceDispatch);

//---------------------------------------------------------------------------------------
// Device
//---------------------------------------------------------------------------------------

typedef struct VulkanDynamicDeviceDispatch
{
    // Vulkan Core 1.0
    VULKANDYNAMIC_DECLARE_FUNCTION(GetDeviceProcAddr);
    VULKANDYNAMIC_DECLARE_FUNCTION(DestroyDevice);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetDeviceQueue);
    VULKANDYNAMIC_DECLARE_FUNCTION(QueueSubmit);
    VULKANDYNAMIC_DECLARE_FUNCTION(QueueWaitIdle);
    VULKANDYNAMIC_DECLARE_FUNCTION(DeviceWaitIdle);
    VULKANDYNAMIC_DECLARE_FUNCTION(AllocateMemory);
    VULKANDYNAMIC_DECLARE_FUNCTION(FreeMemory);
    VULKANDYNAMIC_DECLARE_FUNCTION(MapMemory);
    VULKANDYNAMIC_DECLARE_FUNCTION(UnmapMemory);
    VULKANDYNAMIC_DECLARE_FUNCTION(FlushMappedMemoryRanges);
    VULKANDYNAMIC_DECLARE_FUNCTION(InvalidateMappedMemoryRanges);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetDeviceMemoryCommitment);
    VULKANDYNAMIC_DECLARE_FUNCTION(BindBufferMemory);
    VULKANDYNAMIC_DECLARE_FUNCTION(BindImageMemory);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetBufferMemoryRequirements);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetImageMemoryRequirements);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetImageSparseMemoryRequirements);
    VULKANDYNAMIC_DECLARE_FUNCTION(QueueBindSparse);
    VULKANDYNAMIC_DECLARE_FUNCTION(CreateFence);
    VULKANDYNAMIC_DECLARE_FUNCTION(DestroyFence);
    VULKANDYNAMIC_DECLARE_FUNCTION(ResetFences);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetFenceStatus);
    VULKANDYNAMIC_DECLARE_FUNCTION(WaitForFences);
    VULKANDYNAMIC_DECLARE_FUNCTION(CreateSemaphore);
    VULKANDYNAMIC_DECLARE_FUNCTION(DestroySemaphore);
    VULKANDYNAMIC_DECLARE_FUNCTION(CreateEvent);
    VULKANDYNAMIC_DECLARE_FUNCTION(DestroyEvent);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetEventStatus);
    VULKANDYNAMIC_DECLARE_FUNCTION(SetEvent);
    VULKANDYNAMIC_DECLARE_FUNCTION(ResetEvent);
    VULKANDYNAMIC_DECLARE_FUNCTION(CreateQueryPool);
    VULKANDYNAMIC_DECLARE_FUNCTION(DestroyQueryPool);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetQueryPoolResults);
    VULKANDYNAMIC_DECLARE_FUNCTION(CreateBuffer);
    VULKANDYNAMIC_DECLARE_FUNCTION(DestroyBuffer);
    VULKANDYNAMIC_DECLARE_FUNCTION(CreateBufferView);
    VULKANDYNAMIC_DECLARE_FUNCTION(DestroyBufferView);
    VULKANDYNAMIC_DECLARE_FUNCTION(CreateImage);
    VULKANDYNAMIC_DECLARE_FUNCTION(DestroyImage);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetImageSubresourceLayout);
    VULKANDYNAMIC_DECLARE_FUNCTION(CreateImageView);
    VULKANDYNAMIC_DECLARE_FUNCTION(DestroyImageView);
    VULKANDYNAMIC_DECLARE_FUNCTION(CreateShaderModule);
    VULKANDYNAMIC_DECLARE_FUNCTION(DestroyShaderModule);
    VULKANDYNAMIC_DECLARE_FUNCTION(CreatePipelineCache);
    VULKANDYNAMIC_DECLARE_FUNCTION(DestroyPipelineCache);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetPipelineCacheData);
    VULKANDYNAMIC_DECLARE_FUNCTION(MergePipelineCaches);
    VULKANDYNAMIC_DECLARE_FUNCTION(CreateGraphicsPipelines);
    VULKANDYNAMIC_DECLARE_FUNCTION(CreateComputePipelines);
    VULKANDYNAMIC_DECLARE_FUNCTION(DestroyPipeline);
    VULKANDYNAMIC_DECLARE_FUNCTION(CreatePipelineLayout);
    VULKANDYNAMIC_DECLARE_FUNCTION(DestroyPipelineLayout);
    VULKANDYNAMIC_DECLARE_FUNCTION(CreateSampler);
    VULKANDYNAMIC_DECLARE_FUNCTION(DestroySampler);
    VULKANDYNAMIC_DECLARE_FUNCTION(CreateDescriptorSetLayout);
    VULKANDYNAMIC_DECLARE_FUNCTION(DestroyDescriptorSetLayout);
    VULKANDYNAMIC_DECLARE_FUNCTION(CreateDescriptorPool);
    VULKANDYNAMIC_DECLARE_FUNCTION(DestroyDescriptorPool);
    VULKANDYNAMIC_DECLARE_FUNCTION(ResetDescriptorPool);
    VULKANDYNAMIC_DECLARE_FUNCTION(AllocateDescriptorSets);
    VULKANDYNAMIC_DECLARE_FUNCTION(FreeDescriptorSets);
    VULKANDYNAMIC_DECLARE_FUNCTION(UpdateDescriptorSets);
    VULKANDYNAMIC_DECLARE_FUNCTION(CreateFramebuffer);
    VULKANDYNAMIC_DECLARE_FUNCTION(DestroyFramebuffer);
    VULKANDYNAMIC_DECLARE_FUNCTION(CreateRenderPass);
    VULKANDYNAMIC_DECLARE_FUNCTION(DestroyRenderPass);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetRenderAreaGranularity);
    VULKANDYNAMIC_DECLARE_FUNCTION(CreateCommandPool);
    VULKANDYNAMIC_DECLARE_FUNCTION(DestroyCommandPool);
    VULKANDYNAMIC_DECLARE_FUNCTION(ResetCommandPool);
    VULKANDYNAMIC_DECLARE_FUNCTION(AllocateCommandBuffers);
    VULKANDYNAMIC_DECLARE_FUNCTION(FreeCommandBuffers);
    VULKANDYNAMIC_DECLARE_FUNCTION(BeginCommandBuffer);
    VULKANDYNAMIC_DECLARE_FUNCTION(EndCommandBuffer);
    VULKANDYNAMIC_DECLARE_FUNCTION(ResetCommandBuffer);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdBindPipeline);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdSetViewport);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdSetScissor);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdSetLineWidth);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdSetDepthBias);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdSetBlendConstants);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdSetDepthBounds);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdSetStencilCompareMask);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdSetStencilWriteMask);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdSetStencilReference);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdBindDescriptorSets);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdBindIndexBuffer);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdBindVertexBuffers);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdDraw);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdDrawIndexed);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdDrawIndirect);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdDrawIndexedIndirect);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdDispatch);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdDispatchIndirect);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdCopyBuffer);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdCopyImage);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdBlitImage);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdCopyBufferToImage);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdCopyImageToBuffer);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdUpdateBuffer);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdFillBuffer);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdClearColorImage);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdClearDepthStencilImage);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdClearAttachments);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdResolveImage);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdSetEvent);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdResetEvent);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdWaitEvents);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdPipelineBarrier);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdBeginQuery);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdEndQuery);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdResetQueryPool);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdWriteTimestamp);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdCopyQueryPoolResults);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdPushConstants);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdBeginRenderPass);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdNextSubpass);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdEndRenderPass);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdExecuteCommands);

    // Vulkan Core 1.1
    VULKANDYNAMIC_DECLARE_FUNCTION(BindBufferMemory2);
    VULKANDYNAMIC_DECLARE_FUNCTION(BindImageMemory2);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetDeviceGroupPeerMemoryFeatures);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdSetDeviceMask);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdDispatchBase);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetImageMemoryRequirements2);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetBufferMemoryRequirements2);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetImageSparseMemoryRequirements2);
    VULKANDYNAMIC_DECLARE_FUNCTION(TrimCommandPool);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetDeviceQueue2);
    VULKANDYNAMIC_DECLARE_FUNCTION(CreateSamplerYcbcrConversion);
    VULKANDYNAMIC_DECLARE_FUNCTION(DestroySamplerYcbcrConversion);
    VULKANDYNAMIC_DECLARE_FUNCTION(CreateDescriptorUpdateTemplate);
    VULKANDYNAMIC_DECLARE_FUNCTION(DestroyDescriptorUpdateTemplate);
    VULKANDYNAMIC_DECLARE_FUNCTION(UpdateDescriptorSetWithTemplate);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetDescriptorSetLayoutSupport);

    // Vulkan Core 1.2
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdDrawIndirectCount);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdDrawIndexedIndirectCount);
    VULKANDYNAMIC_DECLARE_FUNCTION(CreateRenderPass2);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdBeginRenderPass2);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdNextSubpass2);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdEndRenderPass2);
    VULKANDYNAMIC_DECLARE_FUNCTION(ResetQueryPool);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetSemaphoreCounterValue);
    VULKANDYNAMIC_DECLARE_FUNCTION(WaitSemaphores);
    VULKANDYNAMIC_DECLARE_FUNCTION(SignalSemaphore);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetBufferDeviceAddress);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetBufferOpaqueCaptureAddress);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetDeviceMemoryOpaqueCaptureAddress);

#if defined(VK_KHR_swapchain)
    VULKANDYNAMIC_DECLARE_FUNCTION(CreateSwapchainKHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(DestroySwapchainKHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetSwapchainImagesKHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(AcquireNextImageKHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(QueuePresentKHR);
#endif // VK_KHR_swapchain

#if defined(VK_KHR_display_swapchain)
    VULKANDYNAMIC_DECLARE_FUNCTION(CreateSharedSwapchainsKHR);
#endif // VK_KHR_display_swapchain

#if defined(VK_EXT_debug_marker)
    VULKANDYNAMIC_DECLARE_FUNCTION(DebugMarkerSetObjectTagEXT);
    VULKANDYNAMIC_DECLARE_FUNCTION(DebugMarkerSetObjectNameEXT);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdDebugMarkerBeginEXT);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdDebugMarkerEndEXT);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdDebugMarkerInsertEXT);
#endif // VK_EXT_debug_marker

#if defined(VK_KHR_video_queue)
    VULKANDYNAMIC_DECLARE_FUNCTION(GetPhysicalDeviceVideoCapabilitiesKHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetPhysicalDeviceVideoFormatPropertiesKHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(CreateVideoSessionKHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(DestroyVideoSessionKHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetVideoSessionMemoryRequirementsKHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(BindVideoSessionMemoryKHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(CreateVideoSessionParametersKHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(UpdateVideoSessionParametersKHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(DestroyVideoSessionParametersKHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdBeginVideoCodingKHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdEndVideoCodingKHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdControlVideoCodingKHR);
#endif // VK_KHR_video_queue

#if defined(VK_KHR_video_decode_queue)
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdDecodeVideoKHR);
#endif // VK_KHR_video_decode_queue

#if defined(VK_EXT_transform_feedback)
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdBindTransformFeedbackBuffersEXT);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdBeginTransformFeedbackEXT);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdEndTransformFeedbackEXT);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdBeginQueryIndexedEXT);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdEndQueryIndexedEXT);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdDrawIndirectByteCountEXT);
#endif // VK_EXT_transform_feedback

#if defined(VK_NVX_binary_import)
    VULKANDYNAMIC_DECLARE_FUNCTION(CreateCuModuleNVX);
    VULKANDYNAMIC_DECLARE_FUNCTION(CreateCuFunctionNVX);
    VULKANDYNAMIC_DECLARE_FUNCTION(DestroyCuModuleNVX);
    VULKANDYNAMIC_DECLARE_FUNCTION(DestroyCuFunctionNVX);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdCuLaunchKernelNVX);
#endif // VK_NVX_binary_import

#if defined(VK_NVX_image_view_handle)
    VULKANDYNAMIC_DECLARE_FUNCTION(GetImageViewHandleNVX);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetImageViewAddressNVX);
#endif // VK_NVX_image_view_handle

#if defined(VK_AMD_draw_indirect_count)
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdDrawIndirectCountAMD);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdDrawIndexedIndirectCountAMD);
#endif // VK_AMD_draw_indirect_count

#if defined(VK_AMD_shader_info)
    VULKANDYNAMIC_DECLARE_FUNCTION(GetShaderInfoAMD);
#endif // VK_AMD_shader_info

#if defined(VK_NV_external_memory_win32)
    VULKANDYNAMIC_DECLARE_FUNCTION(GetMemoryWin32HandleNV);
#endif // VK_NV_external_memory_win32

#if defined(VK_KHR_device_group)
    VULKANDYNAMIC_DECLARE_FUNCTION(GetDeviceGroupPeerMemoryFeaturesKHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdSetDeviceMaskKHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdDispatchBaseKHR);
#endif // VK_KHR_device_group

#if defined(VK_KHR_maintenance1)
    VULKANDYNAMIC_DECLARE_FUNCTION(TrimCommandPoolKHR);
#endif // VK_KHR_maintenance1

#if defined(VK_KHR_external_memory_win32)
    VULKANDYNAMIC_DECLARE_FUNCTION(GetMemoryWin32HandleKHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetMemoryWin32HandlePropertiesKHR);
#endif // VK_KHR_external_memory_win32

#if defined(VK_KHR_external_memory_fd)
    VULKANDYNAMIC_DECLARE_FUNCTION(GetMemoryFdKHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetMemoryFdPropertiesKHR);
#endif // VK_KHR_external_memory_fd

#if defined(VK_KHR_external_semaphore_win32)
    VULKANDYNAMIC_DECLARE_FUNCTION(ImportSemaphoreWin32HandleKHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetSemaphoreWin32HandleKHR);
#endif // VK_KHR_external_semaphore_win32

#if defined(VK_KHR_external_semaphore_fd)
    VULKANDYNAMIC_DECLARE_FUNCTION(ImportSemaphoreFdKHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetSemaphoreFdKHR);
#endif // VK_KHR_external_semaphore_fd

#if defined(VK_KHR_push_descriptor)
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdPushDescriptorSetKHR);
#endif // VK_KHR_push_descriptor

#if defined(VK_EXT_conditional_rendering)
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdBeginConditionalRenderingEXT);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdEndConditionalRenderingEXT);
#endif // VK_EXT_conditional_rendering

#if defined(VK_KHR_descriptor_update_template)
    VULKANDYNAMIC_DECLARE_FUNCTION(CreateDescriptorUpdateTemplateKHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(DestroyDescriptorUpdateTemplateKHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(UpdateDescriptorSetWithTemplateKHR);
#endif // VK_KHR_descriptor_update_template

#if defined(VK_NV_clip_space_w_scaling)
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdSetViewportWScalingNV);
#endif // VK_NV_clip_space_w_scaling

#if defined(VK_EXT_display_control)
    VULKANDYNAMIC_DECLARE_FUNCTION(DisplayPowerControlEXT);
    VULKANDYNAMIC_DECLARE_FUNCTION(RegisterDeviceEventEXT);
    VULKANDYNAMIC_DECLARE_FUNCTION(RegisterDisplayEventEXT);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetSwapchainCounterEXT);
#endif // VK_EXT_display_control

#if defined(VK_GOOGLE_display_timing)
    VULKANDYNAMIC_DECLARE_FUNCTION(GetRefreshCycleDurationGOOGLE);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetPastPresentationTimingGOOGLE);
#endif // VK_GOOGLE_display_timing

#if defined(VK_EXT_discard_rectangles)
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdSetDiscardRectangleEXT);
#endif // VK_EXT_discard_rectangles

#if defined(VK_EXT_hdr_metadata)
    VULKANDYNAMIC_DECLARE_FUNCTION(SetHdrMetadataEXT);
#endif // VK_EXT_hdr_metadata

#if defined(VK_KHR_create_renderpass2)
    VULKANDYNAMIC_DECLARE_FUNCTION(CreateRenderPass2KHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdBeginRenderPass2KHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdNextSubpass2KHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdEndRenderPass2KHR);
#endif // VK_KHR_create_renderpass2

#if defined(VK_KHR_shared_presentable_image)
    VULKANDYNAMIC_DECLARE_FUNCTION(GetSwapchainStatusKHR);
#endif // VK_KHR_shared_presentable_image

#if defined(VK_KHR_external_fence_win32)
    VULKANDYNAMIC_DECLARE_FUNCTION(ImportFenceWin32HandleKHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetFenceWin32HandleKHR);
#endif // VK_KHR_external_fence_win32

#if defined(VK_KHR_external_fence_fd)
    VULKANDYNAMIC_DECLARE_FUNCTION(ImportFenceFdKHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetFenceFdKHR);
#endif // VK_KHR_external_fence_fd

#if defined(VK_KHR_performance_query)
    VULKANDYNAMIC_DECLARE_FUNCTION(EnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(AcquireProfilingLockKHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(ReleaseProfilingLockKHR);
#endif // VK_KHR_performance_query

#if defined(VK_ANDROID_external_memory_android_hardware_buffer)
    VULKANDYNAMIC_DECLARE_FUNCTION(GetAndroidHardwareBufferPropertiesANDROID);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetMemoryAndroidHardwareBufferANDROID);
#endif // VK_ANDROID_external_memory_android_hardware_buffer

#if defined(VK_EXT_sample_locations)
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdSetSampleLocationsEXT);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetPhysicalDeviceMultisamplePropertiesEXT);
#endif // VK_EXT_sample_locations

#if defined(VK_KHR_get_memory_requirements2)
    VULKANDYNAMIC_DECLARE_FUNCTION(GetImageMemoryRequirements2KHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetBufferMemoryRequirements2KHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetImageSparseMemoryRequirements2KHR);
#endif // VK_KHR_get_memory_requirements2

#if defined(VK_KHR_acceleration_structure)
    VULKANDYNAMIC_DECLARE_FUNCTION(CreateAccelerationStructureKHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(DestroyAccelerationStructureKHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdBuildAccelerationStructuresKHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdBuildAccelerationStructuresIndirectKHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(BuildAccelerationStructuresKHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(CopyAccelerationStructureKHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(CopyAccelerationStructureToMemoryKHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(CopyMemoryToAccelerationStructureKHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(WriteAccelerationStructuresPropertiesKHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdCopyAccelerationStructureKHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdCopyAccelerationStructureToMemoryKHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdCopyMemoryToAccelerationStructureKHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetAccelerationStructureDeviceAddressKHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdWriteAccelerationStructuresPropertiesKHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetDeviceAccelerationStructureCompatibilityKHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetAccelerationStructureBuildSizesKHR);
#endif // VK_KHR_acceleration_structure

#if defined(VK_KHR_ray_tracing_pipeline)
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdTraceRaysKHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(CreateRayTracingPipelinesKHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetRayTracingShaderGroupHandlesKHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetRayTracingCaptureReplayShaderGroupHandlesKHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdTraceRaysIndirectKHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetRayTracingShaderGroupStackSizeKHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdSetRayTracingPipelineStackSizeKHR);
#endif // VK_KHR_ray_tracing_pipeline

#if defined(VK_KHR_sampler_ycbcr_conversion)
    VULKANDYNAMIC_DECLARE_FUNCTION(CreateSamplerYcbcrConversionKHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(DestroySamplerYcbcrConversionKHR);
#endif // VK_KHR_sampler_ycbcr_conversion

#if defined(VK_KHR_bind_memory2)
    VULKANDYNAMIC_DECLARE_FUNCTION(BindBufferMemory2KHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(BindImageMemory2KHR);
#endif // VK_KHR_bind_memory2

#if defined(VK_EXT_image_drm_format_modifier)
    VULKANDYNAMIC_DECLARE_FUNCTION(GetImageDrmFormatModifierPropertiesEXT);
#endif // VK_EXT_image_drm_format_modifier

#if defined(VK_EXT_validation_cache)
    VULKANDYNAMIC_DECLARE_FUNCTION(CreateValidationCacheEXT);
    VULKANDYNAMIC_DECLARE_FUNCTION(DestroyValidationCacheEXT);
    VULKANDYNAMIC_DECLARE_FUNCTION(MergeValidationCachesEXT);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetValidationCacheDataEXT);
#endif // VK_EXT_validation_cache

#if defined(VK_NV_shading_rate_image)
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdBindShadingRateImageNV);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdSetViewportShadingRatePaletteNV);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdSetCoarseSampleOrderNV);
#endif // VK_NV_shading_rate_image

#if defined(VK_NV_ray_tracing)
    VULKANDYNAMIC_DECLARE_FUNCTION(CreateAccelerationStructureNV);
    VULKANDYNAMIC_DECLARE_FUNCTION(DestroyAccelerationStructureNV);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetAccelerationStructureMemoryRequirementsNV);
    VULKANDYNAMIC_DECLARE_FUNCTION(BindAccelerationStructureMemoryNV);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdBuildAccelerationStructureNV);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdCopyAccelerationStructureNV);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdTraceRaysNV);
    VULKANDYNAMIC_DECLARE_FUNCTION(CreateRayTracingPipelinesNV);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetRayTracingShaderGroupHandlesNV);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetAccelerationStructureHandleNV);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdWriteAccelerationStructuresPropertiesNV);
    VULKANDYNAMIC_DECLARE_FUNCTION(CompileDeferredNV);
#endif // VK_NV_ray_tracing

#if defined(VK_KHR_maintenance3)
    VULKANDYNAMIC_DECLARE_FUNCTION(GetDescriptorSetLayoutSupportKHR);
#endif // VK_KHR_maintenance3

#if defined(VK_KHR_draw_indirect_count)
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdDrawIndirectCountKHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdDrawIndexedIndirectCountKHR);
#endif // VK_KHR_draw_indirect_count

#if defined(VK_EXT_external_memory_host)
    VULKANDYNAMIC_DECLARE_FUNCTION(GetMemoryHostPointerPropertiesEXT);
#endif // VK_EXT_external_memory_host

#if defined(VK_AMD_buffer_marker)
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdWriteBufferMarkerAMD);
#endif // VK_AMD_buffer_marker

#if defined(VK_EXT_calibrated_timestamps)
    VULKANDYNAMIC_DECLARE_FUNCTION(GetPhysicalDeviceCalibrateableTimeDomainsEXT);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetCalibratedTimestampsEXT);
#endif // VK_EXT_calibrated_timestamps

#if defined(VK_NV_mesh_shader)
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdDrawMeshTasksNV);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdDrawMeshTasksIndirectNV);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdDrawMeshTasksIndirectCountNV);
#endif // VK_NV_mesh_shader

#if defined(VK_NV_scissor_exclusive)
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdSetExclusiveScissorNV);
#endif // VK_NV_scissor_exclusive

#if defined(VK_NV_device_diagnostic_checkpoints)
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdSetCheckpointNV);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetQueueCheckpointDataNV);
#endif // VK_NV_device_diagnostic_checkpoints

#if defined(VK_KHR_timeline_semaphore)
    VULKANDYNAMIC_DECLARE_FUNCTION(GetSemaphoreCounterValueKHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(WaitSemaphoresKHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(SignalSemaphoreKHR);
#endif // VK_KHR_timeline_semaphore

#if defined(VK_INTEL_performance_query)
    VULKANDYNAMIC_DECLARE_FUNCTION(InitializePerformanceApiINTEL);
    VULKANDYNAMIC_DECLARE_FUNCTION(UninitializePerformanceApiINTEL);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdSetPerformanceMarkerINTEL);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdSetPerformanceStreamMarkerINTEL);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdSetPerformanceOverrideINTEL);
    VULKANDYNAMIC_DECLARE_FUNCTION(AcquirePerformanceConfigurationINTEL);
    VULKANDYNAMIC_DECLARE_FUNCTION(ReleasePerformanceConfigurationINTEL);
    VULKANDYNAMIC_DECLARE_FUNCTION(QueueSetPerformanceConfigurationINTEL);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetPerformanceParameterINTEL);
#endif // VK_INTEL_performance_query

#if defined(VK_AMD_display_native_hdr)
    VULKANDYNAMIC_DECLARE_FUNCTION(SetLocalDimmingAMD);
#endif // VK_AMD_display_native_hdr

#if defined(VK_KHR_fragment_shading_rate)
    VULKANDYNAMIC_DECLARE_FUNCTION(GetPhysicalDeviceFragmentShadingRatesKHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdSetFragmentShadingRateKHR);
#endif // VK_KHR_fragment_shading_rate

#if defined(VK_EXT_buffer_device_address)
    VULKANDYNAMIC_DECLARE_FUNCTION(GetBufferDeviceAddressEXT);
#endif // VK_EXT_buffer_device_address

#if defined(VK_EXT_tooling_info)
    VULKANDYNAMIC_DECLARE_FUNCTION(GetPhysicalDeviceToolPropertiesEXT);
#endif // VK_EXT_tooling_info

#if defined(VK_KHR_present_wait)
    VULKANDYNAMIC_DECLARE_FUNCTION(WaitForPresentKHR);
#endif // VK_KHR_present_wait

#if defined(VK_NV_cooperative_matrix)
    VULKANDYNAMIC_DECLARE_FUNCTION(GetPhysicalDeviceCooperativeMatrixPropertiesNV);
#endif // VK_NV_cooperative_matrix

#if defined(VK_NV_coverage_reduction_mode)
    VULKANDYNAMIC_DECLARE_FUNCTION(GetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV);
#endif // VK_NV_coverage_reduction_mode

#if defined(VK_EXT_full_screen_exclusive)
    VULKANDYNAMIC_DECLARE_FUNCTION(GetPhysicalDeviceSurfacePresentModes2EXT);
    VULKANDYNAMIC_DECLARE_FUNCTION(AcquireFullScreenExclusiveModeEXT);
    VULKANDYNAMIC_DECLARE_FUNCTION(ReleaseFullScreenExclusiveModeEXT);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetDeviceGroupSurfacePresentModes2EXT);
#endif // VK_EXT_full_screen_exclusive

#if defined(VK_KHR_buffer_device_address)
    VULKANDYNAMIC_DECLARE_FUNCTION(GetBufferDeviceAddressKHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetBufferOpaqueCaptureAddressKHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetDeviceMemoryOpaqueCaptureAddressKHR);
#endif // VK_KHR_buffer_device_address

#if defined(VK_EXT_line_rasterization)
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdSetLineStippleEXT);
#endif // VK_EXT_line_rasterization

#if defined(VK_EXT_host_query_reset)
    VULKANDYNAMIC_DECLARE_FUNCTION(ResetQueryPoolEXT);
#endif // VK_EXT_host_query_reset

#if defined(VK_EXT_extended_dynamic_state)
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdSetCullModeEXT);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdSetFrontFaceEXT);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdSetPrimitiveTopologyEXT);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdSetViewportWithCountEXT);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdSetScissorWithCountEXT);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdBindVertexBuffers2EXT);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdSetDepthTestEnableEXT);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdSetDepthWriteEnableEXT);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdSetDepthCompareOpEXT);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdSetDepthBoundsTestEnableEXT);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdSetStencilTestEnableEXT);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdSetStencilOpEXT);
#endif // VK_EXT_extended_dynamic_state

#if defined(VK_KHR_deferred_host_operations)
    VULKANDYNAMIC_DECLARE_FUNCTION(CreateDeferredOperationKHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(DestroyDeferredOperationKHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetDeferredOperationMaxConcurrencyKHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetDeferredOperationResultKHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(DeferredOperationJoinKHR);
#endif // VK_KHR_deferred_host_operations

#if defined(VK_KHR_pipeline_executable_properties)
    VULKANDYNAMIC_DECLARE_FUNCTION(GetPipelineExecutablePropertiesKHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetPipelineExecutableStatisticsKHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetPipelineExecutableInternalRepresentationsKHR);
#endif // VK_KHR_pipeline_executable_properties

#if defined(VK_NV_device_generated_commands)
    VULKANDYNAMIC_DECLARE_FUNCTION(GetGeneratedCommandsMemoryRequirementsNV);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdPreprocessGeneratedCommandsNV);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdExecuteGeneratedCommandsNV);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdBindPipelineShaderGroupNV);
    VULKANDYNAMIC_DECLARE_FUNCTION(CreateIndirectCommandsLayoutNV);
    VULKANDYNAMIC_DECLARE_FUNCTION(DestroyIndirectCommandsLayoutNV);
#endif // VK_NV_device_generated_commands

#if defined(VK_EXT_private_data)
    VULKANDYNAMIC_DECLARE_FUNCTION(CreatePrivateDataSlotEXT);
    VULKANDYNAMIC_DECLARE_FUNCTION(DestroyPrivateDataSlotEXT);
    VULKANDYNAMIC_DECLARE_FUNCTION(SetPrivateDataEXT);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetPrivateDataEXT);
#endif // VK_EXT_private_data

#if defined(VK_KHR_video_encode_queue)
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdEncodeVideoKHR);
#endif // VK_KHR_video_encode_queue

#if defined(VK_KHR_synchronization2)
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdSetEvent2KHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdResetEvent2KHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdWaitEvents2KHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdPipelineBarrier2KHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdWriteTimestamp2KHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(QueueSubmit2KHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdWriteBufferMarker2AMD);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetQueueCheckpointData2NV);
#endif // VK_KHR_synchronization2

#if defined(VK_NV_fragment_shading_rate_enums)
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdSetFragmentShadingRateEnumNV);
#endif // VK_NV_fragment_shading_rate_enums

#if defined(VK_KHR_copy_commands2)
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdCopyBuffer2KHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdCopyImage2KHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdCopyBufferToImage2KHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdCopyImageToBuffer2KHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdBlitImage2KHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdResolveImage2KHR);
#endif // VK_KHR_copy_commands2

#if defined(VK_NV_acquire_winrt_display)
    VULKANDYNAMIC_DECLARE_FUNCTION(AcquireWinrtDisplayNV);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetWinrtDisplayNV);
#endif // VK_NV_acquire_winrt_display

#if defined(VK_EXT_vertex_input_dynamic_state)
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdSetVertexInputEXT);
#endif // VK_EXT_vertex_input_dynamic_state

#if defined(VK_FUCHSIA_external_memory)
    VULKANDYNAMIC_DECLARE_FUNCTION(GetMemoryZirconHandleFUCHSIA);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetMemoryZirconHandlePropertiesFUCHSIA);
#endif // VK_FUCHSIA_external_memory

#if defined(VK_FUCHSIA_external_semaphore)
    VULKANDYNAMIC_DECLARE_FUNCTION(ImportSemaphoreZirconHandleFUCHSIA);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetSemaphoreZirconHandleFUCHSIA);
#endif // VK_FUCHSIA_external_semaphore

#if defined(VK_HUAWEI_subpass_shading)
    VULKANDYNAMIC_DECLARE_FUNCTION(GetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdSubpassShadingHUAWEI);
#endif // VK_HUAWEI_subpass_shading

#if defined(VK_HUAWEI_invocation_mask)
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdBindInvocationMaskHUAWEI);
#endif // VK_HUAWEI_invocation_mask

#if defined(VK_NV_external_memory_rdma)
    VULKANDYNAMIC_DECLARE_FUNCTION(GetMemoryRemoteAddressNV);
#endif // VK_NV_external_memory_rdma

#if defined(VK_EXT_extended_dynamic_state2)
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdSetPatchControlPointsEXT);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdSetRasterizerDiscardEnableEXT);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdSetDepthBiasEnableEXT);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdSetLogicOpEXT);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdSetPrimitiveRestartEnableEXT);
#endif // VK_EXT_extended_dynamic_state2

#if defined(VK_EXT_color_write_enable)
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdSetColorWriteEnableEXT);
#endif // VK_EXT_color_write_enable

#if defined(VK_EXT_multi_draw)
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdDrawMultiEXT);
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdDrawMultiIndexedEXT);
#endif // VK_EXT_multi_draw

#if defined(VK_EXT_pageable_device_local_memory)
    VULKANDYNAMIC_DECLARE_FUNCTION(SetDeviceMemoryPriorityEXT);
#endif // VK_EXT_pageable_device_local_memory

#if defined(VK_KHR_device_group) || defined(VK_KHR_swapchain)
    VULKANDYNAMIC_DECLARE_FUNCTION(GetDeviceGroupPresentCapabilitiesKHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetDeviceGroupSurfacePresentModesKHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(GetPhysicalDevicePresentRectanglesKHR);
    VULKANDYNAMIC_DECLARE_FUNCTION(AcquireNextImage2KHR);
#endif // VK_KHR_device_group || VK_KHR_swapchain

#if defined(VK_KHR_push_descriptor) || defined(VK_KHR_descriptor_update_template)
    VULKANDYNAMIC_DECLARE_FUNCTION(CmdPushDescriptorSetWithTemplateKHR);
#endif // VK_KHR_push_descriptor || VK_KHR_descriptor_update_template
} VulkanDynamicDeviceDispatch;

VKAPI_ATTR VkResult VKAPI_CALL VulkanDynamicGetDeviceDispatch(VkDevice device, const VulkanDynamicInstanceDispatch* instanceDispatch, VulkanDynamicDeviceDispatch* deviceDispatch);

#if defined(__cplusplus)
}
#endif // __cplusplus

#endif // __VULKANDYNAMIC_H__
