#ifndef ROPHY_ENGINE_H_
#define ROPHY_ENGINE_H_

#include <memory>

#include <rophy/window/window_manager.h>
#include <rophy/window/engine_window.h>

namespace rophy
{
class Engine
{
public:
  Engine();

  ~Engine();

  void Initialize();

  void Run();

private:
  window::WindowManager window_manager_;

  std::shared_ptr<window::EngineWindow> engine_window_;
};
}

#endif // ROPHY_ENGINE_H_
