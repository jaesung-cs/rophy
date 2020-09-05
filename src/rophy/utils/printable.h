#ifndef ROPHY_UTILS_PRINTABLE_H_
#define ROPHY_UTILS_PRINTABLE_H_

#include <iostream>
#include <vector>
#include <string>

namespace rophy
{
namespace utils
{
class Printable
{
protected:
  static void PrintStrings(std::ostream& out, const char* const* p, int count, int indent = 0)
  {
    auto indent_string = std::string(indent, ' ');

    for (int i = 0; i < count; i++)
      out << indent_string << p[i] << std::endl;
  }

  static void PrintStrings(std::ostream& out, const std::vector<std::string>& s, int indent = 0)
  {
    auto indent_string = std::string(indent, ' ');

    for (const auto& str : s)
      out << indent_string << str << std::endl;
  }

public:
  void Print() const
  {
    Print(std::cout);
  }

protected:
  virtual void Print(std::ostream& out) const
  {
    out << "Printable";
  }

private:
  friend std::ostream& operator << (std::ostream& out, const Printable& rhs)
  {
    rhs.Print(out);

    return out;
  }
};
}
}

#endif // ROPHY_UTILS_PRINTABLE_H_
