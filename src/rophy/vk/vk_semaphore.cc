#include <rophy/vk/vk_semaphore.h>

namespace rophy
{
namespace vk
{
namespace impl
{
SemaphoreImpl::SemaphoreImpl(VkDevice device, VkSemaphore semaphore)
  : semaphore_(semaphore)
  , device_(device)
{
}

SemaphoreImpl::~SemaphoreImpl()
{
  DestroyThis();
}

void SemaphoreImpl::Destroy()
{
  if (semaphore_ != nullptr)
  {
    vkDestroySemaphore(device_, semaphore_, nullptr);
    semaphore_ = nullptr;
  }
}

void SemaphoreImpl::Print(std::ostream& out) const
{
  out << "VkSemaphore";
}
}
}
}
