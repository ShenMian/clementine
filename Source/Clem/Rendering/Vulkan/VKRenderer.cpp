// Copyright 2021 SMS
// License(Apache-2.0)

#include "VKRenderer.h"
#include "Clem/Version.h"
#include <cassert>
#include <vector>
#include <vulkan/vulkan.h>

namespace clem
{

void vkCheck(VkResult);

static VkInstance        vkInstance = nullptr;
static VkDevice          vkDevice   = nullptr;
static VkApplicationInfo applicationInfo;

void VKRenderer::init()
{
	initInstance();
	initDevice();
}

void VKRenderer::deinit()
{
	deinitDevice();
	deinitInstance();
}

void VKRenderer::initInstance()
{
	assert(vkInstance == nullptr);

	memset(&applicationInfo, 0, sizeof(applicationInfo));
	applicationInfo.apiVersion    = VK_MAKE_VERSION(1, 0, 3); // 驱动应该支持的最低 API 版本
	applicationInfo.pEngineName   = "Clementine";
	applicationInfo.engineVersion = VK_MAKE_VERSION(clem::version_major, clem::version_minor, clem::version_patch);

	VkInstanceCreateInfo instanceCreateInfo = {
			.sType            = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
			.pApplicationInfo = &applicationInfo};

	auto ret = vkCreateInstance(&instanceCreateInfo, nullptr, &vkInstance);
	vkCheck(ret);
}

void VKRenderer::deinitInstance()
{
	vkDestroyInstance(vkInstance, nullptr);
	vkInstance = nullptr;
}

void VKRenderer::initDevice()
{
	assert(vkDevice == nullptr);

	auto gpu = findSuitableDevice();
	assert(gpu != nullptr);

	auto [queueIndex, queueCount] = findSuitableQueueFamily(gpu);
	assert(queueIndex != -1);

	float                   queuePriorities       = 1.0f;
	VkDeviceQueueCreateInfo deviceQueueCreateInfo = {
			.sType            = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
			.queueFamilyIndex = queueIndex,
			.queueCount       = queueCount,
			.pQueuePriorities = &queuePriorities};

	VkDeviceCreateInfo deviceCreateInfo = {
			.sType                = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
			.queueCreateInfoCount = 1,
			.pQueueCreateInfos    = &deviceQueueCreateInfo};

	auto ret = vkCreateDevice(gpu, &deviceCreateInfo, nullptr, &vkDevice);
	vkCheck(ret);
}

void VKRenderer::deinitDevice()
{
	vkDestroyDevice(vkDevice, nullptr);
	vkDevice = nullptr;
}

VkPhysicalDevice VKRenderer::findSuitableDevice() const
{
	// 获取 Device 列表
	uint32_t devicesCount;
	vkEnumeratePhysicalDevices(vkInstance, &devicesCount, nullptr);
	std::vector<VkPhysicalDevice> devicesList(devicesCount);
	vkEnumeratePhysicalDevices(vkInstance, &devicesCount, devicesList.data());

	// 查找合适的 Device
	for(const auto device : devicesList)
		if(isDeviceSuitable(device))
			return device;

	return nullptr;
}

bool VKRenderer::isDeviceSuitable(const VkPhysicalDevice device) const
{
	VkPhysicalDeviceProperties properties;
	VkPhysicalDeviceFeatures   features;

	vkGetPhysicalDeviceProperties(device, &properties);
	if(properties.deviceType != VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
		return false;

	vkGetPhysicalDeviceFeatures(device, &features);
	if(!features.geometryShader)
		return false;

	auto [queueIndex, queueCount] = findSuitableQueueFamily(device);
	if(queueIndex == -1)
		return false;

	return true;
}

std::tuple<uint32_t, uint32_t> VKRenderer::findSuitableQueueFamily(const VkPhysicalDevice device) const
{
	// 获取 QueueFamily 属性列表
	uint32_t propertiesCount;
	vkGetPhysicalDeviceQueueFamilyProperties(device, &propertiesCount, nullptr);
	std::vector<VkQueueFamilyProperties> propertiesList(propertiesCount);
	vkGetPhysicalDeviceQueueFamilyProperties(device, &propertiesCount, propertiesList.data());

	// 查找合适的 QueueFamily
	uint32_t index = -1;
	for(uint32_t i = 0; i < propertiesCount; i++)
		if(isQueueFamilySuitable(propertiesList[i]))
			index = i;

	return {index, propertiesList[index].queueCount};
}

bool VKRenderer::isQueueFamilySuitable(VkQueueFamilyProperties& properties) const
{
	return properties.queueFlags & VK_QUEUE_GRAPHICS_BIT && properties.queueCount > 0;
}

void vkCheck(VkResult result)
{
	switch(result)
	{
	case VK_SUCCESS:
		return;
	case VK_NOT_READY:
		assert(false && "VK_NOT_READY");
		break;
	case VK_TIMEOUT:
		assert(false && "VK_TIMEOUT");
		break;
	case VK_EVENT_SET:
		assert(false && "VK_EVENT_SET");
		break;
	case VK_EVENT_RESET:
		assert(false && "VK_EVENT_RESET");
		break;
	case VK_INCOMPLETE:
		assert(false && "VK_INCOMPLETE");
		break;
	case VK_ERROR_OUT_OF_HOST_MEMORY:
		assert(false && "VK_ERROR_OUT_OF_HOST_MEMORY");
		break;
	case VK_ERROR_OUT_OF_DEVICE_MEMORY:
		assert(false && "VK_ERROR_OUT_OF_DEVICE_MEMORY");
		break;
	case VK_ERROR_INITIALIZATION_FAILED:
		assert(false && "VK_ERROR_INITIALIZATION_FAILED");
		break;
	case VK_ERROR_DEVICE_LOST:
		assert(false && "VK_ERROR_DEVICE_LOST");
		break;
	case VK_ERROR_MEMORY_MAP_FAILED:
		assert(false && "VK_ERROR_MEMORY_MAP_FAILED");
		break;
	case VK_ERROR_LAYER_NOT_PRESENT:
		assert(false && "VK_ERROR_LAYER_NOT_PRESENT");
		break;
	case VK_ERROR_EXTENSION_NOT_PRESENT:
		assert(false && "VK_ERROR_EXTENSION_NOT_PRESENT");
		break;
	case VK_ERROR_FEATURE_NOT_PRESENT:
		assert(false && "VK_ERROR_FEATURE_NOT_PRESENT");
		break;
	case VK_ERROR_INCOMPATIBLE_DRIVER:
		assert(false && "VK_ERROR_INCOMPATIBLE_DRIVER");
		break;
	case VK_ERROR_TOO_MANY_OBJECTS:
		assert(false && "VK_ERROR_TOO_MANY_OBJECTS");
		break;
	case VK_ERROR_FORMAT_NOT_SUPPORTED:
		assert(false && "VK_ERROR_FORMAT_NOT_SUPPORTED");
		break;
	case VK_ERROR_FRAGMENTED_POOL:
		assert(false && "VK_ERROR_FRAGMENTED_POOL");
		break;
	case VK_ERROR_UNKNOWN:
		assert(false && "VK_ERROR_UNKNOWN");
		break;
	case VK_ERROR_OUT_OF_POOL_MEMORY:
		assert(false && "VK_ERROR_OUT_OF_POOL_MEMORY");
		break;
	case VK_ERROR_INVALID_EXTERNAL_HANDLE:
		assert(false && "VK_ERROR_INVALID_EXTERNAL_HANDLE");
		break;
	case VK_ERROR_FRAGMENTATION:
		assert(false && "VK_ERROR_FRAGMENTATION");
		break;
	case VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS:
		assert(false && "VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS");
		break;
	case VK_ERROR_SURFACE_LOST_KHR:
		assert(false && "VK_ERROR_SURFACE_LOST_KHR");
		break;
	case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:
		assert(false && "VK_ERROR_NATIVE_WINDOW_IN_USE_KHR");
		break;
	case VK_SUBOPTIMAL_KHR:
		assert(false && "VK_SUBOPTIMAL_KHR");
		break;
	case VK_ERROR_OUT_OF_DATE_KHR:
		assert(false && "VK_ERROR_OUT_OF_DATE_KHR");
		break;
	case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:
		assert(false && "VK_ERROR_INCOMPATIBLE_DISPLAY_KHR");
		break;
	case VK_ERROR_VALIDATION_FAILED_EXT:
		assert(false && "VK_ERROR_VALIDATION_FAILED_EXT");
		break;
	case VK_ERROR_INVALID_SHADER_NV:
		assert(false && "VK_ERROR_INVALID_SHADER_NV");
		break;
	case VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT:
		assert(false && "VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT");
		break;
	case VK_ERROR_NOT_PERMITTED_EXT:
		assert(false && "VK_ERROR_NOT_PERMITTED_EXT");
		break;
	case VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT:
		assert(false && "VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT");
		break;
	case VK_THREAD_IDLE_KHR:
		assert(false && "VK_THREAD_IDLE_KHR");
		break;
	case VK_THREAD_DONE_KHR:
		assert(false && "VK_THREAD_DONE_KHR");
		break;
	case VK_OPERATION_DEFERRED_KHR:
		assert(false && "VK_OPERATION_DEFERRED_KHR");
		break;
	case VK_OPERATION_NOT_DEFERRED_KHR:
		assert(false && "VK_OPERATION_NOT_DEFERRED_KHR");
		break;
	case VK_PIPELINE_COMPILE_REQUIRED_EXT:
		assert(false && "VK_PIPELINE_COMPILE_REQUIRED_EXT");
		break;
	default:
		assert(false && "unknown vulkan result code");
		break;
	}
}

} // namespace clem