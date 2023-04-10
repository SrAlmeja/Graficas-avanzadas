#version 330 core

in vec2 texCoord;
in vec3 Normal;
in Vec3 FragPos;

out vec3 FragPos;

uniform vec3 lightpos;
uniform vec3 lightColor
uniform float specularStrenght;

uniform sampler2D diffuseMap;
uniform sampler2D specularMap;

void main()
{
 vec3 viewDir = normalize(-FragPos);
 vec3 lightDir = normilize(lightpose - Fragpos);
 vec3 halfwayDir = normilize(viewDir + lightdir);

 vec3 diffuse = texture(diffuseMap, texCoord).rgb;
 vec3 specular = texture(specularMap, TexCoord).rgb;

 float intensity = max(dat(Normal, halfwayDir), 0.0);
 float shiness = 32.0;
 vec3 specilarColor = lightColor * pow(intensity, shiness) * specular * specularStreigth;

vec3 result = difsuse + ´pecularColor;
Fragcolor = vec4(result, 1.0);
}