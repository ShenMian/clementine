// Copyright 2020 SMS
// License(Apache-2.0)

#include "clem/clem.hpp"

class Player : public Factor
{
public:
	Player(Scene& s)
			: Factor(s)
	{
		sprite.setSize({1, 5});
		sprite.drawLine({0, 0}, {0, 4}, Tile('#'));
		addComponent(keyboard);
		addComponent(sprite);
		addComponent(rigidbody);
	}

	void bind(Keyboard::Key up, Keyboard::Key down)
	{
		static const float speed = 5;
		keyboard.bindOnChanged(up, [&](bool state) {
			if(state)
				rigidbody.velocity = {0, -speed};
			else
				rigidbody.velocity = {0, 0};
		});
		keyboard.bindOnChanged(down, [&](bool state) {
			if(state)
				rigidbody.velocity = {0, speed};
			else
				rigidbody.velocity = {0, 0};
		});
	}

private:
	Keyboard  keyboard;
	Sprite    sprite;
	Rigidbody rigidbody;
};
