#include <rophy/vk/vk_render_pass_creator.h>

#include <iostream>

#include <rophy/vk/vk_exception.h>

namespace rophy
{
namespace vk
{
RenderPassCreator::RenderPassCreator(Device device)
  : device_(device)
{
  color_attachment_.samples = VK_SAMPLE_COUNT_1_BIT;
  color_attachment_.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
  color_attachment_.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
  color_attachment_.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
  color_attachment_.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
  color_attachment_.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
  color_attachment_.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

  color_attachment_ref_.attachment = 0;
  color_attachment_ref_.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

  subpass_.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
  subpass_.colorAttachmentCount = 1;
  subpass_.pColorAttachments = &color_attachment_ref_;

  dependency_.srcSubpass = VK_SUBPASS_EXTERNAL;
  dependency_.dstSubpass = 0;
  dependency_.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
  dependency_.srcAccessMask = 0;
  dependency_.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
  dependency_.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

  create_info_.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
  create_info_.attachmentCount = 1;
  create_info_.pAttachments = &color_attachment_;
  create_info_.subpassCount = 1;
  create_info_.pSubpasses = &subpass_;
  create_info_.dependencyCount = 1;
  create_info_.pDependencies = &dependency_;
}

RenderPassCreator::~RenderPassCreator()
{
}

void RenderPassCreator::SetImageFormat(VkFormat image_format)
{
  color_attachment_.format = image_format;
}

RenderPass RenderPassCreator::Create()
{
  // Verbose log
  Print(std::cout);
  std::cout << std::endl;

  VkRenderPass render_pass_handle;
  VkResult result;
  if ((result = vkCreateRenderPass(*device_, &create_info_, nullptr, &render_pass_handle)) != VK_SUCCESS)
    throw vk::Exception("Failed to create render pass.", result);

  auto render_pass = std::make_shared<impl::RenderPassImpl>(*device_, render_pass_handle);
  device_->AddChildObject(render_pass);

  return render_pass;
}

void RenderPassCreator::Print(std::ostream& out) const
{
  out
    << "RenderPass create info" << std::endl;
}
}
}
