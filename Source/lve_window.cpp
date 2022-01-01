#include "lve_window.hpp"

#include <stdexcept>

namespace lve{
	LveWindow::LveWindow(int h, int w, std::string name) : height{ h }, width{ w }, windowName{ name }{
		initWindow();
	}

	LveWindow::~LveWindow() {
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	void LveWindow::initWindow() {
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // No utilitzam openGL aixi que totes ses funcionalitats base fora
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); // Perque no peti quan feim resize

		// Aquest es es window* que utilitzam per tancar o manipular
		window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr); // Crea una finestra, es primer nullptr es per fullscreen es segon es per pasar info
	}
	void LveWindow::createWindowSurface(VkInstance instance, VkSurfaceKHR* surface)
	{
		if (glfwCreateWindowSurface(instance, window, nullptr, surface) != VK_SUCCESS)
			throw std::runtime_error("Failed to create the window surface");
	}
}