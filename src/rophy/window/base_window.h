#ifndef ROPHY_WINDOW_WINDOW_BASE_H_
#define ROPHY_WINDOW_WINDOW_BASE_H_

#include <string>

#include <GLFW/glfw3.h>

#include <rophy/glsl/vec.h>

namespace rophy
{
namespace window
{
class BaseWindow
{
public:
  BaseWindow();

  BaseWindow(int width, int height);

  virtual ~BaseWindow();

  void Create();
  void DestroyWindow();

  bool IsActivated() const noexcept
  {
    return window_ != nullptr;
  }

  bool ShouldClose() const;

  void SwapBuffers();

  void SetTitle(const std::string& title);

  //
  // Event listeners
  //
  void ResizeEvent(int width, int height);
  void KeyboardEvent();


  //
  // Callback events
  //
  virtual void Initialize();
  virtual void Resize(int width, int height);
  virtual void Keyboard();


  auto GetPosition() const
  {
    return glsl::vec2(x_, y_);
  }

  auto GetSize() const
  {
    return glsl::vec2(width_, height_);
  }

  auto Width() const
  {
    return width_;
  }

  auto Height() const
  {
    return height_;
  }

protected:
  auto GetWindow() const
  {
    return window_;
  }

private:
  GLFWwindow* window_ = nullptr;

  // Window info
  int x_ = 100;
  int y_ = 100;
  int width_ = 800;
  int height_ = 600;
  std::string title_ = "Window";
};
}
}

#endif // ROPHY_WINDOW_WINDOW_BASE_H_
