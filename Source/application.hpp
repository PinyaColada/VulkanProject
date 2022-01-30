#pragma once

#include "lve_window.hpp"
#include "lve_game_object.hpp"
#include "lve_renderer.hpp"
#include "lve_render_system.hpp"

// Imgui


// Glm 
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include <string>
#include <memory>

namespace lve {

	class Application {
		public:
			static const int WIDTH = 800;
			static const int HEIGHT = 800;

			const std::string NAME = "Vulkan test";

			Application();
			~Application();

			void run();

		private:
			void loadGameObjects();

			LveWindow lveWindow{ WIDTH, HEIGHT, NAME };
			LveDevice lveDevice{ lveWindow };
			LveRenderer lveRenderer{ lveWindow, lveDevice };
			LveRenderSystem lveRenderSystem{ lveDevice, lveRenderer.getSwapChainRenderPass() };

			std::vector<LveGameObject> gameObjects;
	};
}
