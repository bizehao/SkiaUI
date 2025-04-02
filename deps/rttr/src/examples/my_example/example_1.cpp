#include <rttr/registration.h>
#include <iostream>
#include <rttr/type>
#include <rttr/registration>

using namespace rttr;

namespace su
{
	template<typename T>
	class base_property
	{
	public:
		virtual ~base_property() = default;


		virtual const T& get() const = 0;

		virtual void set(T q) = 0;

		operator const T& () const
		{
			return get();
		}

		template <typename Q>
		void operator=(Q&& q)
		{
			set(std::forward<Q>(q));
		}
	};


	template <typename T>
	class property : public base_property<T>
	{
	public:
		property(const T& value = T{}) : _value{ value }
		{}

		const T& get() const override
		{
			return _value;
		}

		void set(T q) override
		{
			if (q != _value)
			{
				_value = std::move(q);
			}
		}

	private:
		T _value;
	};
}

void add(int a);

struct test_class
{
	test_class(int value) : m_value(value) {}
	void print_value() const { std::cout << m_value; }

	su::property<int> get()
	{
		return {};
	}

	void set(su::property<int>)
	{
	}

	su::property<int> m_value;
};

static su::property<int> convert_to_string(const int& p, bool& ok)
{
	ok = true;
	return p;
}

template<typename T>
su::property<T> convert_property(const T& p, bool& ok)
{
	ok = true;
	return p;
}

RTTR_REGISTRATION
{
	registration::class_<test_class>("test_class")
	.constructor<int>()
	.method("print_value", &test_class::print_value)
	.property("value", &test_class::m_value);
	//.property("value", &TTget, &TTset);

	type::register_converter_func(convert_property<int>);

	//variant pp = 100;
	argument arg = 100;

	arg.get_value<int>();

	//pp.convert<int>();

	//arg.get_type().get_type_converter(rttr::type::get<T>())
	
	
}

struct AA{};

int main()
{
	//float m1 = 3.14f;
	//int k1 = 100;
	//variant return_value = type::invoke("add", { k1 });
	//std::cout << std::boolalpha << return_value.is_valid() << std::endl;


	test_class obj(20);
	type class_type = type::get_by_name("test_class");
	// option 1
	variant a1 = 50;
	//int a1 = 50;
	bool success = class_type.set_property_value("value", obj, a1);
	std::cout << obj.m_value << std::endl; // prints "50"

	//// option 2
	//property prop = class_type.get_property("value");
	//success = prop.set_value(obj, 24);
	//std::cout << obj.m_value << std::endl; // prints "24"

}