#include <rophy/vk/vk_surface.h>

namespace rophy
{
namespace vk
{
namespace impl
{
SurfaceImpl::SurfaceImpl(VkInstance instance, VkSurfaceKHR surface)
  : surface_(surface)
  , instance_(instance)
{
}

SurfaceImpl::~SurfaceImpl() = default;

void SurfaceImpl::Destroy()
{
  if (surface_ != nullptr)
  {
    vkDestroySurfaceKHR(instance_, surface_, nullptr);
    surface_ = nullptr;
  }
}
}
}
}
