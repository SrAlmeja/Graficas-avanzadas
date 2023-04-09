#include"Texture.h"

Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType)
{
	// Texture definmement
	type = texType;

	int widthTx, heightTx, numCol;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* bytes = stbi_load(image, &widthTx, &heightTx, &numCol, 0);
	
	if(bytes)
	{
		std::cout << "image loaded successfully" << std::endl;
		std::cout << "Width" << widthTx << std::endl;
		std::cout << "heaight" << heightTx << std::endl;
		std::cout << "Number of Chanels" << numCol << std::endl;

		for (int i = 0; i < 16; i++)
		{
			std::cout << "Pixel " << ":R=" << (int)bytes[i * numCol] << "G=" << (int)bytes[1 * numCol + 1] << "b=" << (int)bytes[i * numCol + 2] << std::endl;
		}
	}
	else
	{
		std::cout << "pixel " << "Failed to load image" << std::endl;
	}
	
	// Actiovation and bind of texture object
	glGenTextures(1, &ID);
	glActiveTexture(slot);
	glBindTexture(texType, ID);

	// Settings of the texture
	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	// Repetition of the texture
	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	glTexImage2D(texType, 0, GL_RGB, widthTx, heightTx, 0, GL_RGB, GL_UNSIGNED_BYTE, bytes);
	glGenerateMipmap(texType);
	
	stbi_image_free(bytes);
	glBindTexture(texType, 0);
}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit)
{
	// Gets the location of the uniform
	GLuint texUni = glGetUniformLocation(shader.ID, uniform);
	// Shader needs to be activated before changing the value of a uniform
	shader.Activate();
	// Sets the value of the uniform
	glUniform1i(texUni, unit);
}

void Texture::Bind()
{
	glBindTexture(type, ID);
}

void Texture::Unbind()
{
	glBindTexture(type, 0);
}

void Texture::Delete()
{
	glDeleteTextures(1, &ID);
}
