#include <rophy/vk/vk_device_creator.h>

#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>

#include <rophy/vk/vk_exception.h>

namespace rophy
{
namespace vk
{
DeviceCreator::DeviceCreator(PhysicalDevice physical_device)
  : physical_device_(physical_device)
{
  create_info_.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

  create_info_.pEnabledFeatures = &required_features_;
}

DeviceCreator::~DeviceCreator()
{
}

void DeviceCreator::AddExtension(const std::string& extension_name)
{
  extension_names_.push_back(extension_name);
}

void DeviceCreator::AddLayer(const std::string& layer_name)
{
  layer_names_.push_back(layer_name);
}

void DeviceCreator::AddValidationLayer()
{
  AddLayer("VK_LAYER_KHRONOS_validation");
}

void DeviceCreator::AddGraphicsQueue(int num_queues)
{
  QueueCreateRequest request;
  request.type = QueueType::GRAPHICS;
  request.count = num_queues;

  queue_create_requests_.push_back(request);
}

Device DeviceCreator::Create()
{
  // Queues
  std::vector<int> queue_counts(physical_device_->NumQueueFamilies(), 0);
  queue_create_infos_.clear();
  for (auto queue_create_request : queue_create_requests_)
  {
    auto queue_family_index = physical_device_->GetQueueFamilyIndex(queue_create_request.type);
    auto queue_count = queue_create_request.count;

    VkDeviceQueueCreateInfo queue_create_info{};
    queue_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queue_create_info.queueFamilyIndex = queue_family_index;
    queue_create_info.queueCount = queue_create_request.count;
    queue_create_info.pQueuePriorities = queue_priorities_.data();
    queue_create_infos_.push_back(queue_create_info);

    queue_counts[queue_family_index] += queue_count;
  }

  create_info_.pQueueCreateInfos = queue_create_infos_.data();
  create_info_.queueCreateInfoCount = static_cast<uint32_t>(queue_create_infos_.size());

  // Extensions
  std::vector<const char*> extension_names;
  for (const auto& extension_name_string : extension_names_)
    extension_names.push_back(extension_name_string.c_str());

  create_info_.enabledExtensionCount = static_cast<uint32_t>(extension_names.size());
  create_info_.ppEnabledExtensionNames = extension_names.data();

  // Layers
  std::vector<const char*> layer_names;
  for (const auto& layer_name_string : layer_names_)
    layer_names.push_back(layer_name_string.c_str());

  create_info_.enabledLayerCount = static_cast<uint32_t>(layer_names.size());
  create_info_.ppEnabledLayerNames = layer_names.data();

  // Verbose log
  Print(std::cout);
  std::cout << std::endl;

  VkDevice device_handle;
  VkResult result;
  if ((result = vkCreateDevice(*physical_device_, &create_info_, nullptr, &device_handle)) != VK_SUCCESS)
    throw vk::Exception("Failed to create device.", result);

  auto device = std::make_shared<impl::DeviceImpl>(device_handle, queue_counts);
  physical_device_->AddChildObject(device);

  return device;
}

void DeviceCreator::Print(std::ostream& out) const
{
  out
    << "Device create info" << std::endl
    << "  enabledExtensionCount  : " << create_info_.enabledExtensionCount << std::endl
    << "  ppEnabledExtensionNames: " << std::endl;
  PrintStrings(out, create_info_.ppEnabledExtensionNames, create_info_.enabledExtensionCount, 4);
  out
    << "  enabledLayerCount      : " << create_info_.enabledLayerCount << std::endl
    << "  ppEnabledLayerNames    : " << std::endl;
  PrintStrings(out, create_info_.ppEnabledLayerNames, create_info_.enabledLayerCount, 4);
  out
    << "  queueCreateInfoCount: " << create_info_.queueCreateInfoCount << std::endl;

  std::vector<std::string> queue_create_info_strings;
  for (uint32_t i = 0; i < create_info_.queueCreateInfoCount; i++)
  {
    const auto& queue_create_info = create_info_.pQueueCreateInfos[i];

    {
      std::ostringstream sout;
      sout << "pQueueCreateInfo[" << i << "]:";
      queue_create_info_strings.emplace_back(sout.str());
    }

    {
      std::ostringstream sout;
      sout << "  queueFamilyIndex: " << queue_create_info.queueFamilyIndex;
      queue_create_info_strings.emplace_back(sout.str());
    }

    {
      std::ostringstream sout;
      sout << "  queueCount      : " << queue_create_info.queueCount;
      queue_create_info_strings.emplace_back(sout.str());
    }

    {
      std::ostringstream sout;
      sout << "  pQueuePriorities: [";
      for (uint32_t j = 0; j < queue_create_info.queueCount; j++)
      {
        sout << queue_create_info.pQueuePriorities[j];
        if (j + 1 < queue_create_info.queueCount)
          sout << ", ";
      }
      sout << "]";
      queue_create_info_strings.emplace_back(sout.str());
    }
  }
  PrintStrings(out, queue_create_info_strings, 2);
}
}
}
