// Copyright 2021 SMS
// License(Apache-2.0)

namespace clem
{

template <typename T, typename... Ts>
[[nodiscard]] inline bool Archtype::all() const
{
    if constexpr(sizeof...(Ts) > 0)
        return types.find(Typeid<T>()) != types.end() && all<Ts...>();
    else
        return types.find(Typeid<T>()) != types.end();
}

template <typename T, typename... Ts>
[[nodiscard]] inline bool Archtype::any() const
{
    if constexpr(sizeof...(Ts) > 0)
        return types.find(Typeid<T>()) != types.end() || any<Ts...>();
    else
        return types.find(Typeid<T>()) != types.end();
}

template <typename... Ts>
[[nodiscard]] inline bool Archtype::none() const
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

namespace std
{

template <>
struct hash<clem::Archtype>
{
    size_t operator()(const clem::Archtype& archtype) const
    {
        return archtype.hashCode();
    }
};

} // namespace std