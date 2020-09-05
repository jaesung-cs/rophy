#include <rophy/vk/vk_instance.h>

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

InstanceImpl::InstanceImpl(VkInstance instance)
  : instance_(instance)
{
  uint32_t device_count = 0;
  vkEnumeratePhysicalDevices(instance_, &device_count, nullptr);
  std::vector<VkPhysicalDevice> devices(device_count);
  vkEnumeratePhysicalDevices(instance_, &device_count, devices.data());

  for (auto device : devices)
  {
    auto physical_device = std::make_shared<impl::PhysicalDeviceImpl>(device);
    AddChildObject(physical_device);
    physical_devices_.push_back(physical_device);
  }
}

InstanceImpl::~InstanceImpl() = default;

void InstanceImpl::Destroy()
{
  if (debug_messenger_ != nullptr)
  {
    DestroyDebugUtilsMessengerEXT(instance_, debug_messenger_, nullptr);
    debug_messenger_ = nullptr;
  }

  vkDestroyInstance(instance_, nullptr);
  instance_ = nullptr;
}
}
}
}
