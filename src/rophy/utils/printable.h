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
private:
  static bool IsEndline(char c)
  {
    return c == '\n';
  }

protected:
  static void PrintString(std::ostream& out, const std::string& s, int indent = 0)
  {
    auto indent_string = std::string(indent, ' ');

    bool line_begin = true;
    for (auto c : s)
    {
      if (IsEndline(c))
      {
        out << std::endl;
        line_begin = true;
      }
      else
      {
        if (line_begin)
        {
          line_begin = false;
          out << indent_string;
        }
        out << c;
      }
    }
  }

  static void PrintStrings(std::ostream& out, const char* const* p, int count, int indent = 0)
  {
    auto indent_string = std::string(indent, ' ');

    for (int i = 0; i < count; i++)
    {
      PrintString(out, p[i], indent);
      out << std::endl;
    }
  }

  static void PrintStrings(std::ostream& out, const std::vector<std::string>& s, int indent = 0)
  {
    for (const auto& str : s)
    {
      PrintString(out, str, indent);
      out << std::endl;
    }
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
