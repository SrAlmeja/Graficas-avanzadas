#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTex;
out vec2 texCoord;
out vec3 color;
uniform float scale;
void main()
{
 gl_Position = vec4(
 aPos.x + aPos.x * scale * 1.5f,
 aPos.y + aPos.y * scale * 1.5f,
 aPos.z + aPos.z * scale * 1.5f, 1.0);
 color = aColor;
}