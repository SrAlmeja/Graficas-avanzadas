#include"Texture.h"

Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType)
{
	// Texture definmement
	type = texType;
	int widthTx, heightTx, numCol;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* bytes = stbi_load(image, &widthTx, &heightTx, &numCol, 0);
	// Actiovation and bind of texture object
	glGenTextures(1, &ID);
	glActiveTexture(slot);
	glBindTexture(texType, ID);
	// Settings of the texture
	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// Repetition of the texture
	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(texType, 0, GL_RGBA, widthTx, heightTx, 0, format, pixelType, bytes);
	glGenerateMipmap(texType);
	stbi_image_free(bytes);
	glBindTexture(texType, 0);
}