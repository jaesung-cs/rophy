#include <rophy/vk/vk_image_view.h>

namespace rophy
{
namespace vk
{
namespace impl
{
ImageViewImpl::ImageViewImpl(VkDevice device, VkImageView image_view)
  : image_view_(image_view)
  , device_(device)
{
}

ImageViewImpl::~ImageViewImpl() = default;

void ImageViewImpl::Destroy()
{
  if (image_view_ != nullptr)
  {
    vkDestroyImageView(device_, image_view_, nullptr);
    image_view_ = nullptr;
  }
}

void ImageViewImpl::Print(std::ostream& out) const
{
  out << "VkImageView";
}
}
}
}
