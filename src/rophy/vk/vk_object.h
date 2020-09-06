#ifndef ROPHY_VK_VK_OBJECT_H_
#define ROPHY_VK_VK_OBJECT_H_

#include <memory>
#include <vector>

namespace rophy
{
namespace vk
{
class Object
{
public:
  Object();

  virtual ~Object();

  void DestroyThis();

protected:
  virtual void Destroy();

  void AddChildObject(std::shared_ptr<Object> child);
  void DestroyChildren();

private:
  std::vector<std::weak_ptr<Object>> children_;
};
}
}

#endif // ROPHY_VK_VK_OBJECT_H_
