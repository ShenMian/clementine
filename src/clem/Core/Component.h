
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
