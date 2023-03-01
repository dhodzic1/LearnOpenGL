#version 460 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

// In this struct we define a color vector for each of Phong's lighting components
struct Material {
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
    float shininess;
}; 

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Material material;  // uniform where the type is structname Material
uniform Light light;
uniform vec3 viewPos;
uniform float time;

void main()
{	
	// ambient
    vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;

    // diffuse 
    vec3 norm = normalize(Normal);  // we always work with unit vectors, so DONT FORGET TO NORMALIZE VECTORS
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0); // diffuse impact on current fragment is dot product of normal vector and light direction vector
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb; 

    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm); 
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);   // raised to power of material.shininess for 'shininess' of highlight
    vec3 specular = light.specular * spec * (texture(material.specular, TexCoords).rgb);

    // emission
    vec2 myTexCoords = TexCoords;
    myTexCoords.x = myTexCoords.x + 0.045f; // slightly shift texture on x for better alignment
    vec3 emissionMap = texture(material.emission, myTexCoords + vec2(0.0,time*0.75)).rgb;
    vec3 emission = emissionMap * (sin(time)*0.5f+0.5f)*2.0;

    // emission mask
    vec3 emissionMask = step(vec3(1.0f), vec3(1.0f)-texture(material.specular, TexCoords).rgb); 
    emission = emission * emissionMask;

    vec3 result = ambient + diffuse + specular + emission;
	FragColor = vec4(result, 1.0);
}