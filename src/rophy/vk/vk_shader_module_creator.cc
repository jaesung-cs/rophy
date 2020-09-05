#include <rophy/vk/vk_shader_module_creator.h>

#include <fstream>
#include <algorithm>

#include <rophy/vk/vk_exception.h>

namespace rophy
{
namespace vk
{
namespace
{
std::vector<char> ReadFile(const std::string& filename)
{
  std::ifstream file(filename, std::ios::ate | std::ios::binary);

  if (!file.is_open())
    throw std::runtime_error("Failed to open file.");

  auto file_size = static_cast<size_t>(file.tellg());
  std::vector<char> buffer(file_size);

  file.seekg(0);
  file.read(buffer.data(), file_size);

  file.close();

  return buffer;
}
}

ShaderModuleCreator::ShaderModuleCreator(Device device, const std::string& filename)
  : device_(device)
{
  code_ = ReadFile(filename);

  create_info_.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
  create_info_.codeSize = code_.size();
  create_info_.pCode = reinterpret_cast<const uint32_t*>(code_.data());
}

ShaderModuleCreator::~ShaderModuleCreator()
{
}

ShaderModule ShaderModuleCreator::Create()
{
  // Verbose log
  Print(std::cout);
  std::cout << std::endl;

  VkShaderModule shader_module_handle;
  VkResult result;
  if ((result = vkCreateShaderModule(*device_, &create_info_, nullptr, &shader_module_handle)) != VK_SUCCESS)
    throw vk::Exception("Failed to create shader module.", result);

  auto shader_module = std::make_shared<impl::ShaderModuleImpl>(*device_, shader_module_handle);
  device_->AddChildObject(shader_module);

  return shader_module;
}

void ShaderModuleCreator::Print(std::ostream& out) const
{
  out
    << "ShaderModule create info" << std::endl
    << "  codeSize: " << create_info_.codeSize << std::endl;
}
}
}
