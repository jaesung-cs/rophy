#include <rophy/vk/vk_shader_module.h>

namespace rophy
{
namespace vk
{
namespace impl
{
ShaderModuleImpl::ShaderModuleImpl(VkDevice device, VkShaderModule shader_module)
  : shader_module_(shader_module)
  , device_(device)
{
}

ShaderModuleImpl::~ShaderModuleImpl() = default;

void ShaderModuleImpl::Destroy()
{
  if (shader_module_ != nullptr)
  {
    vkDestroyShaderModule(device_, shader_module_, nullptr);
    shader_module_ = nullptr;
  }
}

void ShaderModuleImpl::Print(std::ostream& out) const
{
  out << "VkImageView";
}
}
}
}
