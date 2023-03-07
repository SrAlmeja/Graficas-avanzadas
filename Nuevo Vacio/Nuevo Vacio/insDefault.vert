#version 330 core
layout (location = 0) in vec3 aPos;

uniform float scale;
uniform float time;

void main()
{
    gl_Position = vec4(aPos.x + aPos.x * (scale/5),
                        aPos.y + aPos.y * (scale/5),
                        aPos.z + aPos.z * (scale/5), 1.0);
}
