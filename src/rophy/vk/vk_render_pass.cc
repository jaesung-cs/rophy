#include <rophy/vk/vk_render_pass.h>

namespace rophy
{
namespace vk
{
namespace impl
{
RenderPassImpl::RenderPassImpl(VkDevice device, VkRenderPass render_pass)
  : render_pass_(render_pass)
  , device_(device)
{
}

RenderPassImpl::~RenderPassImpl() = default;

void RenderPassImpl::Destroy()
{
  if (render_pass_ != nullptr)
  {
    vkDestroyRenderPass(device_, render_pass_, nullptr);
    render_pass_ = nullptr;
  }
}

void RenderPassImpl::Print(std::ostream& out) const
{
  out << "VkRenderPass";
}
}
}
}
