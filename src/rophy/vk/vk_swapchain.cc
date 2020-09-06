#include <rophy/vk/vk_swapchain.h>

#include <sstream>
#include <iomanip>

#include <rophy/vk/vk_exception.h>

namespace rophy
{
namespace vk
{
namespace impl
{
SwapchainImpl::SwapchainImpl(VkDevice device, VkSwapchainKHR swapchain, ImageInfo image_info)
  : swapchain_(swapchain)
  , device_(device)
{
  uint32_t image_count = 0;
  vkGetSwapchainImagesKHR(device, swapchain_, &image_count, nullptr);
  std::vector<VkImage> vk_images(image_count);
  vkGetSwapchainImagesKHR(device, swapchain_, &image_count, vk_images.data());

  for (auto vk_image : vk_images)
    images_.push_back(std::make_shared<impl::ImageImpl>(vk_image, image_info));
}

SwapchainImpl::~SwapchainImpl()
{
  DestroyThis();
}

void SwapchainImpl::Destroy()
{
  if (swapchain_ != nullptr)
  {
    vkDestroySwapchainKHR(device_, swapchain_, nullptr);
    swapchain_ = nullptr;
  }
}

uint32_t SwapchainImpl::AcquireNextImage(Semaphore semaphore)
{
  VkResult result;
  uint32_t image_index;
  if ((result = vkAcquireNextImageKHR(device_, swapchain_, UINT64_MAX, *semaphore, VK_NULL_HANDLE, &image_index)) != VK_SUCCESS)
    throw vk::Exception("Failed to present swap chain image.", result);

  return image_index;
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
