
class Application
{
public:
	static Application& getInstance();

protected:

private:
	/**
	 * @brief 构造函数.
	 */
	Application();

	virtual ~Application();
};
