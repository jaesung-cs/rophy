#include <rophy/vk/vk_fence_creator.h>

#include <iostream>

#include <rophy/vk/vk_exception.h>

namespace rophy
{
namespace vk
{
FenceCreator::FenceCreator(Device device)
  : device_(device)
{
  create_info_.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
  create_info_.flags = VK_FENCE_CREATE_SIGNALED_BIT;
}

FenceCreator::~FenceCreator()
{
}

Fence FenceCreator::Create()
{
  // Verbose log
  Print(std::cout);
  std::cout << std::endl;

  VkFence fence_handle;
  VkResult result;
  if ((result = vkCreateFence(*device_, &create_info_, nullptr, &fence_handle)) != VK_SUCCESS)
    throw vk::Exception("Failed to create fence.", result);

  auto fence = std::make_shared<impl::FenceImpl>(*device_, fence_handle);
  device_->AddChildObject(fence);

  return fence;
}

void FenceCreator::Print(std::ostream& out) const
{
  out
    << "Fence create info" << std::endl;
}
}
}
