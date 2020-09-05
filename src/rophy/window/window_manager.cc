#include <rophy/window/window_manager.h>

#include <GLFW/glfw3.h>

namespace rophy
{
namespace window
{
WindowManager::WindowManager()
{
}

WindowManager::~WindowManager()
{
}

void WindowManager::Initialize()
{
  glfwInit();

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
}

void WindowManager::Destroy()
{
  for (auto window : windows_)
  {
    window->DestroyWindow();
  }

  windows_.clear();

  glfwTerminate();
}

void WindowManager::ActivateWindows()
{
  for (auto window : windows_)
  {
    window->Create();
  }
}

void WindowManager::PollEvents()
{
  glfwPollEvents();
}
}
}
