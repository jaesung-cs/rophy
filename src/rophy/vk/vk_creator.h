#ifndef ROPHY_VK_VK_CREATOR_H_
#define ROPHY_VK_VK_CREATOR_H_

#include <iostream>
#include <vector>
#include <string>

#include <vulkan/vulkan.h>

namespace rophy
{
namespace vk
{
class Creator
{
protected:
  static void PrintStrings(std::ostream& out, const char* const* p, int count, int indent = 0);
  static void PrintStrings(std::ostream& out, const std::vector<std::string>& s, int indent = 0);

public:
  Creator();

  virtual ~Creator();

  void Print() const
  {
    Print(std::cout);
  }

protected:
  virtual void Print(std::ostream& out) const;

public:
  friend std::ostream& operator << (std::ostream& out, const Creator& rhs)
  {
    rhs.Print(out);

    return out;
  }
};
}
}

#endif // ROPHY_VK_VK_CREATOR_H_
