#pragma once

#include <string>
#include <vector>

#include "lve_device.hpp"

namespace lve {
	struct pipelineConfigInfo {
		VkViewport viewport;
		VkRect2D scissor;
		VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo;
		VkPipelineRasterizationStateCreateInfo rasterizationInfo;
		VkPipelineMultisampleStateCreateInfo multisampleInfo;
		VkPipelineColorBlendAttachmentState colorBlendAttachment;
		VkPipelineColorBlendStateCreateInfo colorBlendInfo;
		VkPipelineDepthStencilStateCreateInfo depthStencilInfo;
		VkPipelineLayout pipelineLayout = nullptr;
		VkRenderPass renderPass = nullptr;
		uint32_t subpass = 0;
	};

	class LvePipeline {
		public:
			LvePipeline(const pipelineConfigInfo& configInfo,
						const std::string vertFilepath, 
						const std::string fragFilepath,
						LveDevice &device);

			~LvePipeline();

			static pipelineConfigInfo defaultPipelineConfigInfo(uint32_t width, uint32_t height);

		private:
			static std::vector<char> readFile(const std::string &filepath);

			void createPipeline(const pipelineConfigInfo& configInfo, 
								const std::string vertFilepath, 
								const std::string fragFilepath);

			void createShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule);

			LveDevice & lveDevice;
			VkPipeline graphicsPipeline;
			VkShaderModule vertShaderModule;
			VkShaderModule fragShaderModule;
	};
}
