# CMakeList.txt: SkiaUI 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#

find_package(fmt CONFIG REQUIRED)
find_package(tinyxml2 CONFIG REQUIRED)

# 将源代码添加到此项目的可执行文件。
set(p_include
	"base/window.h" "controls/view.h"
	"controls/button.h" "controls/view_group.h" "controls/content_view.h"
	"controls/image_view.h" "helper/xml_helper.cpp" "core/parse_xml.h"
	)

set(p_source
	"main.cpp" "base/window.cpp"  "core/register_meta.cpp" "controls/view.cpp"
	"controls/button.cpp" "controls/view_group.cpp" "controls/content_view.cpp"
	"controls/image_view.cpp" "helper/xml_helper.cpp" "core/parse_xml.cpp"
	)

add_executable (SkiaUI ${p_include} ${p_source})

target_compile_features(SkiaUI PUBLIC cxx_std_20)

target_include_directories(SkiaUI PRIVATE ./)

target_link_libraries(SkiaUI PRIVATE eventpp RTTR::Core_Lib reflect::reflect fmt::fmt tinyxml2::tinyxml2)

# TODO: 如有需要，请添加测试并安装目标。
