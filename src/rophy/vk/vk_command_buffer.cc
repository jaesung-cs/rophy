#include <rophy/vk/vk_command_buffer.h>

#include <rophy/vk/vk_exception.h>

namespace rophy
{
namespace vk
{
namespace impl
{
CommandBufferImpl::CommandBufferImpl(VkDevice device, VkCommandPool command_pool, VkCommandBuffer command_buffer)
  : command_buffer_(command_buffer)
  , command_pool_(command_pool)
  , device_(device)
{
}

CommandBufferImpl::~CommandBufferImpl()
{
  DestroyThis();
}

void CommandBufferImpl::Destroy()
{
  if (command_buffer_ != nullptr)
  {
    vkFreeCommandBuffers(device_, command_pool_, 1, &command_buffer_);
    command_pool_ = nullptr;
  }
}

void CommandBufferImpl::Begin()
{
  VkCommandBufferBeginInfo begin_info{};
  begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  begin_info.flags = 0;
  begin_info.pInheritanceInfo = nullptr;

  VkResult result;
  if ((result = vkBeginCommandBuffer(command_buffer_, &begin_info)) != VK_SUCCESS)
    throw vk::Exception("Failed to begin recording command buffer.", result);
}

void CommandBufferImpl::CmdBeginRenderPass(RenderPass render_pass, Framebuffer framebuffer, int width, int height)
{
  VkRenderPassBeginInfo render_pass_info{};
  render_pass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
  render_pass_info.renderPass = *render_pass;
  render_pass_info.framebuffer = *framebuffer;

  render_pass_info.renderArea.offset = { 0, 0 };
  render_pass_info.renderArea.extent.width = width;
  render_pass_info.renderArea.extent.height = height;

  VkClearValue clear_color = { 0.0f, 0.0f, 0.0f, 1.0f };
  render_pass_info.clearValueCount = 1;
  render_pass_info.pClearValues = &clear_color;

  vkCmdBeginRenderPass(command_buffer_, &render_pass_info, VK_SUBPASS_CONTENTS_INLINE);
}

void CommandBufferImpl::CmdBindGraphicsPipeline(Pipeline pipeline)
{
  vkCmdBindPipeline(command_buffer_, VK_PIPELINE_BIND_POINT_GRAPHICS, *pipeline);
}

void CommandBufferImpl::CmdDraw(int vertex_count, int instance_count, int first_vertex, int first_instance)
{
  vkCmdDraw(command_buffer_, vertex_count, instance_count, first_vertex, first_instance);
}

void CommandBufferImpl::CmdEndRenderPass()
{
  vkCmdEndRenderPass(command_buffer_);
}

void CommandBufferImpl::End()
{
  VkResult result;
  if ((result = vkEndCommandBuffer(command_buffer_)) != VK_SUCCESS)
    throw vk::Exception("Failed to record command buffer.", result);
}

void CommandBufferImpl::Print(std::ostream& out) const
{
  out
    << "VkCommandBuffer";
}
}
}
}
