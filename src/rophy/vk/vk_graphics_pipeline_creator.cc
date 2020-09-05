#include <rophy/vk/vk_graphics_pipeline_creator.h>

#include <fstream>
#include <algorithm>

#include <rophy/vk/vk_exception.h>

namespace rophy
{
namespace vk
{
GraphicsPipelineCreator::GraphicsPipelineCreator(Device device)
  : device_(device)
  , shader_stages_(2, VkPipelineShaderStageCreateInfo{})
{
  vertex_input_info_.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
  vertex_input_info_.vertexBindingDescriptionCount = 0;
  vertex_input_info_.pVertexBindingDescriptions = nullptr;
  vertex_input_info_.vertexAttributeDescriptionCount = 0;
  vertex_input_info_.pVertexAttributeDescriptions = nullptr;

  input_assembly_.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
  input_assembly_.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
  input_assembly_.primitiveRestartEnable = VK_FALSE;

  viewport_.x = 0.0f;
  viewport_.y = 0.0f;
  viewport_.minDepth = 0.0f;
  viewport_.maxDepth = 1.0f;

  scissor_.offset = { 0, 0 };

  viewport_state_.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
  viewport_state_.viewportCount = 1;
  viewport_state_.pViewports = &viewport_;
  viewport_state_.scissorCount = 1;
  viewport_state_.pScissors = &scissor_;

  rasterizer_.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
  rasterizer_.depthClampEnable = VK_FALSE;
  rasterizer_.rasterizerDiscardEnable = VK_FALSE;
  rasterizer_.polygonMode = VK_POLYGON_MODE_FILL;
  rasterizer_.lineWidth = 1.0f;
  rasterizer_.cullMode = VK_CULL_MODE_BACK_BIT;
  rasterizer_.frontFace = VK_FRONT_FACE_CLOCKWISE;
  rasterizer_.depthBiasEnable = VK_FALSE;
  rasterizer_.depthBiasConstantFactor = 0.0f;
  rasterizer_.depthBiasClamp = 0.0f;
  rasterizer_.depthBiasSlopeFactor = 0.0f;

  multisampling_.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
  multisampling_.sampleShadingEnable = VK_FALSE;
  multisampling_.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
  multisampling_.minSampleShading = 1.0f;
  multisampling_.pSampleMask = nullptr;
  multisampling_.alphaToCoverageEnable = VK_FALSE;
  multisampling_.alphaToOneEnable = VK_FALSE;

  color_blend_attachment_.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
  color_blend_attachment_.blendEnable = VK_TRUE;
  color_blend_attachment_.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
  color_blend_attachment_.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
  color_blend_attachment_.colorBlendOp = VK_BLEND_OP_ADD;
  color_blend_attachment_.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
  color_blend_attachment_.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
  color_blend_attachment_.alphaBlendOp = VK_BLEND_OP_ADD;

  color_blending_.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
  color_blending_.logicOpEnable = VK_FALSE;
  color_blending_.logicOp = VK_LOGIC_OP_COPY;
  color_blending_.attachmentCount = 1;
  color_blending_.pAttachments = &color_blend_attachment_;
  color_blending_.blendConstants[0] = 0.0f;
  color_blending_.blendConstants[1] = 0.0f;
  color_blending_.blendConstants[2] = 0.0f;
  color_blending_.blendConstants[3] = 0.0f;

  dynamic_state_.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
  dynamic_state_.dynamicStateCount = 2;
  dynamic_state_.pDynamicStates = dynamic_states_;

  create_info_.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
  create_info_.stageCount = 2;
  create_info_.pStages = shader_stages_.data();
  create_info_.pVertexInputState = &vertex_input_info_;
  create_info_.pInputAssemblyState = &input_assembly_;
  create_info_.pViewportState = &viewport_state_;
  create_info_.pRasterizationState = &rasterizer_;
  create_info_.pMultisampleState = &multisampling_;
  create_info_.pDepthStencilState = nullptr;
  create_info_.pColorBlendState = &color_blending_;
  create_info_.pDynamicState = nullptr;

  create_info_.basePipelineHandle = VK_NULL_HANDLE;
  create_info_.basePipelineIndex = -1;
}

GraphicsPipelineCreator::~GraphicsPipelineCreator()
{
}

void GraphicsPipelineCreator::SetVertexShader(ShaderModule shader_module)
{
  shader_stages_[0].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
  shader_stages_[0].stage = VK_SHADER_STAGE_VERTEX_BIT;
  shader_stages_[0].module = *shader_module;
  shader_stages_[0].pName = "main";
}

void GraphicsPipelineCreator::SetFragmentShader(ShaderModule shader_module)
{
  shader_stages_[1].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
  shader_stages_[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
  shader_stages_[1].module = *shader_module;
  shader_stages_[1].pName = "main";
}

void GraphicsPipelineCreator::SetExtent(uint32_t width, uint32_t height)
{
  viewport_.width = static_cast<float>(width);
  viewport_.height = static_cast<float>(height);
  scissor_.extent = { width, height };
}

void GraphicsPipelineCreator::SetPipelineLayout(PipelineLayout pipeline_layout)
{
  create_info_.layout = *pipeline_layout;
}

void GraphicsPipelineCreator::SetRenderPass(RenderPass render_pass)
{
  create_info_.renderPass = *render_pass;
  create_info_.subpass = 0;
}

Pipeline GraphicsPipelineCreator::Create()
{
  // Verbose log
  Print(std::cout);
  std::cout << std::endl;

  VkPipeline pipeline_handle;
  VkResult result;
  if ((result = vkCreateGraphicsPipelines(*device_, VK_NULL_HANDLE, 1, &create_info_, nullptr, &pipeline_handle)) != VK_SUCCESS)
    throw vk::Exception("Failed to create graphics pipeline.", result);

  auto pipeline = std::make_shared<impl::PipelineImpl>(*device_, pipeline_handle);
  device_->AddChildObject(pipeline);

  return pipeline;
}

void GraphicsPipelineCreator::Print(std::ostream& out) const
{
  out
    << "GraphicsPipeline create info" << std::endl;
}
}
}
