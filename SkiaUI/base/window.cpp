#include "window.h"

su::window::window()
{}

su::window::~window()
{}

void su::window::add_child(std::shared_ptr<view> child)
{
	_children.push_back(std::move(child));
}

void su::window::set_children(std::vector<std::shared_ptr<view>> children)
{
	_children = std::move(children);
}
