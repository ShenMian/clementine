// Copyright 2020 SMS
// License(Apache-2.0)
// ±ªπ€≤Ï’ﬂ

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

private:
	std::vector<Observer*> observers;
};

#endif // CLEM_OBSERVABLE_H_
