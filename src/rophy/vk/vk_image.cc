#include <rophy/vk/vk_image.h>

namespace rophy
{
namespace vk
{
namespace impl
{
ImageImpl::ImageImpl(VkImage image, ImageInfo image_info)
  : image_(image), image_info_(image_info)
{
}

ImageImpl::~ImageImpl() = default;

void ImageImpl::Destroy()
{
  // TODO: delete if created
}

void ImageImpl::Print(std::ostream& out) const
{
  out << "VkImage";
}
}
}
}
