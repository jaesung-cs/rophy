#ifndef ROPHY_VK_VK_EXCEPTION_H_
#define ROPHY_VK_VK_EXCEPTION_H_

#include <exception>
#include <string>

#include <vulkan/vulkan.h>

namespace rophy
{
namespace vk
{
class Exception : public std::exception
{
public:
  explicit Exception(const std::string& what_arg, VkResult result)
    : what_(what_arg), error_code_(result)
  {
  }

  const char* what() const override
  {
    return what_.c_str();
  }

  VkResult ErrorCode() const
  {
    return error_code_;
  }

private:
  std::string what_;
  VkResult error_code_;
};
}
}

#endif // ROPHY_VK_VK_EXCEPTION_H_
