#include <rophy/vk/vk_pipeline.h>

namespace rophy
{
namespace vk
{
namespace impl
{
PipelineImpl::PipelineImpl(VkDevice device, VkPipeline pipeline)
  : pipeline_(pipeline)
  , device_(device)
{
}

PipelineImpl::~PipelineImpl() = default;

void PipelineImpl::Destroy()
{
  if (pipeline_ != nullptr)
  {
    vkDestroyPipeline(device_, pipeline_, nullptr);
    pipeline_ = nullptr;
  }
}

void PipelineImpl::Print(std::ostream& out) const
{
  out << "VkPipeline";
}
}
}
}
