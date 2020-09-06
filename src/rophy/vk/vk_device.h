#ifndef ROPHY_VK_VK_DEVICE_H_
#define ROPHY_VK_VK_DEVICE_H_

#include <rophy/vk/vk_object.h>

#include <memory>

#include <vulkan/vulkan.h>

#include <rophy/vk/vk_queue.h>
#include <rophy/utils/printable.h>
#include <rophy/vk/vk_physical_device.h>

namespace rophy
{
namespace vk
{
class ImageViewCreator;
class ShaderModuleCreator;
class SwapchainCreator;
class GraphicsPipelineCreator;
class PipelineLayoutCreator;
class RenderPassCreator;
class FramebufferCreator;
class CommandPoolCreator;
class CommandBufferAllocator;
class SemaphoreCreator;

namespace impl
{
class DeviceImpl : public vk::Object, public utils::Printable
{
  friend class ImageViewCreator;
  friend class ShaderModuleCreator;
  friend class SwapchainCreator;
  friend class GraphicsPipelineCreator;
  friend class PipelineLayoutCreator;
  friend class RenderPassCreator;
  friend class FramebufferCreator;
  friend class CommandPoolCreator;
  friend class CommandBufferAllocator;
  friend class SemaphoreCreator;

public:
  DeviceImpl() = delete;

  DeviceImpl(const PhysicalDevice physical_device, VkDevice handle, const std::vector<int>& queue_counts);

  ~DeviceImpl() override;

  void Destroy() override;

  operator VkDevice ()
  {
    return device_;
  }

  const auto GetPhysicalDevice() const
  {
    return physical_device_;
  }

  auto GetQueue(int index) const
  {
    return queues_[index];
  }

protected:
  void Print(std::ostream& out) const override;

private:
  VkDevice device_ = nullptr;

  const PhysicalDevice physical_device_;

  std::vector<Queue> queues_;
};
}

using Device = ::std::shared_ptr<impl::DeviceImpl>;
}
}

#endif // ROPHY_VK_VK_DEVICE_H_
