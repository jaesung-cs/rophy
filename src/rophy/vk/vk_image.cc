#include <rophy/vk/vk_image.h>

namespace rophy
{
namespace vk
{
namespace impl
{
ImageImpl::ImageImpl(VkImage image)
  : image_(image)
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
