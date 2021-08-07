// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Shader.h"
#include <cstddef>
#include <initializer_list>
#include <memory>
#include <unordered_map>
#include <vector>

namespace clem
{

/**
 * @addtogroup Rendering
 * @{
 */

class VertexBuffer
{
public:
    class Layout
    {
    public:
        class Element
        {
        public:
            Element(const std::string& name, Shader::Type type, bool normalized = false);

            std::string  name;
            Shader::Type type;
            bool         normalized;
            size_t       offset;

            size_t count() const;
            size_t size() const;

        private:
            static std::unordered_map<Shader::Type, size_t> sizeOf;
            static std::unordered_map<Shader::Type, size_t> countOf;
        };

        Layout() = default;
        Layout(const std::initializer_list<Element>& elements);

        const std::vector<Element>& elements() const;
        size_t                      stride() const;
        bool                        empty() const;

        std::vector<Element>::iterator       begin();
        std::vector<Element>::iterator       end();
        std::vector<Element>::const_iterator begin() const;
        std::vector<Element>::const_iterator end() const;

    private:
        std::vector<Element> elements_;
        size_t               stride_ = 0;
    };

    /**
	 * @brief 创建 VertexBuffer.
	 *
	 * @param data 缓冲区数据指针.
	 * @param size 缓冲区数据大小.
	 */
    static std::shared_ptr<VertexBuffer> create(const void* data, size_t size);

    virtual void bind() = 0;

    Layout layout;
};

/**
 * end of Rendering group
 * @}
 */

} // namespace clem