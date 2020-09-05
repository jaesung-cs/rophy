#include <rophy/vk/vk_object.h>

namespace rophy
{
namespace vk
{
Object::Object()
{
}

Object::~Object()
{
  DestroyRecursive();
}

void Object::Destroy()
{
}

void Object::DestroyRecursive()
{
  for (auto weak_child : children_)
  {
    auto child = weak_child.lock();

    if (child != nullptr)
      child->DestroyRecursive();
  }

  children_.clear();

  Destroy();
}

void Object::AddChildObject(std::shared_ptr<Object> child)
{
  children_.push_back(child);
}
}
}
