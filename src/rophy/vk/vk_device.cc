#include <rophy/vk/vk_device.h>

#include <sstream>
#include <iomanip>

namespace rophy
{
namespace vk
{
namespace impl
{
DeviceImpl::DeviceImpl(const PhysicalDevice physical_device, VkDevice handle, const std::vector<int>& queue_counts)
  : device_(handle)
  , physical_device_(physical_device)
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

DeviceImpl::~DeviceImpl()
{
  DestroyThis();
}

void DeviceImpl::Destroy()
{
  if (device_ != nullptr)
  {
    vkDestroyDevice(device_, nullptr);
    device_ = nullptr;
  }
}

void DeviceImpl::Print(std::ostream& out) const
{
  out
    << "VkDevice" << std::endl
    << "  Queues:" << std::endl;

  std::vector<std::string> queue_strings;
  for (int i = 0; i < queues_.size(); i++)
  {
    std::ostringstream sout;
    sout << "Index " << std::setw(2) << i << ": " << *queues_[i];
    queue_strings.emplace_back(sout.str());
  }
  PrintStrings(out, queue_strings, 4);
}
}
}
}
