
#include <string>

/// 终端
class Terminal
{
public:
  static void setTitle(const std::string&);
  static bool getch(char&);
};

