#pragma once

#include "lve_window.hpp"
#include "lve_pipeline.hpp"
#include "lve_device.hpp"
#include "lve_swap_chain.hpp"
#include "lve_model.hpp"

#include <string>
#include <memory>

namespace lve {
	class Application {
		public:
			static const int WIDTH = 800;
			static const int HEIGHT = 800;

			const std::string NAME = "Vulkan test";
			const std::string vertFilepath = "Shaders/vert.spv";
			const std::string fragFilepath = "Shaders/frag.spv";

			Application();
			~Application();

			void run();

		private:
			void createPipelineLayout();
			void createPipeline();
			void createCommandBuffers();
			void drawFrame();
			void loadModels();

			LveWindow lveWindow{ WIDTH, HEIGHT, NAME };
			LveDevice lveDevice{ lveWindow };
			LveSwapChain lveSwapChain{ lveDevice, lveWindow.getExtent() };

			std::unique_ptr<LvePipeline> lvePipeline;
			std::unique_ptr<LveModel> lveModel;

			VkPipelineLayout pipelineLayout;
			std::vector<VkCommandBuffer> commandBuffers;
	};
}
