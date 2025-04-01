#pragma once

#include <vector>
#include <memory>
#include "controls/view.h"
#include "helper/authoring.hpp"

namespace su
{

	class window
	{
	public:

		window();

		~window();

		su::property<int> width;
		su::property<int> height;

		void add_child(std::shared_ptr<view> child);
		void set_children(std::vector<std::shared_ptr<view>> children);

	private:
		std::vector<std::shared_ptr<view>> _children;
	};

}

