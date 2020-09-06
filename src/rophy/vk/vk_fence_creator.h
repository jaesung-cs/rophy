#ifndef ROPHY_VK_VK_FENCE_CREATOR_H_
#define ROPHY_VK_VK_FENCE_CREATOR_H_

#include <rophy/utils/printable.h>

#include <vulkan/vulkan.h>

#include <rophy/vk/vk_fence.h>
#include <rophy/vk/vk_device.h>

namespace rophy
{
namespace vk
{
class FenceCreator : public utils::Printable
{
public:
  FenceCreator() = delete;

  explicit FenceCreator(Device device);

  ~FenceCreator();

  Fence Create();

protected:
  void Print(std::ostream& out) const override;

private:
  Device device_;

  VkFenceCreateInfo create_info_{};
};
}
}

#endif // ROPHY_VK_VK_FENCE_CREATOR_H_
