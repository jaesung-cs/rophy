#include <rophy/vk/vk_instance_creator.h>

#include <iostream>
#include <algorithm>

#include <GLFW/glfw3.h>

#include <rophy/vk/vk_exception.h>

namespace rophy
{
namespace vk
{
namespace
{
VKAPI_ATTR VkBool32 VKAPI_CALL debug_callback(
  VkDebugUtilsMessageSeverityFlagBitsEXT message_severity,
  VkDebugUtilsMessageTypeFlagsEXT message_type,
  const VkDebugUtilsMessengerCallbackDataEXT* callback_data,
  void* user_data)
{
  std::cerr << "Validation layer: " << callback_data->pMessage << std::endl << std::endl;

  return VK_FALSE;
}

VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger)
{
  auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
  if (func != nullptr)
    return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
  else
    return VK_ERROR_EXTENSION_NOT_PRESENT;
}
}

InstanceCreator::InstanceCreator()
{
  app_info_.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  app_info_.pApplicationName = "Hello Triangle";
  app_info_.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
  app_info_.pEngineName = "No Engine";
  app_info_.engineVersion = VK_MAKE_VERSION(1, 0, 0);
  app_info_.apiVersion = VK_API_VERSION_1_0;

  create_info_.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  create_info_.pApplicationInfo = &app_info_;

  debug_messenger_create_info_.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
  debug_messenger_create_info_.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
  debug_messenger_create_info_.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
  debug_messenger_create_info_.pfnUserCallback = debug_callback;
  debug_messenger_create_info_.pUserData = nullptr;
}

InstanceCreator::~InstanceCreator()
{
}

void InstanceCreator::AddExtension(const std::string& extension_name)
{
  extension_names_.push_back(extension_name);
}

void InstanceCreator::AddGlfwRequiredExtensions()
{
  uint32_t glfw_extension_count = 0;
  const char** glfw_extensions;
  glfw_extensions = glfwGetRequiredInstanceExtensions(&glfw_extension_count);

  std::transform(glfw_extensions, glfw_extensions + glfw_extension_count, std::back_inserter(extension_names_),
    [](const char* s) { return std::string(s); });
}

void InstanceCreator::AddLayer(const std::string& layer_name)
{
  layer_names_.push_back(layer_name);
}

void InstanceCreator::AddValidationLayer()
{
  AddLayer("VK_LAYER_KHRONOS_validation");
  AddExtension(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

  is_validation_layer_enabled_ = true;
}

Instance InstanceCreator::Create()
{
  // Extensions
  std::vector<const char*> extension_names;
  for (const auto& extension_name_string : extension_names_)
    extension_names.push_back(extension_name_string.c_str());

  create_info_.enabledExtensionCount = static_cast<uint32_t>(extension_names.size());
  create_info_.ppEnabledExtensionNames = extension_names.data();

  // Layers
  std::vector<const char*> layer_names;
  for (const auto& layer_name_string : layer_names_)
    layer_names.push_back(layer_name_string.c_str());

  create_info_.enabledLayerCount = static_cast<uint32_t>(layer_names.size());
  create_info_.ppEnabledLayerNames = layer_names.data();

  if (IsValidationLayerEnabled())
    create_info_.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debug_messenger_create_info_;

  // Verbose log
  Print(std::cout);
  std::cout << std::endl;

  VkInstance instance_handle;
  VkResult result;
  if ((result = vkCreateInstance(&create_info_, nullptr, &instance_handle)) != VK_SUCCESS)
    throw vk::Exception("Failed to create instance.", result);

  auto instance = std::make_shared<impl::InstanceImpl>(instance_handle);

  if (IsValidationLayerEnabled())
  {
    if ((result = CreateDebugUtilsMessengerEXT(*instance, &debug_messenger_create_info_, nullptr, &instance->DebugMessenger())) != VK_SUCCESS)
      throw vk::Exception("Failed to set up debug messenger.", result);
  }

  return instance;
}

void InstanceCreator::Print(std::ostream& out) const
{
  out
    << "Instance create info" << std::endl
    << "  enabledExtensionCount  : " << create_info_.enabledExtensionCount << std::endl
    << "  ppEnabledExtensionNames: " << std::endl;
  PrintStrings(out, create_info_.ppEnabledExtensionNames, create_info_.enabledExtensionCount, 4);
  out
    << "  enabledLayerCount      : " << create_info_.enabledLayerCount << std::endl
    << "  ppEnabledLayerNames    : " << std::endl;
  PrintStrings(out, create_info_.ppEnabledLayerNames, create_info_.enabledLayerCount, 4);
  out << "  pApplicationInfo" << std::endl;

  // Application
  out
    << "    pApplicationName  : " << create_info_.pApplicationInfo->pApplicationName << std::endl
    << "    applicationVersion: " << create_info_.pApplicationInfo->applicationVersion << std::endl
    << "    pEngineName       : " << create_info_.pApplicationInfo->pEngineName << std::endl
    << "    engineVersion     : " << create_info_.pApplicationInfo->engineVersion << std::endl
    << "    apiVersion        : " << create_info_.pApplicationInfo->apiVersion << std::endl;
  // TODO: application pNext
  // TODO: createInfo pNext
}
}
}
