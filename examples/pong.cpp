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
		// �������� scene, ���ڹ���ʵ��
		auto scene = make_shared<Scene>();

		// �� scene ѹ���ջ, λ��ջ���ĳ���������Ϸ����ʱ��ִ��
		pushScene(scene);

		// ����ʵ�� ball, ͨ���� scene ����һ��ʵ��
		auto ball = scene->createEntity();

		// Ϊ ball ����һ�� Sprite ���
		auto& sprite = ball.addComponent<Sprite>();

		// ���� Sprite �Ĵ�С, ���ɻ�������Ĵ�С
		sprite.setSize({1, 1});

		// �� 0,0 ������һ�� Tile
		sprite.drawPoint({0, 0}, Tile('O'));
	}

	~Pong()
	{
	}
};

Application* CreateApplication()
{
	return new Pong();
}
