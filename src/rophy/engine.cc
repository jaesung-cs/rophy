#include <rophy/engine.h>

namespace rophy
{
Engine::Engine()
{
}

Engine::~Engine()
{
}

void Engine::Initialize()
{
  window_manager_.Initialize();
  engine_window_ = window_manager_.CreateWindow<window::EngineWindow>(1600, 900);
}

void Engine::Run()
{
  window_manager_.ActivateWindows();

  while (!engine_window_->ShouldClose())
  {
    window_manager_.PollEvents();

    engine_window_->Draw();

    engine_window_->SwapBuffers();
  }

  window_manager_.Destroy();
}
}
