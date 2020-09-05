#include <rophy/vk/vk_image_view_creator.h>

#include <iostream>
#include <algorithm>

#include <GLFW/glfw3.h>

#include <rophy/vk/vk_exception.h>

namespace rophy
{
namespace vk
{
ImageViewCreator::ImageViewCreator(Device device, Image image)
  : device_(device)
{
  create_info_.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
  create_info_.image = *image;

  create_info_.viewType = VK_IMAGE_VIEW_TYPE_2D;
  create_info_.format = VkFormat::VK_FORMAT_B8G8R8A8_SRGB; // TODO: put the input argument image's format

  create_info_.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
  create_info_.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
  create_info_.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
  create_info_.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;

  create_info_.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
  create_info_.subresourceRange.baseMipLevel = 0;
  create_info_.subresourceRange.levelCount = 1;
  create_info_.subresourceRange.baseArrayLayer = 0;
  create_info_.subresourceRange.layerCount = 1;
}

ImageViewCreator::~ImageViewCreator()
{
}

ImageView ImageViewCreator::Create()
{
  // Verbose log
  Print(std::cout);
  std::cout << std::endl;

  VkImageView image_view_handle;
  VkResult result;
  if ((result = vkCreateImageView(*device_, &create_info_, nullptr, &image_view_handle)) != VK_SUCCESS)
    throw vk::Exception("Failed to create instance.", result);

  auto image_view = std::make_shared<impl::ImageViewImpl>(*device_, image_view_handle);
  device_->AddChildObject(image_view);

  return image_view;
}

void ImageViewCreator::Print(std::ostream& out) const
{
  out
    << "ImageView create info" << std::endl
    << "  image           : " << std::endl
    << "  viewType        : " << create_info_.viewType << std::endl
    << "  format          : " << create_info_.format << std::endl
    << "  components      : [" << create_info_.components.r << ' ' << create_info_.components.g << ' ' << create_info_.components.b << ' ' << create_info_.components.a << "]" << std::endl
    << "  subresourceRange: " << std::endl
    << "    aspectMask    : " << create_info_.subresourceRange.aspectMask << std::endl
    << "    baseMipLevel  : " << create_info_.subresourceRange.baseMipLevel << std::endl
    << "    levelCount    : " << create_info_.subresourceRange.levelCount << std::endl
    << "    baseArrayLayer: " << create_info_.subresourceRange.baseArrayLayer << std::endl
    << "    layerCount    : " << create_info_.subresourceRange.layerCount << std::endl;
}
}
}
