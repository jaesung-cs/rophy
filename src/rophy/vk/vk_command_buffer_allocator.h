#ifndef ROPHY_VK_VK_COMMAND_BUFFER_ALLOCATOR_H_
#define ROPHY_VK_VK_COMMAND_BUFFER_ALLOCATOR_H_

#include <rophy/utils/printable.h>

#include <vulkan/vulkan.h>

#include <rophy/vk/vk_command_buffer.h>

namespace rophy
{
namespace vk
{
class CommandBufferAllocator : public utils::Printable
{
public:
  CommandBufferAllocator() = delete;

  CommandBufferAllocator(Device device, CommandPool command_pool);

  ~CommandBufferAllocator();

  std::vector<CommandBuffer> Allocate(int command_buffer_count);

protected:
  void Print(std::ostream& out) const override;

private:
  const Device device_;
  const CommandPool command_pool_;

  VkCommandBufferAllocateInfo allocate_info_{};
};
}
}

#endif // ROPHY_VK_VK_COMMAND_BUFFER_ALLOCATOR_H_
