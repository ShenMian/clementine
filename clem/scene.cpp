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

/**
 * @brief 构造 Scene 对象
 */
Scene::Scene()
{
	auto director = Director::getInstance();

	auto camera = new Camera();
	camera->setSize(director->getWinSize());
	addCamera(*camera); // 添加默认摄像机
}

/**
 * @brief 析构 Scene 对象
 */
Scene::~Scene()
{
	if(!cameras.empty() && cameras[0] != nullptr)
		delete cameras[0]; // 删除默认摄像机
}

/**
 * @brief 更新游戏对象和物理引擎
 * 
 * @param dt 
 */
void Scene::update(float dt)
{
	updateFactors(dt);
	updatePhysics(dt);
}

/**
 * @brief 渲染全部摄像机的画面
 */
void Scene::render()
{
	frameBuffer.clear();

	for(auto cam : cameras)
		cam->render(sprites);

	frameBuffer.swapBuffers();
	frameBuffer.render();
}

/**
 * @brief 添加游戏对象
 * 
 * @param f 游戏对象
 */
void Scene::addFactor(Factor& f)
{
	f.setScene(this);
	factors.push_back(&f);
}

/**
 * @brief 移除游戏对象
 * 
 * @param f 游戏对象
 */
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

/**
 * @brief 获取全部游戏对象
 * 
 * @return const std::vector<Factor*>& 
 */
const std::vector<Factor*>& Scene::getFactors() const
{
	return factors;
}

/**
 * @brief 添加摄像机
 * 
 * @param cam 摄像机
 */
void Scene::addCamera(Camera& cam)
{
  cam.setScene(this);
	auto it = std::lower_bound(cameras.begin(), cameras.end(), &cam, [](const Camera* a, const Camera* b) {
		return a->getDepth() - b->getDepth();
	});
	cameras.insert(it, &cam);
}

/**
 * @brief 移除摄像机
 * 
 * @param cam 摄像机
 */
void Scene::removeCamera(Camera& cam)
{
	auto it = std::find(cameras.begin(), cameras.end(), &cam);
	if(it != cameras.end())
		cameras.erase(it);
	else
		assert(false);
}

/**
 * @brief 获取全部摄像机
 * 
 * @return const vector<Camera*>& 
 */
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

/**
 * @brief 更新游戏对象
 * 
 * @param dt 
 */
void Scene::updateFactors(float dt)
{
	for(auto f : factors)
		f->update(dt);
}

#include "physics/rigidbody.h"
#include "physics/collider.h"
#include "physics/circle_collider.h"

/**
 * @brief 更新物理引擎
 * 
 * @param dt 
 */
void Scene::updatePhysics(float dt)
{
	vector<Collider*> colliders;
	for(auto body : rigidbodies)
		for(auto c : body->getColliders())
			colliders.push_back(c);

	for(size_t i = 0; i < colliders.size(); i++)
		for(size_t j = i + 1; j < colliders.size(); j++)
			if(Collider::collides(*dynamic_cast<CircleCollider*>(colliders[i]), *dynamic_cast<CircleCollider*>(colliders[j])))
			{
				colliders[i]->getOwner()->getOwner()->onCollision(*colliders[i], *colliders[j]);
				colliders[j]->getOwner()->getOwner()->onCollision(*colliders[j], *colliders[i]);
			}
}
