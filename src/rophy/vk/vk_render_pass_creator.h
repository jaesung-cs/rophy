#ifndef ROPHY_VK_VK_RENDER_PASS_CREATOR_H_
#define ROPHY_VK_VK_RENDER_PASS_CREATOR_H_

#include <rophy/utils/printable.h>

#include <vulkan/vulkan.h>

#include <rophy/vk/vk_device.h>
#include <rophy/vk/vk_render_pass.h>

namespace rophy
{
namespace vk
{
class RenderPassCreator : public utils::Printable
{
public:
  RenderPassCreator() = delete;

  explicit RenderPassCreator(Device device);

  ~RenderPassCreator();

  void SetImageFormat(VkFormat image_format);

  RenderPass Create();

protected:
  void Print(std::ostream& out) const override;

private:
  Device device_;

  VkRenderPassCreateInfo create_info_{};

  VkAttachmentDescription color_attachment_{};
  VkAttachmentReference color_attachment_ref_{};
  VkSubpassDescription subpass_{};
};
}
}

#endif // ROPHY_VK_VK_RENDER_PASS_CREATOR_H_
