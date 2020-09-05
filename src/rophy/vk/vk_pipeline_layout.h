#ifndef ROPHY_VK_VK_PIPELINE_LAYOUT_H_
#define ROPHY_VK_VK_PIPELINE_LAYOUT_H_

#include <rophy/vk/vk_object.h>
#include <rophy/utils/printable.h>

#include <memory>

#include <vulkan/vulkan.h>

namespace rophy
{
namespace vk
{
class PipelineLayoutCreator;

namespace impl
{
class PipelineLayoutImpl : public vk::Object, public utils::Printable
{
  friend class PipelineLayoutCreator;

public:
  PipelineLayoutImpl() = delete;

  PipelineLayoutImpl(VkDevice device, VkPipelineLayout pipeline_layout);

  ~PipelineLayoutImpl() override;

  void Destroy() override;

  operator VkPipelineLayout ()
  {
    return pipeline_layout_;
  }

protected:
  void Print(std::ostream& out) const override;

private:
  VkPipelineLayout pipeline_layout_ = nullptr;

  VkDevice device_ = nullptr;
};
}

using PipelineLayout = std::shared_ptr<impl::PipelineLayoutImpl>;
}
}

#endif // ROPHY_VK_VK_PIPELINE_LAYOUT_H_
