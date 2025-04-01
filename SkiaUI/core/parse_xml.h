#include <string_view>
#include <memory>
#include "base/window.h"

namespace su
{
std::shared_ptr<window> parse_xml_handle(std::string_view path);
}
