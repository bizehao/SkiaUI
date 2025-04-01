#pragma once

#include "content_view.h"

namespace su
{
	class button : public content_view
	{
		RTTR_ENABLE(content_view)
	public:
		button();

		void on_draw() override;

	};
}