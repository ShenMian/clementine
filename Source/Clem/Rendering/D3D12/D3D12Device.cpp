// Copyright 2021 SMS
// License(Apache-2.0)

#include "D3D12Device.h"
#include "Assert.hpp"
#include <dxgi.h>

namespace clem
{

void D3D12Device::create()
{
    Assert::isTrue(handle == nullptr, "device has been created");

    auto res = D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(&handle));
    Assert::isFalse(FAILED(res), "can't create device");
}

void D3D12Device::destroy()
{
    Assert::isTrue(handle, "device has not been created");
    handle->Release();
}

D3D12Device::handle_type& D3D12Device::operator()()
{
    return handle;
}

} // namespace clem