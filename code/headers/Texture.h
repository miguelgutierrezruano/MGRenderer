
// Distributed under MIT License
// @miguelgutierrezruano
// 2023

#pragma once

#include <string>

namespace mg
{
	class Texture
	{

	public:

		unsigned int id;
		std::string type;

	private:

		std::string filePath;
		unsigned char* localBuffer;

		int width;
		int height;
		int bitsPerPixel;

	public:

		Texture(const std::string& path);
	   ~Texture();

		void bind(unsigned slot = 0);
		void unbind();
		
		int getWidth () const { return  width; }
		int getHeight() const { return height; }

		const std::string& getPath() { return filePath; }
	};
}
