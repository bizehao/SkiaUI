#include <string>

#include "base/window.h"
#include "controls/button.h"
#include "controls/content_view.h"
#include "controls/image_view.h"
#include "controls/view.h"
#include "controls/view_group.h"
#include "helper/authoring.hpp"
#include <rttr/registration.h>
#include <nameof/nameof.hpp>

namespace su
{

namespace
{
template <typename T>
su::property<T> convert_property(const T& p, bool& ok)
{
    ok = true;
    return p;
}

template <typename T>
constexpr bool _is_prop = false;

template <typename Clazz, typename T>
constexpr bool _is_prop<su::property<T> Clazz::*> = true;

template <typename T>
concept is_prop_t = _is_prop<T>;

template <typename T>
struct _prop_t;

template <typename Clazz, typename T>
struct _prop_t<su::property<T> Clazz::*>
{
    using type = T;
};

template <typename T>
using prop_t = typename _prop_t<T>::type;

template <typename B>
void _bind(B& b)
{}

template <typename B, typename Pair, typename... Pairs>
auto _bind(B& b, Pair prop, Pairs... tail)
{
    rttr::type::register_converter_func(convert_property<prop_t<typename Pair::second_type>>);
    auto o = b.property(prop.first, prop.second);
    return _bind(o, tail...);
}

template <typename Clazz, bool CanInstance = true, typename... Pair>
void registration_skiaui_impl(std::string_view class_name, Pair... props)
{
    if constexpr (CanInstance)
    {
        auto o = rttr::registration::class_<Clazz>(class_name).constructor<>()(rttr::policy::ctor::as_std_shared_ptr);
        _bind(o, props...);
    }
    else
    {
        auto o = rttr::registration::class_<Clazz>(class_name);
        _bind(o, props...);
    }
}

template <typename Clazz, bool CanInstance = true, typename... Pair>
void registration_skiaui(std::string_view class_name, Pair... props)
{
    registration_skiaui_impl<Clazz, CanInstance>(class_name, props...);
}

template <typename Clazz, bool CanInstance = true, typename... Pair>
void registration_skiaui(Pair... props)
{
    registration_skiaui<Clazz, CanInstance>(static_cast<std::string_view>(nameof::nameof_short_type<Clazz>()), props...);
}
} // namespace

#define P(v) std::make_pair(static_cast<std::string_view>(NAMEOF(v)), &v)

static struct init_meta
{
    init_meta()
    {
        using namespace std::literals;
        registration_skiaui<window>(P(window::width), P(window::height));
        registration_skiaui<view>(P(view::width), P(view::height));
        registration_skiaui<view_group>(P(view_group::children));
        registration_skiaui<content_view, false>(P(content_view::content));
        registration_skiaui<button>();
        registration_skiaui<image_view>(P(image_view::src));
    }
} init_meta_instance;
} // namespace su
