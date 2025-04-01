// SkiaUI.cpp: 定义应用程序的入口点。
//
#include <format>
#include <fmt/printf.h>
#include "helper/authoring.hpp"
#include <string>
#include "base/window.h"
#include <tinyxml2.h>
#include "controls/button.h"
#include "controls/view_group.h"
#include <unordered_map>
#include "controls/content_view.h"
#include <variant>
#include "controls/image_view.h"
#include <rttr/registration.h>
#include "core/parse_xml.h"

using namespace std;

int main()
{
    auto window_ptr = su::parse_xml_handle("E:/CppProjects/SkiaUI/Resources/test1.xml");
	
	return 0;
}
