# Vulkan Dynamic Dispatch

Vulkan Dynamic Dispatch is a dynamic loader of Vulkan entry points. This approach can provide the best performance on Vulkan function call.

Vulkan Dynamic Dispatch provides dispatch function tables per the following levels:
 - Loader (Global)
 - Instance
 - Device.

Vulkan Dynamic Dispatch can be used in C and C++ projects.

References:
 - https://vulkan.lunarg.com/doc/view/1.1.121.1/linux/loader_and_layer_interface.html
 - https://vulkan.lunarg.com/doc/view/1.1.121.1/linux/loader_and_layer_interface.html#user-content-best-application-performance-setup
