#ifndef ROPHY_VK_VK_INSTANCE_H_
#define ROPHY_VK_VK_INSTANCE_H_

#include <memory>
#include <vector>
#include <string>

#include <vulkan/vulkan.h>

namespace rophy
{
namespace vk
{
class InstanceCreator;

namespace impl
{
class InstanceImpl
{
  friend class InstanceCreator;

public:
  InstanceImpl();

  ~InstanceImpl();

  operator VkInstance ()
  {
    return instance_;
  }

  auto& DebugMessenger()
  {
    return debug_messenger_;
  }

private:
  VkInstance instance_ = nullptr;
  VkDebugUtilsMessengerEXT debug_messenger_ = nullptr;
};
}

using Instance = ::std::shared_ptr<impl::InstanceImpl>;
}
}

#endif // ROPHY_VK_VK_INSTANCE_H_
