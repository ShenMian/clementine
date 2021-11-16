// Copyright 2021 ShenMian
// License(Apache-2.0)

#include "Panel.h"

class PropertiesPanel : public Panel
{
public:
    void update() override;

private:
    template <typename T>
    void show();
};