#include <iostream>
#include <variant>

#include "controls/content_view.h"
#include "controls/view.h"
#include "controls/view_group.h"
#include "helper/xml_helper.h"
#include <tinyxml2.h>
#include "parse_xml.h"
#include <format>

namespace su
{

static void handle_of_view(rttr::type clazz, rttr::instance obj, std::unordered_map<std::string_view, std::string_view> attrs)
{
    for (auto& item : attrs)
    {
        auto member = clazz.get_property(item.first);

        if (member)
        {
            auto v = tranform_str(item.second);
            bool success = std::visit(
              [&member, &obj, &item](auto&& it) {
                  std::cout << std::format("prop: {}, value: {}", item.first, it) << std::endl;
                  return member.set_value(obj, rttr::variant{it});
              },
              v);

            if (!success)
            {
                std::cout << "set_value is error, type not match" << std::endl;
            }
        }
        else
        {
            std::cout << std::format("warning 没找到属性: {}", item.first) << std::endl;
        }
    }
}

static void handle_of_content_view(rttr::type clazz, rttr::instance obj, su::content_view::content_t content)
{
    auto content_member = clazz.get_property("content");
    bool success        = content_member.set_value(obj, rttr::variant{content});
    if (!success)
    {
        std::cout << "set_value is error, type not match" << std::endl;
    }
}

static std::shared_ptr<su::view> parse_node(tinyxml2::XMLElement* element);

static std::vector<std::shared_ptr<su::view>> handle_node(tinyxml2::XMLElement* node)
{
    // 遍历整个 XML 结构
    // NextSiblingElement() 函数用于获取同一层级的下一个元素
    // FirstChildElement(): 该方法用于获取当前元素的第一个子元素，而不需要指定名称。
    std::vector<std::shared_ptr<su::view>> sub_views;
    for (tinyxml2::XMLElement* element = node->FirstChildElement(); element; element = element->NextSiblingElement())
    {
        auto v = parse_node(element);
        if (v)
        {
            sub_views.push_back(std::move(v));
        }
    }
    return sub_views;
}

static std::unordered_map<std::string_view, std::string_view> get_attrs(tinyxml2::XMLElement* element)
{
    std::unordered_map<std::string_view, std::string_view> attrs;
    // 遍历元素的属性
    for (const tinyxml2::XMLAttribute* attr = element->FirstAttribute(); attr; attr = attr->Next())
    {
        std::string_view attrName  = attr->Name();
        std::string_view attrValue = attr->Value();
        attrs.emplace(attrName, attrValue);
        std::cout << "Attribute: " << attrName << " = " << attrValue << std::endl;
    }
    return attrs;
}

static std::shared_ptr<su::view> parse_node(tinyxml2::XMLElement* element)
{
    // 获取元素名称
    std::string_view elementName = element->Name();
    std::cout << "Element Name: " << elementName << std::endl;

    auto var_t = rttr::type::get_by_name(elementName);

    if (!var_t)
    {
        // print error
        return nullptr;
    }

    auto attrs = get_attrs(element);

    std::cout << std::endl;
    const rttr::type class_t = rttr::type::get_by_name(elementName);
    const rttr::type view_t  = rttr::type::get<su::view>();
    if (class_t == view_t || class_t.is_derived_from(view_t))
    {
        // some view handle
        auto view_obj = class_t.create();
        if (class_t == rttr::type::get<su::view_group>())
        {
            // view_group
            std::vector<std::shared_ptr<su::view>> cs = handle_node(element);

            // todo:
        }
        else
        {
            handle_of_view(class_t, view_obj, attrs);
            auto content_member = class_t.get_property("content");
            if (content_member && !attrs.contains("content"))
            {
                // 有sub view的元素
                su::content_view::content_t content{nullptr};
                if (!element->NoChildren())
                {
                    // 获取元素的文本内容
                    auto text_content = element->GetText();
                    if (text_content)
                    {
                        content = std::string_view(text_content);
                        std::cout << "Text: " << text_content << std::endl;
                    }
                    else
                    {
                        std::shared_ptr<su::view> sub_view = parse_node(element->FirstChildElement());
                        if (sub_view)
                        {
                            content = std::move(sub_view);
                        }
                        else
                        {
                            // todoL error sub view error
                        }
                    }
                    handle_of_content_view(class_t, view_obj, content);
                }
            }
        }

        return view_obj.get_value<std::shared_ptr<su::view>>();
    }
    else
    {
        // 一些未做处理的类型
        return nullptr;
    }
}

std::shared_ptr<window> parse_xml_handle(std::string_view path)
{
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLError loadResult = doc.LoadFile(path.data());
    // 检查加载操作是否成功
    if (loadResult != tinyxml2::XML_SUCCESS)
    {
        // 如果加载操作失败，输出错误信息
        std::cout << "Failed to load XML document. Error code: " << loadResult << std::endl;
        return nullptr;
    }

    tinyxml2::XMLElement* root = doc.RootElement();
    std::string elementName    = root->Name();
    if (elementName != "window")
    {
        std::cout << "root element have be window" << std::endl;
        return nullptr;
    }
    std::cout << "Element Name: " << elementName << std::endl;
    auto attrs = get_attrs(root);
    rttr::type window_type = rttr::type::get<su::window>();
    auto window_obj        = window_type.create();
    handle_of_view(window_type, window_obj, attrs);
    auto window_ptr = window_obj.convert<std::shared_ptr<su::window>>();
    auto children   = handle_node(root);
    window_ptr->set_children(std::move(children));
    return window_ptr;
}

} // namespace su
