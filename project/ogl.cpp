#include <glad/glad.h>
#include <C:\glfw-3.3.8\include\GLFW\glfw3.h>
#include <iostream>

// prototypes
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// Vertex Shader GLSL
const char* vertexShaderSource = R"(
#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor; 
out vec3 ourColor;
void main()
{
   gl_Position = vec4(aPos, 1.0);
   ourColor = aColor;
};)";

// Fragment 1 Shader GLSL
const char* fragmentShaderSource = R"(
#version 460 core
out vec4 FragColor;
in vec3 ourColor;
void main()
{
    FragColor = vec4(ourColor, 1.0);
};)";


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

    //// rectangle vertices
    //float vertices[] = {
    // 0.5f,  0.5f, 0.0f,  // top right
    // 0.5f, -0.5f, 0.0f,  // bottom right
    //-0.5f, -0.5f, 0.0f,  // bottom left
    //-0.5f,  0.5f, 0.0f   // top left 
    //};

    //// indices to be used for element buffer object (EBO)
    //unsigned int indices[] = {  // note that we start from 0!
    //    0, 1, 3,   // first triangle
    //    1, 2, 3    // second triangle
    //};

    // 2D triangle vertex coordinates
    float triangle[] = {
        // positions         // colors
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
    };

    // Create a vertex shader object
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // Link to vertex shader GLSL source code
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    // Compile the vertex shader
    glCompileShader(vertexShader);

    // Create a fragment shader object
    unsigned int fragmentShader; /*fragmentShaderTwo;*/
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    
    // Link to fragment shader GLSL source code
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    
    // Compile the fragment shader
    glCompileShader(fragmentShader);
  

    // error checking for compilation of vertex shader and fragment shader
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    if (!success && &fragmentShader)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    } 

    // Create Shader program
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    // Attach previously defined vertex and fragment shaders to shader program object
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    // Link the attached shaders via glLinkProgram 
    glLinkProgram(shaderProgram);

    // error checking for shader program linking
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) 
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Delete defined shaders since they've been linked into shader program
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    unsigned int VAOs[2], VBOs[2];
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
        
        // Activate shader program
        glUseProgram(shaderProgram);

        float timeValue = glfwGetTime();
        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
       
        // Now render the triangle
        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3); // Draw the triangle
        /*glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);*/ // WIREFRAME, COMMENT FOR FILL

        // Draw rectangle
        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        //// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // WIREFRAME
        //glBindVertexArray(0);

        // check and call events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents(); // Check if any events are triggered such as key input or mouse movement, etc.s
    }

    // Deallocate all resources once they're done with
    glDeleteVertexArrays(1, VAOs);
    glDeleteBuffers(1, VBOs);
    glDeleteProgram(shaderProgram);

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