#include "lve_model.hpp"

#include <cassert>
#include <cstring>

namespace lve {
    LveModel::LveModel(LveDevice &device, const std::vector<Vertex> &vertices) : lveDevice{device} {
        createVertexBuffers(vertices);
    }

    LveModel::~LveModel() {
        vkDestroyBuffer(lveDevice.device(), vertexBuffer, nullptr);
        vkFreeMemory(lveDevice.device(), vertexBufferMemory, nullptr);
    }

    void LveModel::createVertexBuffers(const std::vector<Vertex> &vertices) {
        /*  This function creates the data pointer in the host (CPU) and copy that information
            to the vertex buffer information in the GPU */

        vertexCount = static_cast<uint32_t>(vertices.size());
        assert(vertexCount >= 3 && "Vertex count must be at least 3");
        VkDeviceSize bufferSize = sizeof(vertices[0]) * vertexCount; // This is for allocate the memmory
        lveDevice.createBuffer(
            bufferSize,
            VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
            VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, // This is to make it visible to the host
            vertexBuffer,
            vertexBufferMemory); // Create the vertex buffer

        void *data;
        vkMapMemory(lveDevice.device(), vertexBufferMemory, 0, bufferSize, 0, &data); // This is to map the memory with offset 0 and flag 0
        memcpy(data, vertices.data(), static_cast<size_t>(bufferSize));
        vkUnmapMemory(lveDevice.device(), vertexBufferMemory); // Then we unmap the memory
    }

    void LveModel::draw(VkCommandBuffer commandBuffer) {
        vkCmdDraw(commandBuffer, vertexCount, 1, 0, 0); // Just one instance to draw
    }

    void LveModel::bind(VkCommandBuffer commandBuffer) {
        VkBuffer buffers[] = {vertexBuffer};
        VkDeviceSize offsets[] = {0}; // No offsets
        vkCmdBindVertexBuffers(commandBuffer, 0, 1, buffers, offsets); // Starting in vertex 0 we bind 1 by 1
    }

    std::vector<VkVertexInputBindingDescription> LveModel::Vertex::getBindingDescriptions() {
        // This is to especify the parameters in the binding and then use it in the pipeline creation
        std::vector<VkVertexInputBindingDescription> bindingDescriptions(1);
        bindingDescriptions[0].binding = 0;
        bindingDescriptions[0].stride = sizeof(Vertex);
        bindingDescriptions[0].inputRate = VK_VERTEX_INPUT_RATE_VERTEX; 
        return bindingDescriptions;
    }

    std::vector<VkVertexInputAttributeDescription> LveModel::Vertex::getAttributeDescriptions() {
        // This is to especify the parameters of the description and then use it in the pipeline creation
        std::vector<VkVertexInputAttributeDescription> attributeDescriptions(2); // The vertex has 2 attributes
        // The first one is the position (vec3)
        attributeDescriptions[0].binding = 0; 
        attributeDescriptions[0].location = 0;
        attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
        attributeDescriptions[0].offset = offsetof(Vertex, position);
        // The first one is the color (vec3)
        attributeDescriptions[1].binding = 0;
        attributeDescriptions[1].location = 1;
        attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[1].offset = offsetof(Vertex, color);

        return attributeDescriptions;
    }
}
