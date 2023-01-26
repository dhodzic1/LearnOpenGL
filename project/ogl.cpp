#include <glad/glad.h>
#include <C:\glfw-3.3.8\include\GLFW\glfw3.h>
#include <iostream>

// prototypes
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// Vertex Shader GLSL
const char *vertexShaderSource = R"(
#version 460 core
layout (location = 0) in vec3 aPos;
void main()
{
   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
};)";

// Fragment 1 Shader GLSL
const char *fragmentShaderSource = R"(
#version 460 core
out vec4 FragColor;
void main()
{
  FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
};)";

// Fragment 2 Shader GLSL
const char* fragmentShaderSourceTwo = R"(
#version 460 core
out vec4 FragColor;
void main()
{
  FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);
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
    float triangleOne[] = {
        -0.5f, -0.5f, 0.0f,
         0.0f, -0.5f, 0.0f,
         0.0f,  0.0f, 0.0f
    };

    float triangleTwo[] = {
         0.0f, 0.0f, 0.0f,
         0.0f, -0.5f, 0.0f,
         0.5, -0.5f, 0.0f
    };

    // Create a vertex shader object
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // Link to vertex shader GLSL source code
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    // Compile the vertex shader
    glCompileShader(vertexShader);

    // Create a fragment shader object
    unsigned int fragmentShader, fragmentShaderTwo;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    fragmentShaderTwo = glCreateShader(GL_FRAGMENT_SHADER);
    // Link to fragment shader GLSL source code
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glShaderSource(fragmentShaderTwo, 1, &fragmentShaderSourceTwo, NULL);
    // Compile the fragment shader
    glCompileShader(fragmentShader);
    glCompileShader(fragmentShaderTwo);

    // error checking for compilation of vertex shader and fragment shader
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    glGetShaderiv(fragmentShaderTwo, GL_COMPILE_STATUS, &success);
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
    else {
        glGetShaderInfoLog(fragmentShaderTwo, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Create Shader program
    unsigned int shaderProgramOrange, shaderProgramYellow;
    shaderProgramOrange = glCreateProgram();
    shaderProgramYellow = glCreateProgram();

    // Attach previously defined vertex and fragment shaders to shader program object
    glAttachShader(shaderProgramOrange, vertexShader);
    glAttachShader(shaderProgramOrange, fragmentShader);
    // Link the attached shaders via glLinkProgram 
    glLinkProgram(shaderProgramOrange);

    glAttachShader(shaderProgramYellow, vertexShader);
    glAttachShader(shaderProgramYellow, fragmentShaderTwo);
    // Link the attached shaders via glLinkProgram 
    glLinkProgram(shaderProgramYellow);

    // error checking for shader program linking
    glGetProgramiv(shaderProgramOrange, GL_LINK_STATUS, &success);
    if (!success) 
    {
        glGetProgramInfoLog(shaderProgramOrange, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    glGetProgramiv(shaderProgramYellow, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgramYellow, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Delete defined shaders since they've been linked into shader program
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteShader(fragmentShaderTwo);

    unsigned int VAOs[2], VBOs[2];
    // Generate vertex array objects and vertex buffer objects
    glGenVertexArrays(2, VAOs);
    glGenBuffers(2, VBOs);
    
    // Do VAO and VBO binding and load data into buffer for triangle one
    // Bind Vertex Array Object (Do this before VBO always)
    glBindVertexArray(VAOs[0]);
    // Bind VBO (Only a single buffer, in this case the VBO, can be defined for each buffer type)
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]); // vertex buffer object is of type GL_ARRAY_BUFFER in OpenGL
    // Copy previously defined vertex data into the bound buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleOne), triangleOne, GL_STATIC_DRAW);
    // Set vertex attribute pointers
    // 0 is attribute location, 3 is how many numbers (floats in this case), GL_FLOAT is type, 3 * sizeof... is STRIDE in buffer,
    // (void*)0 is starting point
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Do VAO and VBO binding and load data into buffer triangle two
    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleTwo), triangleTwo, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Generate element buffer object and bind it
    /*unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/
  

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
        glUseProgram(shaderProgramOrange);
        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3); // Draw the triangle
        /*glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);*/ // WIREFRAME, COMMENT FOR FILL

        glUseProgram(shaderProgramYellow);
        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
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
    glDeleteVertexArrays(2, VAOs);
    glDeleteBuffers(2, VBOs);
    glDeleteProgram(shaderProgramOrange);
    glDeleteProgram(shaderProgramYellow);

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