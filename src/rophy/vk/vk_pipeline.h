#ifndef ROPHY_VK_VK_PIPELINE_H_
#define ROPHY_VK_VK_PIPELINE_H_

#include <rophy/vk/vk_object.h>
#include <rophy/utils/printable.h>

#include <memory>

#include <vulkan/vulkan.h>

namespace rophy
{
namespace vk
{
class GraphicsPipelineCreator;

namespace impl
{
class PipelineImpl : public vk::Object, public utils::Printable
{
  friend class GraphicsPipelineCreator;

public:
  PipelineImpl() = delete;

  PipelineImpl(VkDevice device, VkPipeline pipeline);

  ~PipelineImpl() override;

  void Destroy() override;

protected:
  void Print(std::ostream& out) const override;

private:
  VkPipeline pipeline_ = nullptr;

  VkDevice device_ = nullptr;
};
}

using Pipeline = std::shared_ptr<impl::PipelineImpl>;
}
}

#endif // ROPHY_VK_VK_GRAPHICS_PIPELINE_H_
