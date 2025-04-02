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
#include <filesystem>
#include <iostream>
#include <nameof.hpp>

using namespace std;

struct AABB
{
    int _idA;
};

int main()
{
    std::cout << nameof::nameof_short_type<AABB>() << std::endl;
	namespace fs = std::filesystem;
    auto path = fs::current_path();
    std::cout << path << std::endl;
    auto window_ptr = su::parse_xml_handle("C:/Users/BiZeHao/source/repos/SkiaUI/Resources/test1.xml");
	
	return 0;
}
