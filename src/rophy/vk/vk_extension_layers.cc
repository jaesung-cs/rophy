#include <rophy/vk/vk_extension_layers.h>

#include <iostream>

namespace rophy
{
namespace vk
{
ExtensionLayers::ExtensionLayers()
{
  vkEnumerateInstanceExtensionProperties(nullptr, &extension_count_, nullptr);
  extensions_.resize(extension_count_);
  vkEnumerateInstanceExtensionProperties(nullptr, &extension_count_, extensions_.data());

  vkEnumerateInstanceLayerProperties(&layer_count_, nullptr);
  layers_.resize(layer_count_);
  vkEnumerateInstanceLayerProperties(&layer_count_, layers_.data());
}

ExtensionLayers::~ExtensionLayers()
{
}

void ExtensionLayers::PrintExtensions() const
{
  PrintExtensions(std::cout);
}

void ExtensionLayers::PrintLayers() const
{
  PrintLayers(std::cout);
}

void ExtensionLayers::PrintExtensions(std::ostream& out) const
{
  out << "Extensions:" << std::endl;

  for (const auto& extension : extensions_)
    out << "  " << extension.extensionName << std::endl;
}

void ExtensionLayers::PrintLayers(std::ostream& out) const
{
  out << "Layers:" << std::endl;

  for (const auto& layer : layers_)
    out << "  " << layer.layerName << ": " << layer.description << std::endl;
}

/*
Extensions:
  VK_KHR_device_group_creation
  VK_KHR_external_fence_capabilities
  VK_KHR_external_memory_capabilities
  VK_KHR_external_semaphore_capabilities
  VK_KHR_get_physical_device_properties2
  VK_KHR_get_surface_capabilities2
  VK_KHR_surface
  VK_KHR_surface_protected_capabilities
  VK_KHR_win32_surface
  VK_EXT_debug_report
  VK_EXT_debug_utils
  VK_EXT_swapchain_colorspace
  VK_NV_external_memory_capabilities

Layers:
  VK_LAYER_NV_optimus: NVIDIA Optimus layer
  VK_LAYER_OBS_HOOK: Open Broadcaster Software hook
  VK_LAYER_NV_nsight: NVIDIA Nsight Visual Studio Edition interception layer
  VK_LAYER_VALVE_steam_overlay: Steam Overlay Layer
  VK_LAYER_VALVE_steam_fossilize: Steam Pipeline Caching Layer
  VK_LAYER_LUNARG_api_dump: LunarG API dump layer
  VK_LAYER_LUNARG_device_simulation: LunarG device simulation layer
  VK_LAYER_LUNARG_gfxreconstruct: GFXReconstruct Capture Layer Version 0.9.1
  VK_LAYER_KHRONOS_validation: Khronos Validation Layer
  VK_LAYER_LUNARG_monitor: Execution Monitoring Layer
  VK_LAYER_LUNARG_screenshot: LunarG image capture layer
  VK_LAYER_LUNARG_vktrace: Vktrace tracing library
  VK_LAYER_NV_nsight-sys: NVIDIA Nsight Systems profiler layer
  VK_LAYER_LUNARG_standard_validation: LunarG Standard Validation Layer
*/
}
}
