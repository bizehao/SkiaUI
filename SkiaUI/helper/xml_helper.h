#include <variant>
#include <string>
#include <cstdint>
#include <string_view>

namespace su
{
using xml_attr_t = std::variant<bool, int32_t, uint32_t, int64_t, uint64_t, double, float, std::string>;

xml_attr_t tranform_str(std::string_view isv);
}

