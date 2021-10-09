// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <cstddef>
#include <initializer_list>
#include <typeindex>
#include <vector>

class Properties
{
public:
    struct Member
    {
        const std::type_index type;
        const uint32_t        offset;

        Member(const std::type_index& type, uint32_t offset)
            : type(type), offset(offset)
        {
        }
    };

    /**
    * @brief 构造函数.
    *
    * @param list 构造函数列表.
    */
    Properties(const std::initializer_list<Member>& list)
        : members(list)
    {
        members.shrink_to_fit();
    }

    const std::vector<Member>& getMembers() const
    {
        return members;
    }

private:
    std::vector<Member> members;
};

#define Offsetof(C, M) ((size_t) & static_cast<C*>(nullptr)->M)