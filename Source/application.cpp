#include "application.hpp"

#include <stdexcept>
#include <array>

namespace lve {

	Application::Application()
	{
		loadGameObjects(); // Load the model from the objects
	}

	Application::~Application()
	{
	}

	void Application::run()
	{
		while (!lveWindow.shouldClose()) {
			glfwPollEvents();
			
			if (auto CommandBuffer = lveRenderer.beginFrame()){
				lveRenderer.beginSwapChainRenderPass(CommandBuffer); // Begin to 
				lveRenderSystem.renderGameObjects(CommandBuffer, gameObjects);
				lveRenderer.endSwapChainRenderPass(CommandBuffer);
				lveRenderer.endFrame();
			}
		}

		vkDeviceWaitIdle(lveDevice.device());
	}
	
	void Application::loadGameObjects() {
		std::vector<LveModel::Vertex> vertices{
			{{0.0f, -0.5f}, {1.0f, 0.0f, 0.0f}},
			{{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
			{{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}}};
		auto lveModel = std::make_shared<LveModel>(lveDevice, vertices);

		auto triangle = LveGameObject::createGameObject();
		triangle.model = lveModel;
		triangle.color = {1.0f, 1.0f, 0.0f};
		triangle.transform2d.translation.x = 1.0f;
		triangle.transform2d.scale = {2.f, .5f};
  		triangle.transform2d.rotation = .25f * glm::two_pi<float>();

		gameObjects.push_back(std::move(triangle));
	}
} // End namespace
