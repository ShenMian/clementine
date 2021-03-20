// Copyright 2021 SMS
// License(Apache-2.0)

#include "Clem.h"
#include <cassert>
#include <iostream>
#include <stdio.h>

using namespace std;

class Pong : public Application
{
public:
	Pong()
			: Application("Pong")
	{
		scene = make_shared<Scene>();  // �������� scene, ���ڹ���ʵ��
		pushScene(scene);              // �� scene ѹ���ջ
		createBall();
	}

	void createBall()
	{
		auto ball = scene->createEntity();           // �� scene ���봴��һ��ʵ�� ball

		auto& sprite = ball.addComponent<Sprite>();  // Ϊ ball ����һ�� Sprite ���
		sprite.setSize({1, 1});                      // ���� Sprite �Ĵ�С, ���ɻ�������Ĵ�С
		sprite.drawPoint({0, 0}, Tile('O'));         // �� 0,0 ������һ�� Tile

		auto& body = ball.addComponent<Rigidbody>(); // Ϊ ball ����һ�� Rigidbody ���
	}

private:
	std::shared_ptr<Scene> scene;
};

Application* CreateApplication()
{
	return new Pong();
}
