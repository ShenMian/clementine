// Copyright 2020 SMS
// License(Apache-2.0)
// 场景

#include "scene.h"
#include "type.h"

#include "input.h"
#include "physics.h"
#include "renderer.h"

#include "entity.h"
#include "camera.h"

#include "terminal.h"

#include <algorithm>
#include <assert.h>

using std::vector;

Scene::Scene()
		: Scene(Size(Terminal::getWindowSize().x, Terminal::getWindowSize().y))
{
}

Scene::Scene(const Size& size)
		: size(size)
{
	Rect rect(0, this->size.y, size.x, size.y);

  // 添加默认摄像机
	auto cam = new Camera(*this);
	cam->setInputRect(rect);
	cam->setOutputRect(rect);
  addCamera(cam);
}

void Scene::update()
{
	for(auto in : inputs)
		in->update();

  for(auto obj : entitys)
	{
		physics->update(*obj);
		obj->update();
	}

	render();
}

void Scene::render()
{
  for(auto cam : cameras)
		cam->render(*renderer, entitys);
}

void Scene::addEntity(Entity* obj)
{
	entitys.push_back(obj);
}

void Scene::removeEntity(Entity* entity)
{
	auto it = std::find(entitys.begin(), entitys.end(), entity);
	if(it != entitys.end())
		entitys.erase(it);
	else
		assert(false);
}

void Scene::addInput(Input* in)
{
	inputs.push_back(in);
}

void Scene::setPhysics(Physics* p)
{
	this->physics = p;
}

Physics* Scene::getPhysics() const
{
	return this->physics;
}

void Scene::setRenderer(Renderer* r)
{
	this->renderer = r;
}

Renderer* Scene::getRenderer() const
{
	return renderer;
}


void Scene::addCamera(Camera* cam)
{
  cameras.push_back(cam);
}

void Scene::removeCamera(Camera* cam)
{
	auto it = std::find(cameras.begin(), cameras.end(), cam);
	if(it != cameras.end())
		cameras.erase(it);
	else
		assert(false);
}

const vector<Camera*>& Scene::getCameras() const
{
	return cameras;
}
