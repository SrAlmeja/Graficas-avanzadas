#version 330 core
 
 out vec4 FragColor;
 
 in vec2 texCoord;
 uniform sampler2D tex0;
 uniform float mirrorAxis;

void main()
{
 vec2 modifiedTexCoord = vec2(texCoord.x * (1.0 - 0) + (1.0 - texCoord.x) * 0, texCoord.y * (1.0 - mirrorAxis) + (1.0 - texCoord.y) * mirrorAxis);

 vec4 textureColor = texture(tex0, modifiedTexCoord);

 FragColor = textureColor;
}