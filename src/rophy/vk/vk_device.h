#ifndef ROPHY_VK_VK_DEVICE_H_
#define ROPHY_VK_VK_DEVICE_H_

#include <rophy/vk/vk_object.h>

#include <memory>

#include <vulkan/vulkan.h>

#include <rophy/vk/vk_queue.h>
#include <rophy/utils/printable.h>

namespace rophy
{
namespace vk
{
namespace impl
{
class DeviceImpl : public vk::Object, public utils::Printable
{
public:
  DeviceImpl() = delete;

  DeviceImpl(VkDevice handle, const std::vector<int>& queue_counts);

  ~DeviceImpl();

  void Destroy() override;

protected:
  void Print(std::ostream& out) const override;

private:
  VkDevice device_ = nullptr;

  std::vector<Queue> queues_;
};
}

using Device = ::std::shared_ptr<impl::DeviceImpl>;
}
}

#endif // ROPHY_VK_VK_DEVICE_H_
