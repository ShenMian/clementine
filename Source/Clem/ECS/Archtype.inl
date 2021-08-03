// Copyright 2021 SMS
// License(Apache-2.0)

namespace clem
{

template <typename T, typename... Ts>
inline bool Archtype::all() const
{
	if constexpr(sizeof...(Ts) > 0)
		return types.find(Typeid<T>()) != types.end() && all<Ts...>();
	else
		return types.find(Typeid<T>()) != types.end();
}

template <typename T, typename... Ts>
inline bool Archtype::any() const
{
	if constexpr(sizeof...(Ts) > 0)
		return types.find(Typeid<T>()) != types.end() || any<Ts...>();
	else
		return types.find(Typeid<T>()) != types.end();
}

template <typename... Ts>
inline bool Archtype::none() const
{
	return !any<Ts...>();
}

template <typename T>
inline Archtype& Archtype::add()
{
	types.insert(Typeid<T>());
	return *this;
}

template <typename T>
inline Archtype& Archtype::remove()
{
	types.erase(Typeid<T>());
	return *this;
}

} // namespace clem

/*
template <>
struct std::hash<clem::Archtype>
{
	size_t operator()(const clem::Archtype& v) const noexcept
	{
		return v.hashCode();
	}
};

template <>
struct std::equal_to<clem::Archtype>
{
	bool operator()(const clem::Archtype& lhs, const clem::Archtype& rhs) const
	{
		return lhs == rhs;
	}
};
*/