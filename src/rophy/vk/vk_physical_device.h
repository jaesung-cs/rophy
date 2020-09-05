#ifndef ROPHY_VK_VK_PHYSICAL_DEVICE_H_
#define ROPHY_VK_VK_PHYSICAL_DEVICE_H_

#include <rophy/vk/vk_object.h>
#include <rophy/utils/printable.h>

#include <memory>
#include <vector>
#include <string>

#include <vulkan/vulkan.h>

#include <rophy/vk/vk_queue.h>
#include <rophy/vk/vk_extension_layers.h>
#include <rophy/vk/vk_surface.h>

namespace rophy
{
namespace vk
{
class DeviceCreator;

namespace impl
{
class PhysicalDeviceImpl : public vk::Object, public utils::Printable
{
  friend class DeviceCreator;

public:
  PhysicalDeviceImpl() = delete;

  explicit PhysicalDeviceImpl(VkPhysicalDevice handle);

  ~PhysicalDeviceImpl();

  auto NumQueueFamilies() const
  {
    return queue_families_.size();
  }

  int GetQueueFamilyIndex(BitFlags type) const;
  int GetSurfaceSupportedQueueFamilyIndex(Surface surface) const;

  operator VkPhysicalDevice ()
  {
    return physical_device_;
  }

protected:
  void Print(std::ostream& out) const override;

private:
  VkPhysicalDevice physical_device_ = nullptr;

  VkPhysicalDeviceProperties properties_{};
  VkPhysicalDeviceFeatures features_{};
  ExtensionLayers extension_layers_;

  std::vector<VkQueueFamilyProperties> queue_families_;
};
}

using PhysicalDevice = std::shared_ptr<impl::PhysicalDeviceImpl>;
}
}

#endif // ROPHY_VK_VK_PHYSICAL_DEVICE_H_
