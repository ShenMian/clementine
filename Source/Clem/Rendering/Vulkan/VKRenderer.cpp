﻿// Copyright 2021 SMS
// License(Apache-2.0)

#include "VKRenderer.h"
#include "Assert.hpp"
#include "Core/Application.h"
#include "Logger.h"
#include "Version.h"
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
    device.create();

    commandPool.create();
    commandBuffer = commandPool.allocateCommandBuffer();
    commandBuffer.begin();

    vk::SubmitInfo                 submitInfo;
    std::vector<vk::CommandBuffer> commandBuffers(1);
    commandBuffers[0]             = commandBuffer;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers    = commandBuffers.data();

    // device.queue.submit(submitInfo);
    // device.queue.waitIdle();
}

void VKRenderer::deinit()
{
    commandBuffer.end();
    commandPool.destroy();

    device.destroy();
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