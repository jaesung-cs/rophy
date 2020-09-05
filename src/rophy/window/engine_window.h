#ifndef ROPHY_WINDOW_ENGINE_WINDOW_H_
#define ROPHY_WINDOW_ENGINE_WINDOW_H_

#include "base_window.h"

#include <rophy/vk/vk_instance.h>
#include <rophy/vk/vk_device.h>

namespace rophy
{
namespace window
{
class EngineWindow : public BaseWindow
{
public:
  EngineWindow();

  EngineWindow(int width, int height);

  virtual ~EngineWindow() override;

  void Initialize() override;

private:
  vk::Instance vk_instance_;
  vk::Device vk_device_;
};
}
}

#endif // ROPHY_WINDOW_ENGINE_WINDOW_H_
