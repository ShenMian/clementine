// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <vector>

class Session;

/**
 * @brief ���ܷ�����.
 * ֧���Բ�ͬ�ĸ�ʽ������������. ������������� Tracking ������ JSON ��ʽ.
 */
class Profiler
{
public:
	static Profiler& get();

	void addSession(Session& s);

private:
	std::vector<Session> sessions;
};
