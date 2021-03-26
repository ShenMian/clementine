// Copyright 2021 SMS
// License(Apache-2.0)

#include "Clem.h"

using namespace std;

class Chess : public Application
{
public:
	Chess()
			: Application("Chess")
	{
		shared_ptr<Scene> keyboardScene = make_shared<Scene>();
		pushScene(keyboardScene);

		auto keyboard = keyboardScene->createEntity("keyboard");
		auto esc      = keyboardScene->createEntity("esc");
		esc.addComponent<Sprite>(Size2(5, 1)).drawString({0, 0}, L"[Esc]");

/*
". -------------------------------------------------------------------."
"| [Esc] [F1][F2][F3][F4][F5][F6][F7][F8][F9][F0][F10][F11][F12] o o o|"
"|                                                                    |"
"| [`][1][2][3][4][5][6][7][8][9][0][-][=][_<_] [I][H][U] [N][/][*][-]|"
"| [|-][Q][W][E][R][T][Y][U][I][O][P][{][}] | | [D][E][D] [7][8][9]|+||"
"| [CAP][A][S][D][F][G][H][J][K][L][;]['][#]|_|           [4][5][6]|_||"
"| [^][\][Z][X][C][V][B][N][M][,][.][/] [__^__]    [^]    [1][2][3]| ||"
"| [c]   [a][________________________][a]   [c] [<][V][>] [ 0  ][.]|_||"
"`--------------------------------------------------------------------'"
*/

		EventDispatcher::getInstance().addListener(Event::Type::key, [&](Event* e) {
			auto event = dynamic_cast<KeyEvent*>(e);
			if(event->state == false)
				return;
			switch(event->keyCode)
			{
			case KeyCode::ESCAPE:
				keyboardScene->getEntityByTag("esc").getComponent<Sprite>().drawString({0, 0}, L"[Esc]");
				break;
			}
		});

		/*
		auto  e = scene->createEntity("controller");
		auto& s = e.addComponent<Sprite>(Size2(120, 30));
		s.drawString({0, 0},  L"            ..                          ..");
		s.drawString({0, 1},  L"         .''..''.      .--~~--.      .``..``.");
		s.drawString({0, 2},  L"        .:''     `----'        `----'     ``:.");
		s.drawString({0, 3},  L"        |       .    ( * )  ( * )    .       |");
		s.drawString({0, 4},  L"       .' ....   `.  L1/L2  R1/R2  .'     _  `.");
		s.drawString({0, 5},  L"      : .;\\  /;.  :  ( * )  ( * )  :   _ (B) _ :");
		s.drawString({0, 6},  L"     :  :) () (:   :              :   (A) _ (D) :");
		s.drawString({0, 7},  L"      : `:/  \\:'  :       B        :     (C)   :");
		s.drawString({0, 8},  L"       :  ''''   .'   A ( * ) D    `.         :");
		s.drawString({0, 9},  L"      .'        '   ( * ) C ( * )    `        `.");
		s.drawString({0, 10}, L"     .'        .''.     ( * )      .``.        `.");
		s.drawString({0, 11}, L"   .'        .'   `. (o)      (o) .'   `.        `.");
		s.drawString({0, 12}, L"  .'       .'      `.   1(* )2   .'      `.       `.");
		s.drawString({0, 13}, L".'       .'         `............'         `.       `.");
		s.drawString({0, 14}, L"`.      .' 4 BUTTON FLIGHT  YOKE W/THROTTLE `.      .'");
		s.drawString({0, 15}, L"  `....'   Lester                       AMC   `....'");
		e.getComponent<Transform>().setLocalPosition(Point2(20, 5));
		*/
	}
};

Application* CreateApplication()
{
	return new Chess;
}
