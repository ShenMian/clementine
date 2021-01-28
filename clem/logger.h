
#ifndef CLEM_LOGGER_H_
#define CLEM_LOGGER_H_

class Logger
{
public:
	void   write(short id, std::string msg);
	static add(short id, std::string path);
	static remove(short id);

private:
	static map<short, std::ofstream> index;
};

#endif // CLEM_LOGGER_H_

