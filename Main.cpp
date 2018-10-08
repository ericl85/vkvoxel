#include <iostream>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

using namespace std;

int main(int argc, char* args[])
{
	if (glfwVulkanSupported())
	{
		cout << "Vulkan is supported!!!!!" << endl;
	}
	else
	{
		cout << "Vulkan is not supported!!!!" << endl;
	}
}
