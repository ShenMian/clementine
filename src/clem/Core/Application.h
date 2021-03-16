
#ifndef CLEM_CORE_APPLICATION_H_
#define CLEM_CORE_APPLICATION_H_

#include <string>

class Application
{
public:
	static Application& getInstance();

	virtual ~Application();

	const std::string& getName() const;

protected:
	/**
	 * @brief 构造函数.
	 */
	Application(const std::string& = "Clementine");

private:
	std::string         name;
	static Application* instance;
};

Application* CreateApplication();

#endif // !CLEM_CORE_APPLICATION_H_
