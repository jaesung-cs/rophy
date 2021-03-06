#ifndef ROPHY_VK_VK_QUEUE_H_
#define ROPHY_VK_VK_QUEUE_H_

#include <rophy/vk/vk_object.h>
#include <rophy/utils/printable.h>

#include <memory>

#include <vulkan/vulkan.h>

#include <rophy/vk/vk_semaphore.h>
#include <rophy/vk/vk_fence.h>
#include <rophy/vk/vk_swapchain.h>

namespace rophy
{
namespace vk
{
using BitFlags = uint32_t;

enum QueueType
{
  ANY = 0x0,
  GRAPHICS = 0x1,
  COMPUTE = 0x2,
  TRANSFER = 0x4,
};

namespace impl
{
//
// Forward declarations
//
class CommandBufferImpl;

class QueueImpl : public vk::Object, public utils::Printable
{
public:
  QueueImpl() = delete;

  explicit QueueImpl(VkQueue queue);

  ~QueueImpl() override;

  void Submit(std::shared_ptr<CommandBufferImpl> command_buffer, Semaphore wait_semaphore, Semaphore signal_semaphore, Fence fence);
  void Present(Swapchain swapchain, uint32_t image_index, Semaphore wait_semaphore);

protected:
  void Print(std::ostream& out) const override;

private:
  VkQueue queue_ = nullptr;
};
}

using Queue = std::shared_ptr<impl::QueueImpl>;
}
}

#endif // ROPHY_VK_VK_QUEUE_H_
