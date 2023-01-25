#include <glad/glad.h>
#include <C:\glfw-3.3.8\include\GLFW\glfw3.h>
#include <iostream>

// prototypes
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// Vertex Shader GLSL
const char *vertexShaderSource = "#version 460 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

// Fragment Shader GLSL
const char *fragmentShaderSource = "#version 460 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"  FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";

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

    // 2D triangle vertex coordinates
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    // Generate vertex buffer object to send vertex coordinates to GPU
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    // Bind VBO (Only a single buffer, in this case the VBO, can be defined for each buffer type)
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // vertex buffer object is of type GL_ARRAY_BUFFER in OpenGL
    // Copy previously defined vertex data into the bound buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    /*
    * GL_STREAM_DRAW: the data is set only once and used by the GPU at most a few times.
    * GL_STATIC_DRAW: the data is set only once and used many times.
    * GL_DYNAMIC_DRAW: the data is changed a lot and used many times.
    */

    // Create a vertex shader object
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // Link to vertex shader GLSL source code
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    // Compile the vertex shader
    glCompileShader(vertexShader);

    // Create a fragment shader object
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // Link to fragment shader GLSL source code
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    // Compile the fragment shader
    glCompileShader(fragmentShader);

    // error checking for compilation of vertex shader and fragment shader
    int successV;
    int successF;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &successV);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &successF);
    if (!successV)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    if (!successF)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Render loop, that keeps on running until we tell GLFW to stop.
    /*The glfwSwapBuffers will swap the color buffer
    (a large 2D buffer that contains color values for each pixel in GLFW's window)
    that is used to render to during this render iteration and show it as output to the screen.*/
    while (!glfwWindowShouldClose(window))
    {   
        // input
        processInput(window);

        // rendering commands here ...
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // Specify color to clear screen with
        glClear(GL_COLOR_BUFFER_BIT); // clear the color buffer

        // check and call events and swap the buffers
        glfwSwapBuffers(window);
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

// Function that closes open GLFW window when ESC key is pressed
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}