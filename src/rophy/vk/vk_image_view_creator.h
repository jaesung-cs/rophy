#ifndef ROPHY_VK_VK_IMAGE_VIEW_CREATOR_H_
#define ROPHY_VK_VK_IMAGE_VIEW_CREATOR_H_

#include <rophy/utils/printable.h>

#include <vulkan/vulkan.h>

#include <rophy/vk/vk_image_view.h>
#include <rophy/vk/vk_device.h>
#include <rophy/vk/vk_image.h>

namespace rophy
{
namespace vk
{
class ImageViewCreator : public utils::Printable
{
public:
  ImageViewCreator() = delete;

  ImageViewCreator(Device device, Image image);

  ~ImageViewCreator();

  ImageView Create();

protected:
  void Print(std::ostream& out) const override;

private:
  Device device_;

  VkImageViewCreateInfo create_info_{};
};
}
}

#endif // ROPHY_VK_VK_IMAGE_VIEW_CREATOR_H_
