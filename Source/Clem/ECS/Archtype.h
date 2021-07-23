// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <set>
#include <typeindex>

// TODO: Avoid RTTI

namespace clem
{

struct Chunk;

class Archtype
{
public:
	Archtype() = default;

	Archtype(std::set<std::type_index>&&);

	/**
	 * @brief �ж��Ƿ���ָ����ȫ������.
	 */
	template <typename T, typename... Ts>
	bool all() const;

	/**
	 * @brief �ж��Ƿ���ָ������������.
	 */
	template <typename T, typename... Ts>
	bool any() const;

	/**
	 * @brief �ж��Ƿ�û��ָ�����κ�����.
	 */
	template <typename... Ts>
	bool none() const;

	/**
	 * @brief �������.
	 */
	template <typename T>
	Archtype& add();

	/**
	 * @brief �Ƴ�����.
	 */
	template <typename T>
	Archtype& remove();

	/**
	 * @brief �Ƴ�ȫ������.
	 */
	void clear();

	bool operator==(const Archtype& rhs) const;
	bool operator<(const Archtype& rhs) const;

	size_t hashCode() const;

private:
	std::set<std::type_index> types;
};

template <typename... Ts>
inline Archtype makeArchtype()
{
	return Archtype(std::move({std::type_index(typeid(Ts))...}));
}

} // namespace clem

#include "Archtype.inl"
