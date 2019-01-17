#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "olcPGEX_UI.h"

static int screenW = 640, screenH = 480;

class Example : public olc::PixelGameEngine
{
public:
	int w = screenW;

	//We need a stage controller for multiple stages
	olc::UI_STAGE_CONTROLL myUI;

	// a stage enum to dictate teh current stage
	pgrSTAGE currentStage = MAIN_MENU;


	Example()
	{
		sAppName = "UI Sample";
	}

public:
	bool OnUserCreate() override
	{
		std::vector<pgrSTAGE> allStages;
		allStages.push_back(MAIN_MENU);
		allStages.push_back(PGR_STG0);
		allStages.push_back(PGR_STG1);

		myUI.setUp(screenW, screenH, allStages);

		// When adding to the UI_STAGE_CONTROLL, it is important to call the stage you wish to add to first
		// lets add to the mainmenu, if such one exists. (it does, we added it first to the vector ;)
		if (myUI.addToStage(MAIN_MENU)) {
			// Here we will just add adrop down menu that will let uc chose the tow other stages. we will aslo add an exit button
			myUI.addNewDropDown(UI_BLACK, UI_BLUE, 5, 5, 100, "MAIN", "STAGE 0,Stage 1,EXIT", "PGR_STG0,PGR_STG1,EXIT");
			//do you want the ID to be visible durring the debud time?
			//myUI.toggleDEBUGMODE();
		}


		if (myUI.addToStage(PGR_STG0)) {
			// in stage 0 we will just add a return button, that will let us return tom main menu
			myUI.addNewButton("MAIN_MENU", 0, screenH*0.5, screenW, 50, "MAIN MENU");
			//do you want the ID to be visible durring the debud time?
			//myUI.toggleDEBUGMODE();
		}

		if (myUI.addToStage(PGR_STG1)) {
			// in stage 1 we will add a button that will take us to stage 0 if we press space
			myUI.addNewButton(olc::Key::SPACE, "PGR_STG0", 0, screenH*0.1, screenW, 50, "Press Space to get to stage 0");
			//do you want the ID to be visible durring the debud time?
			//myUI.toggleDEBUGMODE();
		}

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{

		// this handles the uopdate of all items, it needs our current stage so it cvan update it.
		myUI.Update(fElapsedTime, currentStage);

		// if any button in the current UI sends the command EXIT, letsd exit
		if (myUI.hasCommand("EXIT", false)) return 0;


		//say you want to use teh stage to do stuff like letting a ball pass the screen in some odd way.
		// Short program irellevant for the setup, but demonstration of the UI_STAGE_CONTROLL handeling all things
		// we will just let a ball bounce on the screen without a care in the world.
		static float x = 200.0f, y = 200.0f, xspeed = 105.5f, yspeed = 125.8f;

		switch (currentStage)
		{
		case MAIN_MENU:
			x += xspeed * fElapsedTime;
			y += yspeed * fElapsedTime;
			if (x > screenW && xspeed > 0) xspeed = xspeed * -1;
			else if (x < 0 && xspeed < 0) xspeed = xspeed * -1;

			if (y > screenH && yspeed > 0) yspeed = yspeed * -1;
			else if (y < 0 && yspeed < 0) yspeed = yspeed * -1;

			break;
		case PGR_STG0:
			y += yspeed * fElapsedTime;
			if (x > screenW && xspeed > 0) xspeed = xspeed * -1;
			else if (x < 0 && xspeed < 0) xspeed = xspeed * -1;

			if (y > screenH && yspeed > 0) yspeed = yspeed * -1;
			else if (y < 0 && yspeed < 0) yspeed = yspeed * -1;

			break;
		case PGR_STG1:
			x += xspeed * fElapsedTime;
			if (x > screenW && xspeed > 0) xspeed = xspeed * -1;
			else if (x < 0 && xspeed < 0) xspeed = xspeed * -1;

			if (y > screenH && yspeed > 0) yspeed = yspeed * -1;
			else if (y < 0 && yspeed < 0) yspeed = yspeed * -1;

			break;
		default:
			break;
		}


		// CLEAR THE SCREEN
		Clear(olc::DARK_GREY);

		// This draws all items in the UI
		myUI.drawUIObjects();

		// lets print a string to the screen telling if the mouse is in any UI.
		if (myUI.isMouseInUI()) DrawString(50, screenH* 0.9, ":THE MOUSE IS IN THE UI", olc::RED);
		else DrawString(50, screenH* 0.9, ":THE MOUSE NOT IN THE UI", olc::RED);


		// lets also draw all current commands to the screen
		std::string myOut = myUI.getAllCmds();
		DrawString(50, screenH* 0.95, myOut);

		DrawCircle(x, y, 10);
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
