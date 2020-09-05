#ifndef ROPHY_VK_VK_SWAPCHAIN_CREATOR_H_
#define ROPHY_VK_VK_SWAPCHAIN_CREATOR_H_

#include <vector>

#include <vulkan/vulkan.h>

#include <rophy/vk/vk_swapchain.h>
#include <rophy/vk/vk_device.h>
#include <rophy/vk/vk_surface.h>

namespace rophy
{
namespace vk
{
class SwapchainCreator : public utils::Printable
{
public:
  SwapchainCreator() = delete;

  SwapchainCreator(Device device, Surface surface);

  ~SwapchainCreator();

  void SetExtent(int width, int height);

  Swapchain Create();

protected:
  void Print(std::ostream& out) const override;

private:
  const Device device_;
  const Surface surface_;

  VkSwapchainCreateInfoKHR create_info_{};

  VkSurfaceCapabilitiesKHR surface_capabilities_;
  std::vector<VkSurfaceFormatKHR> surface_formats_;
  std::vector<VkPresentModeKHR> present_modes_;
};
}
}

#endif // ROPHY_VK_VK_SWAPCHAIN_CREATOR_H_
