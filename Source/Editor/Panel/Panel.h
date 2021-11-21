// Copyright 2021 ShenMian
// License(Apache-2.0)

#pragma once

#include <vector>

class Panel
{
public:
    Panel();
    virtual ~Panel();

    static void updateAll();

    virtual void update() = 0;

    bool visible;

protected:
    void addPanel(Panel* panel);
    void removePanel(Panel* panel);

private:
    inline static std::vector<Panel*> panels;
};
