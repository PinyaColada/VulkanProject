#include "application.hpp"

namespace lve {

	Application::Application()
	{
		createPipelineLayout();
		createPipeline();
		createCommandBuffers();
	}

	Application::~Application()
	{
		vkDestroyPipelineLayout(lveDevice.device(), pipelineLayout, nullptr);
	}

	void Application::run()
	{
		while (!lveWindow.shouldClose()) {
			glfwPollEvents();
		}
	}

	void Application::createPipelineLayout()
	{
		VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
		pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipelineLayoutInfo.setLayoutCount = 0;
		pipelineLayoutInfo.pSetLayouts = nullptr;
		pipelineLayoutInfo.pushConstantRangeCount = 0;
		pipelineLayoutInfo.pPushConstantRanges = nullptr;

		if (vkCreatePipelineLayout(lveDevice.device(), &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS)
			throw std::exception("Failed to create pipeline layout.");
	}

	void Application::createPipeline()
	{
		auto pipelineConfig = LvePipeline::defaultPipelineConfigInfo(lveSwapChain.width(), lveSwapChain.height());
		pipelineConfig.renderPass = lveSwapChain.getRenderPass();
		pipelineConfig.pipelineLayout = pipelineLayout;
		lvePipeline = std::make_unique<LvePipeline> (pipelineConfig, vertFilepath, fragFilepath, lveDevice);
	}

	void Application::createCommandBuffers()
	{
	}

	void Application::drawFrame()
	{
	}
}
