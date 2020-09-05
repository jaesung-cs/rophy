#include <rophy/vk/vk_command_pool_creator.h>

#include <iostream>

#include <rophy/vk/vk_exception.h>

namespace rophy
{
namespace vk
{
CommandPoolCreator::CommandPoolCreator(Device device)
  : device_(device)
{
  create_info_.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
  create_info_.flags = 0;
}

CommandPoolCreator::~CommandPoolCreator() = default;

void CommandPoolCreator::SetQueueFamilyIndex(int queue_family_index)
{
  create_info_.queueFamilyIndex = queue_family_index;
}

CommandPool CommandPoolCreator::Create()
{
  // Verbose log
  Print(std::cout);
  std::cout << std::endl;

  VkCommandPool command_pool_handle;
  VkResult result;
  if ((result = vkCreateCommandPool(*device_, &create_info_, nullptr, &command_pool_handle)) != VK_SUCCESS)
    throw Exception("Failed to create command pool.", result);

  CommandPool command_pool = std::make_shared<impl::CommandPoolImpl>(*device_, command_pool_handle);
  device_->AddChildObject(command_pool);

  return command_pool;
}

void CommandPoolCreator::Print(std::ostream& out) const
{
  out
    << "CommandPool create info" << std::endl;
}
}
}
