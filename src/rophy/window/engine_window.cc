#include <rophy/window/engine_window.h>

#include <iostream>

#include <rophy/vk/vk_extension_layers.h>
#include <rophy/vk/vk_instance_creator.h>
#include <rophy/vk/vk_device_creator.h>
#include <rophy/vk/vk_surface_creator.h>
#include <rophy/vk/vk_swapchain_creator.h>
#include <rophy/vk/vk_image_view_creator.h>

namespace rophy
{
namespace window
{
EngineWindow::EngineWindow()
  : BaseWindow()
{
}

EngineWindow::EngineWindow(int width, int height)
  : BaseWindow(width, height)
{
}

EngineWindow::~EngineWindow()
{
  instance_ = nullptr;
}

void EngineWindow::Initialize()
{
  vk::ExtensionLayers extension_layers;
  std::cout << extension_layers << std::endl;

  vk::InstanceCreator instance_creator;
  instance_creator.AddValidationLayer();
  instance_creator.AddGlfwRequiredExtensions();
  instance_ = instance_creator.Create();

  auto physical_device = instance_->GetPhysicalDevice(0);
  std::cout << *physical_device << std::endl;

  vk::SurfaceCreator surface_creator{ instance_, GetWindow() };
  surface_ = surface_creator.Create();

  vk::DeviceCreator device_creator{ physical_device };
  device_creator.AddValidationLayer();
  device_creator.AddSwapchainExtension();
  device_creator.AddSurfaceQueue(surface_);
  device_creator.AddGraphicsQueue(2);
  device_ = device_creator.Create();
  std::cout << *device_ << std::endl;

  vk::SwapchainCreator swapchain_creator{ device_, surface_ };
  swapchain_ = swapchain_creator.Create();
  std::cout << *swapchain_ << std::endl;

  for (auto swapchain_image : swapchain_->Images())
  {
    vk::ImageViewCreator image_view_creator{ device_, swapchain_image };
    auto swapchain_image_view = image_view_creator.Create();
    swapchain_image_views_.push_back(swapchain_image_view);
    std::cout << *swapchain_image_view << std::endl;
  }
}
}
}
