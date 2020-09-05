#ifndef ROPHY_VK_VK_FRAMEBUFFER_CREATOR_H_
#define ROPHY_VK_VK_FRAMEBUFFER_CREATOR_H_

#include <vector>

#include <vulkan/vulkan.h>

#include <rophy/vk/vk_swapchain.h>
#include <rophy/vk/vk_framebuffer.h>
#include <rophy/vk/vk_render_pass.h>
#include <rophy/vk/vk_image_view.h>

namespace rophy
{
namespace vk
{
class FramebufferCreator : public utils::Printable
{
public:
  FramebufferCreator() = delete;

  explicit FramebufferCreator(Device device);

  ~FramebufferCreator();

  void SetRenderPass(RenderPass render_pass);
  void AddImageView(ImageView image_view);
  void SetExtent(int width, int height);

  Framebuffer Create();

protected:
  void Print(std::ostream& out) const override;

private:
  const Device device_;

  VkFramebufferCreateInfo create_info_{};
  std::vector<VkImageView> attachments_{};
};
}
}

#endif // ROPHY_VK_VK_FRAMEBUFFER_CREATOR_H_
