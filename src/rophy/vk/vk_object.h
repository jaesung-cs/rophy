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

  virtual void Destroy();

protected:
  void AddChildObject(std::shared_ptr<Object> child);

private:
  void DestroyRecursive();

private:
  std::vector<std::weak_ptr<Object>> children_;
};
}
}

#endif // ROPHY_VK_VK_OBJECT_H_
