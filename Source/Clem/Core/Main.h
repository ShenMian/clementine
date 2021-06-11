// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

int main(int argc, char* argv[]);

namespace clem
{

/**
 * @addtogroup Core
 * @{
 */

class Main
{
public:
	int main(int argc, char* argv[]);

	void init();
	void deinit();

private:
	void parseArgs(int argc, char* argv[]);
};

/**
 * end of Core group
 * @}
 */

} // namespace clem
