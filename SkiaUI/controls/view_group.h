#pragma once

#include "view.h"

namespace su
{
	class view_group final : public view
	{
		RTTR_ENABLE(view)
	public:
		view_group();

		su::property<std::vector<std::shared_ptr<view>>> children;
	};
}