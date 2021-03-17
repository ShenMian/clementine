// Copyright 2021 SMS
// License(Apache-2.0)

class NScene;

class NComponent
{
public:
	virtual void onAdd();

	virtual void onRemove();

	void    setScene(NScene*);
	NScene* getScene() const;

protected:
	NScene* scene;
};
