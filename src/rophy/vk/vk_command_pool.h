#ifndef ROPHY_VK_VK_COMMAND_POOL_H_
#define ROPHY_VK_VK_COMMAND_POOL_H_

#include <rophy/vk/vk_object.h>
#include <rophy/utils/printable.h>

#include <vulkan/vulkan.h>

#include <rophy/vk/vk_device.h>

namespace rophy
{
namespace vk
{
class CommandPoolCreator;

namespace impl
{
class CommandPoolImpl : public vk::Object, public utils::Printable
{
  friend class CommandPoolCreator;

public:
  CommandPoolImpl() = delete;

  CommandPoolImpl(VkDevice device, VkCommandPool command_pool);

  ~CommandPoolImpl() override;

  void Destroy() override;

  operator VkCommandPool ()
  {
    return command_pool_;
  }

protected:
  void Print(std::ostream& out) const override;

private:
  VkCommandPool command_pool_ = nullptr;
  VkDevice device_ = nullptr;
};
}

using CommandPool = std::shared_ptr<impl::CommandPoolImpl>;
}
}

#endif // ROPHY_VK_VK_COMMAND_POOL_H_
