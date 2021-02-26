// Copyright 2020 SMS
// License(Apache-2.0)
// ×é¼þ

#ifndef CLEM_COMPONENT_H_
#define CLEM_COMPONENT_H_

class Factor;

class Component
{
public:
	Component();

	virtual void update() = 0;

	virtual void onEnter() = 0;
	virtual void onExit() = 0;
	virtual void onAdd() = 0;
	virtual void onRemove() = 0;

	Factor* getOwner() const;
	void setOwner(Factor* owner);

protected:
	Factor* owner;
};

#endif // !CLEM_COMPONENT_H_

