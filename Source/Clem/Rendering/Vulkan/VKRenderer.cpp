// Copyright 2021 SMS
// License(Apache-2.0)

#include "VKRenderer.h"
#include "Clem/Version.h"
#include <cassert>
#include <vector>
#include <vulkan/vulkan.h>

namespace clem
{

void vkCheck(VkResult result)
{
	switch(result)
	{
	case VK_SUCCESS:
		return;
	case VK_NOT_READY:
		break;
	case VK_TIMEOUT:
		break;
	case VK_EVENT_SET:
		break;
	case VK_EVENT_RESET:
		break;
	case VK_INCOMPLETE:
		break;
	case VK_ERROR_OUT_OF_HOST_MEMORY:
		break;
	case VK_ERROR_OUT_OF_DEVICE_MEMORY:
		break;
	case VK_ERROR_INITIALIZATION_FAILED:
		break;
	case VK_ERROR_DEVICE_LOST:
		break;
	case VK_ERROR_MEMORY_MAP_FAILED:
		break;
	case VK_ERROR_LAYER_NOT_PRESENT:
		break;
	case VK_ERROR_EXTENSION_NOT_PRESENT:
		break;
	case VK_ERROR_FEATURE_NOT_PRESENT:
		break;
	case VK_ERROR_INCOMPATIBLE_DRIVER:
		break;
	case VK_ERROR_TOO_MANY_OBJECTS:
		break;
	case VK_ERROR_FORMAT_NOT_SUPPORTED:
		break;
	case VK_ERROR_FRAGMENTED_POOL:
		break;
	case VK_ERROR_UNKNOWN:
		break;
	case VK_ERROR_OUT_OF_POOL_MEMORY:
		break;
	case VK_ERROR_INVALID_EXTERNAL_HANDLE:
		break;
	case VK_ERROR_FRAGMENTATION:
		break;
	case VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS:
		break;
	case VK_ERROR_SURFACE_LOST_KHR:
		break;
	case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:
		break;
	case VK_SUBOPTIMAL_KHR:
		break;
	case VK_ERROR_OUT_OF_DATE_KHR:
		break;
	case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:
		break;
	case VK_ERROR_VALIDATION_FAILED_EXT:
		break;
	case VK_ERROR_INVALID_SHADER_NV:
		break;
	case VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT:
		break;
	case VK_ERROR_NOT_PERMITTED_EXT:
		break;
	case VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT:
		break;
	case VK_THREAD_IDLE_KHR:
		break;
	case VK_THREAD_DONE_KHR:
		break;
	case VK_OPERATION_DEFERRED_KHR:
		break;
	case VK_OPERATION_NOT_DEFERRED_KHR:
		break;
	case VK_PIPELINE_COMPILE_REQUIRED_EXT:
		break;
	case VK_RESULT_MAX_ENUM:
		break;
	default:
		assert(false && "unknown vulkan result code");
		break;
	}
}

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
	applicationInfo.engineVersion = VK_MAKE_VERSION(CLEM_VERSION_MAJOR, CLEM_VERSION_MINOR, CLEM_VERSION_PATCH);

	VkInstanceCreateInfo instanceCreateInfo = {};
	instanceCreateInfo.sType                = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	instanceCreateInfo.pApplicationInfo     = &applicationInfo;

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

	// 获取 GPU 列表
	uint32_t gpuCount;
	vkEnumeratePhysicalDevices(vkInstance, &gpuCount, nullptr);
	std::vector<VkPhysicalDevice> gpuList(gpuCount);
	vkEnumeratePhysicalDevices(vkInstance, &gpuCount, gpuList.data());

	auto gpu = gpuList[0];

	// 获取 GPU 属性
	VkPhysicalDeviceProperties gpuProperties;
	vkGetPhysicalDeviceProperties(gpu, &gpuProperties);

	// 获取 QueueFamily 属性列表
	uint32_t familyPropertiesCount;
	vkGetPhysicalDeviceQueueFamilyProperties(gpu, &familyPropertiesCount, nullptr);
	std::vector<VkQueueFamilyProperties> familyPropertiesList(familyPropertiesCount);
	vkGetPhysicalDeviceQueueFamilyProperties(gpu, &familyPropertiesCount, familyPropertiesList.data());

	// 查找支持图像的 QueueFamily
	uint32_t queueFamilyIndex = -1;
	for(uint32_t i = 0; i < familyPropertiesCount; i++)
		if(familyPropertiesList[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
			queueFamilyIndex = i;
	assert(queueFamilyIndex != -1);

	float queuePriorities = {1.0f};

	VkDeviceQueueCreateInfo deviceQueueCreateInfo = {};
	deviceQueueCreateInfo.sType                   = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	deviceQueueCreateInfo.queueCount              = 1;
	deviceQueueCreateInfo.queueFamilyIndex        = queueFamilyIndex;
	deviceQueueCreateInfo.pQueuePriorities        = &queuePriorities;

	VkDeviceCreateInfo deviceCreateInfo   = {};
	deviceCreateInfo.sType                = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	deviceCreateInfo.queueCreateInfoCount = 1;
	deviceCreateInfo.pQueueCreateInfos    = &deviceQueueCreateInfo;

	auto ret = vkCreateDevice(gpu, &deviceCreateInfo, nullptr, &vkDevice);
	vkCheck(ret);
}

void VKRenderer::deinitDevice()
{
	vkDestroyDevice(vkDevice, nullptr);
	vkDevice = nullptr;
}

} // namespace clem