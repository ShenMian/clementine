// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <cstdint>

namespace clem
{

class Time
{
public:
	/**
	 * @brief ��ȡ����Ϊ��λ��ʱ��.
	 */
	float seconds() const;

	/**
	 * @brief ��ȡ�Ժ���Ϊ��λ��ʱ��.
	 */
	uint32_t milliseconds() const;

	/**
	 * @brief ��ȡ��΢��Ϊ��λ��ʱ��.
	 */
	uint64_t microseconds() const;

private:
	Time(uint64_t us);

	uint64_t microseconds_;

	friend Time seconds(float sec);
	friend Time milliseconds(uint32_t ms);
	friend Time microseconds(uint64_t us);
};

} // namespace clem
