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
	auto cam = new Camera();
	cam->setInputRect(rect);
	cam->setOutputRect(rect);
  addCamera(cam);
}

void Scene::update()
{
	updateInput();
	updatePhysics();
}

void Scene::render()
{
  for(auto cam : cameras)
		cam->render(entitys);
}

void Scene::addEntity(Entity* obj)
{
	assert(obj != nullptr);
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
	assert(in != nullptr);
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
	assert(r != nullptr);
	this->renderer = r;
}

Renderer* Scene::getRenderer() const
{
	return renderer;
}


void Scene::addCamera(Camera* cam)
{
	assert(cam != nullptr);
	cam->setScene(this);
	// TODO: 使用二分法插入提高效率
	for(auto it = cameras.begin(); it != cameras.end(); ++it)
		if((*it)->getDepth() <= cam->getDepth())
			cameras.insert(it, cam);
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

void Scene::updateInput()
{
	for(auto input : inputs)
		input->update();
}

void Scene::updatePhysics()
{
	assert(physics != nullptr);
  for(auto obj : entitys)
		physics->update(*obj);
}

