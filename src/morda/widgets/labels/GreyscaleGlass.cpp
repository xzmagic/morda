#include "GreyscaleGlass.hpp"

#include "../../util/Texture2D.hpp"

#include "../../App.hpp"


using namespace morda;



GreyscaleGlass::GreyscaleGlass(const stob::Node* chain) :
		Widget(chain)
{}



void GreyscaleGlass::Render(const morda::Matr4r& matrix) const{
	Texture2D texture(this->Rect().d.ConvertTo<unsigned>(), 3, Render::ETexFilter::NEAREST, Render::ETexFilter::NEAREST);
	//texture is bound right after creation
	
	Rect2i viewPortRect = this->ComputeViewportRect(matrix);
	
	if(!viewPortRect.d.IsPositive()){
		return;
	}
	
	Render::copyColorBufferToTexture(Vec2i(0), viewPortRect);
	
	morda::Matr4r matr(matrix);
	matr.Scale(this->Rect().d);

	morda::PosTexShader &s = App::Inst().Shaders().simpleGrayscalePosTexShader;

	s.SetMatrix(matr);
	
	s.render(morda::PosShader::quad01Fan, s.quadFanTexCoords);
}
