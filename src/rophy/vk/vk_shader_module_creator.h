#ifndef ROPHY_VK_VK_SHADER_MODULE_CREATOR_H_
#define ROPHY_VK_VK_SHADER_MODULE_CREATOR_H_

#include <rophy/utils/printable.h>

#include <vulkan/vulkan.h>

#include <rophy/vk/vk_device.h>
#include <rophy/vk/vk_shader_module.h>

namespace rophy
{
namespace vk
{
class ShaderModuleCreator : public utils::Printable
{
public:
  ShaderModuleCreator() = delete;

  ShaderModuleCreator(Device device, const std::string& filename);

  ~ShaderModuleCreator();

  ShaderModule Create();

protected:
  void Print(std::ostream& out) const override;

private:
  Device device_;

  VkShaderModuleCreateInfo create_info_{};

  std::vector<char> code_;
};
}
}

#endif // ROPHY_VK_VK_SHADER_MODULE_CREATOR_H_
