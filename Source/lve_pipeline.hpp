#pragma once

#include <string>
#include <vector>

#include "lve_device.hpp"

namespace lve {
	struct PipelineConfigInfo {
		VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo;
		VkPipelineRasterizationStateCreateInfo rasterizationInfo;
		VkPipelineViewportStateCreateInfo viewportInfo;
		VkPipelineMultisampleStateCreateInfo multisampleInfo;
		VkPipelineColorBlendAttachmentState colorBlendAttachment;
		VkPipelineColorBlendStateCreateInfo colorBlendInfo;
		VkPipelineDepthStencilStateCreateInfo depthStencilInfo;
		std::vector<VkDynamicState> dynamicStateEnables;
		VkPipelineDynamicStateCreateInfo dynamicStateInfo;
		VkPipelineLayout pipelineLayout = nullptr;
		VkRenderPass renderPass = nullptr;
		uint32_t subpass = 0;
	};

	class LvePipeline {
		public:
			LvePipeline(const PipelineConfigInfo& configInfo,
						const std::string vertFilepath, 
						const std::string fragFilepath,
						LveDevice &device);

			~LvePipeline();

			void bind(VkCommandBuffer commandBuffer);

			static void defaultPipelineConfigInfo(PipelineConfigInfo& configInfo);

		private:
			static std::vector<char> readFile(const std::string &filepath);

			void createPipeline(const PipelineConfigInfo& configInfo, 
								const std::string vertFilepath, 
								const std::string fragFilepath);

			void createShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule);

			LveDevice & lveDevice;
			VkPipeline graphicsPipeline;
			VkShaderModule vertShaderModule;
			VkShaderModule fragShaderModule;
	};
}
