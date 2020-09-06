#include <rophy/vk/vk_queue.h>

#include <iostream>

#include <rophy/vk/vk_command_buffer.h>
#include <rophy/vk/vk_exception.h>

namespace rophy
{
namespace vk
{
namespace impl
{
QueueImpl::QueueImpl(VkQueue queue)
  : queue_(queue)
{
}

QueueImpl::~QueueImpl() = default;

void QueueImpl::Submit(std::shared_ptr<CommandBufferImpl> command_buffer, Semaphore wait_semaphore, Semaphore signal_semaphore)
{
  VkSubmitInfo submit_info{};
  submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

  VkSemaphore wait_semaphores[] = { *wait_semaphore };
  VkPipelineStageFlags wait_stages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
  submit_info.waitSemaphoreCount = 1;
  submit_info.pWaitSemaphores = wait_semaphores;
  submit_info.pWaitDstStageMask = wait_stages;

  VkCommandBuffer command_buffers[] = { *command_buffer };
  submit_info.commandBufferCount = 1;
  submit_info.pCommandBuffers = command_buffers;

  VkSemaphore signal_semaphores[] = { *signal_semaphore };
  submit_info.signalSemaphoreCount = 1;
  submit_info.pSignalSemaphores = signal_semaphores;

  VkResult result;
  if ((result = vkQueueSubmit(queue_, 1, &submit_info, VK_NULL_HANDLE)) != VK_SUCCESS)
    throw vk::Exception("Failed to submit draw command buffer.", result);
}

void QueueImpl::Print(std::ostream& out) const
{
  out << "Queue";
}
}
}
}
