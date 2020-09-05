#include <rophy/vk/vk_surface_creator.h>

#include <GLFW/glfw3.h>

#include <rophy/vk/vk_exception.h>

namespace rophy
{
namespace vk
{
SurfaceCreator::SurfaceCreator(Instance instance, GLFWwindow* window)
  : instance_(instance)
  , window_(window)
{
}

SurfaceCreator::~SurfaceCreator() = default;

Surface SurfaceCreator::Create()
{
  VkSurfaceKHR surface_handle;
  VkResult result;
  if ((result = glfwCreateWindowSurface(*instance_, window_, nullptr, &surface_handle)) != VK_SUCCESS)
    throw Exception("Failed to create GLFW window vulkan surface.", result);

  Surface surface = std::make_shared<impl::SurfaceImpl>(*instance_, surface_handle);

  return surface;
}
}
}
