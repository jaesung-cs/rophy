#ifndef ROPHY_VK_VK_COMMAND_BUFFER_H_
#define ROPHY_VK_VK_COMMAND_BUFFER_H_

#include <rophy/vk/vk_object.h>
#include <rophy/utils/printable.h>

#include <vulkan/vulkan.h>

#include <rophy/vk/vk_device.h>
#include <rophy/vk/vk_command_pool.h>
#include <rophy/vk/vk_render_pass.h>
#include <rophy/vk/vk_framebuffer.h>
#include <rophy/vk/vk_pipeline.h>

namespace rophy
{
namespace vk
{
class CommandBufferAllocator;

namespace impl
{
class CommandBufferImpl : public vk::Object, public utils::Printable
{
  friend class CommandBufferAllocator;

public:
  CommandBufferImpl() = delete;

  CommandBufferImpl(VkDevice device, VkCommandPool command_pool, VkCommandBuffer command_buffer);

  ~CommandBufferImpl() override;

  void Destroy() override;

  operator VkCommandBuffer ()
  {
    return command_buffer_;
  }

  void Begin();
  void CmdBeginRenderPass(RenderPass render_pass, Framebuffer framebuffer, int width, int height);
  void CmdBindGraphicsPipeline(Pipeline pipeline);
  void CmdDraw(int vertex_count, int instance_count = 1, int first_vertex = 0, int first_instance = 0);
  void CmdEndRenderPass();
  void End();

protected:
  void Print(std::ostream& out) const override;

private:
  VkCommandBuffer command_buffer_ = nullptr;
  VkCommandPool command_pool_ = nullptr;
  VkDevice device_ = nullptr;
};
}

using CommandBuffer = std::shared_ptr<impl::CommandBufferImpl>;
}
}

#endif // ROPHY_VK_VK_COMMAND_BUFFER_H_
