// Copyright 2020 SMS
// License(Apache-2.0)
// 被观察者

#ifndef CLEM_OBSERVABLE_H_
#define CLEM_OBSERVABLE_H_

#include <vector>
#include "observer.h"

/// 被观察者(已弃用)
class Observable
{
public:
	virtual void notifyObserver() const;
	virtual void addObserver(Observer* o);
	virtual void removeObserver(Observer* o);

	void setDirty(bool);
	bool isDirty() const;

protected:
	std::vector<Observer*> observers;

private:
	bool dirty;
};

#endif // !CLEM_OBSERVABLE_H_

