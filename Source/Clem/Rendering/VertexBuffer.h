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

struct Vertex
{
    Vector3 position;
    Vector3 color = {1.f, 1.f, 1.f};
    Vector3 normal;
    Vector2 uv;

    bool operator==(const Vertex& rhs) const = default;
};

class VertexBuffer
{
public:
    using value_type = Vertex;

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

            size_t size() const;
            size_t count() const;

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
	 * @param data 缓冲区.
	 */
    static std::shared_ptr<VertexBuffer> create(const std::vector<value_type>& data);

    /**
	 * @brief 创建 VertexBuffer.
	 *
	 * @param data 缓冲区数据指针.
	 * @param size 缓冲区数据大小.
	 */
    static std::shared_ptr<VertexBuffer> create(const void* data, size_t size);

    size_t size() const;

    virtual void bind() = 0;

    Layout layout;

protected:
    size_t size_;
};

/**
 * end of Rendering group
 * @}
 */

template <typename T, typename... Ts>
void hashCombine(std::size_t& seed, const T& v, const Ts&... rest)
{
    seed ^= std::hash<T>{}(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    (hashCombine(seed, rest), ...);
};

} // namespace clem

namespace std
{

template <>
struct hash<clem::Vertex>
{
    size_t operator()(const clem::Vertex& v) const
    {
        size_t hash = 0;
        clem::hashCombine(hash, v.position, v.color, v.normal, v.uv);
        return hash;
    }
};

} // namespace std