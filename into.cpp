#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <spdlog/spdlog.h>
#include <vulkan/vulkan.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>

#include <spdlog/spdlog.h>
class HelloTriangleApplication
{
public:
    void run()
    {
        initWindow(); 
        initVulkan();
        mainLoop();
        cleanup();
    }

private:

    GLFWwindow* window; 
    const uint32_t WIDTH = 800; 
    const uint32_t HEIGHT = 600; 
    VkInstance instance; 
    void initVulkan()
    {
        spdlog::info("reached createInstance"); 
        createInstance(); 
    }

    void mainLoop()
    {
        while (!glfwWindowShouldClose(window)) { 
            glfwPollEvents(); 
        }
    }

    void cleanup()
    {
        vkDestroyInstance(instance, nullptr); 
        glfwDestroyWindow(window); 
        glfwTerminate(); 
    }

    void initWindow() {
        glfwInit(); 

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); 
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); //handle resizing later

        window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr); 
    }

    void createInstance() { 
        VkApplicationInfo appInfo {}; 
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO; 
        appInfo.pApplicationName = "hello triangle"; 
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0); 
        appInfo.pEngineName = "No Engine"; 
        appInfo.engineVersion = VK_MAKE_VERSION(1,0, 0); 
        appInfo.apiVersion = VK_API_VERSION_1_0; 

        VkInstanceCreateInfo createInfo{}; 
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO; 
        createInfo.pApplicationInfo = &appInfo;

        uint32_t glfwExtensionCount = 0; 
        const char** glfwExtensions; 
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount); 
        createInfo.enabledExtensionCount = glfwExtensionCount; 
        createInfo.ppEnabledExtensionNames = glfwExtensions; 
        createInfo.enabledLayerCount = 0; 
        VkResult result = vkCreateInstance(&createInfo, nullptr, &instance); 

        if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) { 
            throw std::runtime_error("failed to create instance"); 
        }
        uint32_t extensionCount = 0; 
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr); 
        std::vector<VkExtensionProperties> extensions(extensionCount); 
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data()); 
        spdlog::info("available extensions:" ) ; 
        for (const auto& extension : extensions) { 
            spdlog::info ( extension.extensionName, " " ) ; 
        }
        spdlog::info("vkInstance creation reached --> createInstance() "); 
    }
};

int main()
{
    HelloTriangleApplication app;

    try
    {
        app.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}