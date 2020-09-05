#ifndef ROPHY_VK_VK_EXTENSIONS_H_
#define ROPHY_VK_VK_EXTENSIONS_H_

#include <string>
#include <vector>
#include <iostream>

#include <vulkan/vulkan.h>

namespace rophy
{
namespace vk
{
class ExtensionLayers
{
public:
  ExtensionLayers();

  ~ExtensionLayers();

  void PrintExtensions() const;

  void PrintLayers() const;

private:
  void PrintExtensions(std::ostream& out) const;

  void PrintLayers(std::ostream& out) const;

  // Extensions
  uint32_t extension_count_ = 0;
  std::vector<VkExtensionProperties> extensions_;

  // Layers
  uint32_t layer_count_;
  std::vector<VkLayerProperties> layers_;

public:
  friend std::ostream& operator << (std::ostream& out, const ExtensionLayers& rhs)
  {
    rhs.PrintExtensions(out);
    out << std::endl;
    rhs.PrintLayers(out);

    return out;
  }
};
}
}

#endif // ROPHY_VK_VK_EXTENSIONS_H_
