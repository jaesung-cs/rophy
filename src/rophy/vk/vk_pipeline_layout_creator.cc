#include <rophy/vk/vk_pipeline_layout_creator.h>

#include <iostream>

#include <rophy/vk/vk_exception.h>

namespace rophy
{
namespace vk
{
PipelineLayoutCreator::PipelineLayoutCreator(Device device)
  : device_(device)
{
  create_info_.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
  create_info_.setLayoutCount = 0;
  create_info_.pSetLayouts = nullptr;
  create_info_.pushConstantRangeCount = 0;
  create_info_.pPushConstantRanges = nullptr;
}

PipelineLayoutCreator::~PipelineLayoutCreator()
{
}

PipelineLayout PipelineLayoutCreator::Create()
{
  // Verbose log
  Print(std::cout);
  std::cout << std::endl;

  VkPipelineLayout pipeline_layout_handle;
  VkResult result;
  if ((result = vkCreatePipelineLayout(*device_, &create_info_, nullptr, &pipeline_layout_handle)) != VK_SUCCESS)
    throw vk::Exception("Failed to create pipeline layout.", result);

  auto pipeline_layout = std::make_shared<impl::PipelineLayoutImpl>(*device_, pipeline_layout_handle);
  device_->AddChildObject(pipeline_layout);

  return pipeline_layout;
}

void PipelineLayoutCreator::Print(std::ostream& out) const
{
  out
    << "PipelineLayout create info" << std::endl;
}
}
}
