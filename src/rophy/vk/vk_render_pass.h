#ifndef ROPHY_VK_VK_RENDER_PASS_H_
#define ROPHY_VK_VK_RENDER_PASS_H_

#include <rophy/vk/vk_object.h>
#include <rophy/utils/printable.h>

#include <memory>

#include <vulkan/vulkan.h>

namespace rophy
{
namespace vk
{
class RenderPassCreator;

namespace impl
{
class RenderPassImpl : public vk::Object, public utils::Printable
{
  friend class RenderPassCreator;

public:
  RenderPassImpl() = delete;

  RenderPassImpl(VkDevice device, VkRenderPass render_pass);

  ~RenderPassImpl() override;

  void Destroy() override;

  operator VkRenderPass ()
  {
    return render_pass_;
  }

protected:
  void Print(std::ostream& out) const override;

private:
  VkRenderPass render_pass_ = nullptr;

  VkDevice device_ = nullptr;
};
}

using RenderPass = std::shared_ptr<impl::RenderPassImpl>;
}
}

#endif // ROPHY_VK_VK_RENDER_PASS_H_
