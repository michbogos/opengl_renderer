#version 330 core
out vec4 FragColor;

uniform sampler2D ourTexture;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoord;

uniform int lights_size;
uniform vec3 lights[100];
uniform vec3 cameraPos;

float specularStrength = 256;


void main()
{
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(vec3(2.0, 2.0, 2.0) - FragPos); 
    vec3 viewDir = normalize(cameraPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm); 
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * vec3(1.0, 1.0, 1.0);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * vec3(1.0, 1.0, 1.0);  
    vec3 result = (vec3(0.3,0.3, 0.3) + diffuse + specular) * vec3(texture(ourTexture, TexCoord)) ;
    FragColor = vec4(result, 1.0);
}