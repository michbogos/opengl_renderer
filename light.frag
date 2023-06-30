#version 330 core
out vec4 FragColor;

uniform sampler2D SPECULAR_0;
uniform sampler2D NORMAL_0;
uniform sampler2D DIFFUSE_0;
uniform sampler2D DIFFUSE_2;

in vec3 Normal;
in vec3 FragPos;
in vec3 Tangent;
in vec2 TexCoord;

uniform int lights_size;
uniform vec3 lights[100];
uniform vec3 cameraPos;

float specularStrength = float(texture(SPECULAR_0, TexCoord));

vec3 CalcPointLight(vec3 position, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 16);
    // attenuation
    float distance    = length(position - fragPos);
    float attenuation = 1.0 / (1.0 + 0.09 * distance + 
  			     0.035 * (distance * distance));    
    // combine results
    vec3 ambient  = vec3(1.0, 1.0, 1.0)  * vec3(texture(DIFFUSE_0, TexCoord));
    vec3 diffuse  = vec3(1.0, 1.0, 1.0)  * diff * vec3(texture(DIFFUSE_0, TexCoord));
    vec3 specular = vec3(1.0, 1.0, 1.0)  * spec * vec3(texture(SPECULAR_0, TexCoord));
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular)*texture(DIFFUSE_2, TexCoord).x;
} 


void main()
{
    vec3 norm = normalize(Normal);
    vec3 tangent = normalize(Tangent);
    tangent = normalize(tangent - dot(tangent, norm) * norm);
    vec3 Bitangent = cross(tangent, norm);
    vec3 BumpMapNormal = texture(NORMAL_0, TexCoord).xyz;
    BumpMapNormal = 2.0 * BumpMapNormal - vec3(1.0, 1.0, 1.0);
    vec3 NewNormal;
    mat3 TBN = mat3(tangent, Bitangent, norm);
    NewNormal = TBN * BumpMapNormal;
    NewNormal = normalize(NewNormal);


    vec3 viewDir = normalize(cameraPos - FragPos);
    vec3 result = vec3(0.0, 0.0, 0.0);
    for(int i = 0; i < lights_size; i++){
        result += CalcPointLight(lights[i], NewNormal, FragPos, viewDir);
    }
    FragColor = vec4(result, 1.0);
    //FragColor = texture(DIFFUSE_1, TexCoord);
}