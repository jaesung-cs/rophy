#ifndef ROPHY_WINDOW_WINDOW_MANAGER_H_
#define ROPHY_WINDOW_WINDOW_MANAGER_H_

#include <vector>
#include <memory>
#include <type_traits>

#include "base_window.h"

namespace rophy
{
namespace window
{
class WindowManager
{
public:
  WindowManager();

  ~WindowManager();

private:
  template <class WindowType, typename Enabled, typename... Ts>
  std::shared_ptr<WindowType> CreateWindowImpl(Ts&&... args)
  {
    auto window = std::make_shared<WindowType>(std::forward<Ts>(args)...);
    windows_.push_back(window);
    return window;
  }

public:
  template <class WindowType, typename... Ts>
  std::shared_ptr<WindowType> CreateWindow(Ts&&... args)
  {
    return CreateWindowImpl<WindowType, std::enable_if_t<std::is_base_of_v<BaseWindow, WindowType>>>(std::forward<Ts>(args)...);
  }

  void Initialize();
  void Destroy();

  void ActivateWindows();

  void PollEvents();

private:
  std::vector<std::shared_ptr<BaseWindow>> windows_;
};
}
}

#endif // ROPHY_WINDOW_WINDOW_MANAGER_H_
