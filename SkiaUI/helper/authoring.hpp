#pragma once

#include <type_traits>
#include <concepts>
#include <optional>
#include <eventpp/callbacklist.h>
#include <variant>

namespace su
{
	template<typename T>
	class changed_notifier
	{
	public:
		using handle = typename eventpp::CallbackList<void(const T&)>::Handle;
		handle operator+=(std::function<void(const T&)> callback)
		{
			return _callbackList.append(std::move(callback));
		}

		void operator-=(handle hdl)
		{
			_callbackList.remove(hdl);
		}
	protected:
		eventpp::CallbackList<void(const T&)> _callbackList;
	};

	/*template<typename T>
	class base_property : public changed_notifier<T>
	{
	public:
		virtual ~base_property() = default;
		

		virtual const T& get() const = 0;

		virtual void set(T q) = 0;

		operator const T& () const
		{
			return get();
		}

		template <typename Q> requires std::same_as<T, std::remove_cvref_t<Q>>
		void operator=(Q&& q)
		{
			set(std::forward<Q>(q));
		}
	};*/


	template <typename T>
	class property : public changed_notifier<T>
	{
		using VT = std::pair<std::function<const T& ()>, std::function<void(T)>>;
	public:
		property(const T& value = T{})
			: _value{ value }
		{}
		property(std::function<const T& ()> get_fun, std::function<void(T)> set_fun) 
			: _value{ std::make_pair(get_fun, set_fun)}
		{}

		const T& get() const
		{
			return std::visit(GetVisitor{}, _value);
		}

		void set(T q)
		{
			
			if (q != get())
			{
				std::visit(SetVisitor{ q }, _value);
				this->_callbackList(q);
			}
		}

		operator const T& () const
		{
			return get();
		}

		template <typename Q> requires std::same_as<T, std::remove_cvref_t<Q>>
		void operator=(Q&& q)
		{
			set(std::forward<Q>(q));
		}

	private:
		struct GetVisitor
		{
			const T& operator()(const T& v) const
			{
				return v;
			}

			const T& operator()(const VT& v) const
			{
				return v.first();
			}
		};
		struct SetVisitor
		{
			void operator()(T& v) const
			{
				v = std::move(_v);
			}

			void operator()(VT& v) const
			{
				v.second(_v);
			}

			T _v;
		};
		std::variant<T, VT> _value;
	};

	/*template <typename T>
	class property<T, way::cus> : public base_property<T>
	{
	public:
		property(std::function<const T& ()> get_fun, std::function<void(T)> set_fun) : _get_fun{ get_fun }, _set_fun{ set_fun }
		{}

		const T& get() const override
		{
			return _get_fun();
		}

		void set(T q) override
		{
			if (q != get())
			{
				_set_fun(std::move(q));
				this->_callbackList(get());
			}
		}

	private:
		std::function<const T& ()> _get_fun;
		std::function<void(T)> _set_fun;
	};*/

	template <typename T>
	class readonly_property : public changed_notifier<T>
	{
	public:
		readonly_property(std::function<const T& ()> get_fun) : _get_fun{ get_fun }
		{}

		const T& get() const
		{
			return _get_fun();
		}

		operator const T& () const
		{
			return get();
		}

		void emit() const
		{
			this->_callbackList(get());
		}

	private:
		std::function<const T& ()> _get_fun;
	};
}

