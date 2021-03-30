// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Clem/Core/Math/Math.h"
#include <unordered_map>

/**
 * @brief ���.
 * 
 * @warn ��֧�� Windows ϵͳ
 */
class Mouse
{
public:
	enum class Key : uint8_t;

	/**
	 * @brief ��ȡ����״̬.
	 * 
	 * @param k ����.
	 * @return ��������ʱ���� true.
	 */
	static bool getKeyState(Key k);

	/**
	 * @brief ���ð���״̬.
	 * 
	 * @param k ����.
	 * @param s ״̬, ����Ϊ true.
	 */
	static void setKeyState(Key k, bool s);

	static Point2i getPosition();

	static void setPosition(Point2i p);

private:
	static std::unordered_map<Key, bool> states;
	static Point2i                       position;
};

enum class Mouse::Key : uint8_t
{
	left,
	right
};
