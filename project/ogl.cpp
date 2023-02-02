#include <glad/glad.h>
#include <C:\glfw-3.3.8\include\GLFW\glfw3.h>
#include <iostream>
#include <C:\hLib\Include/shader_s.h>

// prototypes
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

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

    Shader ourShader("C:/hLib/glProject/LearnOpenGL/project/Shaders/shader.vs", "C:/hLib/glProject/LearnOpenGL/project/Shaders/shader.fs");

    // 2D triangle vertex coordinates
    float triangle[] = {
        // positions         // colors
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
    };

    unsigned int VAOs[2], VBOs[2];  // for single do unsigned int VAO, VBO and reference in genVertexArrays and genBuffers as &VAO or &VBO
    // Generate vertex array objects and vertex buffer objects
    glGenVertexArrays(1, VAOs);
    glGenBuffers(1, VBOs);
    
    // Do VAO and VBO binding and load data into buffer for triangle one
    // Bind Vertex Array Object (Do this before VBO always)
    glBindVertexArray(VAOs[0]);
    // Bind VBO (Only a single buffer, in this case the VBO, can be defined for each buffer type)
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]); // vertex buffer object is of type GL_ARRAY_BUFFER in OpenGL
    // Copy previously defined vertex data into the bound buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);

    // Set vertex attribute pointers
    // 0 is attribute location, 3 is how many numbers (floats in this case), GL_FLOAT is type, 3 * sizeof... is STRIDE in buffer,
    // (void*)0 is starting point
 
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);   // NOTE sizeOf(float) is 4 BYTES
    glEnableVertexAttribArray(0);

    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


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
        
        ourShader.use();
        // Now render the triangle
        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3); // Draw the triangle
        /*glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);*/ // WIREFRAME, COMMENT FOR FILL

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