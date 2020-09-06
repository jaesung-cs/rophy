#include <rophy/vk/vk_framebuffer.h>

#include <sstream>
#include <iomanip>

namespace rophy
{
namespace vk
{
namespace impl
{
FramebufferImpl::FramebufferImpl(VkDevice device, VkFramebuffer framebuffer)
  : framebuffer_(framebuffer)
  , device_(device)
{
}

FramebufferImpl::~FramebufferImpl()
{
  DestroyThis();
}

void FramebufferImpl::Destroy()
{
  if (framebuffer_ != nullptr)
  {
    vkDestroyFramebuffer(device_, framebuffer_, nullptr);
    framebuffer_ = nullptr;
  }
}

void FramebufferImpl::Print(std::ostream& out) const
{
  out
    << "VkFramebuffer";
}
}
}
}
