/* The MIT License:

Copyright (c) 2012-2015 Ivan Gagis <igagis@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE. */

// Home page: http://morda.googlecode.com

/**
 * @author Ivan Gagis <igagis@gmail.com>
 */

#pragma once

#include "../config.hpp"

#if M_MORDA_RENDER == M_MORDA_RENDER_OPENGLES
#	include <GLES2/gl2.h>
#else
#	include <GL/glew.h>
#endif

#include <ting/debug.hpp>

#include "Vector2.hpp"

#include "Image.hpp"



namespace morda{



class Texture{
	
	Texture(const Texture& tex) = delete;
	Texture& operator=(const Texture& tex) = delete;

	GLuint tex = 0;

	morda::Vec2r dim;

	void Constructor(Vec2ui d, unsigned numChannels, ting::Buffer<const std::uint8_t> data, GLint minFilter, GLint magFilter);
public:
	Texture(const Image& image, GLint minFilter = GL_LINEAR, GLint magFilter = GL_LINEAR){
		this->Constructor(image.Dim(), image.NumChannels(), image.Buf(), minFilter, magFilter);
	}
	
	Texture(Vec2ui dimensions, unsigned numChannels, GLint minFilter = GL_LINEAR, GLint magFilter = GL_LINEAR){
		this->Constructor(dimensions, numChannels, ting::Buffer<const std::uint8_t>(), minFilter, magFilter);
	}

	Texture(){}

	~Texture()NOEXCEPT{
		this->Destructor();
	}

	void Init(const Image& image, GLint minFilter = GL_LINEAR, GLint magFilter = GL_LINEAR){
		if(this->tex != 0){
			this->Destructor();
		}

		this->Constructor(image.Dim(), image.NumChannels(), image.Buf(), minFilter, magFilter);
	}

	void Bind()const{
		ASSERT(glGetError() == GL_NO_ERROR)
		glBindTexture(GL_TEXTURE_2D, this->tex);
		ASSERT(glGetError() == GL_NO_ERROR)
	}
	
	void Bind(unsigned texUnitNum)const{
		ASSERT(glGetError() == GL_NO_ERROR)
		glActiveTexture(GL_TEXTURE0 + texUnitNum);
		ASSERT(glGetError() == GL_NO_ERROR)
		glBindTexture(GL_TEXTURE_2D, this->tex);
		ASSERT(glGetError() == GL_NO_ERROR)
	}

	morda::Vec2r Dim()const NOEXCEPT{
		return this->dim;
	}

private:
	void Destructor()NOEXCEPT{
		glBindTexture(GL_TEXTURE_2D, 0);
		glDeleteTextures(1, &this->tex);
	}
};



}//~namespace