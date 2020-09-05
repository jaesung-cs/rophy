#ifndef ROPHY_VK_VK_GRAPHICS_PIPELINE_CREATOR_H_
#define ROPHY_VK_VK_GRAPHICS_PIPELINE_CREATOR_H_

#include <rophy/utils/printable.h>

#include <vulkan/vulkan.h>

#include <rophy/vk/vk_device.h>
#include <rophy/vk/vk_pipeline.h>
#include <rophy/vk/vk_shader_module.h>
#include <rophy/vk/vk_pipeline_layout.h>
#include <rophy/vk/vk_render_pass.h>

namespace rophy
{
namespace vk
{
class GraphicsPipelineCreator : public utils::Printable
{
public:
  GraphicsPipelineCreator() = delete;

  explicit GraphicsPipelineCreator(Device device);

  ~GraphicsPipelineCreator();

  void SetVertexShader(ShaderModule shader_module);
  void SetFragmentShader(ShaderModule shader_module);
  void SetExtent(uint32_t width, uint32_t height);
  void SetPipelineLayout(PipelineLayout pipeline_layout);
  void SetRenderPass(RenderPass render_pass);

  Pipeline Create();

protected:
  void Print(std::ostream& out) const override;

private:
  Device device_;

  VkGraphicsPipelineCreateInfo create_info_{};

  std::vector<VkPipelineShaderStageCreateInfo> shader_stages_;
  VkPipelineVertexInputStateCreateInfo vertex_input_info_{};
  VkPipelineInputAssemblyStateCreateInfo input_assembly_{};
  VkViewport viewport_{};
  VkRect2D scissor_{};
  VkPipelineViewportStateCreateInfo viewport_state_{};
  VkPipelineRasterizationStateCreateInfo rasterizer_{};
  VkPipelineMultisampleStateCreateInfo multisampling_{};
  VkPipelineColorBlendAttachmentState color_blend_attachment_{};
  VkPipelineColorBlendStateCreateInfo color_blending_{};
  VkDynamicState dynamic_states_[2] = {
    VK_DYNAMIC_STATE_VIEWPORT,
    VK_DYNAMIC_STATE_LINE_WIDTH
  };
  VkPipelineDynamicStateCreateInfo dynamic_state_{};
};
}
}

#endif // ROPHY_VK_VK_GRAPHICS_PIPELINE_CREATOR_H_
