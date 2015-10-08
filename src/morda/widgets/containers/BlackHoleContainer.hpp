/**
 * @author Ivan Gagis <igagis@gmail.com>
 */

#pragma once

#include "FrameContainer.hpp"

namespace morda{


/**
 * @brief Container which makes minimal size to be zero.
 */
class BlackHoleContainer : public FrameContainer{
	kolme::Vec2b shrink;
public:
	BlackHoleContainer(const stob::Node* chain = nullptr);
	
	BlackHoleContainer(const BlackHoleContainer&) = delete;
	BlackHoleContainer& operator=(const BlackHoleContainer&) = delete;
	
	Vec2r measure(const morda::Vec2r& constraint)const override;
	
	void setShrink(kolme::Vec2b shrink){
		this->shrink = shrink;
	}
};

}
