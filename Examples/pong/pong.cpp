// Copyright 2021 SMS
// License(Apache-2.0)

#include <Clem.h>
#include <future>
#include <iostream>
#include <string>

using namespace std;
using namespace clem;

// TODO: 物理引擎: 碰撞检测, 乒乓球反弹, 约束球拍

class App : public Application
{
public:
	App()
			: Application("Pong")
	{
	}

	void init() override
	{
		Main::getWindow()->add(new ui::Hierarchy);
		Main::getWindow()->add(new ui::Properties);

		Main::getWindow()->add(new ui::DevelopMenu);

		// 加载音频文件
		pop.loadFromFile("assets/pop.wav");
		score.loadFromFile("assets/score.wav");

		// 设置音源方位
		up.setPosition({0, 5});
		down.setPosition({0, -5});
		left.setPosition({-5, 0});
		right.setPosition({5, 0});

		auto& reg = Main::registry;

		// 创建背景
		auto board = reg.create("board");
		board.add<Transform>();
		auto& boardSprite = board.add<Sprite>(Size2(80, 25));
		boardSprite.drawRect(Rect2i({0, 0}, {80, 25}), Tile('#'));
		boardSprite.fillRect(Rect2i({39, 1}, {2, 23}), Tile('.', Color::green));
		board.add<Script>().onUpdate = [&](Time dt) {
			boardSprite.drawString({34, 2}, to_wstring(player_score));
			boardSprite.drawString({44, 2}, to_wstring(ai_score));
		};

		// 创建乒乓球 Sprite
		Sprite ballSprite({1, 1});
		ballSprite.drawPoint({0, 0}, Tile('O', Color::yellow));

		// 创建乒乓球
		auto ball = reg.create("ball");
		ball.add<Sprite>(ballSprite);
		ball.add<Rigidbody>();
		ball.add<Transform>();

		// 创建乒乓球球拍 Sprite
		Sprite batSprite({1, 5});
		batSprite.fillRect(Rect2i({0, 0}, {1, 5}), Tile(L'█', Color::blue));

		// 创建两个乒乓球拍
		for(int i = 0; i < 2; i++)
		{
			bats[i] = reg.create();
			bats[i].add<Sprite>(batSprite);
			bats[i].add<Rigidbody>();
			bats[i].add<Transform>();
		}

		// Bat1 由玩家控制
		// 为 bats[0] 创建一个事件监听器, 监听按键事件
		EventDispatcher::get().addListener(Event::Type::key, [&](Event* e) {
			auto  event = dynamic_cast<KeyEvent*>(e);
			auto& body  = bats[0].get<Rigidbody>(); // 通过 Tag 组件获取 bats[0] 实体的 Rigidbody 组件
			auto& tf    = bats[0].get<Transform>();

			if(event->state == false)
				body.velocity = Vector2::zero;
			else if(event->keyCode == KeyCode::W)
				body.velocity = {0, -player_speed};
			else if(event->keyCode == KeyCode::S)
				body.velocity = {0, player_speed};

			if(tf.getPosition().y + body.velocity.y < 1)
			{
				body.velocity = Vector2::zero;
				tf.setPosition({tf.getPosition().x, 1});
				return;
			}
			else if(tf.getPosition().y + body.velocity.y > 19)
			{
				body.velocity = Vector2::zero;
				tf.setPosition({tf.getPosition().x, 19});
				return;
			}
		});

		// Bat2 由AI控制, 不推测路径
		// 为 bats[1] 创建一个脚本
		bats[1].add<Script>().onUpdate = [&](Time) {
			auto  ballPos = Main::registry.get("ball").get<Transform>().getPosition();
			auto& batBody = bats[1].get<Rigidbody>();
			auto  batPos  = bats[1].get<Transform>().getPosition();
			auto& batSize = bats[1].get<Sprite>().getSize();

			// 获取 bats[1] 的 Sprite 的几何中心
			auto batCenter = batPos + batSize / 2;

			// 以 ai_speed 速度向 ball 所在的 y 坐标移动
			batBody.velocity = Vector2(0, ballPos.y - batCenter.y).normalize() * ai_speed;
		};

		// 碰撞检测
		ball.add<Script>().onUpdate = [&](Time) {
			auto  ball    = Main::registry.get("ball");
			auto& ts      = ball.get<Transform>();
			auto& vel     = ball.get<Rigidbody>().velocity;
			auto& sprite  = ball.get<Sprite>();
			auto& ballPos = ts.getPosition();

			// 球与球拍
			for(int i = 0; i < 2; i++)
			{
				auto& tf   = bats[i].get<Transform>();
				auto& pos  = tf.getPosition();
				auto& size = bats[i].get<Sprite>().getSize();
				Rect2 rect(pos, Size2((float)size.x, (float)size.y));

				if(rect.intersectsPoint(ballPos))
				{
					if(ballPos.x < 39)
					{
						left.play(pop);
						ts.setPosition({pos.x + 1, ballPos.y});
					}
					else
					{
						right.play(pop);
						ts.setPosition({pos.x - 1, ballPos.y});
					}
					vel.x = -vel.x;
					vel.y += (float)random.getInt32(-random_rebound_angle, random_rebound_angle) / 100;
				}
			}

			// 球拍与边界
			auto& tf   = bats[1].get<Transform>();
			auto& body = bats[1].get<Rigidbody>();
			if(tf.getPosition().y + body.velocity.y < 1)
			{
				body.velocity = Vector2::zero;
				tf.setPosition({tf.getPosition().x, 1});
			}
			else if(tf.getPosition().y + body.velocity.y > 19)
			{
				body.velocity = Vector2::zero;
				tf.setPosition({tf.getPosition().x, 19});
			}

			// 球与边界
			if(ballPos.x < 1)
			{
				// ts.setPosition({1, ballPos.y});
				// vel.x = -vel.x;
				// vel.y += (float)random.getInt32(-random_rebound_angle, random_rebound_angle) / 100;
				resetBall();
				resetBats();
				left.play(score);
				ai_score++;
			}
			else if(ballPos.x >= 79)
			{
				// ts.setPosition({78, ballPos.y});
				// vel.x = -vel.x;
				// vel.y += (float)random.getInt32(-random_rebound_angle, random_rebound_angle) / 100;
				resetBall();
				resetBats();
				right.play(score);
				player_score++;
			}
			else if(ballPos.y < 1)
			{
				ts.setPosition({ballPos.x, 1});
				vel.y = -vel.y;
				vel.x += (float)random.getInt32(-random_rebound_angle, random_rebound_angle) / 100;
				up.play(pop);
			}
			else if(ballPos.y >= 24)
			{
				ts.setPosition({ballPos.x, 23});
				vel.y = -vel.y;
				vel.x += (float)random.getInt32(-random_rebound_angle, random_rebound_angle) / 100;
				down.play(pop);
			}
			else
				return;
			vel = vel.normalize() * ball_speed;
		};

		resetBall();
		resetBats();
	}

	// 重置 ball 的位置
	void resetBall()
	{
		Main::registry.get("ball").get<Transform>().setPosition({39, 12});
		Main::registry.get("ball").get<Rigidbody>().velocity = Vector2::zero;

		static future<void> h;
		h = async([this]() {
			this_thread::sleep_for(chrono::seconds(2));
			Main::registry.get("ball").get<Rigidbody>().velocity = Vector2::right * ball_speed;
		});
	}

	// 重置 bat 的位置
	void resetBats()
	{
		bats[0].get<Transform>().setPosition({2, 10});
		bats[1].get<Transform>().setPosition({77, 10});
	}

private:
	int player_score = 0;
	int ai_score     = 0;

	const float ball_speed           = 1.0f;  // 球的移动速度
	const float player_speed         = 0.15f; // 玩家乒乓球拍的移动速度
	const float ai_speed             = 0.1f;  // AI 乒乓球拍的移动速度
	const int   random_rebound_angle = 5;     // 碰撞时随机调整角度系数
	const float volume               = 0.1f;  // 声音效果音量

	Entity bats[2];

	Sound  pop, score;
	Source up, down, left, right;

	Random random;
};

Application* clem::CreateApplication()
{
	return new App;
}