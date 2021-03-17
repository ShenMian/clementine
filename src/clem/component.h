// Copyright 2021 SMS
// License(Apache-2.0)

#ifndef CLEM_COMPONENT_H_
#define CLEM_COMPONENT_H_

class Scene;

class Component
{
public:
	virtual void onAdd();

	virtual void onRemove();

	void    setScene(Scene*);
	Scene* getScene() const;

protected:
	Scene* scene;
};

#endif // !CLEM_COMPONENT_H_
