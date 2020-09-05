#ifndef ROPHY_VK_VK_INSTANCE_CREATOR_H_
#define ROPHY_VK_VK_INSTANCE_CREATOR_H_

#include <vulkan/vulkan.h>

#include <rophy/vk/vk_instance.h>
#include <rophy/vk/vk_creator.h>

namespace rophy
{
namespace vk
{
class InstanceCreator : public Creator
{
public:
  InstanceCreator();

  ~InstanceCreator();

  void AddExtension(const std::string& extension_name);
  void AddGlfwRequiredExtensions();

  void AddLayer(const std::string& layer_name);
  void AddValidationLayer();
  bool IsValidationLayerEnabled() const
  {
    return is_validation_layer_enabled_;
  }

  Instance Create();

protected:
  void Print(std::ostream& out) const override;

private:
  VkApplicationInfo app_info_{};
  VkInstanceCreateInfo create_info_{};
  VkDebugUtilsMessengerCreateInfoEXT debug_messenger_create_info_{};

  bool is_validation_layer_enabled_ = false;

  std::vector<std::string> extension_names_;
  std::vector<std::string> layer_names_;
};
}
}

#endif // ROPHY_VK_VK_INSTANCE_CREATOR_H_
