#ifndef ROPHY_VK_VK_COMMAND_POOL_CREATOR_H_
#define ROPHY_VK_VK_COMMAND_POOL_CREATOR_H_

#include <rophy/utils/printable.h>

#include <vulkan/vulkan.h>

#include <rophy/vk/vk_command_pool.h>

namespace rophy
{
namespace vk
{
class CommandPoolCreator : public utils::Printable
{
public:
  CommandPoolCreator() = delete;

  explicit CommandPoolCreator(Device device);

  ~CommandPoolCreator();

  void SetQueueFamilyIndex(int queue_family_index);

  CommandPool Create();

protected:
  void Print(std::ostream& out) const override;

private:
  const Device device_;

  VkCommandPoolCreateInfo create_info_{};
};
}
}

#endif // ROPHY_VK_VK_COMMAND_POOL_CREATOR_H_
