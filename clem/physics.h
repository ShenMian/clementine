// Copyright 2020 SMS
// License(Apache-2.0)
// 物理引擎

#ifndef CLEM_PHYSICS_H_
#define CLEM_PHYSICS_H_

class Factor;

class Physics
{
public:
	virtual void update(Factor&);
};

#endif // CLEM_PHYSICS_H_
