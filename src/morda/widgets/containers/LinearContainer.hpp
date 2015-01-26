/* The MIT License:

Copyright (c) 2014 Ivan Gagis

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

#include "Container.hpp"
#include "../../util/Orientable.hpp"
#include "DimContainer.hpp"

#include <ting/types.hpp>


namespace morda{



class LinearContainer :
		public DimContainer,
		public Orientable
{
	LinearContainer(const LinearContainer&) = delete;
	LinearContainer& operator=(const LinearContainer&) = delete;

public:
	LinearContainer(const stob::Node* chain = nullptr);
public:

	void OnResize() override;	
	
	morda::Vec2r ComputeMinDim()const NOEXCEPT override;
	
	
	class LayoutParams : public DimContainer::LayoutParams{
	protected:
		LayoutParams(const stob::Node* chain);
	public:
		real weight;
		
		static std::unique_ptr<LayoutParams> New(const stob::Node* chain = nullptr){
			return std::unique_ptr<LayoutParams>(new LayoutParams(chain));
		}
	};
private:
	std::unique_ptr<morda::LayoutParams> CreateLayoutParams(const stob::Node* chain)const override{
		return LayoutParams::New(chain);
	}
};


}