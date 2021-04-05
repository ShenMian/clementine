// Copyright 2021 SMS
// License(Apache-2.0)

#include <Clem.h>
#include <future>
#include <iostream>
#include <string>

using namespace std;

// TODO: 碰撞检测: 乒乓球反弹, 约束球拍

class Pong : public Application
{
public:
	Pong()
			: Application("Pong")
	{
	}

	void init() override
	{
		pushScene(scene);

		// 加载音频文件
		popSound   = audio.loadSound("assets/pop.wav");
		scoreSound = audio.loadSound("assets/score.wav");

		// 设置音源方位
		upSource.setPosition({0, 5});
		downSource.setPosition({0, -5});
		leftSource.setPosition({-5, 0});
		rightSource.setPosition({5, 0});

		// 创建乒乓球 Sprite
		Sprite ballSprite({1, 1});
		ballSprite.drawPoint({0, 0}, Tile('O', Color::yellow));

		// 创建乒乓球
		auto ball = scene->createEntity("ball"); // 向 scene 申请创建一个实体 ball
		ball.addComponent<Sprite>(ballSprite);   // 为 ball 创建一个复制 ballSprite 的 Sprite 组件
		ball.addComponent<Rigidbody>();          // 为 ball 创建一个 Rigidbody 组件

		// 创建乒乓球球拍 Sprite
		Sprite batSprite({1, 5});
		batSprite.fillRect(Rect2i({0, 0}, {1, 5}), Tile('#', Color::blue));

		// 创建两个乒乓球拍
		auto bat1 = scene->createEntity("bat1");
		auto bat2 = scene->createEntity("bat2");
		bat1.addComponent<Sprite>(batSprite);
		bat2.addComponent<Sprite>(batSprite);
		bat1.addComponent<Rigidbody>();
		bat2.addComponent<Rigidbody>();

		// Bat1 由玩家控制
		// 为 bat1 创建一个事件监听器, 监听按键事件
		EventDispatcher::getInstance().addListener(Event::Type::key, [&](Event* e) {
			auto  event = dynamic_cast<KeyEvent*>(e);
			auto& body  = scene->getEntity("bat1").getComponent<Rigidbody>(); // 通过 Tag 组件获取 bat1 实体的 Rigidbody 组件
			if(event->state == false)
				body.velocity = Vector2::zero;
			else if(event->keyCode == KeyCode::W)
				body.velocity = {0, -player_speed};
			else if(event->keyCode == KeyCode::S)
				body.velocity = {0, player_speed};
		});

		// Bat2 由AI控制, 不推测路径
		// 为 bat2 创建一个脚本
		bat2.addComponent<Script>().onUpdate = [&](float) {
			auto  bat     = scene->getEntity("bat2");
			auto  ballPos = scene->getEntity("ball").getComponent<Transform>().getLocalPosition();
			auto& batBody = bat.getComponent<Rigidbody>();
			auto  batPos  = bat.getComponent<Transform>().getLocalPosition();
			auto& batSize = bat.getComponent<Sprite>().getSize();

			// 获取 bat2 的 Sprite 的几何中心
			auto batCenter = batPos + batSize / 2;

			// 以 ai_speed 速度向 ball 所在的 y 坐标移动
			batBody.velocity = Vector2(0, ballPos.y - batCenter.y).normalize() * ai_speed;
		};

		// TODO: 碰撞检测. 碰撞时被回调, 调整随机角度
		ball.addComponent<Script>().onUpdate = [&](float) {
			auto   ball    = scene->getEntity("ball");
			auto&  ts      = ball.getComponent<Transform>();
			auto&  vel     = ball.getComponent<Rigidbody>().velocity;
			auto&  sprite  = ball.getComponent<Sprite>();
			auto&  ballPos = ts.getPosition();
			Entity bats[2];
			bats[0] = scene->getEntity("bat1");
			bats[1] = scene->getEntity("bat2");

			for(int i = 0; i < 2; i++)
			{
				auto& pos  = bats[i].getComponent<Transform>().getPosition();
				auto& size = bats[i].getComponent<Sprite>().getSize();
				Rect2 rect(pos, Size2((float)size.x, (float)size.y));
				if(rect.intersectsPoint(ballPos))
				{
					if(ballPos.x < 39)
					{
						leftSource.play(popSound);
						ts.setLocalPosition({pos.x + 1, ballPos.y});
					}
					else
					{
						rightSource.play(popSound);
						ts.setLocalPosition({pos.x - 1, ballPos.y});
					}
					vel.x = -vel.x;
					vel.y += (float)random.getInt32(-random_rebound_angle, random_rebound_angle) / 100;
				}
			}

			if(ballPos.x < 1)
			{
				ts.setLocalPosition({1, ballPos.y});
				vel.x = -vel.x;
				vel.y += (float)random.getInt32(-random_rebound_angle, random_rebound_angle) / 100;
				resetBall();
				resetBats();
				leftSource.play(scoreSound);
				ai_score++;
			}
			else if(ballPos.x >= 79)
			{
				ts.setLocalPosition({78, ballPos.y});
				vel.x = -vel.x;
				vel.y += (float)random.getInt32(-random_rebound_angle, random_rebound_angle) / 100;
				resetBall();
				resetBats();
				rightSource.play(scoreSound);
				player_score++;
			}
			else if(ballPos.y < 1)
			{
				ts.setLocalPosition({ballPos.x, 1});
				vel.y = -vel.y;
				vel.x += (float)random.getInt32(-random_rebound_angle, random_rebound_angle) / 100;
				upSource.play(popSound);
			}
			else if(ballPos.y >= 24)
			{
				ts.setLocalPosition({ballPos.x, 23});
				vel.y = -vel.y;
				vel.x += (float)random.getInt32(-random_rebound_angle, random_rebound_angle) / 100;
				downSource.play(popSound);
			}
			else
				return;
			vel = vel.normalize() * ball_speed;
		};

		// 创建场景中的其他元素
		auto  board       = scene->createEntity("board");
		auto& boardSprite = board.addComponent<Sprite>(Size2(80, 25));
		boardSprite.drawRect(Rect2i({0, 0}, {80, 25}), Tile('#'));
		boardSprite.fillRect(Rect2i({39, 1}, {2, 23}), Tile('.', Color::green));
		board.addComponent<Script>().onUpdate = [&](float dt) {
			boardSprite.drawString({34, 2}, to_wstring(player_score));
			boardSprite.drawString({44, 2}, to_wstring(ai_score));
		};

		resetBall();
		resetBats();
	}

	// 重置 ball 的位置
	void resetBall()
	{
		scene->getEntity("ball").getComponent<Transform>().setLocalPosition({39, 12});
		scene->getEntity("ball").getComponent<Rigidbody>().velocity = Vector2::zero;
		
		static future<void> h;
		h = async([&]() {
			this_thread::sleep_for(chrono::seconds(2));
			scene->getEntity("ball").getComponent<Rigidbody>().velocity = Vector2::right * ball_speed;
		});
	}

	// 重置 bat 的位置
	void resetBats()
	{
		scene->getEntity("bat1").getComponent<Transform>().setLocalPosition({2, 10});
		scene->getEntity("bat2").getComponent<Transform>().setLocalPosition({77, 10});
	}

private:
	int player_score = 0;
	int ai_score     = 0;

	const float ball_speed           = 0.8f;  // 球的移动速度, 始终恒定
	const float player_speed         = 0.15f; // 玩家乒乓球拍的移动速度
	const float ai_speed             = 0.1f;  // AI 乒乓球拍的移动速度
	const int   random_rebound_angle = 5;     // 碰撞时随机调整角度系数
	const float volume               = 0.1f;  // 声音效果音量

	Audio&      audio = Audio::get();
	Audio::id_t popSound, scoreSound;
	Source      upSource, downSource, leftSource, rightSource;

	Random random;

	shared_ptr<Scene> scene = make_shared<Scene>();
};

#if 1
Application* CreateApplication()
{
	return new Pong;
}
#endif
