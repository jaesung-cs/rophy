#include <rophy/vk/vk_semaphore_creator.h>

#include <iostream>

#include <rophy/vk/vk_exception.h>

namespace rophy
{
namespace vk
{
SemaphoreCreator::SemaphoreCreator(Device device)
  : device_(device)
{
  create_info_.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
}

SemaphoreCreator::~SemaphoreCreator()
{
}

Semaphore SemaphoreCreator::Create()
{
  // Verbose log
  Print(std::cout);
  std::cout << std::endl;

  VkSemaphore semaphore_handle;
  VkResult result;
  if ((result = vkCreateSemaphore(*device_, &create_info_, nullptr, &semaphore_handle)) != VK_SUCCESS)
    throw vk::Exception("Failed to create semaphore.", result);

  auto semaphore = std::make_shared<impl::SemaphoreImpl>(*device_, semaphore_handle);
  device_->AddChildObject(semaphore);

  return semaphore;
}

void SemaphoreCreator::Print(std::ostream& out) const
{
  out
    << "Semaphore create info" << std::endl;
}
}
}
