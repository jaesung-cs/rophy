#ifndef ROPHY_VK_VK_FRAMEBUFFER_H_
#define ROPHY_VK_VK_FRAMEBUFFER_H_

#include <rophy/vk/vk_object.h>
#include <rophy/utils/printable.h>

#include <vulkan/vulkan.h>

#include <rophy/vk/vk_device.h>

namespace rophy
{
namespace vk
{
class FramebufferCreator;

namespace impl
{
class FramebufferImpl : public vk::Object, public utils::Printable
{
  friend class FramebufferCreator;

public:
  FramebufferImpl() = delete;

  FramebufferImpl(VkDevice device, VkFramebuffer framebuffer);

  ~FramebufferImpl() override;

  void Destroy() override;

  operator VkFramebuffer ()
  {
    return framebuffer_;
  }

protected:
  void Print(std::ostream& out) const override;

private:
  VkFramebuffer framebuffer_ = nullptr;
  VkDevice device_ = nullptr;
};
}

using Framebuffer = std::shared_ptr<impl::FramebufferImpl>;
}
}

#endif // ROPHY_VK_VK_FRAMEBUFFER_H_
