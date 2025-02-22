//
// Created by ryen on 2/21/25.
//

#include <SDL3/SDL_vulkan.h>
#include <nvrhi/validation.h>
#include <spdlog/spdlog.h>

#include "MECore/render/VulkanInterface.h"

VULKAN_HPP_DEFAULT_DISPATCH_LOADER_DYNAMIC_STORAGE

namespace ME::render {
    static constexpr uint32_t MAX_FRAMES_IN_FLIGHT = 2;

    static std::vector<const char *> StringSetToVector(const std::unordered_set<std::string>& set) {
        std::vector<const char *> ret;
        for(const auto& s : set)
        {
            ret.push_back(s.c_str());
        }

        return ret;
    }

    template <typename T>
    static std::vector<T> SetToVector(const std::unordered_set<T>& set) {
        std::vector<T> ret;
        for(const auto& s : set)
        {
            ret.push_back(s);
        }

        return ret;
    }

    bool VulkanInterface::CreateInstance() {
        SDL_Vulkan_LoadLibrary(nullptr);

        auto vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)SDL_Vulkan_GetVkGetInstanceProcAddr();
        VULKAN_HPP_DEFAULT_DISPATCHER.init(vkGetInstanceProcAddr);

        Uint32 sdlReqCount = 0;
        auto* sdlRequirements = SDL_Vulkan_GetInstanceExtensions(&sdlReqCount);

        for (int i = 0; i < sdlReqCount; i++) {
            enabledExtensions.instance.insert(std::string(sdlRequirements[i]));
        }

        // Check required extensions
        auto requiredExtensions = enabledExtensions.instance;
        for (const auto& extension : vk::enumerateInstanceExtensionProperties()) {
            const std::string& name = extension.extensionName;
            if (optionalExtensions.instance.contains(name)) {
                enabledExtensions.instance.insert(name);
            }
            requiredExtensions.erase(name);
        }

        if (!requiredExtensions.empty()) {
            spdlog::error("Failed to create Vulkan Instance. Required extension(s) missing:");
            for (const auto& extension : requiredExtensions) {
                spdlog::error("- {}", extension);
            }
            return false;
        }

        spdlog::info("Enabled Vulkan instance extensions:");
        for (const auto& extension : enabledExtensions.instance) {
            spdlog::info("- {}", extension);
        }

        // Check required layers
        auto requiredLayers = enabledExtensions.layers;
        for (const auto& layer : vk::enumerateInstanceLayerProperties()) {
            const std::string name = layer.layerName;
            if (optionalExtensions.layers.contains(name)) {
                enabledExtensions.layers.insert(name);
            }
            requiredLayers.erase(name);
        }

        if (!requiredLayers.empty()) {
            spdlog::error("Failed to create Vulkan Instance. Required layer(s) missing:");
            for (const auto& layer : requiredLayers) {
                spdlog::error("- {}", layer);
            }
            return false;
        }

        spdlog::info("Enabled Vulkan layers: ");
        for (const auto& layer : enabledExtensions.layers) {
            spdlog::info("- {}", layer);
        }

        auto instanceExtVec = StringSetToVector(enabledExtensions.instance);
        auto instanceLayerVec = StringSetToVector(enabledExtensions.layers);

        // Create app info
        // TODO: add version checks
        vk::ApplicationInfo appInfo{};
        appInfo.pApplicationName = "MECore"; // TODO: Make this configurable
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "MANIFOLDEngine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_3;

        vk::InstanceCreateInfo createInfo{};
        createInfo.pApplicationInfo = &appInfo;
        createInfo.enabledLayerCount = instanceLayerVec.size();
        createInfo.ppEnabledLayerNames = instanceLayerVec.data();
        createInfo.enabledExtensionCount = instanceExtVec.size();
        createInfo.ppEnabledExtensionNames = instanceExtVec.data();

        vk::Result instResult = vk::createInstance(&createInfo, nullptr, &vkInstance);
        if (instResult != vk::Result::eSuccess) {
            spdlog::error("Failed to create Vulkan instance. Code: {}", nvrhi::vulkan::resultToString(VkResult(instResult)));
            return false;
        }

        VULKAN_HPP_DEFAULT_DISPATCHER.init(vkInstance);

        return true;
    }

    bool VulkanInterface::CreateDevice() {
        assert(PickPhysicalDevice());
        assert(FindQueueFamilies(vkPhysicalDevice));
        assert(CreateVulkanDevice());
        assert(CreateVulkanSurface());

        auto vecInstanceExt = StringSetToVector(enabledExtensions.instance);
        auto vecLayers = StringSetToVector(enabledExtensions.layers);
        auto vecDeviceExt = StringSetToVector(enabledExtensions.device);

        nvrhi::vulkan::DeviceDesc deviceDesc{};
        deviceDesc.errorCB = &DefaultMessageCallback::GetInstance();
        deviceDesc.instance = vkInstance;
        deviceDesc.physicalDevice = vkPhysicalDevice;
        deviceDesc.device = vkDevice;

        deviceDesc.graphicsQueue = graphicsQueue;
        deviceDesc.graphicsQueueIndex = graphicsQueueFamily;
        deviceDesc.computeQueue = computeQueue;
        deviceDesc.computeQueueIndex = computeQueueFamily;
        deviceDesc.transferQueue = transferQueue;
        deviceDesc.transferQueueIndex = transferQueueFamily;

        deviceDesc.instanceExtensions = vecInstanceExt.data();
        deviceDesc.numInstanceExtensions = vecInstanceExt.size();
        deviceDesc.deviceExtensions = vecDeviceExt.data();
        deviceDesc.numDeviceExtensions = vecDeviceExt.size();
        deviceDesc.bufferDeviceAddressSupported = true;

        nvDevice = nvrhi::vulkan::createDevice(deviceDesc);
        nvValidationLayer = nvrhi::validation::createValidationLayer(nvDevice);

        return true;
    }

    bool VulkanInterface::CreateSwapchain() {
        if (!CreateSwapchainInternal()) return false;

        presentSemaphores.reserve(MAX_FRAMES_IN_FLIGHT + 1);
        acquireSemaphores.reserve(MAX_FRAMES_IN_FLIGHT + 1);
        for (uint32_t i = 0; i < MAX_FRAMES_IN_FLIGHT + 1; i++) {
            presentSemaphores.push_back(vkDevice.createSemaphore(vk::SemaphoreCreateInfo()));
            acquireSemaphores.push_back(vkDevice.createSemaphore(vk::SemaphoreCreateInfo()));
        }

        return true;
    }

    void VulkanInterface::DestroyDevice() {
        nvDevice = nullptr;
        nvValidationLayer = nullptr;

        if (vkDevice) {
            vkDevice.destroy();
            vkDevice = nullptr;
        }
        if (vkSurface) {
            assert(vkInstance);
            SDL_Vulkan_DestroySurface(vkInstance, vkSurface, nullptr);
            vkSurface = nullptr;
        }
        if (vkInstance) {
            vkInstance.destroy();
            vkInstance = nullptr;
        }
    }

    void VulkanInterface::DestroySwapchain() {
        DestroySwapchainInternal();

        for (auto& semaphore : presentSemaphores) {
            if (semaphore) {
                vkDevice.destroySemaphore(semaphore);
                semaphore = vk::Semaphore();
            }
        }
        for (auto& semaphore : acquireSemaphores) {
            if (semaphore) {
                vkDevice.destroySemaphore(semaphore);
                semaphore = vk::Semaphore();
            }
        }
    }

    void VulkanInterface::ResizeSwapchain() {
        if (vkDevice) {
            DestroySwapchainInternal();
            CreateSwapchainInternal();
        }
    }

    bool VulkanInterface::BeginFrame() {
        const auto& semaphore = acquireSemaphores[acquireSemaphoreIndex];

        vk::Result result;

        const int maxAttempts = 3;
        for (int attempt = 0; attempt < maxAttempts; ++attempt) {
            // This line is causing some issues for some reason?
            // result = vkDevice.acquireNextImageKHR(vkSwapchain, std::numeric_limits<uint64_t>::max(), semaphore, vk::Fence(), swapchainIndex).result;
            result = vk::Result(vkAcquireNextImageKHR(vkDevice, vkSwapchain, UINT64_MAX, semaphore, VkFence(), &swapchainIndex));
            if (result == vk::Result::eErrorOutOfDateKHR && attempt < maxAttempts) {
                auto surfaceCaps = vkPhysicalDevice.getSurfaceCapabilitiesKHR(vkSurface);

                spdlog::warn("Vulkan swapchain out of date!");
                // Set buffer sizes

                ResizeSwapchain();
            } else {
                break;
            }
        }

        acquireSemaphoreIndex = (acquireSemaphoreIndex + 1) % acquireSemaphores.size();

        if (result == vk::Result::eSuccess) {
            nvDevice->queueWaitForSemaphore(nvrhi::CommandQueue::Graphics, semaphore, 0);
            return true;
        }
        return false;
    }

    bool VulkanInterface::Present() {
        const auto& semaphore = presentSemaphores[presentSemaphoreIndex];
        nvDevice->queueSignalSemaphore(nvrhi::CommandQueue::Graphics, semaphore, 0);

        // This captures the semaphore apparently
        nvDevice->executeCommandLists(nullptr, 0);

        vk::PresentInfoKHR info = vk::PresentInfoKHR()
        .setWaitSemaphoreCount(1)
        .setPWaitSemaphores(&semaphore)
        .setSwapchainCount(1)
        .setPSwapchains(&vkSwapchain)
        .setPImageIndices(&swapchainIndex);

        const vk::Result result = presentQueue.presentKHR(&info);
        if (!(result == vk::Result::eSuccess || result == vk::Result::eErrorOutOfDateKHR)) {
            return false;
        }

        presentSemaphoreIndex = (presentSemaphoreIndex + 1) % presentSemaphores.size();

        while (framesInFlight.size() >= MAX_FRAMES_IN_FLIGHT) {
            auto query = framesInFlight.front();
            framesInFlight.pop();

            nvDevice->waitEventQuery(query);
            queryPool.push_back(query);
        }

        nvrhi::EventQueryHandle query;
        if (!queryPool.empty()) {
            query = queryPool.back();
            queryPool.pop_back();
        } else {
            query = nvDevice->createEventQuery();
        }

        nvDevice->resetEventQuery(query);
        nvDevice->setEventQuery(query, nvrhi::CommandQueue::Graphics);
        framesInFlight.push(query);
        return true;
    }

    bool VulkanInterface::PickPhysicalDevice() {
        auto devices = vkInstance.enumeratePhysicalDevices();
        vkPhysicalDevice = devices[0]; // dont care just select the first for now

        return true;
    }

    bool VulkanInterface::FindQueueFamilies(vk::PhysicalDevice physicalDevice) {
        auto props = physicalDevice.getQueueFamilyProperties();

        for(int i = 0; i < props.size(); i++) {
            const auto& queueFamily = props[i];

            if (graphicsQueueFamily == -1) {
                if (queueFamily.queueCount > 0 &&
                    (queueFamily.queueFlags & vk::QueueFlagBits::eGraphics)) {
                    graphicsQueueFamily = i;
                }
            }

            if (computeQueueFamily == -1) {
                if (queueFamily.queueCount > 0 &&
                    (queueFamily.queueFlags & vk::QueueFlagBits::eCompute) &&
                    !(queueFamily.queueFlags & vk::QueueFlagBits::eGraphics)) {
                    computeQueueFamily = i;
                }
            }

            if (transferQueueFamily == -1) {
                if (queueFamily.queueCount > 0 &&
                    (queueFamily.queueFlags & vk::QueueFlagBits::eTransfer) &&
                    !(queueFamily.queueFlags & vk::QueueFlagBits::eCompute) &&
                    !(queueFamily.queueFlags & vk::QueueFlagBits::eGraphics)) {
                    transferQueueFamily = i;
                }
            }

            if (presentQueueFamily == -1) {
                if (queueFamily.queueCount > 0 &&
                    SDL_Vulkan_GetPresentationSupport(vkInstance, physicalDevice, i)) {
                    presentQueueFamily = i;
                }
            }
        }

        // no parameters yet
        // if (m_GraphicsQueueFamily == -1 ||
        //     (m_PresentQueueFamily == -1 && !m_DeviceParams.headlessDevice) ||
        //     (m_ComputeQueueFamily == -1 && m_DeviceParams.enableComputeQueue) ||
        //     (m_TransferQueueFamily == -1 && m_DeviceParams.enableCopyQueue)) {
        //     return false;
        // }

        return true;
    }

    bool VulkanInterface::CreateVulkanDevice() {
        auto deviceExtensions = vkPhysicalDevice.enumerateDeviceExtensionProperties();
        for (const auto& extension : deviceExtensions) {
            const std::string name = extension.extensionName;
            if (optionalExtensions.device.contains(name)) {
                // This check happens when headless
                // if (name == VK_KHR_SWAPCHAIN_MUTABLE_FORMAT_EXTENSION_NAME) continue;
                enabledExtensions.device.insert(name);
            }

            // TODO: enable ray tracing extensions here
        }

        // TODO: check if headless here
        enabledExtensions.device.insert(VK_KHR_SWAPCHAIN_EXTENSION_NAME);

        spdlog::info("Enabled Vulkan device extensions:");
        for (const auto& extension : enabledExtensions.device) {
            spdlog::info("- {}", extension);

            // TODO: check for device features (raytracing and stuff)
        }

        std::unordered_set<uint32_t> uniqueQueueFamilies = { graphicsQueueFamily, computeQueueFamily, transferQueueFamily, presentQueueFamily };

        float priority = 1.0f;
        std::vector<vk::DeviceQueueCreateInfo> queueDesc;
        queueDesc.reserve(uniqueQueueFamilies.size());
        for (int family : uniqueQueueFamilies) {
            queueDesc.push_back(vk::DeviceQueueCreateInfo()
                .setQueueFamilyIndex(family)
                .setQueueCount(1)
                .setPQueuePriorities(&priority));
        }

        auto deviceFeatures = vk::PhysicalDeviceFeatures()
            .setShaderImageGatherExtended(true)
            .setSamplerAnisotropy(true)
            .setTessellationShader(true)
            .setTextureCompressionBC(true)
            .setGeometryShader(true)
            .setImageCubeArray(true)
            .setShaderInt16(true)
            .setFillModeNonSolid(true)
            .setFragmentStoresAndAtomics(true)
            .setDualSrcBlend(true)
            .setVertexPipelineStoresAndAtomics(true);

        auto vk11Features = vk::PhysicalDeviceVulkan11Features()
            .setPNext(nullptr);

        auto vk12Features = vk::PhysicalDeviceVulkan12Features()
            .setDescriptorIndexing(true)
            .setRuntimeDescriptorArray(true)
            .setDescriptorBindingPartiallyBound(true)
            .setDescriptorBindingVariableDescriptorCount(true)
            .setTimelineSemaphore(true)
            .setShaderSampledImageArrayNonUniformIndexing(true)
            .setBufferDeviceAddress(true) // TODO: keep track of buffer device address
            .setPNext(&vk11Features);

        auto layerVec = StringSetToVector(enabledExtensions.layers);
        auto deviceVec = StringSetToVector(enabledExtensions.device);

        auto deviceDesc = vk::DeviceCreateInfo()
        .setPQueueCreateInfos(queueDesc.data())
        .setQueueCreateInfoCount(queueDesc.size())
        .setPEnabledFeatures(&deviceFeatures)
        .setEnabledExtensionCount(deviceVec.size())
        .setPpEnabledExtensionNames(deviceVec.data())
        .setEnabledLayerCount(layerVec.size())
        .setPpEnabledLayerNames(layerVec.data())
        .setPNext(&vk12Features);

        // Some weird info callback would happen here in donut

        vk::Result result = vkPhysicalDevice.createDevice(&deviceDesc, nullptr, &vkDevice);
        if (result != vk::Result::eSuccess) {
            spdlog::error("Failed to create logical device! Error Code: {}", nvrhi::vulkan::resultToString(VkResult(result)));
            return false;
        }

        vkDevice.getQueue(graphicsQueueFamily, 0, &graphicsQueue);
        vkDevice.getQueue(computeQueueFamily, 0, &computeQueue);
        vkDevice.getQueue(transferQueueFamily, 0, &transferQueue);
        vkDevice.getQueue(presentQueueFamily, 0, &presentQueue);

        VULKAN_HPP_DEFAULT_DISPATCHER.init(vkDevice);

        // something about bufferDeviceAddress

        spdlog::info("Vulkan device created");
        return true;
    }

    bool VulkanInterface::CreateVulkanSurface() {
        window = SDL_CreateWindow("MANIFOLDEngine", 1280, 720, SDL_WINDOW_VULKAN);
        if (window == nullptr) {
            spdlog::error("Failed to create window! Error: {}", SDL_GetError());
            return false;
        }

        return SDL_Vulkan_CreateSurface(window, vkInstance, nullptr, &vkSurface);
    }

    bool VulkanInterface::CreateSwapchainInternal() {
        auto nvFormat = nvrhi::Format::RGBA8_UNORM; // TODO: make this adjustable
        auto vkFormat = vk::Format(nvrhi::vulkan::convertFormat(nvFormat));
        auto colorSpace = vk::ColorSpaceKHR::eSrgbNonlinear;

        vk::Extent2D extent = { 1280, 720 };

        std::vector<uint32_t> queues = { graphicsQueueFamily, presentQueueFamily };
        const bool enableSharing = queues.size() > 1;

        auto desc = vk::SwapchainCreateInfoKHR()
            .setSurface(vkSurface)
            .setMinImageCount(2) // TODO: allow this to be adjustable
            .setImageFormat(vkFormat)
            .setImageColorSpace(colorSpace)
            .setImageExtent(extent)
            .setImageArrayLayers(1)
            .setImageUsage(vk::ImageUsageFlagBits::eColorAttachment | vk::ImageUsageFlagBits::eTransferDst | vk::ImageUsageFlagBits::eSampled)
            .setImageSharingMode(enableSharing ? vk::SharingMode::eConcurrent : vk::SharingMode::eExclusive)
            .setFlags(vk::SwapchainCreateFlagBitsKHR::eMutableFormat) // TODO: deepnds on mutable swapchain, add check.
            .setQueueFamilyIndexCount(enableSharing ? queues.size() : 0)
            .setPQueueFamilyIndices(enableSharing ? queues.data() : nullptr)
            .setPreTransform(vk::SurfaceTransformFlagBitsKHR::eIdentity)
            .setCompositeAlpha(vk::CompositeAlphaFlagBitsKHR::eOpaque)
            .setPresentMode(vk::PresentModeKHR::eImmediate) // TODO: Immediate means no vsync, FIFO means vsync. Allow this to be set
            .setClipped(true)
            .setOldSwapchain(nullptr);

        std::vector<vk::Format> imageFormats = { vkFormat };
        switch(vkFormat) {
            case vk::Format::eR8G8B8A8Unorm:
                imageFormats.push_back(vk::Format::eR8G8B8A8Srgb);
            break;
            case vk::Format::eR8G8B8A8Srgb:
                imageFormats.push_back(vk::Format::eR8G8B8A8Unorm);
            break;
            case vk::Format::eB8G8R8A8Unorm:
                imageFormats.push_back(vk::Format::eB8G8R8A8Srgb);
            break;
            case vk::Format::eB8G8R8A8Srgb:
                imageFormats.push_back(vk::Format::eB8G8R8A8Unorm);
            break;
            default:
                break;
        }

        auto imageFormatListCreateInfo = vk::ImageFormatListCreateInfo()
        .setViewFormats(imageFormats);

        // TODO: depends on mutable swapchain. add check.
        desc.pNext = &imageFormatListCreateInfo;

        const vk::Result result = vkDevice.createSwapchainKHR(&desc, nullptr, &vkSwapchain);
        if (result != vk::Result::eSuccess) {
            spdlog::error("Failed to create swapchain! Error: {}", nvrhi::vulkan::resultToString(VkResult(result)));
            return false;
        }

        auto images = vkDevice.getSwapchainImagesKHR(vkSwapchain);
        for (auto image : images) {
            SwapChainImage sci;
            sci.image = image;

            nvrhi::TextureDesc textureDesc{};
            textureDesc.width = extent.width;
            textureDesc.height = extent.height;
            textureDesc.format = nvFormat;
            textureDesc.debugName = "Swapchain Image";
            textureDesc.initialState = nvrhi::ResourceStates::Present;
            textureDesc.keepInitialState = true;
            textureDesc.isRenderTarget = true;

            sci.rhiHandle = nvDevice->createHandleForNativeTexture(nvrhi::ObjectTypes::VK_Image, nvrhi::Object(sci.image), textureDesc);
            swapChainImages.push_back(sci);
        }

        swapchainIndex = 0;
        return true;
    }

    void VulkanInterface::DestroySwapchainInternal() {
        if (vkDevice) {
            vkDevice.waitIdle();
        }
        if (vkSwapchain) {
            vkDevice.destroySwapchainKHR(vkSwapchain);
            vkSwapchain = nullptr;
        }

        swapChainImages.clear();
    }

}
