// Copyright 2021 SMS
// License(Apache-2.0)

#include <Clem.h>

using namespace std;
	
class Unnamed : public Application
{
public:
	void init() override
	{
		pushScene(scene);

		auto player = scene->createEntity("player");
		auto& sprite = player.addComponent<Sprite>(Size2i(120, 30));

		sprite.drawString({0, -1},
LR"(
         _._._                       _._._
        _|   |_                     _|   |_
        | ... |_._._._._._._._._._._| ... |
        | ||| |  o NATIONAL BANK o  | ||| |
        | """ |  """    """    """  | """ |
   ())  |[-|-]| [-|-]  [-|-]  [-|-] |[-|-]|  ())
  (())) |     |---------------------|     | (()))
 (())())| """ |  """    """    """  | """ |(())())
 (()))()|[-|-]|  :::   .-"-.   :::  |[-|-]|(()))()
 ()))(()|     | |~|~|  |_|_|  |~|~| |     |()))(()
    ||  |_____|_|_|_|__|_|_|__|_|_|_|_____|  ||
 ~ ~^^ @@@@@@@@@@@@@@/=======\@@@@@@@@@@@@@@ ^^~ ~
      ^~^~                                ~^~^
)");
	}

private:
	shared_ptr<Scene> scene = make_shared<Scene>();
};

Application* CreateApplication()
{
	return new Unnamed;
}
