#ifndef ROPHY_VK_VK_SURFACE_H_
#define ROPHY_VK_VK_SURFACE_H_

#include <rophy/vk/vk_object.h>

#include <vulkan/vulkan.h>

namespace rophy
{
namespace vk
{
class SurfaceCreator;

namespace impl
{
class SurfaceImpl : public vk::Object
{
  friend class SurfaceCreator;

public:
  SurfaceImpl() = delete;

  SurfaceImpl(VkInstance instance, VkSurfaceKHR surface);

  ~SurfaceImpl() override;

  void Destroy() override;

  operator VkSurfaceKHR ()
  {
    return surface_;
  }

private:
  VkSurfaceKHR surface_ = nullptr;
  VkInstance instance_ = nullptr;
};
}

using Surface = std::shared_ptr<impl::SurfaceImpl>;
}
}

#endif // ROPHY_VK_VK_SURFACE_H_
