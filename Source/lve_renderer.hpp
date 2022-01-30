#pragma once

#include "lve_window.hpp"
#include "lve_device.hpp"
#include "lve_swap_chain.hpp"

#include <string>
#include <memory>
#include <assert.h>

namespace lve {
	class LveRenderer {
		public:
			const std::string NAME = "Vulkan test";
			const std::string vertFilepath = "Shaders/vert.spv";
			const std::string fragFilepath = "Shaders/frag.spv";

			LveRenderer(LveWindow &lveWindow, LveDevice &lveDevice);
			~LveRenderer();

            bool inline isFrameInProgress() const { return isFrameStarted; }
			int inline getFrameIndex() const { return currentFrameIndex; }
            VkRenderPass getSwapChainRenderPass() const { return lveSwapChain->getRenderPass(); }
            VkCommandBuffer getCurrentCommandBuffer() const {
                assert(isFrameStarted && "Cannot get command buffer when the frame is not in progress");
                return commandBuffers[currentFrameIndex]; 
            }

            VkCommandBuffer beginFrame();
            void endFrame();
            void beginSwapChainRenderPass(VkCommandBuffer commandBuffer);
            void endSwapChainRenderPass(VkCommandBuffer commandBuffer);
		private:
			void createCommandBuffers();
			void freeCommandBuffers();
			void recreateSwapChain();

            uint32_t currentImageIndex;
			int currentFrameIndex = 0;
            bool isFrameStarted = false;

			LveWindow& lveWindow;
			LveDevice& lveDevice;
			std::unique_ptr<LveSwapChain> lveSwapChain;
			std::vector<VkCommandBuffer> commandBuffers;
	};
}
