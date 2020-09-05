#ifndef ROPHY_VK_VK_INSTANCE_H_
#define ROPHY_VK_VK_INSTANCE_H_

#include <rophy/vk/vk_object.h>

#include <memory>
#include <vector>
#include <string>

#include <vulkan/vulkan.h>

#include <rophy/vk/vk_physical_device.h>

namespace rophy
{
namespace vk
{
class InstanceCreator;

namespace impl
{
class InstanceImpl : public vk::Object
{
  friend class InstanceCreator;

public:
  InstanceImpl() = delete;

  explicit InstanceImpl(VkInstance handle);

  ~InstanceImpl() override;

  void Destroy() override;

  operator VkInstance ()
  {
    return instance_;
  }

  auto& DebugMessenger()
  {
    return debug_messenger_;
  }

  auto GetPhysicalDevice(int index) const
  {
    return physical_devices_[index];
  }

private:
  VkInstance instance_ = nullptr;
  VkDebugUtilsMessengerEXT debug_messenger_ = nullptr;

  // Physical devices
  std::vector<PhysicalDevice> physical_devices_;
};
}

using Instance = std::shared_ptr<impl::InstanceImpl>;
}
}

#endif // ROPHY_VK_VK_INSTANCE_H_
