#include <rophy/vk/vk_queue.h>

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

void QueueImpl::Print(std::ostream& out) const
{
  out << "Queue";
}
}
}
}
