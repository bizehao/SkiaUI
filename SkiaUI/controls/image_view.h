#pragma once

#include "view.h"

namespace su
{
	class image_view : public view
	{
		RTTR_ENABLE(view)
	public:
		image_view();
		su::property<std::string> src;
	};
}