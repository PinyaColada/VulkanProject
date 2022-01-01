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

		private:
			void initWindow();

			const int width;
			const int height;

			std::string windowName;
			GLFWwindow* window;
	};
}
