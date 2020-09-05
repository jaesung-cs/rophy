#include <rophy/vk/vk_queue.h>

namespace rophy
{
namespace vk
{
namespace impl
{
QueueImpl::QueueImpl(VkQueue handle)
  : queue_(handle)
{
}

QueueImpl::~QueueImpl() = default;
}
}
}
