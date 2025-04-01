#pragma once

#include <rttr/type>
#include "helper/authoring.hpp"

namespace su
{

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