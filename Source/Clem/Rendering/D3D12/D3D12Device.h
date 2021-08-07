// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <d3d12.h>

namespace clem
{

class D3D12Device
{
public:
    using handle_type = ID3D12Device*;

    void create();
    void destroy();

    handle_type& operator()();

private:
    handle_type handle = nullptr;
};

} // namespace clem