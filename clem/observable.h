// Copyright 2020 SMS
// License(Apache-2.0)
// 被观察者

#ifndef CLEM_OBSERVABLE_H_
#define CLEM_OBSERVABLE_H_

#include <vector>

class Observer;

class Observable
{
public:
	virtual void notifyObserver() const;
	virtual void addObserver(Observer* o);
	virtual void removeObserver(Observer* o);

	void setDirty(bool);
	bool isDirty() const;

private:
	std::vector<Observer*> observers;
	bool                   dirty;
};

#endif // CLEM_OBSERVABLE_H_
