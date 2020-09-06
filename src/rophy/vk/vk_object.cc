#include <rophy/vk/vk_object.h>

#include <iostream>

namespace rophy
{
namespace vk
{
Object::Object()
{
}

Object::~Object()
{
}

void Object::Destroy()
{
}

void Object::DestroyThis()
{
  DestroyChildren();
  Destroy();
}

void Object::DestroyChildren()
{
  for (auto weak_child : children_)
  {
    auto child = weak_child.lock();

    if (child != nullptr)
      child->DestroyThis();
  }

  children_.clear();
}

void Object::AddChildObject(std::shared_ptr<Object> child)
{
  children_.push_back(child);
}
}
}
