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
namespace impl
{
class ImageImpl : public vk::Object, public utils::Printable
{
public:
  ImageImpl() = delete;

  explicit ImageImpl(VkImage image);

  ~ImageImpl() override;

  void Destroy() override;

  operator VkImage ()
  {
    return image_;
  }

protected:
  void Print(std::ostream& out) const override;

private:
  VkImage image_ = nullptr;
};
}

using Image = std::shared_ptr<impl::ImageImpl>;
}
}

#endif // ROPHY_VK_VK_IMAGE_H_
