#ifndef ROPHY_VK_VK_PIPELINE_LAYOUT_CREATOR_H_
#define ROPHY_VK_VK_PIPELINE_LAYOUT_CREATOR_H_

#include <rophy/utils/printable.h>

#include <vulkan/vulkan.h>

#include <rophy/vk/vk_device.h>
#include <rophy/vk/vk_pipeline_layout.h>

namespace rophy
{
namespace vk
{
class PipelineLayoutCreator : public utils::Printable
{
public:
  PipelineLayoutCreator() = delete;

  explicit PipelineLayoutCreator(Device device);

  ~PipelineLayoutCreator();

  PipelineLayout Create();

protected:
  void Print(std::ostream& out) const override;

private:
  Device device_;

  VkPipelineLayoutCreateInfo create_info_{};
};
}
}

#endif // ROPHY_VK_VK_PIPELINE_LAYOUT_CREATOR_H_
