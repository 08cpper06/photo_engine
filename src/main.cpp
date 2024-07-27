#include <iostream>
#include <GLFW/glfw3.h>


void error_callback(int error, const char* desc) {
	std::cout << "E" << error << ": " << desc << std::endl;
}


int main() {
	glfwSetErrorCallback(error_callback);

	if (!glfwInit()) {
		return 1;
	}

	GLFWwindow* window;
	window = glfwCreateWindow(600, 400, "Preview", nullptr, nullptr);
	if (!window) {
		glfwTerminate();
	}

	glfwMakeContextCurrent(window);

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
	}
	glfwDestroyWindow(window);

	glfwTerminate();

	return 0;
}
