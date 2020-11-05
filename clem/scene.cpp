// Copyright 2020 SMS
// License(Apache-2.0)
// 场景

#include "scene.h"
#include "type.h"

#include "input.h"
#include "physics.h"
#include "renderer.h"

#include "factor.h"
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
	defaultCamera = new Camera();
	addCamera(defaultCamera);
}

Scene::~Scene()
{
	delete defaultCamera;
}

void Scene::update()
{
	updateInput();
	updatePhysics();
}

void Scene::render()
{
  for(auto cam : cameras)
		cam->render();
}

void Scene::addFactor(Factor* f)
{
	assert(f != nullptr);
	factors.push_back(f);
}

void Scene::removeFactor(Factor* f)
{
	auto it = std::find(factors.begin(), factors.end(), f);
	if(it != factors.end())
		factors.erase(it);
	else
		assert(false);
}

const std::vector<Factor*>& Scene::getFactors() const
{
	return factors;
}

void Scene::addInput(Input* in)
{
	assert(in != nullptr);
	inputs.push_back(in);
}

void Scene::setPhysics(Physics* p)
{
	assert(p != nullptr);
	this->physics = p;
}

Physics* Scene::getPhysics() const
{
	return this->physics;
}


void Scene::addCamera(Camera* cam)
{
	assert(cam != nullptr);
	cam->setScene(this);

	auto it = std::lower_bound(cameras.begin(), cameras.end(), cam, [](const Camera* a, const Camera* b) {
		return a->getDepth() - b->getDepth();
	});

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
  for(auto f : factors)
		physics->update(*f);
}

