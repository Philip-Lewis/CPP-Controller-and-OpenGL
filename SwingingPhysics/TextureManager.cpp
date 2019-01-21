#include "TextureManager.h"

void TextureManager::loadTGA(Texture* texture, char* filename)
{
	FILE* TGAFile;
	TGAFile = fopen(filename, "rb");

	if (TGAFile != NULL)
	{
		if (fread(&header, sizeof(TGAHeader), 1, TGAFile) != 0)
		{
			GLubyte uncompTGACompare[12] = { 0,0,2,0,0,0,0,0,0,0,0,0 };
			GLubyte compTGACompare[12] = {0,0,10,0,0,0,0,0,0,0,0,0};

			if (memcmp(uncompTGACompare, &header, sizeof(TGAHeader)) == 0)
			{
				loadUncompressedTGA(texture, filename, TGAFile);
			}
			else if (memcmp(compTGACompare, &header, sizeof(TGAHeader)) == 0)
			{
				loadCompressedTGA(texture, filename, TGAFile);
			}
		}
		else
		{
			if (TGAFile != NULL)
			{
				fclose(TGAFile);
			}
		}
	}
}

void TextureManager::loadUncompressedTGA(Texture* texture, char* filename, FILE* TGAFile)
{
	if (fread(tga.header, sizeof(tga.header), 1, TGAFile) == 0)
	{
		if (TGAFile != NULL)
		{
			fclose(TGAFile);
		}
	}
	else
	{
		texture->width = tga.header[1] * 256 + tga.header[0];
		texture->height = tga.header[3] * 256 + tga.header[2];
		texture->bitsPerPixel = tga.header[4];
		tga.width = texture->width;
		tga.height = texture->height;
		tga.bitsPerPixel = texture->bitsPerPixel;

		if (((texture->width <= 0) || (texture->height <= 0)) || ((texture->bitsPerPixel != 24) && (texture->bitsPerPixel != 32)))
		{
			if (TGAFile != NULL)
			{
				fclose(TGAFile);
			}
		}
		else
		{
			if (texture->bitsPerPixel == 24)
			{
				texture->type = GL_RGB;
			}
			else
			{
				texture->type = GL_RGBA;
			}

			tga.bytesPerPixel = (tga.bitsPerPixel / 8);
			tga.imageSize = (tga.bytesPerPixel * tga.width * tga.height);
			texture->imageData = (GLubyte*)malloc(tga.imageSize);

			if (texture->imageData == NULL)
			{
				fclose(TGAFile);
			}
			else
			{
				if (fread(texture->imageData, 1, tga.imageSize, TGAFile) != tga.imageSize)
				{
					if (texture->imageData != NULL)
					{
						free(texture->imageData);
					}
					fclose(TGAFile);
				}
				else
				{
					for (GLuint i = 0; i < (int)tga.imageSize; i += tga.bytesPerPixel)
					{
						texture->imageData[i] ^= texture->imageData[i + 2] ^=
						texture->imageData[i] ^= texture->imageData[i + 2];
					}

					fclose(TGAFile);
				}
			}
		}
	}
}

void TextureManager::loadCompressedTGA(Texture* texture, char* filename, FILE* TGAFile)
{
	if (fread(tga.header, sizeof(tga.header), 1, TGAFile) == 0)
	{
		if (TGAFile != NULL)
		{
			fclose(TGAFile);
		}
	}
	else
	{
		texture->width = tga.header[1] * 256 + tga.header[0];
		texture->height = tga.header[3] * 256 + tga.header[2];
		texture->bitsPerPixel = tga.header[4];
		tga.width = texture->width;
		tga.height = texture->height;
		tga.bitsPerPixel = texture->bitsPerPixel;

		if (((texture->width <= 0) || (texture->height <= 0)) || ((texture->bitsPerPixel != 24) && (texture->bitsPerPixel != 32)))
		{
			if (TGAFile != NULL)
			{
				fclose(TGAFile);
			}
		}
		else
		{
			if (texture->bitsPerPixel == 24)
			{
				texture->type = GL_RGB;
			}
			else
			{
				texture->type = GL_RGBA;
			}

			tga.bytesPerPixel = (tga.bitsPerPixel / 8);
			tga.imageSize = (tga.bytesPerPixel * tga.width * tga.height);
			texture->imageData = (GLubyte*)malloc(tga.imageSize);

			if (texture->imageData == NULL)
			{
				fclose(TGAFile);
			}
			else
			{
				GLuint pixelCount = tga.height * tga.width;
				GLuint currentPixel = 0;
				GLuint currentByte = 0;
				GLubyte* colorBuffer = (GLubyte*)malloc(tga.bytesPerPixel);

				do
				{
					GLubyte chunkheader = 0;

					if (fread(&chunkheader, sizeof(GLubyte), 1, TGAFile) == 0)
					{
						if (TGAFile != NULL)
						{
							fclose(TGAFile);
						}

						if (texture->imageData != NULL)
						{
							free(texture->imageData);
						}
					}

					if (chunkheader < 128)
					{
						chunkheader++;
						for (short counter = 0; counter < chunkheader; counter++)
						{
							if (fread(colorBuffer, 1, tga.bytesPerPixel, TGAFile) != tga.bytesPerPixel)
							{
								if (TGAFile != NULL)
								{
									fclose(TGAFile);
								}

								if (colorBuffer != NULL)
								{
									free(colorBuffer);
								}

								if (texture->imageData != NULL)
								{
									free(texture->imageData);
								}
							}
							else
							{
								texture->imageData[currentByte] = colorBuffer[2];
								texture->imageData[currentByte + 1] = colorBuffer[1];
								texture->imageData[currentByte + 2] = colorBuffer[0];

								if (tga.bytesPerPixel == 4)
								{
									texture->imageData[currentByte + 3] = colorBuffer[3];
								}

								currentByte += tga.bytesPerPixel;
								currentPixel++;

								if (currentPixel > pixelCount)
								{
									if (TGAFile != NULL)
									{
										fclose(TGAFile);
									}

									if (colorBuffer != NULL)
									{
										free(colorBuffer);
									}

									if (texture->imageData != NULL)
									{
										free(texture->imageData);
									}
								}
							}
						}
					}
					else
					{
						chunkheader -= 127;

						if (fread(colorBuffer, 1, tga.bytesPerPixel, TGAFile) != tga.bytesPerPixel)
						{
							if (TGAFile != NULL)
							{
								fclose(TGAFile);
							}

							if (colorBuffer != NULL)
							{
								free(colorBuffer);
							}

							if (texture->imageData != NULL)
							{
								free(texture->imageData);
							}
						}
						else
						{
							for (short counter = 0; counter < chunkheader; counter++)
							{
								texture->imageData[currentByte] = colorBuffer[2];
								texture->imageData[currentByte + 1] = colorBuffer[1];
								texture->imageData[currentByte + 2] = colorBuffer[0];

								if (tga.bytesPerPixel == 4)
								{
									texture->imageData[currentByte + 3] = colorBuffer[3];
								}

								currentByte += tga.bytesPerPixel;
								currentPixel++;

								if (currentPixel > pixelCount)
								{
									if (TGAFile != NULL)
									{
										fclose(TGAFile);
									}
									
									if (colorBuffer != NULL)
									{
										free(colorBuffer);
									}

									if (texture->imageData != NULL)
									{
										free(texture->imageData);
									}
								}
							}
						}
					}
				}
				while (currentPixel < pixelCount);
				fclose(TGAFile);
			}
		}
	}
}