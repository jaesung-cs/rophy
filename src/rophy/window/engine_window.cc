#include <rophy/window/engine_window.h>

#include <iostream>

#include <rophy/vk/vk_extension_layers.h>
#include <rophy/vk/vk_instance_creator.h>

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
}

void EngineWindow::Initialize()
{
  vk::ExtensionLayers extension_layers;
  std::cout << extension_layers << std::endl;

  vk::InstanceCreator instance_creator;
  instance_creator.AddValidationLayer();
  instance_creator.AddGlfwRequiredExtensions();
  std::cout << instance_creator << std::endl;
  vk_instance_ = instance_creator.Create();
}
}
}
