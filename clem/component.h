// Copyright 2020 SMS
// License(Apache-2.0)
// ×é¼þ

class Factor;

class Component
{
public:
	Component();

	virtual void update();

	virtual void onEnter();
	virtual void onExit();
	virtual void onAdd();
	virtual void onRemove();

	Factor* getOwner() const;
	void setOwner(Factor* owner);

protected:
	Factor* owner;

private:
};
