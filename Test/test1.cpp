#include <iostream>
#include <type_traits>
#include <variant>
#include <string>
#include <algorithm>

//int double float bool
using xml_attr_t = std::variant<bool, int32_t, uint32_t, int64_t, uint64_t, double, float, std::string>;

xml_attr_t tranform_str(std::string_view isv)
{
    std::string sv(isv);
    std::transform(sv.begin(), sv.end(), sv.begin(), [](unsigned char c)
        {
            return std::tolower(c);
        });

    // ����ת��Ϊ bool
    if (sv == "true" || sv == "false")
    {
        return sv == "true";
    }

    int num_base = 10;
    // ����ת��Ϊʮ������ int32_t
    if (sv.size() > 2 && sv[0] == '0' && sv[1] == 'x')
    {
        num_base = 16;
    }

    // ����ת��Ϊ int32_t
    try
    {
        size_t pos;
        int32_t int_val = std::stoi(sv, &pos, num_base);
        if (pos == sv.size())
        {
            return int_val;
        }
    }
    catch (...) {}

    // ����ת��Ϊ uint32_t
    try
    {
        size_t pos;
        uint32_t uint_val = std::stoul(sv, &pos, num_base);
        if (pos == sv.size())
        {
            return uint_val;
        }
    }
    catch (...) {}

    // ����ת��Ϊ int64_t
    try
    {
        size_t pos;
        int64_t int64_val = std::stoll(sv, &pos, num_base);
        if (pos == sv.size())
        {
            return int64_val;
        }
    }
    catch (...) {}

    // ����ת��Ϊ uint64_t
    try
    {
        size_t pos;
        uint64_t uint64_val = std::stoull(sv, &pos, num_base);
        if (pos == sv.size())
        {
            return uint64_val;
        }
    }
    catch (...) {}

    // ����ת��Ϊ double
    try
    {
        size_t pos;
        double double_val = std::stod(sv, &pos);
        if (pos == sv.size())
        {
            return double_val;
        }
    }
    catch (...) {}

    // ����ת��Ϊ float
    try
    {
        size_t pos;
        float float_val = std::stof(sv, &pos);
        if (pos == sv.size() || (pos == sv.size() - 1 && sv.back() == 'f'))
        {
            return float_val;
        }
    }
    catch (...) {}

    // Ĭ�Ϸ����ַ���
    return sv;
}

int main()
{
	auto number = tranform_str("0xFF");
    std::visit([](auto&& v)
        {
            std::cout << "v: " << v << std::endl;
        }, number);
    std::cout << "index: " << number.index() << std::endl;
	int __a = 0;
	return 0;
}