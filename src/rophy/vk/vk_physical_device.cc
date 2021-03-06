#include <rophy/vk/vk_physical_device.h>

#include <iomanip>

#include <sstream>

namespace rophy
{
namespace vk
{
namespace impl
{
PhysicalDeviceImpl::PhysicalDeviceImpl(VkPhysicalDevice handle)
  : physical_device_(handle)
  , extension_layers_(handle)
{
  // Device properties and features
  vkGetPhysicalDeviceProperties(physical_device_, &properties_);
  vkGetPhysicalDeviceFeatures(physical_device_, &features_);

  // Queue families
  uint32_t queue_family_count = 0;
  vkGetPhysicalDeviceQueueFamilyProperties(physical_device_, &queue_family_count, nullptr);
  queue_families_.resize(queue_family_count);
  vkGetPhysicalDeviceQueueFamilyProperties(physical_device_, &queue_family_count, queue_families_.data());
}

PhysicalDeviceImpl::~PhysicalDeviceImpl()
{
  DestroyThis();
}

int PhysicalDeviceImpl::GetQueueFamilyIndex(BitFlags type) const
{
  BitFlags vk_flags = 0;

  if (type & QueueType::GRAPHICS)
    vk_flags |= VK_QUEUE_GRAPHICS_BIT;
  if (type & QueueType::COMPUTE)
    vk_flags |= VK_QUEUE_COMPUTE_BIT;
  if (type & QueueType::TRANSFER)
    vk_flags |= VK_QUEUE_TRANSFER_BIT;

  for (int i = 0; i < queue_families_.size(); i++)
  {
    if ((queue_families_[i].queueFlags & vk_flags) == vk_flags)
      return i;
  }

  return -1;
}

int PhysicalDeviceImpl::GetSurfaceSupportedQueueFamilyIndex(Surface surface) const
{
  for (int i = 0; i < queue_families_.size(); i++)
  {
    VkBool32 supported = false;
    vkGetPhysicalDeviceSurfaceSupportKHR(physical_device_, i, *surface, &supported);
    if (supported)
      return i;
  }

  return -1;
}

void PhysicalDeviceImpl::Print(std::ostream& out) const
{
  out
    << "VkPhysicalDevice" << std::endl
    << "  Queue families:" << std::endl;

  std::vector<std::string> queue_family_strings;
  for (int i = 0; i < queue_families_.size(); i++)
  {
    const auto& queue_family = queue_families_[i];

    std::ostringstream sout;

    sout << "Index " << std::setw(2) << i << ": "
      << std::setw(3) << queue_family.queueCount << " queues.";

    if (queue_family.queueFlags & VK_QUEUE_GRAPHICS_BIT)
      sout << " Graphics";
    if (queue_family.queueFlags & VK_QUEUE_COMPUTE_BIT)
      sout << " Compute";
    if (queue_family.queueFlags & VK_QUEUE_TRANSFER_BIT)
      sout << " Transfer";
    if (queue_family.queueFlags & VK_QUEUE_SPARSE_BINDING_BIT)
      sout << " SparseBinding";
    if (queue_family.queueFlags & VK_QUEUE_PROTECTED_BIT)
      sout << " Protected";

    queue_family_strings.emplace_back(sout.str());
  }
  PrintStrings(out, queue_family_strings, 4);

  out << extension_layers_;
}

/*
Device extensions:
  VK_KHR_16bit_storage
  VK_KHR_8bit_storage
  VK_KHR_bind_memory2
  VK_KHR_buffer_device_address
  VK_KHR_create_renderpass2
  VK_KHR_dedicated_allocation
  VK_KHR_depth_stencil_resolve
  VK_KHR_descriptor_update_template
  VK_KHR_device_group
  VK_KHR_draw_indirect_count
  VK_KHR_driver_properties
  VK_KHR_external_fence
  VK_KHR_external_fence_win32
  VK_KHR_external_memory
  VK_KHR_external_memory_win32
  VK_KHR_external_semaphore
  VK_KHR_external_semaphore_win32
  VK_KHR_get_memory_requirements2
  VK_KHR_image_format_list
  VK_KHR_imageless_framebuffer
  VK_KHR_maintenance1
  VK_KHR_maintenance2
  VK_KHR_maintenance3
  VK_KHR_multiview
  VK_KHR_pipeline_executable_properties
  VK_KHR_push_descriptor
  VK_KHR_relaxed_block_layout
  VK_KHR_sampler_mirror_clamp_to_edge
  VK_KHR_sampler_ycbcr_conversion
  VK_KHR_separate_depth_stencil_layouts
  VK_KHR_shader_atomic_int64
  VK_KHR_shader_clock
  VK_KHR_shader_draw_parameters
  VK_KHR_shader_float16_int8
  VK_KHR_shader_float_controls
  VK_KHR_shader_non_semantic_info
  VK_KHR_shader_subgroup_extended_types
  VK_KHR_spirv_1_4
  VK_KHR_storage_buffer_storage_class
  VK_KHR_swapchain
  VK_KHR_swapchain_mutable_format
  VK_KHR_timeline_semaphore
  VK_KHR_uniform_buffer_standard_layout
  VK_KHR_variable_pointers
  VK_KHR_vulkan_memory_model
  VK_KHR_win32_keyed_mutex
  VK_EXT_blend_operation_advanced
  VK_EXT_buffer_device_address
  VK_EXT_calibrated_timestamps
  VK_EXT_conditional_rendering
  VK_EXT_conservative_rasterization
  VK_EXT_custom_border_color
  VK_EXT_depth_clip_enable
  VK_EXT_depth_range_unrestricted
  VK_EXT_descriptor_indexing
  VK_EXT_discard_rectangles
  VK_EXT_external_memory_host
  VK_EXT_fragment_shader_interlock
  VK_EXT_full_screen_exclusive
  VK_EXT_hdr_metadata
  VK_EXT_host_query_reset
  VK_EXT_index_type_uint8
  VK_EXT_inline_uniform_block
  VK_EXT_line_rasterization
  VK_EXT_memory_budget
  VK_EXT_memory_priority
  VK_EXT_pci_bus_info
  VK_EXT_pipeline_creation_feedback
  VK_EXT_post_depth_coverage
  VK_EXT_sample_locations
  VK_EXT_sampler_filter_minmax
  VK_EXT_scalar_block_layout
  VK_EXT_separate_stencil_usage
  VK_EXT_shader_demote_to_helper_invocation
  VK_EXT_shader_subgroup_ballot
  VK_EXT_shader_subgroup_vote
  VK_EXT_shader_viewport_index_layer
  VK_EXT_subgroup_size_control
  VK_EXT_texel_buffer_alignment
  VK_EXT_tooling_info
  VK_EXT_transform_feedback
  VK_EXT_vertex_attribute_divisor
  VK_EXT_ycbcr_image_arrays
  VK_NV_clip_space_w_scaling
  VK_NV_coverage_reduction_mode
  VK_NV_dedicated_allocation
  VK_NV_dedicated_allocation_image_aliasing
  VK_NV_device_diagnostic_checkpoints
  VK_NV_device_diagnostics_config
  VK_NV_external_memory
  VK_NV_external_memory_win32
  VK_NV_fill_rectangle
  VK_NV_fragment_coverage_to_color
  VK_NV_framebuffer_mixed_samples
  VK_NV_geometry_shader_passthrough
  VK_NV_ray_tracing
  VK_NV_sample_mask_override_coverage
  VK_NV_shader_sm_builtins
  VK_NV_shader_subgroup_partitioned
  VK_NV_viewport_array2
  VK_NV_viewport_swizzle
  VK_NV_win32_keyed_mutex
  VK_NVX_device_generated_commands
  VK_NVX_multiview_per_view_attributes
Device layers:
  VK_LAYER_NV_optimus: NVIDIA Optimus layer
  VK_LAYER_OBS_HOOK: Open Broadcaster Software hook
  VK_LAYER_KHRONOS_validation: Khronos Validation Layer
*/
}
}
}
