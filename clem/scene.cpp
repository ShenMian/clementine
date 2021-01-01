// Copyright 2020 SMS
// License(Apache-2.0)
// 场景

#include <clem/scene.h>
#include <clem/type.h>
#include <clem/director.h>

#include "factor.h"
#include "camera.h"

#include "input.h"

#include <algorithm>
#include <cassert>

using std::vector;

Scene::Scene()
{
	auto director = Director::getInstance();

  // 添加默认摄像机
	defaultCamera = new Camera();
	defaultCamera->setSize(director->getWinSize());
	addCamera(defaultCamera);
}

Scene::~Scene()
{
	delete defaultCamera;
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

Camera* Scene::getDefaultCamera() const
{
	return defaultCamera;
}

void Scene::update()
{
	updateFactors();
	updatePhysics();
}

void Scene::render()
{
  for(auto cam : cameras)
		cam->render();
}

/*
void Scene::updateInput()
{
	for(auto input : inputs)
		input->update();
}
*/

void Scene::updateFactors()
{
	for(auto f : factors)
		f->update();
}

void Scene::updatePhysics()
{
}
