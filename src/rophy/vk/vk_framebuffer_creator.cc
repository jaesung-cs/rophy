#include <rophy/vk/vk_framebuffer_creator.h>

#include <iostream>

#include <rophy/vk/vk_exception.h>

namespace rophy
{
namespace vk
{
FramebufferCreator::FramebufferCreator(Device device)
  : device_(device)
{
  create_info_.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
  create_info_.layers = 1;
}

FramebufferCreator::~FramebufferCreator() = default;

void FramebufferCreator::SetRenderPass(RenderPass render_pass)
{
  create_info_.renderPass = *render_pass;
}

void FramebufferCreator::AddImageView(ImageView image_view)
{
  attachments_.push_back(*image_view);
}

void FramebufferCreator::SetExtent(int width, int height)
{
  create_info_.width = width;
  create_info_.height = height;
}

Framebuffer FramebufferCreator::Create()
{
  // Attachments
  create_info_.attachmentCount = attachments_.size();
  create_info_.pAttachments = attachments_.data();

  // Verbose log
  Print(std::cout);
  std::cout << std::endl;

  VkFramebuffer framebuffer_handle;
  VkResult result;
  if ((result = vkCreateFramebuffer(*device_, &create_info_, nullptr, &framebuffer_handle)) != VK_SUCCESS)
    throw Exception("Failed to create framebuffer.", result);

  Framebuffer framebuffer = std::make_shared<impl::FramebufferImpl>(*device_, framebuffer_handle);
  device_->AddChildObject(framebuffer);

  return framebuffer;
}

void FramebufferCreator::Print(std::ostream& out) const
{
  out
    << "Framebuffer create info" << std::endl;
}
}
}
