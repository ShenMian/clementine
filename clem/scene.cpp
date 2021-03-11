// Copyright 2020 SMS
// License(Apache-2.0)
// 场景

#include "scene.h"
#include "camera.h"
#include "director.h"
#include "factor.h"
#include "frame_buffer.h"
#include "type.h"
#include <algorithm>
#include <cassert>

using std::vector;

Scene::Scene()
{
	auto director = Director::getInstance();

	auto camera = new Camera();
	camera->setSize(director->getWinSize());
	addCamera(*camera); // 添加默认摄像机
}

Scene::~Scene()
{
	if(!cameras.empty() && cameras[0] != nullptr)
		delete cameras[0]; // 删除默认摄像机
}

void Scene::update(float dt)
{
	updateFactors(dt);
	updatePhysics(dt);
}

void Scene::render()
{
	frameBuffer.clear();

	for(auto cam : cameras)
		cam->render(sprites);

	frameBuffer.swapBuffers();
	frameBuffer.render();
}

void Scene::addFactor(Factor& f)
{
	f.setScene(this);
	factors.push_back(&f);
}

void Scene::removeFactor(Factor& f)
{
	auto it = std::find(factors.begin(), factors.end(), &f);
	if(it != factors.end())
	{
		(*it)->setScene(nullptr);
		factors.erase(it);
	}
	else
		assert(false);
}

const std::vector<Factor*>& Scene::getFactors() const
{
	return factors;
}

void Scene::addCamera(Camera& cam)
{
  cam.setScene(this);
	auto it = std::lower_bound(cameras.begin(), cameras.end(), &cam, [](const Camera* a, const Camera* b) {
		return a->getDepth() - b->getDepth();
	});
	cameras.insert(it, &cam);
}

void Scene::removeCamera(Camera& cam)
{
	auto it = std::find(cameras.begin(), cameras.end(), &cam);
	if(it != cameras.end())
		cameras.erase(it);
	else
		assert(false);
}

const vector<Camera*>& Scene::getCameras() const
{
	return cameras;
}

void Scene::addSprite(Sprite& s)
{
	sprites.push_back(&s);
}

void Scene::removeSprite(Sprite& s)
{
	auto it = std::find(sprites.begin(), sprites.end(), &s);
	if(it != sprites.end())
		sprites.erase(it);
	else
		assert(false);
}

void Scene::addRigidbody(Rigidbody& b)
{
	rigidbodies.push_back(&b);
}

void Scene::removeRigidbody(Rigidbody& b)
{
	auto it = std::find(rigidbodies.begin(), rigidbodies.end(), &b);
	if(it != rigidbodies.end())
		rigidbodies.erase(it);
	else
		assert(false);
}

/*
void Scene::updateInput()
{
	for(auto input : inputs)
		input->update();
}
*/

void Scene::updateFactors(float dt)
{
	for(auto f : factors)
		f->update(dt);
}

void Scene::updatePhysics(float dt)
{
}
