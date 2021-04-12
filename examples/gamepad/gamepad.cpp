// Copyright 2021 SMS
// License(Apache-2.0)

#include <Clem.h>
#include <future>

using namespace std;
using namespace clem;

class Gamepad : public Application
{
public:
	Gamepad()
			: Application("Gamepad")
	{
	}

	void init() override
	{
		pushScene(scene);

		sprite = &scene->createEntity().addComponent<Sprite>(Size2i(120, 30));
		sprite->drawString({0, -1},
											 LR"(
            ..                             ..
         .''..''.     .-----~~----.     .``..``.
        .:''     `---'             `---'     ``:.
        |      .       _          _      .       |
       .' ....  `.    (B)        (S)    .'    _  `.
      : .`    `.  :                     :  _ (Y) _ :
     :  :  ()  :   :                   :  (X) _ (B) :
      : `:    :'  :                     :    (A)   :
       :  ''''   .'    _         ....   `.        :
      .'        '    _| |_     .`    `.   `        `.
     .'        .''. |_   _|    :  ()  :  .``.       `.
   .'        .'   `.  |_|      `:    :' .'   `.       `.
  .'       .'      `.            ''''  .'      `.       `.
.'       .'         `..................'         `.       `.
`.      .'                                        `.      .'
  `....'                                            `....')");

		static future<void> h = async([&]() {
			clem::Gamepad gamepad;
			while(true)
			{
				gamepad.update();

				// 按钮
				sprite->drawPoint({46, 7},
													Tile('A', gamepad.get(clem::Gamepad::Button::A) ? Color::red : Color::white));
				sprite->drawPoint({49, 6},
													Tile('B', gamepad.get(clem::Gamepad::Button::B) ? Color::red : Color::white));
				sprite->drawPoint({43, 6},
													Tile('X', gamepad.get(clem::Gamepad::Button::X) ? Color::red : Color::white));
				sprite->drawPoint({46, 5},
													Tile('Y', gamepad.get(clem::Gamepad::Button::Y) ? Color::red : Color::white));
				sprite->drawPoint({34, 4},
													Tile('S', gamepad.get(clem::Gamepad::Button::Start) ? Color::red : Color::white));
				sprite->drawPoint({23, 4},
													Tile('B', gamepad.get(clem::Gamepad::Button::Back) ? Color::red : Color::white));

				sprite->drawPoint({23, 9},
													gamepad.get(clem::Gamepad::Button::DPAD_Up) ? Tile('#', Color::red) : ' ');
				sprite->drawPoint({23, 11},
													gamepad.get(clem::Gamepad::Button::DPAD_Down) ? Tile('#', Color::red) : '_');
				sprite->drawPoint({21, 10},
													gamepad.get(clem::Gamepad::Button::DPAD_Left) ? Tile('#', Color::red) : '_');
				sprite->drawPoint({25, 10},
													gamepad.get(clem::Gamepad::Button::DPAD_Right) ? Tile('#', Color::red) : '_');
			
				sprite->drawString({12, 0}, L"..", gamepad.get(clem::Gamepad::Button::Shoulder_Left) ? Color::red : Color::white);
				sprite->drawString({43, 0}, L"..", gamepad.get(clem::Gamepad::Button::Shoulder_Right) ? Color::red : Color::white);

				// 线性按钮
				sprite->drawString({15, 0}, to_wstring(gamepad.get(clem::Gamepad::Trigger::left)) + L"   \r", gamepad.get(clem::Gamepad::Trigger::left) ? Color::red : Color::white);
				sprite->drawString({46, 0}, to_wstring(gamepad.get(clem::Gamepad::Trigger::right)) + L"   \r", gamepad.get(clem::Gamepad::Trigger::right) ? Color::red : Color::white);

				// 摇杆
				auto& LT      = gamepad.get(clem::Gamepad::Thumb::left);
				auto  LTAngle = LT.angle() * rad_to_deg;
				sprite->drawString({13, 6},
													 LTAngle == 0 && LT.size() ? L"--" : L"  ", Color::red);
				sprite->drawPoint({13, 5},
													0 < LTAngle && LTAngle < 90 ? Tile('/', Color::red) : ' ');
				sprite->drawPoint({12, 5},
													LTAngle == 90 ? Tile('|', Color::red) : ' ');
				sprite->drawPoint({13, 7},
													-90 < LTAngle && LTAngle < 0 ? Tile('\\', Color::red) : ' ');
				sprite->drawString({9, 6},
													LTAngle == 180 && LT.size() ? L"--" : L"  ", Color::red);
				sprite->drawPoint({10, 7},
													-180 < LTAngle && LTAngle < -90 ? Tile('/', Color::red) : ' ');
				sprite->drawPoint({12, 7},
													LTAngle == -90 ? Tile('|', Color::red) : ' ');
				sprite->drawPoint({10, 5},
													90 < LTAngle && LTAngle < 180 ? Tile('\\', Color::red) : ' ');

				auto& RT      = gamepad.get(clem::Gamepad::Thumb::right);
				auto  RTAngle = RT.angle() * rad_to_deg;
				sprite->drawString({13 + 23, 6 + 4},
													 RTAngle == 0 && RT.size() ? L"--" : L"  ", Color::red);
				sprite->drawPoint({13 + 23, 5 + 4},
													0 < RTAngle && RTAngle < 90 ? Tile('/', Color::red) : ' ');
				sprite->drawPoint({12 + 23, 5 + 4},
													RTAngle == 90 ? Tile('|', Color::red) : ' ');
				sprite->drawPoint({13 + 23, 7 + 4},
													-90 < RTAngle && RTAngle < 0 ? Tile('\\', Color::red) : ' ');
				sprite->drawString({9 + 23, 6 + 4},
													 RTAngle == 180 && RT.size() ? L"--" : L"  ", Color::red);
				sprite->drawPoint({10 + 23, 7 + 4},
													-180 < RTAngle && RTAngle < -90 ? Tile('/', Color::red) : ' ');
				sprite->drawPoint({12 + 23, 7 + 4},
													RTAngle == -90 ? Tile('|', Color::red) : ' ');
				sprite->drawPoint({10 + 23, 5 + 4},
													90 < RTAngle && RTAngle < 180 ? Tile('\\', Color::red) : ' ');

				gamepad.setVibration(gamepad.get(clem::Gamepad::Trigger::left) * 120, gamepad.get(clem::Gamepad::Trigger::right) * 120);
			}
		});
	}

private:
	Sprite*           sprite = nullptr;
	shared_ptr<Scene> scene = make_shared<Scene>();
};

Application* clem::CreateApplication()
{
	return new ::Gamepad;
}
