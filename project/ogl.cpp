#include <glad/glad.h>
#include <C:\glfw-3.3.8\include\GLFW\glfw3.h>
#include <iostream>

// prototypes
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main()
{
    // Instantiate GLFW (Graphics Library Framework) window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window object 
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window); // make the context of our window the main context on the current thread.

    // Initialize GLAD before we call any OpenGL function
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    
    // Tell OpenGL the size of the rendering window
    glViewport(0, 0, 800, 600); // 0,0 is location of lower left corner of window and 800, 600 is width and height

    /*When the window is first displayed framebuffer_size_callback gets called as well with the resulting window dimensions.
    For retina displays width and height will end up significantly higher than the original input values.*/
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Render loop, that keeps on running until we tell GLFW to stop.
    while (!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window);
        /*The glfwSwapBuffers will swap the color buffer
        (a large 2D buffer that contains color values for each pixel in GLFW's window) 
        that is used to render to during this render iteration and show it as output to the screen.*/
        glfwPollEvents(); // Check if any events are triggered such as key input or mouse movement, etc.s
    }

    // Delete all of GLFW's resources that were allocated and terminate
    glfwTerminate();
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    return 0;
}   

// Whenever the window changes in size, GLFW calls this function and fills in the proper arguments for viewport adjustment
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}