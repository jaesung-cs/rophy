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
#include <rophy/vk/vk_command_pool_creator.h>
#include <rophy/vk/vk_command_buffer_allocator.h>
#include <rophy/vk/vk_semaphore_creator.h>
#include <rophy/vk/vk_fence_creator.h>
#include <rophy/vk/vk_exception.h>

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

  CreateInstance();
  CreateSurface();
  CreateDevice();
  InitializeQueues();
  CreateSwapchain();
  CreateSwapchainImageViews();
  CreateShaderModules();
  CreatePipelineLayout();
  CreateRenderPass();
  CreateGraphicsPipeline();
  CreateSwapchainFramebuffers();
  CreateCommandPool();
  AllocateCommandBuffers();
  InitializeCommandBuffers();

  for (int i = 0; i < 2; i++)
  {
    vk::SemaphoreCreator semaphore_creator{ device_ };
    image_available_semaphores_[i] = semaphore_creator.Create();
  }

  for (int i = 0; i < 2; i++)
  {
    vk::SemaphoreCreator semaphore_creator{ device_ };
    render_finished_semaphores_[i] = semaphore_creator.Create();
  }

  for (int i = 0; i < 2; i++)
  {
    vk::FenceCreator fence_creator{ device_ };
    in_flight_fences_[i] = fence_creator.Create();
  }

  images_in_flight_.resize(swapchain_image_views_.size());
}

void EngineWindow::Resize(int width, int height)
{
  resized_ = true;

  RecreateSwapchain();
}

void EngineWindow::RecreateSwapchain()
{
  DeviceWaitIdle();

  swapchain_framebuffers_.clear();
  command_buffers_.clear();
  graphics_pipeline_.reset();
  pipeline_layout_.reset();
  render_pass_.reset();
  swapchain_image_views_.clear();
  swapchain_.reset();

  CreateSwapchain();
  CreateSwapchainImageViews();
  CreatePipelineLayout();
  CreateRenderPass();
  CreateGraphicsPipeline();
  CreateSwapchainFramebuffers();
  AllocateCommandBuffers();
  InitializeCommandBuffers();
}

void EngineWindow::CreateInstance()
{
  vk::InstanceCreator instance_creator;
  instance_creator.AddValidationLayer();
  instance_creator.AddGlfwRequiredExtensions();
  instance_ = instance_creator.Create();
}

void EngineWindow::CreateSurface()
{
  vk::SurfaceCreator surface_creator{ instance_, GetGlfwWindow() };
  surface_ = surface_creator.Create();
}

void EngineWindow::CreateDevice()
{
  auto physical_device = instance_->GetPhysicalDevice(0);
  std::cout << *physical_device << std::endl;

  vk::DeviceCreator device_creator{ physical_device };
  device_creator.AddValidationLayer();
  device_creator.AddSwapchainExtension();
  device_creator.AddSurfaceQueue(surface_);
  device_creator.AddGraphicsQueue();
  device_ = device_creator.Create();
  std::cout << *device_ << std::endl;
}

void EngineWindow::InitializeQueues()
{
  present_queue_ = device_->GetQueue(0);
  graphics_queue_ = device_->GetQueue(1);
}

void EngineWindow::CreateSwapchain()
{
  vk::SwapchainCreator swapchain_creator{ device_, surface_ };
  swapchain_creator.SetExtent(Width(), Height());
  swapchain_ = swapchain_creator.Create();
}

void EngineWindow::CreateSwapchainImageViews()
{
  for (auto swapchain_image : swapchain_->Images())
  {
    vk::ImageViewCreator image_view_creator{ device_, swapchain_image };
    auto swapchain_image_view = image_view_creator.Create();
    swapchain_image_views_.push_back(swapchain_image_view);
    std::cout << *swapchain_image_view << std::endl;
  }
}

void EngineWindow::CreateShaderModules()
{
  {
    vk::ShaderModuleCreator shader_module_creator{ device_, "../../src/rophy/shaders/test.vert.spv" };
    vertex_shader_module_ = shader_module_creator.Create();
  }

  {
    vk::ShaderModuleCreator shader_module_creator{ device_, "../../src/rophy/shaders/test.frag.spv" };
    fragment_shader_module_ = shader_module_creator.Create();
  }
}

void EngineWindow::CreatePipelineLayout()
{
  vk::PipelineLayoutCreator pipeline_layout_creator{ device_ };
  pipeline_layout_ = pipeline_layout_creator.Create();
}

void EngineWindow::CreateRenderPass()
{
  vk::RenderPassCreator render_pass_creator{ device_ };
  render_pass_creator.SetImageFormat(swapchain_->Images()[0]->ImageFormat());
  render_pass_ = render_pass_creator.Create();
}

void EngineWindow::CreateGraphicsPipeline()
{
  vk::GraphicsPipelineCreator graphics_pipeline_creator{ device_ };
  graphics_pipeline_creator.SetVertexShader(vertex_shader_module_);
  graphics_pipeline_creator.SetFragmentShader(fragment_shader_module_);
  graphics_pipeline_creator.SetExtent(Width(), Height());
  graphics_pipeline_creator.SetPipelineLayout(pipeline_layout_);
  graphics_pipeline_creator.SetRenderPass(render_pass_);
  graphics_pipeline_ = graphics_pipeline_creator.Create();
}

void EngineWindow::CreateSwapchainFramebuffers()
{
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

void EngineWindow::CreateCommandPool()
{
  vk::CommandPoolCreator command_pool_creator{ device_ };
  command_pool_creator.SetQueueFamilyIndex(0); // TODO: pass queue family class
  command_pool_ = command_pool_creator.Create();
}

void EngineWindow::AllocateCommandBuffers()
{
  vk::CommandBufferAllocator command_buffer_allocator{ device_, command_pool_ };
  command_buffers_ = command_buffer_allocator.Allocate(static_cast<int>(swapchain_framebuffers_.size()));
}

void EngineWindow::InitializeCommandBuffers()
{
  for (int i = 0; i < command_buffers_.size(); i++)
  {
    auto command_buffer = command_buffers_[i];

    command_buffer->Begin();
    command_buffer->CmdBeginRenderPass(render_pass_, swapchain_framebuffers_[i], Width(), Height());
    command_buffer->CmdBindGraphicsPipeline(graphics_pipeline_);
    command_buffer->CmdDraw(3, 1, 0, 0);
    command_buffer->CmdEndRenderPass();
    command_buffer->End();
  }
}

void EngineWindow::Draw()
{
  in_flight_fences_[current_frame_]->Wait();

  uint32_t image_index = -1;
  try
  {
    image_index = swapchain_->AcquireNextImage(image_available_semaphores_[current_frame_]);
  }
  catch (const vk::Exception& e)
  {
    auto error_code = e.ErrorCode();

    switch (error_code)
    {
    case VK_ERROR_OUT_OF_DATE_KHR:
      resized_ = false;
      RecreateSwapchain();
      return;
    case VK_SUBOPTIMAL_KHR:
      return;
    default:
      throw e;
    }
  }

  // Check if a previous frame is using this image (i.e. there is its fence to wait on)
  if (images_in_flight_[image_index] != nullptr)
    images_in_flight_[image_index]->Wait();

  // Mark the image as now being in use by this frame
  images_in_flight_[image_index] = in_flight_fences_[current_frame_];

  in_flight_fences_[current_frame_]->Reset();

  graphics_queue_->Submit(command_buffers_[image_index], image_available_semaphores_[current_frame_], render_finished_semaphores_[current_frame_], in_flight_fences_[current_frame_]);

  try
  {
    present_queue_->Present(swapchain_, image_index, render_finished_semaphores_[current_frame_]);
  }
  catch (const vk::Exception& e)
  {
    auto error_code = e.ErrorCode();
    if (error_code == VK_ERROR_OUT_OF_DATE_KHR || error_code == VK_SUBOPTIMAL_KHR || resized_)
    {
      resized_ = false;
      RecreateSwapchain();
    }
    else
      throw e;
  }

  current_frame_ = (current_frame_ + 1) % 2;
}

void EngineWindow::DeviceWaitIdle()
{
  vkDeviceWaitIdle(*device_);
}
}
}
