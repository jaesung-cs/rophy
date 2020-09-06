#ifndef ROPHY_VK_VK_SEMAPHORE_CREATOR_H_
#define ROPHY_VK_VK_SEMAPHORE_CREATOR_H_

#include <rophy/utils/printable.h>

#include <vulkan/vulkan.h>

#include <rophy/vk/vk_semaphore.h>
#include <rophy/vk/vk_device.h>

namespace rophy
{
namespace vk
{
class SemaphoreCreator : public utils::Printable
{
public:
  SemaphoreCreator() = delete;

  explicit SemaphoreCreator(Device device);

  ~SemaphoreCreator();

  Semaphore Create();

protected:
  void Print(std::ostream& out) const override;

private:
  Device device_;

  VkSemaphoreCreateInfo create_info_{};
};
}
}

#endif // ROPHY_VK_VK_SEMAPHORE_CREATOR_H_
