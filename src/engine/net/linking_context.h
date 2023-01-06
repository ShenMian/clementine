// Copyright 2022 SMS
// License(Apache-2.0)

#pragma once

#include "core/type_index.hpp"
#include <concepts>
#include <cstdint>
#include <unordered_map>

namespace net
{

template <typename T>
concept Syncable = requires(T t)
{
	Typeid<T>();
	t->create();
};

class LinkingContext
{
public:
	using id_type = uint32_t;

	id_type get(void* obj)
	{
		const auto it = objectToId.find(obj);
		if(it != objectToId.end())
			return it->second;
		const auto id = static_cast<id_type>(objectToId.size());
		objectToId.insert({obj, id});
		idToObject.insert({id, obj});
	}

	void* get(id_type id)
	{
		const auto it = idToObject.find(id);
		if(it != idToObject.end())
			return it->second;
		return nullptr;
	}

	template <typename T>
	void registerObject()
	{
		functions.insert({Typeid<T>(), &T::T()});
	}

private:
	id_type createId() { return static_cast<id_type>(objectToId.size()); }
	void*   createObject(core::TypeIndex index) { return functions[index](); }

	std::unordered_map<core::TypeIndex, std::function<void*()>> functions;

	std::unordered_map<id_type, void*> idToObject;
	std::unordered_map<void*, id_type> objectToId;
};

} // namespace net
