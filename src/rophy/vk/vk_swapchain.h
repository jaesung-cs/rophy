#ifndef ROPHY_VK_VK_SWAPCHAIN_H_
#define ROPHY_VK_VK_SWAPCHAIN_H_

#include <rophy/vk/vk_object.h>
#include <rophy/utils/printable.h>

#include <vulkan/vulkan.h>

#include <rophy/vk/vk_image.h>
#include <rophy/vk/vk_semaphore.h>

namespace rophy
{
namespace vk
{
class SwapchainCreator;

namespace impl
{
class SwapchainImpl : public vk::Object, public utils::Printable
{
  friend class SwapchainCreator;

public:
  SwapchainImpl() = delete;

  SwapchainImpl(VkDevice device, VkSwapchainKHR surface, ImageInfo image_info);

  ~SwapchainImpl() override;

  void Destroy() override;

  operator VkSwapchainKHR ()
  {
    return swapchain_;
  }

  const auto& Images() const
  {
    return images_;
  }

  uint32_t AcquireNextImage(Semaphore semaphore);

protected:
  void Print(std::ostream& out) const override;

private:
  VkSwapchainKHR swapchain_ = nullptr;
  VkDevice device_ = nullptr;

  std::vector<Image> images_;
};
}

using Swapchain = std::shared_ptr<impl::SwapchainImpl>;
}
}

#endif // ROPHY_VK_VK_SWAPCHAIN_H_
