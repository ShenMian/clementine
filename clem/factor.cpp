// Copyright 2020 SMS
// License(Apache-2.0)
// 游戏对象

#include "factor.h"
#include "scene.h"
#include <algorithm>
#include <assert.h>

Factor::Factor()
{
}

Factor::Factor(const Texture& texture)
		: texture(texture)
{
}

void Factor::update()
{
}

void Factor::setPosition(const Point& pos)
{
	this->position = pos;
}

void Factor::setTexture(const Texture& texture)
{
	this->texture = texture;
}

const Point& Factor::getPosition() const
{
	return position;
}

const Texture& Factor::getTexture() const
{
	return texture;
}
