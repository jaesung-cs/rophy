#ifndef ROPHY_VK_VK_DEVICE_CREATOR_H_
#define ROPHY_VK_VK_DEVICE_CREATOR_H_

#include <vulkan/vulkan.h>

#include <rophy/vk/vk_device.h>
#include <rophy/vk/vk_physical_device.h>
#include <rophy/vk/vk_queue.h>
#include <rophy/utils/printable.h>

namespace rophy
{
namespace vk
{
class DeviceCreator : public utils::Printable
{
private:
  struct QueueCreateRequest
  {
    int type = QueueType::ANY;
    int count = 1;
  };

public:
  DeviceCreator() = delete;

  DeviceCreator(PhysicalDevice physical_device);

  ~DeviceCreator();

  void AddExtension(const std::string& extension_name);

  void AddLayer(const std::string& layer_name);
  void AddValidationLayer();

  void AddGraphicsQueue(int num_queues = 1);

  Device Create();

protected:
  void Print(std::ostream& out) const override;

private:
  PhysicalDevice physical_device_;

  VkDeviceCreateInfo create_info_{};
  std::vector<VkDeviceQueueCreateInfo> queue_create_infos_{};
  VkPhysicalDeviceFeatures required_features_{};

  std::vector<std::string> extension_names_;
  std::vector<std::string> layer_names_;

  std::vector<float> queue_priorities_ = std::vector<float>(16, 1.f);
  std::vector<QueueCreateRequest> queue_create_requests_;
};
}
}

#endif // ROPHY_VK_VK_DEVICE_CREATOR_H_
