#include <rophy/vk/vk_device.h>

namespace rophy
{
namespace vk
{
namespace impl
{
DeviceImpl::DeviceImpl(VkDevice handle, const std::vector<int>& queue_counts)
  : device_(handle)
{
  for (int i = 0; i < queue_counts.size(); i++)
  {
    for (int j = 0; j < queue_counts[i]; j++)
    {
      VkQueue queue_handle;
      vkGetDeviceQueue(device_, i, j, &queue_handle);

      queues_.push_back(std::make_shared<impl::QueueImpl>(queue_handle));
    }
  }
}

DeviceImpl::~DeviceImpl() = default;

void DeviceImpl::Destroy()
{
  vkDestroyDevice(device_, nullptr);
}
}
}
}
