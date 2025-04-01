#pragma once

#include "view.h"
#include <variant>

namespace su
{
	class content_view : public view
	{
		RTTR_ENABLE(view)
	public:
		using content_t = std::variant<std::nullptr_t, std::string_view, std::shared_ptr<view>>;
		content_view();

		su::property<content_t> content;

	protected:
		virtual void on_draw() = 0;

	};
}