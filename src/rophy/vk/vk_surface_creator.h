#ifndef ROPHY_VK_VK_SURFACE_CREATOR_H_
#define ROPHY_VK_VK_SURFACE_CREATOR_H_

#include <vulkan/vulkan.h>

#include <rophy/vk/vk_instance.h>
#include <rophy/vk/vk_surface.h>

//
// Forward declarations
//
struct GLFWwindow;

namespace rophy
{
namespace vk
{
class SurfaceCreator
{
public:
  SurfaceCreator() = delete;

  SurfaceCreator(Instance instance, GLFWwindow* window);

  ~SurfaceCreator();

  Surface Create();

private:
  const Instance instance_;
  GLFWwindow* window_;
};
}
}

#endif // ROPHY_VK_VK_SURFACE_CREATOR_H_
