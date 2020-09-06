#include <rophy/window/base_window.h>

namespace rophy
{
namespace window
{
//
// Callbacks
//
namespace
{
void ResizeCallback(GLFWwindow* window, int width, int height)
{
  auto base_window = static_cast<BaseWindow*>(glfwGetWindowUserPointer(window));
  base_window->ResizeEvent(width, height);
}

void KeyCallback(GLFWwindow* window, int, int, int, int)
{
  auto base_window = static_cast<BaseWindow*>(glfwGetWindowUserPointer(window));
  base_window->KeyboardEvent();
}
}

BaseWindow::BaseWindow()
{
}

BaseWindow::BaseWindow(int width, int height)
  : width_(width), height_(height)
{
}

BaseWindow::~BaseWindow()
{
}

void BaseWindow::Create()
{
  glfw_window_ = glfwCreateWindow(width_, height_, title_.c_str(), nullptr, nullptr);

  glfwSetWindowPos(glfw_window_, x_, y_);

  // Register callbacks
  glfwSetWindowUserPointer(glfw_window_, this);
  glfwSetWindowSizeCallback(glfw_window_, ResizeCallback);
  glfwSetKeyCallback(glfw_window_, KeyCallback);

  Initialize();
}

void BaseWindow::DestroyWindow()
{
  glfwDestroyWindow(glfw_window_);
  glfw_window_ = nullptr;
}

bool BaseWindow::ShouldClose() const
{
  return glfwWindowShouldClose(glfw_window_);
}

void BaseWindow::SwapBuffers()
{
  glfwSwapBuffers(glfw_window_);
}

void BaseWindow::SetTitle(const std::string& title)
{
  if (IsActivated())
  {
    glfwSetWindowTitle(glfw_window_, title.c_str());
  }

  title_ = title;
}

void BaseWindow::ResizeEvent(int width, int height)
{
  width_ = width;
  height_ = height;

  Resize(width, height);
}

void BaseWindow::KeyboardEvent()
{
  Keyboard();
}

void BaseWindow::Initialize()
{
}

void BaseWindow::Resize(int width, int height)
{
}

void BaseWindow::Keyboard()
{
}
}
}
