#pragma once

#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>
#include <iostream>

namespace lve {
	class LveWindow {
		public:
			LveWindow(int h, int w, std::string name);
			~LveWindow();

			bool inline shouldClose() { return glfwWindowShouldClose(window); }

			VkExtent2D inline getExtent() { return { static_cast<uint32_t>(width), static_cast<uint32_t>(height) }; }

			void createWindowSurface(VkInstance instance, VkSurfaceKHR* surface);
			
			bool wasWindowResized() { return framebufferResized; }
  			void resetWindowResizedFlag() { framebufferResized = false; }

		private:
			void initWindow();
			static void framebufferResizeCallback(GLFWwindow *window, int width, int height);

			int width;
			int height;
			bool framebufferResized = false;

			std::string windowName;
			GLFWwindow* window;
	};
}
