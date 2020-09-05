#include <rophy/window/engine_window.h>

#include <iostream>

#include <rophy/vk/vk_extension_layers.h>
#include <rophy/vk/vk_instance_creator.h>
#include <rophy/vk/vk_device_creator.h>

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
  vk_instance_ = nullptr;
}

void EngineWindow::Initialize()
{
  vk::ExtensionLayers extension_layers;
  std::cout << extension_layers << std::endl;

  vk::InstanceCreator instance_creator;
  instance_creator.AddValidationLayer();
  instance_creator.AddGlfwRequiredExtensions();
  vk_instance_ = instance_creator.Create();

  auto physical_device = vk_instance_->GetPhysicalDevice(0);
  std::cout << *physical_device << std::endl;

  vk::DeviceCreator device_creator{ physical_device };
  device_creator.AddValidationLayer();
  device_creator.AddGraphicsQueue(2);
  vk_device_ = device_creator.Create();
}
}
}
