#include <rophy/vk/vk_command_buffer_allocator.h>

#include <iostream>

#include <rophy/vk/vk_exception.h>

namespace rophy
{
namespace vk
{
CommandBufferAllocator::CommandBufferAllocator(Device device, CommandPool command_pool)
  : device_(device)
  , command_pool_(command_pool)
{
  allocate_info_.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  allocate_info_.commandPool = *command_pool_;
  allocate_info_.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
}

CommandBufferAllocator::~CommandBufferAllocator() = default;

std::vector<CommandBuffer> CommandBufferAllocator::Allocate(int command_buffer_count)
{
  allocate_info_.commandBufferCount = static_cast<uint32_t>(command_buffer_count);

  // Verbose log
  Print(std::cout);
  std::cout << std::endl;

  std::vector<VkCommandBuffer> command_buffer_handles(command_buffer_count);
  VkResult result;
  if ((result = vkAllocateCommandBuffers(*device_, &allocate_info_, command_buffer_handles.data())) != VK_SUCCESS)
    throw Exception("Failed to allocate command buffer.", result);

  std::vector<CommandBuffer> command_buffers;
  for (auto command_buffer_handle : command_buffer_handles)
  {
    auto command_buffer = std::make_shared<impl::CommandBufferImpl>(*device_, allocate_info_.commandPool, command_buffer_handle);
    device_->AddChildObject(command_buffer);
    command_buffers.push_back(command_buffer);
  }

  return command_buffers;
}

void CommandBufferAllocator::Print(std::ostream& out) const
{
  out
    << "CommandBuffer allocate info" << std::endl;
}
}
}
