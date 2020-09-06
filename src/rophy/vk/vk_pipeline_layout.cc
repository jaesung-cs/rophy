#include <rophy/vk/vk_pipeline_layout.h>

namespace rophy
{
namespace vk
{
namespace impl
{
PipelineLayoutImpl::PipelineLayoutImpl(VkDevice device, VkPipelineLayout pipeline_layout)
  : pipeline_layout_(pipeline_layout)
  , device_(device)
{
}

PipelineLayoutImpl::~PipelineLayoutImpl()
{
  DestroyThis();
}

void PipelineLayoutImpl::Destroy()
{
  if (pipeline_layout_ != nullptr)
  {
    vkDestroyPipelineLayout(device_, pipeline_layout_, nullptr);
    pipeline_layout_ = nullptr;
  }
}

void PipelineLayoutImpl::Print(std::ostream& out) const
{
  out << "VkPipelineLayout";
}
}
}
}
