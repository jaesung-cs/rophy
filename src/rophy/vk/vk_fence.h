#ifndef ROPHY_VK_VK_FENCE_H_
#define ROPHY_VK_VK_FENCE_H_

#include <rophy/vk/vk_object.h>
#include <rophy/utils/printable.h>

#include <memory>

#include <vulkan/vulkan.h>

namespace rophy
{
namespace vk
{
class FenceCreator;

namespace impl
{
class FenceImpl : public vk::Object, public utils::Printable
{
  friend class FenceCreator;

public:
  FenceImpl() = delete;

  explicit FenceImpl(VkDevice device, VkFence fence);

  ~FenceImpl() override;

  void Destroy() override;

  operator VkFence ()
  {
    return fence_;
  }

  void Wait();
  void Reset();

protected:
  void Print(std::ostream& out) const override;

private:
  VkFence fence_ = nullptr;

  VkDevice device_ = nullptr;
};
}

using Fence = std::shared_ptr<impl::FenceImpl>;
}
}

#endif // ROPHY_VK_VK_FENCE_H_
