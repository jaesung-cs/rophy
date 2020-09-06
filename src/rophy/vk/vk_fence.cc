#include <rophy/vk/vk_fence.h>

namespace rophy
{
namespace vk
{
namespace impl
{
FenceImpl::FenceImpl(VkDevice device, VkFence fence)
  : fence_(fence)
  , device_(device)
{
}

FenceImpl::~FenceImpl()
{
  DestroyThis();
}

void FenceImpl::Destroy()
{
  if (fence_ != nullptr)
  {
    vkDestroyFence(device_, fence_, nullptr);
    fence_ = nullptr;
  }
}

void FenceImpl::Wait()
{
  vkWaitForFences(device_, 1, &fence_, VK_TRUE, UINT64_MAX);
}

void FenceImpl::Reset()
{
  vkResetFences(device_, 1, &fence_);
}

void FenceImpl::Print(std::ostream& out) const
{
  out << "VkFence";
}
}
}
}
