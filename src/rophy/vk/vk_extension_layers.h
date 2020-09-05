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
  // Instance extensions & layers
  ExtensionLayers();

  // Physical device extensions & layers
  explicit ExtensionLayers(VkPhysicalDevice physical_device);

  ~ExtensionLayers();

  void PrintExtensions() const;

  void PrintLayers() const;

private:
  void PrintExtensions(std::ostream& out) const;

  void PrintLayers(std::ostream& out) const;

  bool is_device_ = false;

  // Extensions
  uint32_t extension_count_ = 0;
  std::vector<VkExtensionProperties> extensions_;

  // Layers
  uint32_t layer_count_ = 0;
  std::vector<VkLayerProperties> layers_;

public:
  friend std::ostream& operator << (std::ostream& out, const ExtensionLayers& rhs)
  {
    rhs.PrintExtensions(out);
    rhs.PrintLayers(out);

    return out;
  }
};
}
}

#endif // ROPHY_VK_VK_EXTENSIONS_H_
