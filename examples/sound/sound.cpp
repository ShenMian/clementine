// Copyright 2021 SMS
// License(Apache-2.0)

#include <Clem.h>
#include <future>

using namespace std;
using namespace clem;

class Sound : public Application
{
public:
	Sound()
			: Application("Sound")
	{
	}

	void init() override
	{
		pushScene(scene);

		sound.loadFromFile("../pong/assets/pop.wav");
		source.setLoop(true);
		source.play(sound);

		auto& s = scene->createEntity("source");
		s.addComponent<Sprite>(Size2i(1, 1)).drawPoint({0, 0}, '*');
		s.addComponent<Script>([&](float) {
			if(Mouse::getKeyState(Mouse::Key::left))
			{
				auto& ts  = scene->getEntity("source").getComponent<Transform>();
				auto& pos = Mouse::getPosition();
				ts.setLocalPosition(pos);
				source.setPosition(ts.getPosition());
			}
		});

		auto& l = scene->createEntity("listener");
		l.addComponent<Sprite>(Size2i(1, 1)).drawPoint({0, 0}, '@');
		l.getComponent<Transform>().setLocalPosition(Point2(size.x / 2, size.y / 2));
		l.addComponent<Script>().onUpdate = [&](float dt) {
				auto& ts = scene->getEntity("listener").getComponent<Transform>();
				if(Keyboard::getKeyState(Keyboard::Key::W))
					ts.setLocalPosition(ts.getLocalPosition() + Vector2::down * 5 * dt);
				if(Keyboard::getKeyState(Keyboard::Key::S))
					ts.setLocalPosition(ts.getLocalPosition() + Vector2::up * 5 * dt);
				if(Keyboard::getKeyState(Keyboard::Key::A))
					ts.setLocalPosition(ts.getLocalPosition() + Vector2::left * 5 * dt);
				if(Keyboard::getKeyState(Keyboard::Key::D))
					ts.setLocalPosition(ts.getLocalPosition() + Vector2::right * 5 * dt);
				Listener::setPosition(ts.getPosition());
		};
	}

private:
	clem::Sound       sound;
	Source            source;
	Random            random;
	Size2i            size  = Window::getSize();
	shared_ptr<Scene> scene = make_shared<Scene>();
};

Application* clem::CreateApplication()
{
	return new ::Sound;
}
