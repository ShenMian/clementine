// Copyright 2020 SMS
// License(Apache-2.0)
// ×é¼þ

#ifndef CLEM_COMPONENT_H_
#define CLEM_COMPONENT_H_

class Entity;

class Component
{
public:
  virtual void update(Entity&) = 0;
};

#endif // CLEM_COMPONENT_H_
