#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 Normal;
out vec3 FragPos;  

void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0));    // calculate fragment position = model matrix * vertexPosition

    // The normal matrix is defined as 'the transpose of the inverse of the upper-left 3x3 part of the model matrix'
    Normal = mat3(transpose(inverse(model))) * aNormal; // notice that we isolate the 3x3 part by casting to a mat3
    // NOTE INVERSE of a matrix is costly, only done in book for learning purposes
    // Usually, you would have to calculate the normal matrix on CPU and then send it to shaders via uniform just like the model matrix

    gl_Position = projection * view * vec4(FragPos, 1.0);
}