#ifndef ROPHY_VK_VK_SHADER_H_
#define ROPHY_VK_VK_SHADER_H_

#include <rophy/vk/vk_object.h>
#include <rophy/utils/printable.h>

#include <memory>

#include <vulkan/vulkan.h>

namespace rophy
{
namespace vk
{
class ShaderModuleCreator;

namespace impl
{
class ShaderModuleImpl : public vk::Object, public utils::Printable
{
  friend class ShaderModuleCreator;

public:
  ShaderModuleImpl() = delete;

  ShaderModuleImpl(VkDevice device, VkShaderModule shader_module);

  ~ShaderModuleImpl() override;

  void Destroy() override;

protected:
  void Print(std::ostream& out) const override;

private:
  VkShaderModule shader_module_ = nullptr;

  VkDevice device_ = nullptr;
};
}

using ShaderModule = std::shared_ptr<impl::ShaderModuleImpl>;
}
}

#endif // ROPHY_VK_VK_SHADER_H_
