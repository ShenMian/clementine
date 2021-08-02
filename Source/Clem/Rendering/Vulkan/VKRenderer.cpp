// Copyright 2021 SMS
// License(Apache-2.0)

#include "VKRenderer.h"
#include "Clem/Assert.h"
#include "Clem/Core/Application.h"
#include "Clem/Logger.h"
#include "Clem/Version.h"
#include <cassert>
#include <vector>

#include <iostream>

namespace clem
{

VKAPI_ATTR vk::Bool32 VKAPI_CALL DebugReportCallback(
    VkDebugReportFlagsEXT,
    VkDebugReportObjectTypeEXT,
    uint64_t,
    size_t,
    int32_t,
    const char*,
    const char*,
    void*);

void vkCheck(VkResult);

VKRenderer& VKRenderer::get()
{
  static auto* instance = new VKRenderer;
  return *instance;
}

void VKRenderer::init()
{
  createInstance();
  createDebugCallback();
  createDevice();

  commandPool.create();
  commandBuffer = commandPool.allocateCommandBuffer();
  commandBuffer.begin();

  vk::SubmitInfo                 submitInfo;
  std::vector<vk::CommandBuffer> commandBuffers(1);
  commandBuffers[0]             = commandBuffer;
  submitInfo.commandBufferCount = 1;
  submitInfo.pCommandBuffers    = commandBuffers.data();

  queue.submit(submitInfo);

  queue.waitIdle();
}

void VKRenderer::deinit()
{
  commandBuffer.end();
  commandPool.destroy();

  destroyDevice();
  destroyDebugCallback();
  destroyInstance();
}

void VKRenderer::createInstance()
{
  Assert::isTrue(!instance);

  // instanceLayers.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);

  vk::ApplicationInfo appInfo;
  appInfo.apiVersion    = VK_MAKE_VERSION(1, 0, 3); // 驱动应该支持的最低 API 版本
  appInfo.pEngineName   = "Clementine";
  appInfo.engineVersion = VK_MAKE_VERSION(version_major, version_minor, version_patch);

  vk::InstanceCreateInfo instanceCreateInfo;
  instanceCreateInfo.pApplicationInfo        = &appInfo;
  instanceCreateInfo.enabledLayerCount       = (uint32_t)instanceLayers.size();
  instanceCreateInfo.ppEnabledLayerNames     = instanceLayers.data();
  instanceCreateInfo.enabledExtensionCount   = (uint32_t)instanceExtensions.size();
  instanceCreateInfo.ppEnabledExtensionNames = instanceExtensions.data();

  try
  {
    instance = vk::createInstance(instanceCreateInfo);
  }
  catch(const std::exception& e)
  {
    Assert::isTrue(false, std::format("create instance faild: {}", e.what()));
  }
}

void VKRenderer::destroyInstance()
{
  instance.destroy();
}

static vk::DebugReportCallbackEXT debugReport;

void VKRenderer::createDebugCallback()
{
  dynamicLoader.init(instance, vkGetInstanceProcAddr);
  if(dynamicLoader.vkCreateDebugReportCallbackEXT == nullptr)
    return;

  vk::DebugReportCallbackCreateInfoEXT createInfo;
  createInfo.pfnCallback = DebugReportCallback;
  createInfo.flags       = vk::DebugReportFlagBitsEXT::eDebug |
                     vk::DebugReportFlagBitsEXT::eError |
                     vk::DebugReportFlagBitsEXT::eInformation |
                     vk::DebugReportFlagBitsEXT::ePerformanceWarning |
                     vk::DebugReportFlagBitsEXT::eWarning;
  debugReport = instance.createDebugReportCallbackEXT(createInfo, nullptr, dynamicLoader);
}

void VKRenderer::destroyDebugCallback()
{
  if(dynamicLoader.vkDestroyDebugReportCallbackEXT == nullptr)
    return;
  instance.destroyDebugReportCallbackEXT(debugReport, nullptr, dynamicLoader);
}

void VKRenderer::createDevice()
{
  Assert::isTrue(!device);

  auto physicalDevice = findSuitablePhysicalDevice();
  Assert::isTrue(physicalDevice, "can't find suitable physical device");
  CLEM_LOG_INFO("render", "Physical Device: {}", physicalDevice.getProperties().deviceName);

  auto     queueFamilyProps = physicalDevice.getQueueFamilyProperties();
  uint32_t queueIndex       = -1;
  for(uint32_t i = 0; i < queueFamilyProps.size(); i++)
    if(isSuitable(queueFamilyProps[i]))
      queueIndex = i;
  Assert::isTrue(queueIndex != -1, "can't find suitable queue family");
  queueFamilyIndex = queueIndex;

  float                     queuePriorities = 1.0f;
  vk::DeviceQueueCreateInfo deviceQueueCreateInfo;
  deviceQueueCreateInfo.queueFamilyIndex = queueFamilyIndex;
  deviceQueueCreateInfo.queueCount       = queueFamilyProps[queueFamilyIndex].queueCount;
  deviceQueueCreateInfo.pQueuePriorities = &queuePriorities;

  vk::DeviceCreateInfo deviceCreateInfo;
  deviceCreateInfo.queueCreateInfoCount    = 1;
  deviceCreateInfo.pQueueCreateInfos       = &deviceQueueCreateInfo;
  deviceCreateInfo.enabledLayerCount       = (uint32_t)deviceLayers.size();
  deviceCreateInfo.ppEnabledLayerNames     = deviceLayers.data();
  deviceCreateInfo.enabledExtensionCount   = (uint32_t)deviceExtensions.size();
  deviceCreateInfo.ppEnabledExtensionNames = deviceExtensions.data();

  try
  {
    device = physicalDevice.createDevice(deviceCreateInfo);
  }
  catch(const std::exception& e)
  {
    Assert::isTrue(false, std::format("create device faild: {}", e.what()));
  }

  queue = device.getQueue(queueFamilyIndex, 0);

  // vkInstance.createDebugReportCallbackEXT(debugReportCallbackCreateInfo);

  /*
	for(auto& layer : vk::enumerateInstanceLayerProperties())
		std::cout << std::format("{:40} {}", layer.layerName, layer.description) << std::endl;
	std::cout << std::endl;
	for(auto& layer : physicalDevice.enumerateDeviceLayerProperties())
		std::cout << std::format("{:40} {}", layer.layerName, layer.description) << std::endl;
	*/
}

void VKRenderer::destroyDevice()
{
  device.destroy();
}

vk::PhysicalDevice VKRenderer::findSuitablePhysicalDevice() const
{
  for(const auto device : instance.enumeratePhysicalDevices())
    if(isSuitable(device))
      return device;
  return nullptr;
}

bool VKRenderer::isSuitable(const vk::PhysicalDevice& device) const
{
  if(device.getProperties().deviceType != vk::PhysicalDeviceType::eDiscreteGpu && device.getFeatures().geometryShader)
    return false;
  return true;
}

bool VKRenderer::isSuitable(const vk::QueueFamilyProperties& props) const
{
  return props.queueFlags & vk::QueueFlagBits::eGraphics && props.queueCount > 0;
}

VKAPI_ATTR vk::Bool32 VKAPI_CALL DebugReportCallback(
    VkDebugReportFlagsEXT      flags,
    VkDebugReportObjectTypeEXT objectType,
    uint64_t                   object,
    size_t                     location,
    int32_t                    messageCode,
    const char*                pLayerPrefix,
    const char*                pMessage,
    void*                      pUserData)
{
  std::cout << pMessage << std::endl;

  return false;
}

} // namespace clem