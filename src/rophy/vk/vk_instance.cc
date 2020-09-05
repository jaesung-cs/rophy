#include <rophy/vk/vk_instance.h>

#include <iostream>
#include <algorithm>

#include <GLFW/glfw3.h>

#include <rophy/vk/vk_exception.h>

namespace rophy
{
namespace vk
{
namespace impl
{
namespace
{
void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debug_messenger, const VkAllocationCallbacks* allocator)
{
  auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
  if (func != nullptr)
  {
    func(instance, debug_messenger, allocator);
  }
}
}

InstanceImpl::InstanceImpl() = default;

InstanceImpl::~InstanceImpl()
{
  if (debug_messenger_ != nullptr)
  {
    DestroyDebugUtilsMessengerEXT(instance_, debug_messenger_, nullptr);
  }

  vkDestroyInstance(instance_, nullptr);
}
}
}
}
