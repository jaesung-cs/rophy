#include <rophy/vk/vk_swapchain_creator.h>

#include <cmath>
#include <iomanip>
#include <sstream>

#include <rophy/vk/vk_exception.h>

namespace rophy
{
namespace vk
{
SwapchainCreator::SwapchainCreator(Device device, Surface surface)
  : device_(device)
{
  create_info_.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
  create_info_.surface = *surface;

  // Surface details
  vkGetPhysicalDeviceSurfaceCapabilitiesKHR(*device->GetPhysicalDevice(), *surface, &surface_capabilities_);

  uint32_t format_count;
  vkGetPhysicalDeviceSurfaceFormatsKHR(*device->GetPhysicalDevice(), *surface, &format_count, nullptr);
  surface_formats_.resize(format_count);
  vkGetPhysicalDeviceSurfaceFormatsKHR(*device->GetPhysicalDevice(), *surface, &format_count, surface_formats_.data());

  uint32_t present_mode_count;
  vkGetPhysicalDeviceSurfacePresentModesKHR(*device->GetPhysicalDevice(), *surface, &present_mode_count, nullptr);
  present_modes_.resize(present_mode_count);
  vkGetPhysicalDeviceSurfacePresentModesKHR(*device->GetPhysicalDevice(), *surface, &present_mode_count, present_modes_.data());

  // Select surface format
  auto surface_format = [this]() {
    for (const auto& surface_format : surface_formats_)
    {
      if (surface_format.format == VK_FORMAT_B8G8R8A8_SRGB && surface_format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
        return surface_format;
    }

    // If no such format, choose any
    return surface_formats_[0];
  } ();

  // Select present mode
  auto present_mode = [this]() {
    for (const auto& present_mode : present_modes_)
    {
      if (present_mode == VK_PRESENT_MODE_MAILBOX_KHR)
        return present_mode;
    }

    // If no MAILBOX mode available, choose FIFO
    return VK_PRESENT_MODE_FIFO_KHR;
  } ();

  // Select extent
  auto extent = [this]() {
    if (surface_capabilities_.currentExtent.width != UINT32_MAX)
      return surface_capabilities_.currentExtent;
    else
    {
      // TODO
      VkExtent2D actual_extent = { 1600, 900 };

      actual_extent.width = std::max(surface_capabilities_.minImageExtent.width, std::min(surface_capabilities_.maxImageExtent.width, actual_extent.width));
      actual_extent.height = std::max(surface_capabilities_.minImageExtent.height, std::min(surface_capabilities_.maxImageExtent.height, actual_extent.height));

      return actual_extent;
    }
  } ();

  auto image_count = surface_capabilities_.minImageCount + 1;
  if (surface_capabilities_.maxImageCount > 0 && image_count > surface_capabilities_.maxImageCount)
    image_count = surface_capabilities_.maxImageCount;

  create_info_.minImageCount = image_count;
  create_info_.imageFormat = surface_format.format;
  create_info_.imageColorSpace = surface_format.colorSpace;
  create_info_.imageExtent = extent;
  create_info_.imageArrayLayers = 1;
  create_info_.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

  create_info_.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;

  create_info_.preTransform = surface_capabilities_.currentTransform;

  create_info_.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;

  create_info_.presentMode = present_mode;
  create_info_.clipped = VK_TRUE;

  create_info_.oldSwapchain = VK_NULL_HANDLE;
}

SwapchainCreator::~SwapchainCreator() = default;

Swapchain SwapchainCreator::Create()
{
  // Verbose log
  Print(std::cout);
  std::cout << std::endl;

  VkSwapchainKHR swapchain_handle;
  VkResult result;
  if ((result = vkCreateSwapchainKHR(*device_, &create_info_, nullptr, &swapchain_handle)) != VK_SUCCESS)
    throw Exception("Failed to create swapchain.", result);

  Swapchain swapchain = std::make_shared<impl::SwapchainImpl>(*device_, swapchain_handle);
  device_->AddChildObject(swapchain);

  return swapchain;
}

void SwapchainCreator::Print(std::ostream& out) const
{
  out
    << "Swapchain create info:" << std::endl
    << "  minImageCount   : " << create_info_.minImageCount << std::endl
    << "  imageFormat     : " << create_info_.imageFormat << std::endl
    << "  imageColorSpace : " << create_info_.imageColorSpace << std::endl
    << "  extent          : [" << create_info_.imageExtent.width << ", " << create_info_.imageExtent.height << "]" << std::endl
    << "  imageArrayLayers: " << create_info_.imageArrayLayers << std::endl
    << "  imageUsage      : " << create_info_.imageUsage << std::endl
    << "  imageSharingMode: " << create_info_.imageSharingMode << std::endl
    << "  preTransform    : " << create_info_.preTransform << std::endl
    << "  compositeAlpha  : " << create_info_.compositeAlpha << std::endl
    << "  presentMode     : " << create_info_.presentMode << std::endl
    << "  clipped         : " << create_info_.clipped << std::endl
    << "  oldSwapchain    : " << create_info_.oldSwapchain << std::endl;

  out
    << "  Available formats:" << std::endl;
  std::vector<std::string> format_strings;
  for (int i = 0; i < surface_formats_.size(); i++)
  {
    const auto& format = surface_formats_[i];

    std::ostringstream sout;
    sout << "Index " << std::setw(2) << i << ": Format: " << format.format << ", colorSpace: " << format.colorSpace;
    format_strings.push_back(sout.str());
  }
  PrintStrings(out, format_strings, 4);

  out
    << "  Available present modes:" << std::endl;
  std::vector<std::string> present_mode_strings;
  for (int i = 0; i < present_modes_.size(); i++)
  {
    auto present_mode = present_modes_[i];

    std::ostringstream sout;
    sout << "Index " << std::setw(2) << i << ": " << present_mode;
    present_mode_strings.push_back(sout.str());
  }
  PrintStrings(out, present_mode_strings, 4);
}
}
}
