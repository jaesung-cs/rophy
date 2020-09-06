#ifndef ROPHY_VK_VK_SEMAPHORE_H_
#define ROPHY_VK_VK_SEMAPHORE_H_

#include <rophy/vk/vk_object.h>
#include <rophy/utils/printable.h>

#include <memory>

#include <vulkan/vulkan.h>

namespace rophy
{
namespace vk
{
class SemaphoreCreator;

namespace impl
{
class SemaphoreImpl : public vk::Object, public utils::Printable
{
  friend class SemaphoreCreator;

public:
  SemaphoreImpl() = delete;

  explicit SemaphoreImpl(VkDevice device, VkSemaphore semaphore_);

  ~SemaphoreImpl() override;

  void Destroy() override;

  operator VkSemaphore ()
  {
    return semaphore_;
  }

protected:
  void Print(std::ostream& out) const override;

private:
  VkSemaphore semaphore_ = nullptr;

  VkDevice device_ = nullptr;
};
}

using Semaphore = std::shared_ptr<impl::SemaphoreImpl>;
}
}

#endif // ROPHY_VK_VK_SEMAPHORE_H_
