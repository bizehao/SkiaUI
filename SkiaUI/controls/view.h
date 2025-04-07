#pragma once

#include <rttr/type>
#include "helper/authoring.hpp"
#include <yoga/Yoga.h>

namespace su
{

	void test() {
	
		YGNodeStyleSetWidth();
        YGNodeStyleSetWidthAuto();
        YGNodeStyleSetWidthFitContent();
	}

	class view
	{
		RTTR_ENABLE()
	public:
		view();
		view(const view&) = delete;
		view& operator=(const view&) = delete;
		virtual ~view() = default;

		su::property<int> width;
		su::property<int> height;
	protected:
		virtual void on_draw();
	};

}