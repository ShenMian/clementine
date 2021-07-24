// Copyright 2021 SMS
// License(Apache-2.0)

#include <Clem.h>
#include <future>

using namespace std;
using namespace clem;

class App : public Application
{
public:
	App()
			: Application("Sound")
	{
	}

	void init() override
	{
		pushScene(scene);

		Sound.loadFromFile("../pong/assets/pop.wav");
		source.setLoop(true);
		source.play(Sound);

		auto& s = scene->createEntity("source");
		s.addComponent<Sprite>(Size2i(1, 1)).drawPoint({0, 0}, '*');
		s.addComponent<Script>().onUpdate = [&](float) {
			if(Mouse::getKeyState(Mouse::Key::left))
			{
				auto& ts  = scene->getEntity("source").getComponent<Transform>();
				auto& pos = Mouse::getPosition();
				ts.setPosition(pos);
				source.setPosition(ts.getWorldPosition());
			}
		};

		auto& l = scene->createEntity("listener");
		l.addComponent<Sprite>(Size2i(1, 1)).drawPoint({0, 0}, '@');
		l.getComponent<Transform>().setPosition(Point2(size.x / 2, size.y / 2));
		l.addComponent<Script>().onUpdate = [&](float dt) {
			auto& ts = scene->getEntity("listener").getComponent<Transform>();
			if(Keyboard::getKeyState(Keyboard::Key::W))
				ts.setPosition(ts.getPosition() + Vector2::down * 5 * dt);
			if(Keyboard::getKeyState(Keyboard::Key::S))
				ts.setPosition(ts.getPosition() + Vector2::up * 5 * dt);
			if(Keyboard::getKeyState(Keyboard::Key::A))
				ts.setPosition(ts.getPosition() + Vector2::left * 5 * dt);
			if(Keyboard::getKeyState(Keyboard::Key::D))
				ts.setPosition(ts.getPosition() + Vector2::right * 5 * dt);
			Listener::setPosition(ts.getWorldPosition());
		};
	}

private:
	Sound             Sound;
	Source            source;
	Random            random;
	Size2i            size  = GlfwWindow::getSize();
	shared_ptr<Scene> scene = make_shared<Scene>();
};

Application* clem::CreateApplication()
{
	return new App;
}