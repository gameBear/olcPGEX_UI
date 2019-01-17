#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "olcPGEX_UI.h"

static int screenW = 640, screenH = 480;

class Example : public olc::PixelGameEngine
{
public:
	int w = screenW;
	olc::UI_CONTAINER myUI;


	Example()
	{
		sAppName = "UI Sample";
	}

public:
	bool OnUserCreate() override
	{

		// A simple button
		myUI.addNewButton(120, 5, 70, 20, "A BOTTEN");

		// Four buttons bound to the keyboard keys WASD
		myUI.addNewButton(olc::Key::W, "UP_Key", screenW - 110, screenH - 130, 32, 32, " W");
		myUI.addNewButton(olc::Key::A, "LEFT_Key", screenW - 160, screenH - 80, 32, 32, " A");
		myUI.addNewButton(olc::Key::S, "DOWN_Key", screenW - 110, screenH - 80, 32, 32, " S");
		myUI.addNewButton(olc::Key::D, "RIGHT_Key", screenW - 60, screenH - 80, 32, 32, " D");

		// a drop down, note that the third sub button has teh cvommand EXIT, we will use this bellow
		myUI.addNewDropDown(UI_BLACK, UI_BLUE, 5, 5, 100, "MAIN", "FIRST,SECOND,EXIT", "CMD_1,CMD_2,EXIT");

		// a test field
		myUI.addTextField(50, screenH * 0.82, 20);

		//a slider with values 0-100 and a width of 400 pixels
		myUI.addSlider(20, 150, 400);

		// a avector used to setup two diffrent sliders.
		std::vector<int> range;
		range.push_back(10);
		range.push_back(15);
		range.push_back(18);
		range.push_back(20);
		range.push_back(50);
		range.push_back(90);

		// this slider will only be set to the values added to the vector "range"
		myUI.addSlider(480, 20, 150, TopBottom, SteppingSlider, range);

		// this slider will return a value between the first and last value in the vector "range"
		myUI.addSlider(520, 20, 150, BottomTop, RangeSetSlider, range);


		// a simple field that lets the mouse know its in the UI.
		//unless you call myUI.ToggleHideUIFIELDS(); you wont be able to see this field, but the mouse will be detected if it hovers it.
		myUI.addUIField(0, 0, screenW, 100);

		//do you want the ID to be visible durring the debud time?
		//myUI.toggleDEBUGMODE();

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{

		// this handles the uopdate of all items
		myUI.Update(fElapsedTime);

		// if any button in the current UI sends the command EXIT, letsd exit
		if (myUI.hasCommand("EXIT", false)) return 0;

		Clear(olc::DARK_GREY);

		// This draws all items in the UI
		myUI.drawUIObjects();

		// lets print a string to the screen telling if the mouse is in any UI.
		if (myUI.isMouseInUI()) DrawString(50, screenH* 0.9, ":THE MOUSE IS IN THE UI", olc::RED);
		else DrawString(50, screenH* 0.9, ":THE MOUSE NOT IN THE UI", olc::RED);


		// lets also draw all current commands to the screen
		std::string myOut = myUI.getAllCmds();
		DrawString(50, screenH* 0.95, myOut);


		DrawString(50, screenH* 0.8, "A text field, try using it:", olc::RED);
		return true;
	}
};


int main()
{
	Example demo;
	if (demo.Construct(screenW, screenH, 1, 1))
		demo.Start();

	return 0;
}
