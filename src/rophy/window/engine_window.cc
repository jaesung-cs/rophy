#include <rophy/window/engine_window.h>

#include <iostream>

#include <rophy/vk/vk_extension_layers.h>
#include <rophy/vk/vk_instance_creator.h>
#include <rophy/vk/vk_device_creator.h>
#include <rophy/vk/vk_surface_creator.h>
#include <rophy/vk/vk_swapchain_creator.h>
#include <rophy/vk/vk_image_view_creator.h>
#include <rophy/vk/vk_shader_module_creator.h>
#include <rophy/vk/vk_pipeline_layout_creator.h>
#include <rophy/vk/vk_render_pass_creator.h>
#include <rophy/vk/vk_graphics_pipeline_creator.h>
#include <rophy/vk/vk_framebuffer_creator.h>

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
  swapchain_creator.SetExtent(Width(), Height());
  swapchain_ = swapchain_creator.Create();
  std::cout << *swapchain_ << std::endl;

  for (auto swapchain_image : swapchain_->Images())
  {
    vk::ImageViewCreator image_view_creator{ device_, swapchain_image };
    auto swapchain_image_view = image_view_creator.Create();
    swapchain_image_views_.push_back(swapchain_image_view);
    std::cout << *swapchain_image_view << std::endl;
  }

  {
    vk::ShaderModuleCreator shader_module_creator{ device_, "../../src/rophy/shaders/test.vert.spv" };
    vertex_shader_module_ = shader_module_creator.Create();
  }

  {
    vk::ShaderModuleCreator shader_module_creator{ device_, "../../src/rophy/shaders/test.frag.spv" };
    fragment_shader_module_ = shader_module_creator.Create();
  }

  vk::PipelineLayoutCreator pipeline_layout_creator{ device_ };
  pipeline_layout_ = pipeline_layout_creator.Create();

  vk::RenderPassCreator render_pass_creator{ device_ };
  render_pass_creator.SetImageFormat(swapchain_->Images()[0]->ImageFormat());
  render_pass_ = render_pass_creator.Create();

  vk::GraphicsPipelineCreator graphics_pipeline_creator{ device_ };
  graphics_pipeline_creator.SetVertexShader(vertex_shader_module_);
  graphics_pipeline_creator.SetFragmentShader(fragment_shader_module_);
  graphics_pipeline_creator.SetExtent(Width(), Height());
  graphics_pipeline_creator.SetPipelineLayout(pipeline_layout_);
  graphics_pipeline_creator.SetRenderPass(render_pass_);
  graphics_pipeline_ = graphics_pipeline_creator.Create();

  for (auto image_view : swapchain_image_views_)
  {
    vk::FramebufferCreator framebuffer_creator{ device_ };
    framebuffer_creator.SetRenderPass(render_pass_);
    framebuffer_creator.AddImageView(image_view);
    framebuffer_creator.SetExtent(Width(), Height());
    auto swapchain_framebuffer = framebuffer_creator.Create();
    swapchain_framebuffers_.push_back(swapchain_framebuffer);
  }
}
}
}
