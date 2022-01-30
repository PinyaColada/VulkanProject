#pragma once

#include "lve_device.hpp"
#include "lve_game_object.hpp"
#include "lve_pipeline.hpp"

// std
#include <memory>
#include <vector>

namespace lve
{
  struct SimplePushConstantData
  {
    glm::mat2 transform{1.f};
    glm::vec2 offset;
    alignas(16) glm::vec3 color;
  };

  class LveRenderSystem
  {
  public:
    LveRenderSystem(LveDevice &device, VkRenderPass renderPass);
    ~LveRenderSystem();

    LveRenderSystem(const LveRenderSystem &) = delete;
    LveRenderSystem &operator=(const LveRenderSystem &) = delete;

    void renderGameObjects(VkCommandBuffer commandBuffer, std::vector<LveGameObject> &gameObjects);

  private:
    void createPipelineLayout();
    void createPipeline(VkRenderPass renderPass);

    const std::string vertFilepath = "Shaders/vert.spv";
    const std::string fragFilepath = "Shaders/frag.spv";

    LveDevice &lveDevice;

    std::unique_ptr<LvePipeline> lvePipeline;
    VkPipelineLayout pipelineLayout;
  };
} // namespace lve