#include <rophy/vk/vk_command_pool.h>

namespace rophy
{
namespace vk
{
namespace impl
{
CommandPoolImpl::CommandPoolImpl(VkDevice device, VkCommandPool command_pool)
  : command_pool_(command_pool)
  , device_(device)
{
}

CommandPoolImpl::~CommandPoolImpl()
{
  DestroyThis();
}

void CommandPoolImpl::Destroy()
{
  if (command_pool_ != nullptr)
  {
    vkDestroyCommandPool(device_, command_pool_, nullptr);
    command_pool_ = nullptr;
  }
}

void CommandPoolImpl::Print(std::ostream& out) const
{
  out
    << "VkCommandPool";
}
}
}
}
