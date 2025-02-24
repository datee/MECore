//
// Created by ryen on 2/24/25.
//

#pragma once

#include <queue>
#include <nvrhi/nvrhi.h>
#include <nvrhi/vulkan.h>
#include <vulkan/vulkan.hpp>

#include "Window.h"
#include "VulkanInterface.h"

namespace ME::render {
    class VulkanWindow : public Window {
        protected:
        struct SwapChainImage {
            vk::Image image;
            nvrhi::TextureHandle rhiHandle;
        };

        VulkanInterface* interface;
        SDL_Window* window;
        VkSurfaceKHR surface;

        vk::SwapchainKHR vkSwapchain;
        std::vector<SwapChainImage> swapChainImages;
        uint32_t swapchainIndex;

        std::vector<vk::Semaphore> presentSemaphores;
        std::vector<vk::Semaphore> acquireSemaphores;
        uint32_t presentSemaphoreIndex;
        uint32_t acquireSemaphoreIndex;

        std::queue<nvrhi::EventQueryHandle> framesInFlight;
        std::vector<nvrhi::EventQueryHandle> queryPool;

        bool CreateSwapchainInternal();
        void DestroySwapchainInternal();

        public:
        VulkanWindow(VulkanInterface* interface, SDL_Window* window, VkSurfaceKHR vkSurface);

        bool IsValid() const override;

        SDL_Window* GetWindow() const override { return window; }
        void GetSize(int* width, int* height) const override {
            SDL_GetWindowSize(window, width, height);
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

        bool CreateSwapchain() override;
        void DestroySwapchain() override;
        void Destroy() override;

        bool BeginFrame() override;
        bool Present() override;
    };
}
