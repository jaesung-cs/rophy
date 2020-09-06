#ifndef ROPHY_WINDOW_ENGINE_WINDOW_H_
#define ROPHY_WINDOW_ENGINE_WINDOW_H_

#include <rophy/window/base_window.h>

#include <vector>

#include <rophy/vk/vk_instance.h>
#include <rophy/vk/vk_device.h>
#include <rophy/vk/vk_queue.h>
#include <rophy/vk/vk_surface.h>
#include <rophy/vk/vk_swapchain.h>
#include <rophy/vk/vk_image_view.h>
#include <rophy/vk/vk_shader_module.h>
#include <rophy/vk/vk_pipeline_layout.h>
#include <rophy/vk/vk_render_pass.h>
#include <rophy/vk/vk_pipeline.h>
#include <rophy/vk/vk_framebuffer.h>
#include <rophy/vk/vk_command_pool.h>
#include <rophy/vk/vk_command_buffer.h>
#include <rophy/vk/vk_semaphore.h>

namespace rophy
{
namespace window
{
class EngineWindow : public BaseWindow
{
public:
  EngineWindow();

  EngineWindow(int width, int height);

  virtual ~EngineWindow() override;

  void Initialize() override;

  void Draw();

  void DeviceWaitIdle();

private:
  vk::Instance instance_;
  vk::Device device_;
  vk::Queue present_queue_;
  vk::Queue graphics_queue_;
  vk::Surface surface_;
  vk::Swapchain swapchain_;
  std::vector<vk::ImageView> swapchain_image_views_;
  vk::ShaderModule vertex_shader_module_;
  vk::ShaderModule fragment_shader_module_;
  vk::PipelineLayout pipeline_layout_;
  vk::RenderPass render_pass_;
  vk::Pipeline graphics_pipeline_;
  std::vector<vk::Framebuffer> swapchain_framebuffers_;
  vk::CommandPool command_pool_;
  std::vector<vk::CommandBuffer> command_buffers_;
  vk::Semaphore image_available_semaphore_;
  vk::Semaphore render_finished_semaphore_;
};
}
}

#endif // ROPHY_WINDOW_ENGINE_WINDOW_H_
