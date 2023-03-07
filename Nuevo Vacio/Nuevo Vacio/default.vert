#version 330 core
layout (location = 0) in vec3 aPos;

uniform float scale;
uniform float time;

void main()
{
    gl_Position = vec4(aPos.x + aPos.x * (scale),
                        aPos.y + aPos.y * scale,
                        aPos.z + aPos.z * scale, 1.0);
}
