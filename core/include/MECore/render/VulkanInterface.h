//
// Created by ryen on 2/21/25.
//

// A lot of this code is derived/copied from NVIDIA's Donut.
// Donut is licensed under the MIT License.

#pragma once

#include <unordered_set>
#include <queue>

#ifndef VULKAN_HPP_DISPATCH_LOADER_DYNAMIC
#define VULKAN_HPP_DISPATCH_LOADER_DYNAMIC 1
#endif
#include <vulkan/vulkan.hpp>
#include <nvrhi/vulkan.h>

#include "RenderInterface.h"

namespace ME::render {
    class VulkanInterface : public RenderInterface {
        protected:
        struct VulkanExtensionSet {
            std::unordered_set<std::string> instance;
            std::unordered_set<std::string> layers;
            std::unordered_set<std::string> device;
        };

        struct SwapChainImage {
            vk::Image image;
            nvrhi::TextureHandle rhiHandle;
        };

        VulkanExtensionSet enabledExtensions = {
            { VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME, VK_EXT_DEBUG_REPORT_EXTENSION_NAME },
            { },
            { VK_KHR_MAINTENANCE1_EXTENSION_NAME }
        };

        VulkanExtensionSet optionalExtensions = {
            {
                VK_EXT_DEBUG_UTILS_EXTENSION_NAME,
                VK_EXT_SAMPLER_FILTER_MINMAX_EXTENSION_NAME,
            },
            { },
            {
                VK_EXT_DEBUG_MARKER_EXTENSION_NAME,
                VK_EXT_DESCRIPTOR_INDEXING_EXTENSION_NAME,
                VK_KHR_BUFFER_DEVICE_ADDRESS_EXTENSION_NAME,
                VK_KHR_FRAGMENT_SHADING_RATE_EXTENSION_NAME,
                VK_KHR_MAINTENANCE_4_EXTENSION_NAME,
                VK_KHR_SWAPCHAIN_MUTABLE_FORMAT_EXTENSION_NAME,
                VK_KHR_SYNCHRONIZATION_2_EXTENSION_NAME,
                VK_NV_MESH_SHADER_EXTENSION_NAME,
            }
        };

        // Vulkan Device
        vk::Instance vkInstance;
        vk::PhysicalDevice vkPhysicalDevice;
        uint32_t graphicsQueueFamily = -1;
        uint32_t computeQueueFamily = -1;
        uint32_t transferQueueFamily = -1;
        uint32_t presentQueueFamily = -1;

        vk::Device vkDevice;
        vk::Queue graphicsQueue;
        vk::Queue computeQueue;
        vk::Queue transferQueue;
        vk::Queue presentQueue;

        // Surface
        SDL_Window* window;
        VkSurfaceKHR vkSurface;

        // Swapchain
        vk::SwapchainKHR vkSwapchain;
        std::vector<SwapChainImage> swapChainImages;
        uint32_t swapchainIndex;

        std::vector<vk::Semaphore> presentSemaphores;
        std::vector<vk::Semaphore> acquireSemaphores;
        uint32_t presentSemaphoreIndex;
        uint32_t acquireSemaphoreIndex;

        std::queue<nvrhi::EventQueryHandle> framesInFlight;
        std::vector<nvrhi::EventQueryHandle> queryPool;

        // NVRHI
        nvrhi::vulkan::DeviceHandle nvDevice;
        nvrhi::DeviceHandle nvValidationLayer;

        bool PickPhysicalDevice();
        bool FindQueueFamilies(vk::PhysicalDevice physicalDevice);
        bool CreateVulkanDevice();
        bool CreateVulkanSurface();

        bool CreateSwapchainInternal();
        void DestroySwapchainInternal();

        public:
        VulkanInterface() = default;
        ~VulkanInterface() override = default;

        bool CreateInstance() override;
        bool CreateDevice() override;
        bool CreateSwapchain() override;

        void DestroyDevice() override;
        void DestroySwapchain() override;

        void ResizeSwapchain() override;

        bool BeginFrame() override;
        bool Present() override;

        nvrhi::IDevice* GetDevice() override {
            if (nvValidationLayer) return nvValidationLayer;
            return nvDevice;
        }

        Uint32 GetSwapchainCount() override {
            return swapChainImages.size();
        }
        Uint32 GetCurrentSwapchainIndex() override {
            return swapchainIndex;
        }
        nvrhi::ITexture* GetSwapchainTexture(Uint32 index) override {
            if (index < swapChainImages.size()) {
                return swapChainImages[index].rhiHandle;
            }
            return nullptr;
        }
        nvrhi::ITexture* GetCurrentSwapchainTexture() override {
            return swapChainImages[swapchainIndex].rhiHandle;
        }

        SDL_Window* GetWindow() override {
            return window;
        }
    };
}
