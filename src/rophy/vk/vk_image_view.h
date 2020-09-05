#ifndef ROPHY_VK_VK_IMAGE_VIEW_H_
#define ROPHY_VK_VK_IMAGE_VIEW_H_

#include <rophy/vk/vk_object.h>
#include <rophy/utils/printable.h>

#include <memory>

#include <vulkan/vulkan.h>

namespace rophy
{
namespace vk
{
class ImageViewCreator;

namespace impl
{
class ImageViewImpl : public vk::Object, public utils::Printable
{
  friend class ImageViewCreator;

public:
  ImageViewImpl() = delete;

  explicit ImageViewImpl(VkDevice device, VkImageView image_view);

  ~ImageViewImpl() override;

  void Destroy() override;

  operator VkImageView ()
  {
    return image_view_;
  }

protected:
  void Print(std::ostream& out) const override;

private:
  VkImageView image_view_ = nullptr;

  VkDevice device_ = nullptr;
};
}

using ImageView = std::shared_ptr<impl::ImageViewImpl>;
}
}

#endif // ROPHY_VK_VK_IMAGE_VIEW_H_
