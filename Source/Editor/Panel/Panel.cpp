#include "Panel.h"
#include <algorithm>

Panel::Panel()
{
	addPanel(this);
}

Panel::~Panel()
{
	removePanel(this);
}

void Panel::updateAll()
{
	for(const auto& panel : panels)
		if(panel->visible)
			panel->update();
}

void Panel::addPanel(Panel* panel)
{
	panels.push_back(panel);
}

void Panel::removePanel(Panel* panel)
{
	panels.erase(std::remove(panels.begin(), panels.end(), panel));
}
