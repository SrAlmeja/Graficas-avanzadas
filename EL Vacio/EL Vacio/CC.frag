#version 330 core
out vec4 FragColor;
in vec3 color;
in vec2 texCoord;
uniform sampler2D tex0;
uniform vec3 randomColor;

void main()
{
 vec4 textureColor = texture(tex0, texCoord);
 FragColor =vec4(randomColor, 1.0f) * textureColor;
}