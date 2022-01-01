#pragma once

#include "lve_window.hpp"
#include "lve_pipeline.hpp"
#include "lve_device.hpp"
#include "lve_swap_chain.hpp"

#include <string>
#include <memory>

namespace lve {
	class Application {
		public:
			static const int WIDTH = 800;
			static const int HEIGHT = 800;
			const std::string NAME = "Vulkan test";
			const std::string vertFilepath = "Shaders/base_shader.vert.spv";
			const std::string fragFilepath = "Shaders/base_shader.frag.spv";

			Application();
			~Application();

			void run();

		private:
			void createPipelineLayout();
			void createPipeline();
			void createCommandBuffers();
			void drawFrame();

			LveWindow lveWindow{ WIDTH, HEIGHT, NAME };
			LveDevice lveDevice{ lveWindow };
			LveSwapChain lveSwapChain{ lveDevice, lveWindow.getExtent() };
			std::unique_ptr<LvePipeline> lvePipeline;
			VkPipelineLayout pipelineLayout;
			std::vector<VkCommandBuffer> commandBuffers;
	};
}
