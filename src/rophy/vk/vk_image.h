#ifndef ROPHY_VK_VK_IMAGE_H_
#define ROPHY_VK_VK_IMAGE_H_

#include <rophy/vk/vk_object.h>
#include <rophy/utils/printable.h>

#include <memory>

#include <vulkan/vulkan.h>

namespace rophy
{
namespace vk
{
struct ImageInfo
{
  int width = 0;
  int height = 0;
  VkFormat format = VkFormat::VK_FORMAT_UNDEFINED;
};

namespace impl
{
class ImageImpl : public vk::Object, public utils::Printable
{
public:
  ImageImpl() = delete;

  ImageImpl(VkImage image, ImageInfo image_info);

  ~ImageImpl() override;

  void Destroy() override;

  operator VkImage ()
  {
    return image_;
  }

  auto ImageFormat() const
  {
    return image_info_.format;
  }

protected:
  void Print(std::ostream& out) const override;

private:
  VkImage image_ = nullptr;

  ImageInfo image_info_;
};
}

using Image = std::shared_ptr<impl::ImageImpl>;
}
}

#endif // ROPHY_VK_VK_IMAGE_H_
