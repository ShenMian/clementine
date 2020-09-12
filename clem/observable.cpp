// Copyright 2020 SMS
// License(Apache-2.0)
// 被观察者

#include "observable.h"
#include "observer.h"
#include <algorithm>
#include <assert.h>

void Observable::notifyObserver() const
{
	for(auto o : observers)
		o->onNotify(*this);
}

void Observable::addObserver(Observer* o)
{
	assert(o != nullptr);
	observers.push_back(o);
}

void Observable::removeObserver(Observer* o)
{
	auto it = std::find(observers.begin(), observers.end(), o);
	assert(it == observers.end());
	observers.erase(it);
}
