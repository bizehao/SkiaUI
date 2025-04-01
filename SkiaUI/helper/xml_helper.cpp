#include "xml_helper.h"
#include <algorithm>

su::xml_attr_t su::tranform_str(std::string_view isv)
{
    std::string sv(isv);
    std::transform(sv.begin(), sv.end(), sv.begin(), [](unsigned char c) {
        return std::tolower(c);
    });

    // 尝试转换为 bool
    if (sv == "true" || sv == "false")
        {
            return sv == "true";
        }

    int num_base = 10;
    // 尝试转换为十六进制 int32_t
    if (sv.size() > 2 && sv[0] == '0' && sv[1] == 'x')
        {
            num_base = 16;
        }

    // 尝试转换为 int32_t
    try
        {
            size_t pos;
            int32_t int_val = std::stoi(sv, &pos, num_base);
            if (pos == sv.size())
                {
                    return int_val;
                }
        }
    catch (...)
        {
        }

    // 尝试转换为 uint32_t
    try
        {
            size_t pos;
            uint32_t uint_val = std::stoul(sv, &pos, num_base);
            if (pos == sv.size())
                {
                    return uint_val;
                }
        }
    catch (...)
        {
        }

    // 尝试转换为 int64_t
    try
        {
            size_t pos;
            int64_t int64_val = std::stoll(sv, &pos, num_base);
            if (pos == sv.size())
                {
                    return int64_val;
                }
        }
    catch (...)
        {
        }

    // 尝试转换为 uint64_t
    try
        {
            size_t pos;
            uint64_t uint64_val = std::stoull(sv, &pos, num_base);
            if (pos == sv.size())
                {
                    return uint64_val;
                }
        }
    catch (...)
        {
        }

    // 尝试转换为 double
    try
        {
            size_t pos;
            double double_val = std::stod(sv, &pos);
            if (pos == sv.size())
                {
                    return double_val;
                }
        }
    catch (...)
        {
        }

    // 尝试转换为 float
    try
        {
            size_t pos;
            float float_val = std::stof(sv, &pos);
            if (pos == sv.size() || (pos == sv.size() - 1 && sv.back() == 'f'))
                {
                    return float_val;
                }
        }
    catch (...)
        {
        }

    // 默认返回字符串
    return sv;
}