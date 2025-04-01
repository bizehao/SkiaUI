/************************************************************************************
*                                                                                   *
*   Copyright (c) 2014 - 2018 Axel Menzel <info@rttr.org>                           *
*                                                                                   *
*   This file is part of RTTR (Run Time Type Reflection)                            *
*   License: MIT License                                                            *
*                                                                                   *
*   Permission is hereby granted, free of charge, to any person obtaining           *
*   a copy of this software and associated documentation files (the "Software"),    *
*   to deal in the Software without restriction, including without limitation       *
*   the rights to use, copy, modify, merge, publish, distribute, sublicense,        *
*   and/or sell copies of the Software, and to permit persons to whom the           *
*   Software is furnished to do so, subject to the following conditions:            *
*                                                                                   *
*   The above copyright notice and this permission notice shall be included in      *
*   all copies or substantial portions of the Software.                             *
*                                                                                   *
*   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR      *
*   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,        *
*   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE     *
*   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER          *
*   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,   *
*   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE   *
*   SOFTWARE.                                                                       *
*                                                                                   *
*************************************************************************************/

#include "rttr/policy.h"

namespace rttr
{

/////////////////////////////////////////////////////////////////////////////////////////

const detail::bind_as_ptr policy::prop::bind_as_ptr = {};

const detail::as_reference_wrapper policy::prop::as_reference_wrapper = {};

const detail::return_as_ptr policy::meth::return_ref_as_ptr = {};

const detail::discard_return policy::meth::discard_return = {};

/////////////////////////////////////////////////////////////////////////////////////////

const detail::as_raw_pointer policy::ctor::as_raw_ptr = {};

const detail::as_std_shared_ptr policy::ctor::as_std_shared_ptr = {};

const detail::as_object policy::ctor::as_object = {};

/////////////////////////////////////////////////////////////////////////////////////////

/**
Register property getter with lambda function.
@code
int get_my_int(const MyClass& my_class);
rttr::registration::class_<MyClass>("MyClass")
    .property_readonly("my_int"
        , rttr::as_member_func(+[](const MyClass* self) { return get_my_int(*self); })
    )
;
@endcode
*/
template <typename Return, typename Class, typename... Args>
auto as_member_func(Return(*func)(const Class*, Args...))
{
    union
    {
        Return(Class::* member_func)(Args...) const;
        void* func_ptr;
    } convert;
    convert.func_ptr = func;
    return convert.member_func;
}

/**
Register property setter with lambda function.
@code
class MyClass {
public:
    explicit MyClass(int my_int);
    int& get();
private:
    int my_int;
};
rttr::registration::class_<MyClass>("MyClass")
    .property("my_int"
        , &MyClass::get,
        , rttr::as_member_func(+[](MyClass* self, int my_int) { self->get() = my_int; })
    )
;
@endcode
*/
template <typename Return, typename Class, typename... Args>
auto as_member_func(Return(*func)(Class*, Args...))
{
    union
    {
        Return(Class::* member_func)(Args...);
        void* func_ptr;
    } convert;
    convert.func_ptr = func;
    return convert.member_func;
}

} // end namespace rttr
