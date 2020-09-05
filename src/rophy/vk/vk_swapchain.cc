#include <rophy/vk/vk_swapchain.h>

#include <sstream>
#include <iomanip>

namespace rophy
{
namespace vk
{
namespace impl
{
SwapchainImpl::SwapchainImpl(VkDevice device, VkSwapchainKHR swapchain)
  : swapchain_(swapchain)
  , device_(device)
{
  uint32_t image_count = 0;
  vkGetSwapchainImagesKHR(device, swapchain_, &image_count, nullptr);
  std::vector<VkImage> vk_images(image_count);
  vkGetSwapchainImagesKHR(device, swapchain_, &image_count, vk_images.data());

  for (auto vk_image : vk_images)
    images_.push_back(std::make_shared<impl::ImageImpl>(vk_image));
}

SwapchainImpl::~SwapchainImpl() = default;

void SwapchainImpl::Destroy()
{
  if (swapchain_ != nullptr)
  {
    vkDestroySwapchainKHR(device_, swapchain_, nullptr);
    swapchain_ = nullptr;
  }
}

void SwapchainImpl::Print(std::ostream& out) const
{
  out
    << "VkSwapchain:" << std::endl
    << "  Images:" << std::endl;

  std::vector<std::string> image_strings;
  for (int i = 0; i < images_.size(); i++)
  {
    auto image = images_[i];

    std::ostringstream sout;

    sout << "Index " << std::setw(2) << i << ": " << *image;

    image_strings.emplace_back(sout.str());
  }
  PrintStrings(out, image_strings, 4);
}
}
}
}
