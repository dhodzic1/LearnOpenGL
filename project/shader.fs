#version 460 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos; 

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{	
	// ambient = (light color * ambientStrength) * objectColor
	float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    // diffuse 
    vec3 norm = normalize(Normal);  // we always work with unit vectors, so DONT FORGET TO NORMALIZE VECTORS
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0); // diffuse impact on current fragment is dot product of normal vector and light direction vector
    vec3 diffuse = diff * lightColor;   // multiply result with lightColor to get diffuse component

    // specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm); 
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);   // raised to power of 32 for 'shininess' of highlight
    vec3 specular = specularStrength * spec * lightColor;  

    vec3 result = (ambient + diffuse + specular) * objectColor;
	FragColor = vec4(result, 1.0);
}