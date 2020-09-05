#include <rophy/vk/vk_creator.h>

namespace rophy
{
namespace vk
{
void Creator::PrintStrings(std::ostream& out, const char* const* p, int count, int indent)
{
  auto indent_string = std::string(indent, ' ');

  for (int i = 0; i < count; i++)
    out << indent_string << p[i] << std::endl;
}

void Creator::PrintStrings(std::ostream& out, const std::vector<std::string>& s, int indent)
{
  auto indent_string = std::string(indent, ' ');

  for (const auto& str : s)
    out << indent_string << str << std::endl;
}

Creator::Creator() = default;

Creator::~Creator() = default;

void Creator::Print(std::ostream& out) const
{
  out << "Base Creator";
}
}
}
