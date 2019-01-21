#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#include "Dependencies\GLEW\glew.h"
#include "Dependencies\FREEGLUT\freeglut.h"
#include "Dependencies\FREEGLUT\glut.h"
#include <stdio.h>
#include <vector>

class TextureManager
{
public:
	struct Texture
	{
		GLubyte* imageData;
		GLuint bitsPerPixel;
		GLuint width;
		GLuint height;
		GLuint type;
		char* textureName;
	};

	void addTexture(char* texName, char* fileName)
	{
		Texture* temp = new Texture();
		temp->textureName = texName;
		loadTGA(temp, fileName);
		textures.push_back(temp);
	}

	Texture* getTexture(char* texName)
	{
		Texture* temp;
		for (int i = 0; i < textures.size() - 1; i++)
		{
			if (textures.at(i)->textureName == texName)
			{
				temp = textures.at(i);
				return temp;
			}
		}

		return nullptr;
	}

private:
	struct TGAHeader
	{
		GLubyte Header[12];
	};

	struct TGA
	{
		GLubyte header[6];
		GLuint bytesPerPixel;
		GLuint imageSize;
		GLuint height;
		GLuint width;
		GLuint bitsPerPixel;
	};

	TGAHeader header;
	TGA tga;
	std::vector<Texture*> textures;

	void loadTGA(Texture* texture, char* filename);
	void loadCompressedTGA(Texture* texture, char* filename, FILE* TGAFile);
	void loadUncompressedTGA(Texture* texture, char* filename, FILE* TGAFile);
};
#endif
