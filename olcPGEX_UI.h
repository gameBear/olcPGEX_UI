/*
	olcPGEX_UI.h v1.2

	+-------------------------------------------------------------+
	|   Extension made with OneLoneCoder Pixel Game Engine v1.12  |
	|      "Simple UI Tool, or.. Simple'ish" - ZleapingBear       |
	+-------------------------------------------------------------+

	What is this?
	~~~~~~~~~~~~~
	This is an extension header for the OlcPixelGameEngine.
	This extension is intented to help users quickly setup a protoptype for any game or program.

	To this end, the extension provides two classes for direct use.
	the UI_CONTAINER and the UI_STAGE_CONTROLL

	the first, UI_CONTAINER handles the updateing and drawing of all UI elements,
	including bottons, drop down menus, text fields, sliders and backgroundfields, as well as asignment of a unique ID and communication with these.
	For a single page application, such as a calculator or a stand-alone main menu this contain can be used and handles all objects by it self.

	The second class UI_STAGE_CONTROLL functions on the surface exactly as the UI_CONTAINER, with one exception.
	The UI_STAGE_CONTROLL contains multiple UI_CONTAINERs at the same time and handles switching between them for the user,
	this can even be done trough Commands bound to bottons at creation time.

	To help these classes there are multiple Enums created. the most important being the pgrSTAGE enum (Program stage)
	this enum contains a list of 20 diffrent stages that teh program can be in, 10 predefined and 10 generic.
	each stage name can also be used as a command on a botton, forcing the UI_STAGE_CONTROLL to switch to that stage if one such exists.



	// All stages are:
	// predefiend
	RUN_INTRO, MAIN_MENU, RUN_PROGRAM, SAVE_LOAD,
	PAUSE_PROGRAM, INVENTORY, VIEW_MAP, CREDITS,
	HIGHSCORE, PGR_OPTIONS,
	//and generic
	PGR_STG0, PGR_STG1, PGR_STG2, PGR_STG3,
	PGR_STG4, PGR_STG5, PGR_STG6, PGR_STG7,
	PGR_STG8, PGR_STG9
	
	This PGEX will be updated when time is. pull requests and errors will be read and fixed when possible.
	suggestions are welcome.

	License notes:
	~~~~~~~~~~~~~~~

	Copyright 2018 Michlas C. Lund-Mouritzen

	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions
	are met:

	1. Redistributions or derivations of source code must retain the above
	copyright notice, this list of conditions and the following disclaimer.

	2. Redistributions or derivative works in binary form must reproduce
	the above copyright notice. This list of conditions and the following
	disclaimer must be reproduced in the documentation and/or other
	materials provided with the distribution.

	3. Neither the name of the copyright holder nor the names of its
	contributors may be used to endorse or promote products derived
	from this software without specific prior written permission.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
	"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
	LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
	A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
	HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
	SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
	LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
	DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
	THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
	OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


	//////////////////////////////////////////////////////////////////////////////
	Links
	~~~~~
		ZleapingBear:
	Youtube:	https://www.youtube.com/zleapingbear
	Twitter:	https://twitter.com/MCLMouritzen
	GitHub:

		OneLoneCoder:
	YouTube:	https://www.youtube.com/javidx9
	Discord:	https://discord.gg/WhwHUMV
	GitHub:		https://www.github.com/onelonecoder
	Homepage:	https://www.onelonecoder.com


	Relevant Videos
	~~~~~~~~~~~~~~~
	PGE
	https://youtu.be/kRH6oJLFYxY Introducing olcPixelGameEngine

	PGEX_UI
	//TBA

	Compiling in XXXX
	~~~~~~~~~~~~~~~~~~
	Sorry all, i have no way of testing this. but should run on all things PGE safe.


	Thanks
	~~~~~~
	I'd like to extend thanks to David Bar for making the PGE, CGE, Videos and all other material aveliable.
	I hope you will keep up the fantastic work.

	Author
	~~~~~~
	Michlas C. Lund-Mouritzen, aka ZleapingBear, ©ZleapingBear 2018
*/

/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////// Minimum program //////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
						single UI_CONTAINER with one of each element.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

		// A simple botton
		myUI.addNewBotton(120, 5, 70, 20, "A BOTTEN");

		// Four bottons bound to the keyboard keys WASD
		myUI.addNewBotton(olc::Key::W, "UP_Key", screenW - 110, screenH - 130, 32, 32, " W");
		myUI.addNewBotton(olc::Key::A, "LEFT_Key", screenW - 160, screenH - 80, 32, 32, " A");
		myUI.addNewBotton(olc::Key::S, "DOWN_Key", screenW - 110, screenH - 80, 32, 32, " S");
		myUI.addNewBotton(olc::Key::D, "RIGHT_Key", screenW - 60, screenH - 80, 32, 32, " D");

		// a drop down, note that the third sub botton has teh cvommand EXIT, we will use this bellow
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

		// if any botton in the current UI sends the command EXIT, letsd exit
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


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			multiple UI_CONTAINERs in a UI_STAGE_CONTROLL with commands to ling between them
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
			// Here we will just add adrop down menu that will let uc chose the tow other stages. we will aslo add an exit botton
			myUI.addNewDropDown(UI_BLACK, UI_BLUE, 5, 5, 100, "MAIN", "STAGE 0,Stage 1,EXIT", "PGR_STG0,PGR_STG1,EXIT");
			//do you want the ID to be visible durring the debud time?
			//myUI.toggleDEBUGMODE();
		}


		if (myUI.addToStage(PGR_STG0)) {
			// in stage 0 we will just add a return botton, that will let us return tom main menu
			myUI.addNewBotton("MAIN_MENU", 0, screenH*0.5, screenW, 50, "MAIN MENU");
			//do you want the ID to be visible durring the debud time?
			//myUI.toggleDEBUGMODE();
		}

		if (myUI.addToStage(PGR_STG1)) {
			// in stage 1 we will add a botton that will take us to stage 0 if we press space
			myUI.addNewBotton(olc::Key::SPACE, "PGR_STG0", 0, screenH*0.1, screenW, 50, "Press Space to get to stage 0");
			//do you want the ID to be visible durring the debud time?
			//myUI.toggleDEBUGMODE();
		}

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{

		// this handles the uopdate of all items, it needs our current stage so it cvan update it.
		myUI.Update(fElapsedTime, currentStage);

		// if any botton in the current UI sends the command EXIT, letsd exit
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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
















#ifndef OLC_PGEX_UI
#define OLC_PGEX_UI
#include <map>

//Enum used to handle the diffren stages 
enum pgrSTAGE { RUN_INTRO, MAIN_MENU, RUN_PROGRAM, SAVE_LOAD, PAUSE_PROGRAM, INVENTORY, VIEW_MAP, CREDITS, HIGHSCORE, PGR_OPTIONS, PGR_STG0, PGR_STG1, PGR_STG2, PGR_STG3, PGR_STG4, PGR_STG5, PGR_STG6, PGR_STG7, PGR_STG8, PGR_STG9};

// converts a game stage to a string for idententification in a command string
std::string stage_to_string(pgrSTAGE in_stage) {
	switch (in_stage) {
	case RUN_INTRO: return "RUN_INTRO"; break;
	case MAIN_MENU: return "MAIN_MENU"; break;
	case RUN_PROGRAM: return "RUN_PROGRAM"; break;
	case SAVE_LOAD: return "SAVE_LOAD"; break;
	case PAUSE_PROGRAM: return "PAUSE_PROGRAM"; break;
	case INVENTORY: return "INVENTORY"; break;
	case VIEW_MAP: return "VIEW_MAP"; break;
	case CREDITS: return "CREDITS"; break;
	case HIGHSCORE: return "HIGHSCORE"; break;
	case PGR_OPTIONS: return "PGR_OPTIONS"; break;
	case PGR_STG0: return "PGR_STG0"; break;
	case PGR_STG1: return "PGR_STG1"; break;
	case PGR_STG2: return "PGR_STG2"; break;
	case PGR_STG3: return "PGR_STG3"; break;
	case PGR_STG4: return "PGR_STG4"; break;
	case PGR_STG5: return "PGR_STG5"; break;
	case PGR_STG6: return "PGR_STG6"; break;
	case PGR_STG7: return "PGR_STG7"; break;
	case PGR_STG8: return "PGR_STG8"; break;
	case PGR_STG9: return "PGR_STG9"; break;
	}
}

// directions for sliders.
enum sliderDirection { LeftRight, RightLeft, TopBottom, BottomTop };
enum sliderType {PercentageSlider, RangeSetSlider, SteppingSlider};
enum btnState { IDLE, HOVER, PRESSED };
enum UIStyle { UI_GREY, UI_RED, UI_GREEN, UI_BLUE, UI_YELLOW, UI_BLACK};
enum menuStage { CLOSED, OPEN_NOHOVER, OPEN_HOVER };
enum txtFieldStage { ISACTIVE, NOTACTIVE, ERASE };

static bool MousePresses = false;

//Uses common math to round floats rather than dropping decimals.
int FloatToInt(float input) {
	int value = (int)input;
	if ((input - value) > 0.5f) value += 1;
	return value;
}

/////////////////// basic items for hit tests ///////
struct point_2d {
	point_2d() : x(0), y(0), lockedToLeft(true), lockedToTop(true) {};
	point_2d(float newX, float newY) : x(newX), y(newY), lockedToLeft(true), lockedToTop(true) {};
	point_2d(float newX, float newY, bool lockedAtLeft, bool lockedAtTop) : x(newX), y(newY), lockedToLeft(lockedAtLeft), lockedToTop(lockedAtTop) {};
	float x; float y;
	bool lockedToTop;
	bool lockedToLeft;
};

//a container for ID and coordinates for any objects that needs debugging.
struct debugID {
	debugID(int newX, int newY, int newID) : x(newX), y(newY), id(newID) {};
	int x, y, id;
};

struct UI_rect {
	UI_rect() : pos(), w(1), h(1), fullWidth(false), fullHeight(false) {};
	UI_rect(float newW, float newH) : pos(), w(newW), h(newH), fullWidth(false), fullHeight(false) {};
	UI_rect(point_2d newPos, float newW, float newH) : pos(newPos.x, newPos.y), w(newW), h(newH), fullWidth(false), fullHeight(false) {};
	UI_rect(float newX, float newY, float newW, float newH) : pos(newX, newY), w(newW), h(newH), fullWidth(false), fullHeight(false) {};
	point_2d pos;
	float w, h;
private:
	bool fullWidth;
	bool fullHeight;
public:
	bool hasLeftAnchor() {
		if (pos.lockedToLeft) return true;
		return false;
	}
	bool hasTopAnchor() {
		if (pos.lockedToTop) return true;
		return false;
	}
	bool isFullWidth() {
		return fullWidth;
	}
	bool isFullHeight() {
		return fullHeight;
	}
};

bool isPointInRect(int x1, int y1, int rx1, int ry1, int w, int h) {
	if (x1 >= rx1 && x1 < rx1 + w && y1 >= ry1 && y1 < ry1 + h) return true;
	return false;
}

//collisiondetection fot all objects
bool isPointInRect(point_2d localpoint, int rx1, int ry1, int w, int h) {
	return isPointInRect(localpoint.x, localpoint.y, rx1, ry1, w, h);
}

//collisiondetection fot all objects
bool isPointInRect(point_2d localpoint, UI_rect localRect) {
	return isPointInRect(localpoint.x, localpoint.y, localRect.pos.x, localRect.pos.y, localRect.w, localRect.h);
}


namespace olc
{
	// Container class for UI elements and functions
	class UI_CONTAINER : public olc::PGEX
	{
	private:
		int screenW = 240, screenH = 220;
		bool showUIFields = false;
		bool showTxtFields = true;
		bool showBtns = true;
		bool showDropDowns = true;
		bool showSliders = true;
		bool debugMode = false;

		

	public:
		std::vector<debugID> drawID;

		//sets up the UI for objects.
		void setUp(int ScreenWidth, int ScreeHeight) {
			screenW = ScreenWidth;
			screenH = ScreeHeight;
		}

		//Draws red test on a white field, based on a drawstack.
		static bool drawAllId(std::vector<debugID> &storeDrawID) {
			for (int i = 0; i < storeDrawID.size(); i++) {
				pge->DrawRect(storeDrawID[i].x - 2, storeDrawID[i].y - 2, 60, 14, olc::RED);
				pge->FillRect(storeDrawID[i].x - 1, storeDrawID[i].y - 1, 59, 13, olc::WHITE);
				pge->DrawString(storeDrawID[i].x, storeDrawID[i].y, "Id: " + std::to_string(storeDrawID[i].id), olc::RED);

			}
			return true;
		}

		//Draws objects according to specifed style, if debugmode is active it will also add an item to a drawStac, sp Id's will be drawn after all objects.
		static bool drawObj(UI_rect &m_rect, UIStyle m_style, btnState m_stage, std::string m_text, bool drawText, int m_screenW, int m_screenH, int id, bool inDebugMode, std::vector<debugID> &storeDrawID) {
			olc::Pixel BGcol;
			olc::Pixel EdgeCol;
			olc::Pixel TxtCol;
			if (m_style == UI_GREY) {
				EdgeCol = olc::DARK_GREY;
				TxtCol = olc::BLACK;
				if (m_stage == IDLE) {
					BGcol = olc::GREY;
				}
				else if (m_stage == HOVER) {
					BGcol = olc::WHITE;
				}
				else if (m_stage == PRESSED) {
					BGcol = olc::GREY;
				}
			}
			else if (m_style == UI_BLUE) {
				EdgeCol = olc::VERY_DARK_BLUE;
				TxtCol = olc::WHITE;
				if (m_stage == IDLE) {
					BGcol = olc::DARK_BLUE;
				}
				else if (m_stage == HOVER) {
					BGcol = olc::BLUE;
				}
				else if (m_stage == PRESSED) {
					BGcol = olc::VERY_DARK_BLUE;
				}
			}
			else if (m_style == UI_GREEN) {
				EdgeCol = olc::VERY_DARK_GREEN;
				TxtCol = olc::WHITE;
				if (m_stage == IDLE) {
					BGcol = olc::DARK_GREEN;
				}
				else if (m_stage == HOVER) {
					BGcol = olc::VERY_DARK_GREEN;
				}
				else if (m_stage == PRESSED) {
					BGcol = olc::GREEN;
				}
			}
			else if (m_style == UI_RED) {
				EdgeCol = olc::DARK_RED;
				TxtCol = olc::BLACK;
				if (m_stage == IDLE) {
					BGcol = olc::RED;
				}
				else if (m_stage == HOVER) {
					BGcol = olc::Pixel(255, 100, 100);
				}
				else if (m_stage == PRESSED) {
					BGcol = olc::DARK_RED;
				}
			}
			else if (m_style == UI_YELLOW) {
				EdgeCol = olc::VERY_DARK_YELLOW;
				TxtCol = olc::BLACK;
				if (m_stage == IDLE) {
					BGcol = olc::DARK_YELLOW;
				}
				else if (m_stage == HOVER) {
					BGcol = olc::YELLOW;
				}
				else if (m_stage == PRESSED) {
					BGcol = olc::VERY_DARK_YELLOW;
				}
			}
			else if (m_style == UI_BLACK) {
				EdgeCol = olc::DARK_GREY;
				TxtCol = olc::WHITE;
				if (m_stage == IDLE) {
					BGcol = olc::BLACK;
				}
				else if (m_stage == HOVER) {
					BGcol = olc::VERY_DARK_GREY;
				}
				else if (m_stage == PRESSED) {
					BGcol = olc::GREY;
				}
			}
			int x, y, w, h;
			if (m_rect.isFullWidth())	x = 0, w = m_screenW;
			else if (!m_rect.hasLeftAnchor()) x = m_screenW - m_rect.pos.x, w = m_rect.w;
			else x = m_rect.pos.x, w = m_rect.w;

			if (m_rect.isFullHeight())	y = 0, h = m_screenH;
			else if (!m_rect.hasTopAnchor()) y = m_screenH - m_rect.pos.y, h = m_rect.h;
			else y = m_rect.pos.y, h = m_rect.h;

			pge->FillRect(x, y, w, h, BGcol);
			pge->DrawRect(x, y, w, h, EdgeCol);
			if (drawText)pge->DrawString(x + 4, y + 4, m_text, TxtCol);
			if (inDebugMode) storeDrawID.push_back(debugID(x + 4, y + 20, id));
			return true;
		}


		//Generates ID for all obejcts in all UI's
		static int newID() {
			static int localId = 0;
			return localId++;
		}

		//collisiondetection fot all objects
		


	public:

		//////////////////////////////////////////////
		///////////////////////////////// Text field class

		//Test field, when pressed is activated and recives textinput in the form of a string that than be retrived.
		class TextField {
		private:
			UI_rect localRect;
			olc::Pixel localfieldColor = olc::BLACK;
			olc::Pixel localfieldTxtColor = olc::WHITE;
			txtFieldStage localstage = NOTACTIVE;
			int maxLetters = 25, screenW = 240, screenH = 220;
			int uID = newID();
			UIStyle m_style = UI_BLACK;
			std::string fieldTxt = "";
			bool isInvisible = false;
			bool isHidden = false;
			const char localChar[62] = { 'A','a','B','b','C','c','D','d','E','e','F','f','G','g','H','h','I','i','J','j','K','k','L','l','M','m','N','n','O','o','P','p','Q','q','R','r','S','s','T','t','U','u','V','v','W','w','X','x','Y','y','Z','z','0','1','2','3','4','5','6','7','8','9' };
			char  lGetLetterPressed() {
				if (pge->GetKey(Key(62)).bPressed) return '<';
				else if (pge->GetKey(Key(52)).bPressed) return ' ';
				for (int i = 0; i < 36; i++) {
					if (pge->GetKey(Key(i)).bPressed) {

						//////////////////////////////// determines if its a letter, and if it is, sees if shift is pressed, then returns the appropiate letter
						if (i < 26) {
							if (pge->GetKey(Key::SHIFT).bHeld) {
								return localChar[i * 2];
							}
							else return localChar[i * 2 + 1];
						}
						///////////// if its not a letter, return the appropiate number
						else return localChar[i + 26];
					}
				}
				for (int i = 68; i <= 77; i++) {
					if (pge->GetKey(Key(i)).bPressed) return localChar[i -16];
				}
				return '*';
			}


		public:
			TextField(UIStyle style, int x, int y, int letters, int m_screenW, int m_screenH) {
				screenW = m_screenW;
				screenH = m_screenH;
				localRect.pos.x = x;
				localRect.pos.y = y;
				maxLetters = letters;
				localRect.w = 16 + (letters + 1) * 8;
				localRect.h = 20;
				fieldTxt = "";
				m_style = style;
			}



			void hideField(bool hide) { isHidden = hide; }
			void updateField() {
				point_2d localmouse(pge->GetMouseX(), pge->GetMouseY());
				bool aClick = false;
				if (pge->GetMouse(0).bPressed) aClick = true;
				else if (pge->GetMouse(0).bHeld) aClick = true;
				else if (pge->GetMouse(0).bReleased) aClick = true;
				bool tEnter = false;
				if (pge->GetKey(olc::ENTER).bPressed) tEnter = true;
				else if (pge->GetKey(olc::ENTER).bHeld) tEnter = true;
				else if (pge->GetKey(olc::ENTER).bReleased) tEnter = true;
				if (tEnter) localstage = NOTACTIVE;
				if (aClick) {
					if (!isPointInRect(localmouse, localRect)) localstage = NOTACTIVE;
					else if (localstage == NOTACTIVE) localstage = ISACTIVE;
				}
				if (localstage == ISACTIVE) {
					char newLetter = lGetLetterPressed();
					if (newLetter == '<' && fieldTxt.length() > 0) {
						std::string tempString = "";
						for (int i = 0; i < fieldTxt.length() - 1; i++) tempString += fieldTxt[i];
						fieldTxt.clear();
						fieldTxt = tempString;
						fieldTxt.shrink_to_fit();
					}
					else if (newLetter != '*' && newLetter != '<' && fieldTxt.size() <= maxLetters) fieldTxt += newLetter;
				}
			}
			void drawField(bool inDebugMode, std::vector<debugID> &storeDrawID) {
				if ((!isHidden && !isInvisible)) {
					std::string showString = fieldTxt;
					if (localstage == ISACTIVE) showString += '<';
					drawObj(localRect, m_style, btnState::IDLE, showString, true, screenW, screenH, uID, inDebugMode, storeDrawID);
				}
			}
			int getX() { return localRect.pos.x; }
			int getY() { return localRect.pos.y; }
			int getW() { return localRect.w; }
			int getH() { return localRect.h; }

			void setX(int newX) { localRect.pos.x = newX; }
			void setY(int newY) { localRect.pos.y = newY; }
			void setW(int newW) { localRect.w = newW; }
			void setH(int newH) { localRect.h = newH; }

			std::string getString() { return fieldTxt; }
			txtFieldStage getFieldStage() { return localstage; }
			int getId() { return uID; }
			UI_rect getRect() { return localRect; }

		};

		///////////////////////////////// Botton class

		//a single botton that reacts to hover and press. can be bound to keyboard keys and can send a command to the command string
		class Botton {
		private:
			UI_rect localRect;
			olc::Pixel localbtnColorIDLE = olc::DARK_GREY;
			olc::Pixel localbtnColorHOVER = olc::VERY_DARK_GREY;
			olc::Pixel localbtnColorPRESS = olc::GREY;
			olc::Pixel localbtnTxtColor = olc::WHITE;
			UIStyle m_style = UI_BLUE;
			btnState localstage = IDLE;
			int uID = newID(), screenW = 240, screenH = 220;
			std::string cmdString;
			std::string btnTxt = "";
			olc::Key mKey;
			bool hasKey = false;
			bool isHidden = false;
			bool isInvisible = false;
			bool followOnPress = false;
		public:
			Botton() {
				localRect.pos.x = 5;
				localRect.pos.y = 5;
				localRect.w = 32;
				localRect.h = 20;
				btnTxt = "";
				mKey = olc::Key::ENTER;
				cmdString = "";
				isHidden = false;
				m_style = UI_BLUE;
			}
			Botton(UIStyle style, olc::Key nKey, bool addKey, std::string nCmd, int newX, int newY, int newW, int newH, bool hide, std::string bottonText, int m_screenW, int m_screenH) {
				screenW = m_screenW;
				screenH = m_screenH;
				localRect.pos.x = newX;
				localRect.pos.y = newY;
				if (newW != 0) localRect.w = newW;
				else if (bottonText.length() > 0) localRect.w = 16 + (bottonText.length() + 1) * 8;
				else localRect.w = 32;
				if (newH != 0) localRect.h = newH;
				else localRect.h = 20;
				if (bottonText.length() > 0) btnTxt = bottonText;
				else btnTxt = std::to_string(uID);
				hasKey = addKey;
				mKey = nKey;
				if (nCmd != "") cmdString = nCmd;
				else cmdString = "";
				isHidden = hide;
				m_style = style;
			}
			void hideBtn(bool hide) { isHidden = hide; }
			void updateBtn() {
				point_2d localmouse(pge->GetMouseX(), pge->GetMouseY());
				if (hasKey && pge->GetKey(mKey).bPressed) localstage = PRESSED;
				else if (hasKey && pge->GetKey(mKey).bHeld) localstage = PRESSED;
				else if (isPointInRect(localmouse, localRect) && !isHidden) {
					if (!MousePresses) {
						if (pge->GetMouse(0).bPressed) {
							localstage = PRESSED;
							MousePresses = true;
						}
						else if (pge->GetMouse(0).bHeld) {
							localstage = PRESSED;
							MousePresses = true;
						}
						else localstage = HOVER;
					}
					
				}
				
				else localstage = IDLE;
			}
			void drawBtn(bool inDebugMode, std::vector<debugID> &storeDrawID) {

				if ((!isHidden && !isInvisible)) {
					drawObj(localRect, m_style, localstage, btnTxt, true, screenW, screenH, uID, inDebugMode, storeDrawID);
				}
			}
			int getX() { return localRect.pos.x; }
			int getY() { return localRect.pos.y; }
			int getW() { return localRect.w; }
			int getH() { return localRect.h; }

			void setX(int newX) {
				localRect.pos.x = newX; 
			}
			void setY(int newY) { localRect.pos.y =newY;
			}
			void setW(int newW) { localRect.w = newW;
			}
			void setH(int newH) { localRect.h = newH;
			}


			btnState getbtnState() { return localstage; }
			int getId() { return uID; }
			std::string getCmdString() {
				if (cmdString != "") return cmdString;
				else return "NONE";
			}

			bool SetbtnTxt(std::string newTxt) {
				btnTxt = newTxt;
				return true;
			}

		};



		///////////////////////////////// DROP DOWN MENU
		
		//Drop down menu, contains multiple bottons that all can contain a command
		class DropDown {
		private:
			UI_rect localRect;
			std::vector<Botton> localBtns;
			menuStage localstage = CLOSED;
			float countDown = 0.0f;
			int screenewW = 240, screenewH = 220;
		public:
			DropDown() {

				localRect.pos.x = 0;
				localRect.pos.y = 0;
				localRect.w = 150;
				localRect.h = 20;
				localBtns.push_back(Botton(UI_BLUE, olc::Key::ENTER, false, "", localRect.pos.x, localRect.pos.y, localRect.w, localRect.h, true, "DRP_DN", screenewW, screenewH));
				localBtns.push_back(Botton(UI_BLUE, olc::Key::ENTER, false, "", localRect.pos.x, localRect.pos.y + 20, localRect.w, localRect.h, true, "DRP_DN", screenewW, screenewH));
				localBtns.back().hideBtn(true);
			}


			DropDown(UIStyle FirstStyle, UIStyle DropStyle, int newX, int newY, int newW, std::string drpDnName, std::string drpDnBtns, std::string commands, int m_screenewW, int m_screenewH) {
				screenewW = m_screenewW;
				screenewH = m_screenewH;
				localBtns.push_back(Botton(FirstStyle, olc::Key::ENTER, false, "", newX, newY, newW, 20, false, drpDnName, screenewW, screenewH));
				localRect.pos.x = newX;
				localRect.pos.y = newY;
				localRect.w = newW;
				localRect.h = 20;
				std::string newBtnName = "";
				int nBtns = 1;
				for (int i = 0, j = 0; i < drpDnBtns.length(); i++) {
					if (drpDnBtns[i] != ',') newBtnName += drpDnBtns[i];
					if (drpDnBtns[i] == ',' || i == drpDnBtns.length() - 1) {

						std::string lcmd = "";
						bool hasCmds = false;
						if (commands.length() <= 2) hasCmds = true;
						else {
							for (; j < commands.length() && !hasCmds; j++) {
								if (commands[j] != ',') lcmd += commands[j];
								if (commands[j] == ',' || j == commands.length() - 1) {
									hasCmds = true;
								}
							}
						}
						if (lcmd == "") lcmd = "";
						localBtns.push_back(Botton(DropStyle, olc::Key::ENTER, false, lcmd, newX, newY + (nBtns * 20), localRect.w, localRect.h, true, newBtnName, screenewW, screenewH));
						newBtnName = "";
						nBtns++;
					}
				}
			}

			void updateDrpDn(float fElapsedTime) {
				if (localstage == CLOSED) {
					localBtns.front().updateBtn();
					if (localBtns.front().getbtnState() == PRESSED) {
						localstage = OPEN_HOVER;
						countDown = 0.5f;
						if (localBtns.size() > 1) {
							for (int i = 1; i < localBtns.size(); i++) {
								localBtns[i].hideBtn(false);
							}
						}
					}
				}
				else {
					bool hovers = false;
					if (localBtns.size() > 0) {
						for (int i = 0; i < localBtns.size(); i++) {
							localBtns[i].updateBtn();
							if (localBtns[i].getbtnState() != IDLE) hovers = true;
						}
					}
					if (hovers) {
						countDown = 0.5f;
						localstage = OPEN_HOVER;
					}
					else if (countDown > 0.0f) {
						countDown -= fElapsedTime;
						localstage = OPEN_NOHOVER;
					}
					if (countDown < 0.0f) {
						if (localBtns.size() > 1) {
							for (int i = 1; i < localBtns.size(); i++) {
								localBtns[i].hideBtn(true);
							}
						}
						localstage = CLOSED;
					}
				}
			}

			int getX() { return localRect.pos.x; }
			int getY() { return localRect.pos.y; }
			int getW() { return localRect.w; }
			int getH() { return localRect.h; }

			void setX(int newX) { 
				localRect.pos.x = newX; 
				if (localBtns.size() > 0) {
					for (int i = 0; i < localBtns.size(); i++) {
						localBtns[i].setX(newX);
					}
				}
			}
			void setY(int newY) { 
				localRect.pos.y = newY; 
				if (localBtns.size() > 0) {
					for (int i = 0; i < localBtns.size(); i++) {
						localBtns[i].setY(newY + ((i + 1) * localRect.h));
					}
				}
			}
			void setW(int newW) { localRect.w = newW; 
				if (localBtns.size() > 0) {
					for (int i = 0; i < localBtns.size(); i++) {
						localBtns[i].setW(newW);
					}
				}
			}
			void setH(int newH) { 
				localRect.h = newH; 
				if (localBtns.size() > 0) {
					for (int i = 0; i < localBtns.size(); i++) {
						localBtns[i].setY(localRect.pos.y + ((i + 1) * newH));
						localBtns[i].setH(newH);
					}
				}
			}



			void drawDrpDn(bool inDebugMode, std::vector<debugID> &storeDrawID) {
				if (localBtns.size() > 0) {
					for (int i = 0; i < localBtns.size(); i++) {
						localBtns[i].drawBtn(inDebugMode, storeDrawID);
					}
				}
			}

			btnState getDrpDnStage() {
				if (localBtns.size() > 0) {
					for (int i = 0; i < localBtns.size(); i++) {
						if (localBtns[i].getbtnState() != IDLE) return localBtns[i].getbtnState();
					}
				}
				return IDLE;
			}


			int getId() {
				return localBtns[0].getId();
			}

			int getIdNonIdle() {
				if (localBtns.size() > 0) {
					for (int i = 0; i < localBtns.size(); i++) {
						if (localBtns[i].getbtnState() != IDLE) return localBtns[i].getId();
					}
				}
				return -1;
			}


			bool hasId(int ID) {
				if (localBtns.size() > 0) {
					for (int i = 0; i < localBtns.size(); i++) {
						if (localBtns[i].getId() == ID) return true;
					}
				}
				return false;
			}

			void hideBtn(int ID, bool hide) {
				if (localBtns.size() > 0) {
					for (int i = 0; i < localBtns.size(); i++) {
						if (localBtns[i].getId() == ID) localBtns[i].hideBtn(hide);
					}
				}
			}

			std::string getCmdString() {
				if (localBtns.size() > 0) {
					for (int i = 0; i < localBtns.size(); i++) {
						if (localBtns[i].getbtnState() != IDLE) return localBtns[i].getCmdString();
					}
				}
				return "NONE";
			}
		};


		////////////////Sliders

		//Slider, contains a dragable botton that will adjust the retunr value of the object.
		class Slider {
		private:

			Botton SliderHandle;
			int screenW = 240, screenH = 220;
			bool following = false;
			point_2d distToMouse;
			sliderDirection localDir= LeftRight;
			sliderType localType = PercentageSlider;
			point_2d position;
			
			int length;
			std::vector<int> range;

		public:
			Slider(int newX, int newY, int newLength) {

				position.x = newX;
				position.y = newY;
				length = newLength;
				SliderHandle.setX(newX + 1);
				SliderHandle.setY(newY - 16);
				SliderHandle.setW(20);
				SliderHandle.setH(32);
				SliderHandle.SetbtnTxt(std::to_string(getValueAsInt()));

			}

			Slider(int newX, int newY, int newLength, sliderDirection newDir) {

				position.x = newX;
				position.y = newY;
				length = newLength;
				if (newDir == LeftRight || newDir == RightLeft) {
					SliderHandle.setX(newX + 1);
					SliderHandle.setY(newY - 16);
					SliderHandle.setW(20);
					SliderHandle.setH(32);
				}
				else {
					SliderHandle.setX(newX -16);
					SliderHandle.setY(newY +1);
					SliderHandle.setW(32);
					SliderHandle.setH(20);
				}
				localDir = newDir;
				SliderHandle.SetbtnTxt(std::to_string(getValueAsInt()));

			}

			Slider(int newX, int newY, int newLength, sliderDirection newDir, sliderType newType, std::vector<int> newRange) {
				position.x = newX;
				position.y = newY;
				length = newLength;
				if (newDir == LeftRight || newDir == RightLeft) {
					if(newDir == LeftRight )SliderHandle.setX(newX);
					else SliderHandle.setX(newX + length - 16);
					SliderHandle.setY(newY - 16);
					SliderHandle.setW(20);
					SliderHandle.setH(32);
				}
				else {
					if (newDir == TopBottom)SliderHandle.setY(newY);
					else SliderHandle.setY(newY + length - 16);
					SliderHandle.setX(newX - 16);
					SliderHandle.setW(32);
					SliderHandle.setH(20);
				}
				localDir = newDir;
				setType(newType, newRange);
				SliderHandle.SetbtnTxt(std::to_string(getValueAsInt()));
			}

			void setType(sliderType newType, std::vector<int> newRange) {
				if (newRange.size() > 1) {
					localType = newType;
					for (int i = 0; i < newRange.size(); i++) {
						range.push_back(newRange[i]);
					}
				}
			}

			void updateSlider() {
				SliderHandle.updateBtn();
				if (SliderHandle.getbtnState() == PRESSED) {
					if (!following) {
						following = true;
						distToMouse.x = SliderHandle.getX() - pge->GetMouseX();
						distToMouse.y = SliderHandle.getY() - pge->GetMouseY();
					}
				}
				if (following) {
					if (pge->GetMouse(0).bReleased) following = false;
					else {
						int mX = pge->GetMouseX() + distToMouse.x;
						int mY = pge->GetMouseY() + distToMouse.y;
						if (localDir == LeftRight || localDir == RightLeft) {
							if (mX > position.x+1 && mX < (position.x + length - SliderHandle.getW())) SliderHandle.setX(mX);
							else if (mX < position.x ) SliderHandle.setX(position.x );
							else if (mX > (position.x + length - SliderHandle.getW())) SliderHandle.setX(position.x + length - SliderHandle.getW());

						}
						else if (localDir == TopBottom || localDir == BottomTop) {
							if (mY > position.y && mY < (position.y + (length - SliderHandle.getH()))) SliderHandle.setY(mY);
							else if (mY < position.y ) SliderHandle.setY(position.y );
							else if (mY > (position.y + (length - SliderHandle.getH()))) SliderHandle.setY(position.y + (length - SliderHandle.getH()));
						}
					}
					if (localType == SteppingSlider) {
						setSteppingSlider(getStep());
					}
					SliderHandle.SetbtnTxt(std::to_string(getValueAsInt()));
				}
			}

			void setSteppingSlider(int atStep) {
				float pos = 0;
				if (localDir == BottomTop) pos = (float)((((float)length - (float)SliderHandle.getH()) / ((float)range.size() - 1)) * ((float)range.size() - (1 + (float)atStep)));
				else if (localDir == TopBottom) pos = (float)((((float)length - (float)SliderHandle.getH()) / ((float)range.size() - 1)) *  (float)atStep);

				else if (localDir == RightLeft) pos = (float)((((float)length - (float)SliderHandle.getW()) / ((float)range.size() - 1)) * ((float)range.size() - (1 + (float)atStep)));
				else if (localDir == LeftRight) pos = (float)((((float)length - (float)SliderHandle.getW()) / ((float)range.size() - 1)) *  (float)atStep);

				if (localDir == BottomTop || localDir == TopBottom) SliderHandle.setY(position.y + pos);

				else SliderHandle.setX(position.x + pos);
			}

			void drawSlider(bool inDebugMode, std::vector<debugID> &storeDrawID) {
				
				if (localDir == LeftRight || localDir == RightLeft) pge->FillRect(position.x, position.y, length, 2, olc::BLACK);
				else pge->FillRect(position.x, position.y, 2, length, olc::BLACK);
				SliderHandle.drawBtn(inDebugMode, storeDrawID);
			}

			btnState getHandleStage() {
				return SliderHandle.getbtnState();
			}

			bool isSliding() {
				return following;
			}

			int getId() {
				return  SliderHandle.getId();
			}

			float getValueAsFloat() {
				float range100 = 100.0f;
				if (localDir == LeftRight || localDir == RightLeft) range100 = range100 * ((SliderHandle.getX() - position.x) / (length - SliderHandle.getW()));
				else range100 = range100 * ((SliderHandle.getY() - position.y) / (length - SliderHandle.getH()));
				if (localDir == LeftRight || localDir == TopBottom) return range100;
				else return 100 - range100;
			}

			int getStep() {
				float step = ((float)(range.size()-1) / 100.0f) * getValueAsFloat();
				return FloatToInt(step);
			}


			int getValueAsInt() {
				if (localType == RangeSetSlider) {
					float localRange = (((range.back() - range.front()) * getValueAsFloat()) * 0.01) + range.front();
					return FloatToInt(localRange);
				}
				else if (localType == SteppingSlider) {
					return range[getStep()];
				}
				return FloatToInt(getValueAsFloat());
			}


			int getX() { return SliderHandle.getX(); }
			int getY() { return SliderHandle.getY(); }
			int getW() { return SliderHandle.getW(); }
			int getH() { return SliderHandle.getH(); }
			int getLength() { return length; }

			void setX(int newX) { position.x = newX; }
			void setY(int newY) { position.y = newY; }
			void setW(int newW) { 
				SliderHandle.setW(newW);
				if (localDir == TopBottom || localDir == BottomTop) {
					SliderHandle.setX(position.x - (newW * 0.5));
				}
			}
			void setH(int newH) { 
				SliderHandle.setH(newH); 
				if (localDir == LeftRight || localDir == RightLeft) {
					SliderHandle.setY(position.y - (newH * 0.5));
				}
			}
			void setLength(int newLength) { length = newLength; }

			void setValue(int newValue) {
				if (localType == SteppingSlider) {
					if (newValue < 0) {
						setSteppingSlider(0);
					}
					else if (newValue >= range.size()) {
						setSteppingSlider(range.size()-1);
					}
					else {
						setSteppingSlider(newValue);
					}
				}

				
				else {
					if (newValue < 0) {
						if (localDir == LeftRight) SliderHandle.setX(position.x);
						else SliderHandle.setX((position.x + (length - SliderHandle.getW())));
					}

					else if (newValue > 100) {
						if (localDir == TopBottom) SliderHandle.setY(position.y);
						else SliderHandle.setY((position.y + (length - SliderHandle.getH())));

					}
					else {
						if (localDir == LeftRight || localDir == RightLeft) {
							int location = (float)((float)((float)length - (float)SliderHandle.getW()) / 100.0f) * (float)newValue;
							if (localDir == LeftRight) SliderHandle.setX(position.x + location);
							else SliderHandle.setX((position.x + (length - SliderHandle.getW())) - location);
						}
						else if (localDir == TopBottom || localDir == BottomTop) {
							int location = (float)((float)((float)length - (float)SliderHandle.getH()) / 100.0f) * (float)newValue;
							if (localDir == TopBottom) SliderHandle.setY(position.y + location);
							else SliderHandle.setY((position.y + (length - SliderHandle.getH())) - location);
						}
					}
				}
				SliderHandle.SetbtnTxt(std::to_string(getValueAsInt()));
			}

		};







		///////////////////////////////////////// UI VECTORS
	private:
		// Text fields
		std::vector<TextField> allTextFields;
		//BTNS
		std::vector<Botton> allBtns;
		//DropDownMenus
		std::vector<DropDown> allDrpDn;
		//Sliders
		std::vector<Slider> allSliders;
		//UIFields
		std::vector<UI_rect> allUIFields;

		///////////////////////////////////////// UI FUNCTIONS
	public:
		//Allows the user to toggle the visibility of all objects, and to exclude text fields from this toggle.	
		bool isAllHidden() {
			if (showUIFields && showBtns &&	showDropDowns && showSliders) return false;
			return true;
		}

		bool SetHideAll(bool hideAll) {
			showTxtFields = !hideAll;
			showUIFields = !hideAll;
			showBtns = !hideAll;
			showDropDowns = !hideAll;
			showSliders = !hideAll;
			return !hideAll;
		}

		bool ToggleHideAll(bool hideTextFields) {
			showTxtFields = !hideTextFields;
			showUIFields = !showUIFields;
			showBtns = showUIFields;
			showDropDowns = showUIFields;
			showSliders = showUIFields;
			return showUIFields;
		}
		
		//Toggles the current UI fields visibility.									
		bool ToggleHideUIFIELDS() {
			showUIFields = !showUIFields;
			return showUIFields;
		}
		
		//Toggles  the current UI bottons visibility									
		bool ToggleHideUIBTNS() {
			showBtns = !showBtns;
			return showBtns;
		}

		//Toggles  the current UI drop down menus visibility									
		bool ToggleHideUIDROPDOWNS() {
			showDropDowns = !showDropDowns;
			return showDropDowns;
		}

		//Toggles  the current UI text fields visibility									
		bool ToggleHideUITXTFIELDS() {
			showTxtFields = !showTxtFields;
			return showTxtFields;
		}

		//Toggles  the current UI sliders visibility									
		bool ToggleHideSLIDERS() {
			showSliders = !showSliders;
			return showSliders;
		}

		//Toggles debugmode, in debugmode all items displays their ID.									
		bool ToggleDEBUGMODE() {
			debugMode = !debugMode;
			return debugMode;
		}

		// A singel line text input field, x positon, y position, number of letters
		bool addTextField(int x, int y, int maxLetters) {
			allTextFields.push_back(TextField(UI_BLACK, x, y, maxLetters, screenW, screenH));
			return true;
		}


		// A singel line text input field, UI style choice, x positon, y position, number of letters desission to hide the ID upon first render									
		bool addTextField(UIStyle colorStyle, int x, int y, int maxLetters) {
			allTextFields.push_back(TextField(colorStyle, x, y, maxLetters, screenW, screenH));
			return true;
		}

		// A horizontal slider, returns a value between 0 and 100. is located on x and y and has length as its width.		
		bool addSlider(int x, int y, int length) {
			allSliders.push_back(Slider(x, y, length));
			return true;
		}

		// A slider, returns a value between 0 and 100. is located on x and y and has length as its width, direction can be set.									
		bool addSlider(int x, int y, int length, sliderDirection newDir) {
			allSliders.push_back(Slider(x, y, length, newDir));
			return true;
		}


		// A slider, Is located on x and y and has length as its width or height. direction of Left to Right, Right to left, Top to Bottom or Bottom to Top. a slider of specifiec range, and steps.									
		bool addSlider(int newX, int newY, int newLength, sliderDirection newDir, sliderType newType, std::vector<int> newRange) {
			allSliders.push_back(Slider(newX, newY, newLength, newDir, newType, newRange));
			return true;
		}



		// A rectangle field that will registrer as UI if the mouse hovers over it.									
		bool addUIField(int x, int y, int w, int h) {
			allUIFields.push_back(UI_rect(x, y, w, h));
			return true;
		}
		
		// A simple botton with width 32 heigth 20									
		bool addNewBotton(int newX, int newY) {
			allBtns.push_back(Botton(UI_BLUE, olc::Key::ENTER, false, "", newX, newY, 0, 0, false, "", screenW, screenH));
			return true;
		}

		// A simple botton with specified width and heigth									
		bool addNewBotton(int newX, int newY, int newW, int newH) {
			allBtns.push_back(Botton(UI_BLUE, olc::Key::ENTER, false, "", newX, newY, newW, newH, false, "", screenW, screenH));
			return true;
		}

		// A simple botton with specified width and heigth, Text displayed on botton.									
		bool addNewBotton(int newX, int newY, int newW, int newH, std::string bottonText) {
			allBtns.push_back(Botton(UI_BLUE, olc::Key::ENTER, false, "", newX, newY, newW, newH, false, bottonText, screenW, screenH));
			return true;
		}
							
		//Botton width a bound key, nKey is a keyboard key, nCmd is a string that is returned as a command when the botton is activated.									
		bool addNewBotton(olc::Key nKey, std::string nCmd, int newX, int newY, int newW, int newH, std::string bottonText) {
			allBtns.push_back(Botton(UI_BLUE, nKey, true, nCmd, newX, newY, newW, newH, false, bottonText, screenW, screenH));
			return true;
		}
								
		//Botton width command. nCmd is a  a string that is returned as a command when the botton is activated.									
		bool addNewBotton(std::string nCmd, int newX, int newY, int newW, int newH, std::string bottonText) {
			allBtns.push_back(Botton(UI_BLUE, olc::Key::ENTER, false, nCmd, newX, newY, newW, newH, false, bottonText, screenW, screenH));
			return true;
		}

		// Botton that allowes for selection of the graphic style. nKey is a keyboard key, if hasKey is set to false, teh botton will not recive the key bibdibg. nCmd is a string that is returned as a command when the botton is activated.									
		bool addNewBotton(UIStyle newStyle, olc::Key newKey, bool hasKey, std::string newCmd, int newX, int newY, int newW, int newH, std::string bottonText) {
			allBtns.push_back(Botton(newStyle, newKey, hasKey, newCmd, newX, newY, newW, newH, false, bottonText, screenW, screenH));
			return true;
		}

		//a dropdown menu, newW specifies teh width of the menu, drpDnName is the text on the top botton. drpDnBtns is a string of names for all sup bottons, formated as "First,Second,Third" ect.									
		bool addNewDropDown(int newX, int newY, int newW, std::string drpDnName, std::string drpDnBtns) {
			allDrpDn.push_back(DropDown(UI_BLUE, UI_GREEN, newX, newY, newW, drpDnName, drpDnBtns, "", screenW, screenH));
			return true;
		}

		//a dropdown menu, allowes for selection of the style for the first and all sup bottons. newW specifies teh width of the menu, drpDnName is the text on the top botton. drpDnBtns is a string of names for all sup bottons, formated as "First,Second,Third" ect.									
		bool addNewDropDown(UIStyle FirstStyle, UIStyle  DropStyle, int newX, int newY, int newW, std::string drpDnName, std::string drpDnBtns) {
			allDrpDn.push_back(DropDown(FirstStyle, DropStyle, newX, newY, newW, drpDnName, drpDnBtns, "", screenW, screenH));
			return true;
		}

		//a dropdown menu, newW specifies teh width of the menu, drpDnName is the text on the top botton. drpDnBtns is a string of names for all sup bottons, formated as "First,Second,Third" ect, commands is as string of commands formated as "FIRST_CMD,SECOND,CMD,THIRD_CMD" ect.									
		bool addNewDropDown(int newX, int newY, int newW, std::string drpDnName, std::string drpDnBtns, std::string commands) {
			allDrpDn.push_back(DropDown(UI_BLUE, UI_GREEN, newX, newY, newW, drpDnName, drpDnBtns, commands, screenW, screenH));
			return true;
		}

		//a dropdown menu, allowes for selection of the style for the first and all sup bottons. newW specifies teh width of the menu, drpDnName is the text on the top botton. drpDnBtns is a string of names for all sup bottons, formated as "First,Second,Third" ect, commands is as string of commands formated as "FIRST_CMD,SECOND,CMD,THIRD_CMD" ect.									
		bool addNewDropDown(UIStyle FirstStyle, UIStyle  DropStyle, int newX, int newY, int newW, std::string drpDnName, std::string drpDnBtns, std::string commands) {
			allDrpDn.push_back(DropDown(FirstStyle, DropStyle, newX, newY, newW, drpDnName, drpDnBtns, commands, screenW, screenH));
			return true;
		}

		///// BASIC UI FUNCTIONS

		//Update all objects in the stage.								
		bool Update(float fElapsedTime) {

			if (allBtns.size() > 0) {
				for (int i = 0; i < allBtns.size(); i++) {
					allBtns[i].updateBtn();
				}
			}
			if (allDrpDn.size() > 0) {
				for (int i = 0; i < allDrpDn.size(); i++) {
					allDrpDn[i].updateDrpDn(fElapsedTime);
				}
			}
			if (allTextFields.size() > 0) {
				for (int i = 0; i < allTextFields.size(); i++) {
					allTextFields[i].updateField();
				}
			}
			if (allSliders.size() > 0) {
				for (int i = 0; i < allSliders.size(); i++) {
					allSliders[i].updateSlider();
				}
			}
			if (pge->GetMouse(0).bReleased) {
				MousePresses = false;
			}
			return true;
		}


		//Will draw all objects in the stage	
		bool drawUIObjects() {
			drawID.clear();
			drawID.shrink_to_fit();
			if (showUIFields) {

				if (allUIFields.size() > 0) {
					pge->SetPixelMode(olc::Pixel::ALPHA);
					for (int i = 0; i < allUIFields.size(); i++) {
						pge->FillRect(allUIFields[i].pos.x, allUIFields[i].pos.y, allUIFields[i].w, allUIFields[i].h, olc::Pixel(230, 0, 100, 80));
						pge->DrawRect(allUIFields[i].pos.x, allUIFields[i].pos.y, allUIFields[i].w, allUIFields[i].h, olc::Pixel(180, 50, 150, 120));
					}
					pge->SetPixelMode(olc::Pixel::NORMAL);
				}
			}
			if (showTxtFields) {

				if (allTextFields.size() > 0) {
					for (int i = 0; i < allTextFields.size(); i++) {
						allTextFields[i].drawField(debugMode, drawID);
					}
				}
			}

			if (showBtns) {
				if (allBtns.size() > 0) {
					for (int i = 0; i < allBtns.size(); i++) {
						allBtns[i].drawBtn(debugMode, drawID);
					}
				}
			}
			if (showDropDowns) {
				if (allDrpDn.size() > 0) {
					for (int i = 0; i < allDrpDn.size(); i++) {
						allDrpDn[i].drawDrpDn(debugMode, drawID);
					}
				}
			}
			if (showSliders) {
				if (allSliders.size() > 0) {
					for (int i = 0; i < allSliders.size(); i++) {
						allSliders[i].drawSlider(debugMode, drawID);
					}
				}

			}

			if (debugMode) {
				drawAllId(drawID);
			}
			return true;
		}

		//Returns true if the mouse is currently over any UI objects area.
		bool isMouseInUI() {
			if (allBtns.size() > 0) {
				for (int i = 0; i < allBtns.size(); i++) {
					if (allBtns[i].getbtnState() != IDLE) return true;
				}
			}
			if (allDrpDn.size() > 0) {
				for (int i = 0; i < allDrpDn.size(); i++) {
					if (allDrpDn[i].getDrpDnStage() != IDLE) return true;
				}
			}
			if (allSliders.size() > 0) {
				for (int i = 0; i < allSliders.size(); i++) {
					if(allSliders[i].getHandleStage() != IDLE) return true;
				}
			}

			if (allTextFields.size() > 0) {
				for (int i = 0; i < allTextFields.size(); i++) {
					if (isPointInRect(pge->GetMouseX(), pge->GetMouseY(), allTextFields[i].getRect().pos.x, allTextFields[i].getRect().pos.y, allTextFields[i].getRect().w, allTextFields[i].getRect().h)) return true;
				}
			}

			if (allUIFields.size() > 0) {
				for (int i = 0; i < allUIFields.size(); i++) {
					if (isPointInRect(pge->GetMouseX(), pge->GetMouseY(), allUIFields[i].pos.x, allUIFields[i].pos.y, allUIFields[i].w, allUIFields[i].h)) return true;
				}
			}
			return false;
		}

		//Returns the ID of any object currently pressed, if none; -1 is returned									
		int getbtnPressed() {
			if (isMouseInUI()) {
				if (allBtns.size() > 0) {
					for (int i = 0; i < allBtns.size(); i++) {
						if (allBtns[i].getbtnState() == PRESSED) return allBtns[i].getId();
					}
				}
				if (allDrpDn.size() > 0) {
					for (int i = 0; i < allDrpDn.size(); i++) {
						if (allDrpDn[i].getDrpDnStage() == PRESSED) return allDrpDn[i].getIdNonIdle();
					}
				}
				if (allSliders.size() > 0) {
					for (int i = 0; i < allSliders.size(); i++) {
						if (allSliders[i].getHandleStage() == PRESSED) return allSliders[i].getId();
					}
				}
			}
			return -1;
		}



		//Returns the ID of any object currently hovered, if none; -1 is returned									
		int getbtnHover() {
			if (isMouseInUI()) {
				if (allBtns.size() > 0) {
					for (int i = 0; i < allBtns.size(); i++) {
						if (allBtns[i].getbtnState() == HOVER) return allBtns[i].getId();
					}
				}
				if (allDrpDn.size() > 0) {
					for (int i = 0; i < allDrpDn.size(); i++) {
						if (allDrpDn[i].getDrpDnStage() == HOVER) return allDrpDn[i].getIdNonIdle();
					}
				}
				if (allSliders.size() > 0) {
					for (int i = 0; i < allSliders.size(); i++) {
						if (allSliders[i].getHandleStage() == HOVER) return allSliders[i].getId();
					}
				}


				if (allTextFields.size() > 0) {
					for (int i = 0; i < allTextFields.size(); i++) {
						if (isPointInRect(pge->GetMouseX(), pge->GetMouseY(), allTextFields[i].getRect().pos.x, allTextFields[i].getRect().pos.y, allTextFields[i].getRect().w, allTextFields[i].getRect().h)) return allTextFields[i].getId();
					}
				}
			}
			return -1;
		}

		//Returns the command string of any botton or dropDownMenu Currently Pressed									
		std::string getCmdString() {
			if (allBtns.size() > 0) {
				for (int i = 0; i < allBtns.size(); i++) {
					if (allBtns[i].getbtnState() == PRESSED) return allBtns[i].getCmdString();
				}
			}
			if (allDrpDn.size() > 0) {
				for (int i = 0; i < allDrpDn.size(); i++) {
					if (allDrpDn[i].getDrpDnStage() == PRESSED) return allDrpDn[i].getCmdString();
				}
			}
			return "NONE";
		}

		//Returns all commands as a string, both hover and pressed
		//the format is "#TYPE:ID:ACTION:DATATYPE:DATA"
		std::string getAllCmds() {
			std::string rtnStr = "";
			if (allBtns.size() > 0) {
				for (int i = 0; i < allBtns.size(); i++) {
					if (allBtns[i].getbtnState() == PRESSED) {
						rtnStr += "#BTN:" + std::to_string(allBtns[i].getId()) + ":PRESS:CMD:" + allBtns[i].getCmdString();
					}
					else if (allBtns[i].getbtnState() == HOVER) {
						rtnStr += "#BTN:" + std::to_string(allBtns[i].getId()) + ":HOVER:CMD:" + allBtns[i].getCmdString();
					}
				}
			}
			if (allDrpDn.size() > 0) {
				for (int i = 0; i < allDrpDn.size(); i++) {
					if (allDrpDn[i].getDrpDnStage() == PRESSED) {
						rtnStr += "#DRP:" + std::to_string(allDrpDn[i].getIdNonIdle()) + ":PRESS:CMD:" + allDrpDn[i].getCmdString();
					}
					else if (allDrpDn[i].getDrpDnStage() == HOVER) {
						rtnStr += "#DRP:" + std::to_string(allDrpDn[i].getIdNonIdle()) + ":HOVER:CMD:" + allDrpDn[i].getCmdString();
					}
				}
			}


			if (allSliders.size() > 0) {
				for (int i = 0; i < allSliders.size(); i++) {
					if (allSliders[i].getHandleStage() == PRESSED) rtnStr += "#SLI:" + std::to_string(allSliders[i].getId()) + ":SLIDING:VAL:" + std::to_string(allSliders[i].getValueAsInt());
					else if (allSliders[i].isSliding()) rtnStr += "#SLI:" + std::to_string(allSliders[i].getId()) + ":SLIDING:VAL:" + std::to_string(allSliders[i].getValueAsInt());
					else if (allSliders[i].getHandleStage() == HOVER) rtnStr += "#SLI:" + std::to_string(allSliders[i].getId()) + ":HOVER:VAL:" + std::to_string(allSliders[i].getValueAsInt());
				}
			}





			for (int i = 0; i < allTextFields.size(); i++) {
				if (isPointInRect(pge->GetMouseX(), pge->GetMouseY(), allTextFields[i].getRect().pos.x, allTextFields[i].getRect().pos.y, allTextFields[i].getRect().w, allTextFields[i].getRect().h)) {
					if(allTextFields[i].getFieldStage() == ISACTIVE) rtnStr += "#TXT:" + std::to_string(allTextFields[i].getId()) + ":TYPING:";
					else rtnStr += "#TXT:" + std::to_string(allTextFields[i].getId()) + ":HOVER:";
					if (allTextFields[i].getString() != "") rtnStr += "STR:" + allTextFields[i].getString();
					else  rtnStr += "NIL:IS_BLANK";
				}
				else if (allTextFields[i].getFieldStage() == ISACTIVE) {
					rtnStr += "#TXT:" + std::to_string(allTextFields[i].getId()) + ":TYPING:";
					if (allTextFields[i].getString() != "") rtnStr += "STR:" + allTextFields[i].getString();
					else  rtnStr += "NIL:IS_BLANK";
				}
			}


			if (rtnStr == "") return "#NON";
			return rtnStr;
		}

		//Loops trougth the current commandstring looking for a specific command from a pressed botton. if CheckHover is true, it will accept the command from a botton hovered. returns true if found.									
		bool hasCommand(std::string cmd, bool checkHover) {
			std::string cmdList = getAllCmds();
			for (int i = 0; i < cmdList.length(); i++) {
				if (cmdList[i] == 'C' && cmdList[i - 1] == ':' && (checkHover || cmdList[i - 2] == 'S')) {
					std::string localcmd = "";
					for (int j = 0; j < cmd.length(); j++) if((j + i + 4) < cmdList.length())localcmd += cmdList[j + i + 4];
					if (localcmd == cmd) return true;
				}
			}
			return false;
		}


		//returns the current text in a textfield.									
		std::string getTxtFieldStr(int id) {
			if (allTextFields.size() > 0) {
				for (int i = 0; i < allTextFields.size(); i++) {
					if (allTextFields[i].getId() == id) return allTextFields[i].getString();
				}
			}
			return "";
		}


		//returns the INT value of a slider.									
		int getSliderInt(int id) {
			if (allSliders.size() > 0) {
				for (int i = 0; i < allSliders.size(); i++) {
					if (allSliders[i].getId() == id) return allSliders[i].getValueAsInt();
				}
			}
			return -1;
		}

		//returns a float value between 0 and 100% based on the Sliders position.									
		float getSliderFloat(int id) {
			if (allSliders.size() > 0) {
				for (int i = 0; i < allSliders.size(); i++) {
					if (allSliders[i].getId() == id) return allSliders[i].getValueAsFloat();
				}
			}
			return -1;
		}




		//returns the objcts X position									
		int getX(int id) {
			if (allBtns.size() > 0) {
				for (int i = 0; i < allBtns.size(); i++) {
					if (allBtns[i].getId() == id) return allBtns[i].getX();
				}
			}
			if (allTextFields.size() > 0) {
				for (int i = 0; i < allTextFields.size(); i++) {
					if (allTextFields[i].getId() == id) return allTextFields[i].getX();
				}
			}
			if (allDrpDn.size() > 0) {
				for (int i = 0; i < allDrpDn.size(); i++) {
					if (allDrpDn[i].getId() == id) return allDrpDn[i].getX();
				}
			}
			if (allSliders.size() > 0) {
				for (int i = 0; i < allSliders.size(); i++) {
					if (allSliders[i].getId() == id) return allSliders[i].getX();
				}
			}
			return -1;
		}

		//returns the objcts Y position									
		int getY(int id) {
			if (allBtns.size() > 0) {
				for (int i = 0; i < allBtns.size(); i++) {
					if (allBtns[i].getId() == id) return allBtns[i].getY();
				}
			}
			if (allTextFields.size() > 0) {
				for (int i = 0; i < allTextFields.size(); i++) {
					if (allTextFields[i].getId() == id) return allTextFields[i].getY();
				}
			}
			if (allDrpDn.size() > 0) {
				for (int i = 0; i < allDrpDn.size(); i++) {
					if (allDrpDn[i].getId() == id) return allDrpDn[i].getY();
				}
			}
			if (allSliders.size() > 0) {
				for (int i = 0; i < allSliders.size(); i++) {
					if (allSliders[i].getId() == id) return allSliders[i].getY();
				}
			}
			return -1;
		}

		//returns the objcts Width									
		int getW(int id) {
			if (allBtns.size() > 0) {
				for (int i = 0; i < allBtns.size(); i++) {
					if (allBtns[i].getId() == id) return allBtns[i].getW();
				}
			}
			if (allTextFields.size() > 0) {
				for (int i = 0; i < allTextFields.size(); i++) {
					if (allTextFields[i].getId() == id) return allTextFields[i].getW();
				}
			}
			if (allDrpDn.size() > 0) {
				for (int i = 0; i < allDrpDn.size(); i++) {
					if (allDrpDn[i].getId() == id) return allDrpDn[i].getW();
				}
			}
			if (allSliders.size() > 0) {
				for (int i = 0; i < allSliders.size(); i++) {
					if (allSliders[i].getId() == id) return allSliders[i].getW();
				}
			}
			return -1;
		}

		//returns the objcts Heigth									
		int getH(int id) {
			if (allBtns.size() > 0) {
				for (int i = 0; i < allBtns.size(); i++) {
					if (allBtns[i].getId() == id) return allBtns[i].getH();
				}
			}
			if (allTextFields.size() > 0) {
				for (int i = 0; i < allTextFields.size(); i++) {
					if (allTextFields[i].getId() == id) return allTextFields[i].getH();
				}
			}
			if (allDrpDn.size() > 0) {
				for (int i = 0; i < allDrpDn.size(); i++) {
					if (allDrpDn[i].getId() == id) return allDrpDn[i].getH();
				}
			}
			if (allSliders.size() > 0) {
				for (int i = 0; i < allSliders.size(); i++) {
					if (allSliders[i].getId() == id) return allSliders[i].getH();
				}
			}
			return -1;
		}

		//returns the length of a slider									
		int getLength(int id) {
			if (allSliders.size() > 0) {
				for (int i = 0; i < allSliders.size(); i++) {
					if (allSliders[i].getId() == id) return allSliders[i].getLength();
				}
			}
			return -1;
		}

		// Sets the X position of an object									
		void setX(int id, int newX) {
			if (allBtns.size() > 0) {
				for (int i = 0; i < allBtns.size(); i++) {
					if (allBtns[i].getId() == id) allBtns[i].setX(newX);
				}
			}
			if (allTextFields.size() > 0) {
				for (int i = 0; i < allTextFields.size(); i++) {
					if (allTextFields[i].getId() == id) allTextFields[i].setX(newX);
				}
			}
			if (allDrpDn.size() > 0) {
				for (int i = 0; i < allDrpDn.size(); i++) {
					if (allDrpDn[i].getId() == id) allDrpDn[i].setX(newX);
				}
			}
			if (allSliders.size() > 0) {
				for (int i = 0; i < allSliders.size(); i++) {
					if (allSliders[i].getId() == id) allSliders[i].setX(newX);
				}
			}
			
		}

		// Sets Height of an object		
		void setH(int id, int newH) {
			if (allBtns.size() > 0) {
				for (int i = 0; i < allBtns.size(); i++) {
					if (allBtns[i].getId() == id) allBtns[i].setH(newH);
				}
			}
			if (allTextFields.size() > 0) {
				for (int i = 0; i < allTextFields.size(); i++) {
					if (allTextFields[i].getId() == id) allTextFields[i].setH(newH);
				}
			}
			if (allDrpDn.size() > 0) {
				for (int i = 0; i < allDrpDn.size(); i++) {
					if (allDrpDn[i].getId() == id) allDrpDn[i].setH(newH);
				}
			}
			if (allSliders.size() > 0) {
				for (int i = 0; i < allSliders.size(); i++) {
					if (allSliders[i].getId() == id) allSliders[i].setH(newH);
				}
			}

		}

		// Sets Width of an object									
		void setW(int id, int newW) {
			if (allBtns.size() > 0) {
				for (int i = 0; i < allBtns.size(); i++) {
					if (allBtns[i].getId() == id) allBtns[i].setW(newW);
				}
			}
			if (allTextFields.size() > 0) {
				for (int i = 0; i < allTextFields.size(); i++) {
					if (allTextFields[i].getId() == id) allTextFields[i].setW(newW);
				}
			}
			if (allDrpDn.size() > 0) {
				for (int i = 0; i < allDrpDn.size(); i++) {
					if (allDrpDn[i].getId() == id) allDrpDn[i].setW(newW);
				}
			}
			if (allSliders.size() > 0) {
				for (int i = 0; i < allSliders.size(); i++) {
					if (allSliders[i].getId() == id) allSliders[i].setW(newW);
				}
			}

		}

										
		// Sets the Y position of an object									
		void setY(int id, int newY) {
			if (allBtns.size() > 0) {
				for (int i = 0; i < allBtns.size(); i++) {
					if (allBtns[i].getId() == id) allBtns[i].setY(newY);
				}
			}
			if (allTextFields.size() > 0) {
				for (int i = 0; i < allTextFields.size(); i++) {
					if (allTextFields[i].getId() == id) allTextFields[i].setY(newY);
				}
			}
			if (allDrpDn.size() > 0) {
				for (int i = 0; i < allDrpDn.size(); i++) {
					if (allDrpDn[i].getId() == id) allDrpDn[i].setY(newY);
				}
			}
			if (allSliders.size() > 0) {
				for (int i = 0; i < allSliders.size(); i++) {
					if (allSliders[i].getId() == id) allSliders[i].setY(newY);
				}
			}

		}

		//Sets teh length of a slider									
		void setLength(int id, int newLength) {
			if (allSliders.size() > 0) {
				for (int i = 0; i < allSliders.size(); i++) {
					if (allSliders[i].getId() == id) allSliders[i].setLength(newLength);
				}
			}

		}

		//Set the position of a slider between min and max. and at step number for SteppingSliders									
		void setValue(int id, int newValue) {
			if (allSliders.size() > 0) {
				for (int i = 0; i < allSliders.size(); i++) {
					if (allSliders[i].getId() == id) allSliders[i].setValue(newValue);
				}
			}

		}
	};

	// Container that controls multiple UIs 
	class UI_STAGE_CONTROLL : public olc::PGEX
	{
	private:

		int screenW = 240, screenH = 220;
		std::vector<UI_CONTAINER> allUIs;
		std::vector<pgrSTAGE> allStages;
		pgrSTAGE mStage;
		float timer = 0;

	public:

		//SetUp the Stage control, the vector must hold one instance of all wanted stages.
		void setUp(int ScreenWidth, int ScreeHeight, std::vector<pgrSTAGE> &addTheseStages) {
			screenW = ScreenWidth;
			screenH = ScreeHeight;
			for (int i = 0; i < addTheseStages.size(); i++) {
				bool addThis = true;
				if (allStages.size() > 0) for (int j = 0; j < allStages.size(); j++) if (addTheseStages[i] == allStages[j]) addThis = false;
				if (addThis) {
					allStages.push_back(addTheseStages[i]);
					allUIs.push_back(UI_CONTAINER());
					allUIs.back().setUp(screenW, screenH);
				}
			}
		}

		//Update all objects in the current stage, if a stage change command is called from a Botton, this update will also update the stage
		void Update(float fElapsedTime, pgrSTAGE &currentStage) {
			if (timer <= 0) {
				for (int i = 0; i < allStages.size(); i++) {
					if (allStages[i] == currentStage) {
						allUIs[i].Update(fElapsedTime);
						///SEEE IF WE SEND THE COMMAND TO CHANGE STAGE
						for (int j = 0; j < allStages.size(); j++) {
							if (allStages[j] != currentStage) {
								if (allUIs[i].hasCommand(stage_to_string(allStages[j]), false)) {
									currentStage = allStages[j];
									MousePresses = false;
									j = allStages.size() + 1;
									timer = 0.2;
								}
							}

						}
						i = allStages.size() + 1;
					}

				}
				mStage = currentStage;
			}
			else timer -= fElapsedTime;
		}

		//Will draw all objects in the current stage
		void drawUIObjects() {
			for (int i = 0; i < allStages.size(); i++) {
				if (allStages[i] == mStage) {
					allUIs[i].drawUIObjects();
					i = allStages.size() + 1;
				}
			}
		}

		//will draw all objects in the selected stage, regardles of update stage.
		void drawUIObjects(pgrSTAGE drawThisStage) {
			for (int i = 0; i < allStages.size(); i++) {
				if (allStages[i] == drawThisStage) {
					allUIs[i].drawUIObjects();
					i = allStages.size() + 1;
				}
			}
		}


		//changes the current stage untill an update is called, this allows for the adding of objects without updating the stages.
		bool addToStage(pgrSTAGE nStage) {
			for (int i = 0; i < allStages.size(); i++) {
				if (allStages[i] == nStage) {
					mStage = nStage;
					return true;
				}
			}
			return false;
		}


		bool isAllHidden() {
			for (int i = 0; i < allStages.size(); i++) {
				if (allStages[i] == mStage) {
					return allUIs[i].isAllHidden();
				}
			}
		}

		bool SetHideAll(bool hideAll) {
			for (int i = 0; i < allStages.size(); i++) {
				if (allStages[i] == mStage) {
					return allUIs[i].SetHideAll(hideAll);
				}
			}
		}

		//Allows the user to toggle the visibility of all objects, and to exclude text fields from this toggle.
		bool ToggleHideAll(bool hideTextFields) {
			for (int i = 0; i < allStages.size(); i++) {
				if (allStages[i] == mStage) {
					return allUIs[i].ToggleHideAll(hideTextFields);
				}
			}
			return false;
		}

		//Toggles the current UI fields visibility.
		bool ToggleHideUIFIELDS() {
			for (int i = 0; i < allStages.size(); i++) {
				if (allStages[i] == mStage) {
					return allUIs[i].ToggleHideUIFIELDS();
				}
			}
			return false;
		}

		//Toggles  the current UI bottons visibility
		bool ToggleHideUIBTNS() {
			for (int i = 0; i < allStages.size(); i++) {
				if (allStages[i] == mStage) {
					return allUIs[i].ToggleHideUIBTNS();
				}
			}
			return false;
		}

		//Toggles  the current UI drop down menus visibility
		bool ToggleHideUIDROPDOWNS() {
			for (int i = 0; i < allStages.size(); i++) {
				if (allStages[i] == mStage) {
					return allUIs[i].ToggleHideUIDROPDOWNS();
				}
			}
			return false;
		}

		//Toggles  the current UI text fields visibility
		bool ToggleHideUITXTFIELDS() {
			for (int i = 0; i < allStages.size(); i++) {
				if (allStages[i] == mStage) {
					return allUIs[i].ToggleHideUITXTFIELDS();
				}
			}
			return false;
		}

		//Toggles  the current UI sliders visibility
		bool ToggleHideSLIDERS() {
			for (int i = 0; i < allStages.size(); i++) {
				if (allStages[i] == mStage) {
					return allUIs[i].ToggleHideSLIDERS();
				}
			}
			return false;
		}

		//Toggles debugmode, in debugmode all items displays their ID.
		bool ToggleDEBUGMODE() {
			for (int i = 0; i < allStages.size(); i++) {
				if (allStages[i] == mStage) {
					return allUIs[i].ToggleDEBUGMODE();
				}
			}
			return false;
		}

		// A singel line text input field, x positon, y position, number of letters desission to hide the ID upon first render
		bool addTextField(int x, int y, int maxLetters) {
			for (int i = 0; i < allStages.size(); i++) {
				if (allStages[i] == mStage) {
					return allUIs[i].addTextField(x,y,maxLetters);
				}
			}
			return false;
		}

		// A singel line text input field, UI style choice, x positon, y position, number of letters.
		bool addTextField(UIStyle colorStyle, int x, int y, int maxLetters) {
			for (int i = 0; i < allStages.size(); i++) {
				if (allStages[i] == mStage) {
					return allUIs[i].addTextField(colorStyle,x,y,maxLetters);
				}
			}
		}

		// A horizontal slider, returns a value between 0 and 100. is located on x and y and has length as its width.
		bool addSlider(int x, int y, int length) {
			for (int i = 0; i < allStages.size(); i++) {
				if (allStages[i] == mStage) {
					return allUIs[i].addSlider(x, y, length);
				}
			}
		}

		// A slider, returns a value between 0 and 100. is located on x and y and has length as its width or height. direction of Left to Right, Right to left, Top to Bottom or Bottom to Top.
		bool addSlider(int x, int y, int length, sliderDirection newDir) {
			for (int i = 0; i < allStages.size(); i++) {
				if (allStages[i] == mStage) {
					return allUIs[i].addSlider(x, y, length, newDir);
				}
			}
		}

		// A slider, Is located on x and y and has length as its width or height. direction of Left to Right, Right to left, Top to Bottom or Bottom to Top. a slider of specifiec range, and steps.
		bool addSlider(int newX, int newY, int newLength, sliderDirection newDir, sliderType newType, std::vector<int> newRange) {
			for (int i = 0; i < allStages.size(); i++) {
				if (allStages[i] == mStage) {
					return allUIs[i].addSlider(newX, newY, newLength, newDir, newType, newRange);
				}
			}
			return true;
		}

		// A rectangle field that will registrer as UI if the mouse hovers over it.
		bool addUIField(int x, int y, int w, int h) {
			for (int i = 0; i < allStages.size(); i++) {
				if (allStages[i] == mStage) {
					return allUIs[i].addUIField(x,y,w,h);
				}
			}
			return false;
		}

		// A simple botton with width 32 heigth 20
		bool addNewBotton(int newX, int newY) {
			for (int i = 0; i < allStages.size(); i++) {
				if (allStages[i] == mStage) {
					return allUIs[i].addNewBotton(newX, newY);
				}
			}
			return false;
		}

		// A simple botton with specified width and heigth
		bool addNewBotton(int newX, int newY, int newW, int newH) {
			for (int i = 0; i < allStages.size(); i++) {
				if (allStages[i] == mStage) {
					return allUIs[i].addNewBotton(newX, newY, newW, newH);
				}
			}
			return false;
		}

		// A simple botton with specified width and heigth, Text displayed on botton.
		bool addNewBotton(int newX, int newY, int newW, int newH, std::string bottonText) {
			for (int i = 0; i < allStages.size(); i++) {
				if (allStages[i] == mStage) {
					return allUIs[i].addNewBotton(newX,newY,newW,newH,bottonText);
				}
			}
			return false;
		}

		//nCmd is a  a string that is returned as a command when the botton is activated.
		bool addNewBotton(std::string nCmd, int newX, int newY, int newW, int newH, std::string bottonText) {
			for (int i = 0; i < allStages.size(); i++) {
				if (allStages[i] == mStage) {
					return allUIs[i].addNewBotton(nCmd, newX, newY, newW, newH, bottonText);
				}
			}
			return false;
		}

		// nKey is a keyboard key, nCmd is a string that is returned as a command when the botton is activated.
		bool addNewBotton(olc::Key nKey, std::string nCmd, int newX, int newY, int newW, int newH, std::string bottonText) {
			for (int i = 0; i < allStages.size(); i++) {
				if (allStages[i] == mStage) {
					return allUIs[i].addNewBotton(nKey, nCmd,newX,newY,newW,newH,bottonText);
				}
			}
			return false;
		}


		// Botton that allowes for selection of the graphic style. nKey is a keyboard key, if hasKey is set to false, teh botton will not recive the key bibdibg. nCmd is a string that is returned as a command when the botton is activated.
		bool addNewBotton(UIStyle style, olc::Key nKey, bool hasKey, std::string nCmd, int newX, int newY, int newW, int newH, std::string bottonText) {
			for (int i = 0; i < allStages.size(); i++) {
				if (allStages[i] == mStage) {
					return allUIs[i].addNewBotton(style,nKey,hasKey, nCmd,newX,newY,newW,newH,bottonText);
				}
			}
			return false;
		}

		//a dropdown menu, newW specifies teh width of the menu, drpDnName is the text on the top botton. drpDnBtns is a string of names for all sup bottons, formated as "First,Second,Third" ect.
		bool addNewDropDown(int newX, int newY, int newW, std::string drpDnName, std::string drpDnBtns) {
			for (int i = 0; i < allStages.size(); i++) {
				if (allStages[i] == mStage) {
					return allUIs[i].addNewDropDown(newX,newY,newW,drpDnName,drpDnBtns);
				}
			}
			return false;
		}

		//a dropdown menu, allowes for selection of the style for the first and all sup bottons. newW specifies teh width of the menu, drpDnName is the text on the top botton. drpDnBtns is a string of names for all sup bottons, formated as "First,Second,Third" ect.
		bool addNewDropDown(UIStyle FirstStyle, UIStyle  DropStyle, int newX, int newY, int newW, std::string drpDnName, std::string drpDnBtns) {
			for (int i = 0; i < allStages.size(); i++) {
				if (allStages[i] == mStage) {
					return allUIs[i].addNewDropDown(FirstStyle,DropStyle,newX,newY,newW,drpDnName,drpDnBtns);
				}
			}
			return false;
		}

		//a dropdown menu, newW specifies teh width of the menu, drpDnName is the text on the top botton. drpDnBtns is a string of names for all sup bottons, formated as "First,Second,Third" ect, commands is as string of commands formated as "FIRST_CMD,SECOND,CMD,THIRD_CMD" ect.
		bool addNewDropDown(int newX, int newY, int newW, std::string drpDnName, std::string drpDnBtns, std::string commands) {
			for (int i = 0; i < allStages.size(); i++) {
				if (allStages[i] == mStage) {
					return allUIs[i].addNewDropDown(newX, newY, newW, drpDnName, drpDnBtns, commands);
				}
			}
			return false;
		}

		//a dropdown menu, allowes for selection of the style for the first and all sup bottons. newW specifies teh width of the menu, drpDnName is the text on the top botton. drpDnBtns is a string of names for all sup bottons, formated as "First,Second,Third" ect, commands is as string of commands formated as "FIRST_CMD,SECOND,CMD,THIRD_CMD" ect.
		bool addNewDropDown(UIStyle FirstStyle, UIStyle  DropStyle, int newX, int newY, int newW, std::string drpDnName, std::string drpDnBtns, std::string commands) {
			for (int i = 0; i < allStages.size(); i++) {
				if (allStages[i] == mStage) {
					return allUIs[i].addNewDropDown(FirstStyle, DropStyle, newX, newY, newW, drpDnName, drpDnBtns, commands);
				}
			}
			return false;
		}

		//Returns true if the mouse is currently over any UI objects area.
		bool isMouseInUI() {
			for (int i = 0; i < allStages.size(); i++) {
				if (allStages[i] == mStage) {
					return allUIs[i].isMouseInUI();
				}
			}
			return false;
		}

		//Returns the ID of any object currently pressed, if none; -1 is returned
		int getbtnPressed() {
			if (isMouseInUI()) {
				for (int i = 0; i < allStages.size(); i++) {
					if (allStages[i] == mStage) {
						return allUIs[i].getbtnPressed();
					}
				}
			}
			return -1;
		}

		//Returns the ID of any object currently hovered, if none; -1 is returned
		int getbtnHover() {
			if (isMouseInUI()) {
				for (int i = 0; i < allStages.size(); i++) {
					if (allStages[i] == mStage) {
						return allUIs[i].getbtnHover();
					}
				}
			}
			return -1;
		}

		//Returns the command string of any botton or dropDownMenu Currently Pressed
		std::string getCmdString() {
			for (int i = 0; i < allStages.size(); i++) {
				if (allStages[i] == mStage) {
					return allUIs[i].getCmdString();
				}
			}
			return "NONE";
		}

		//Returns all commands as a string, both hover and pressed
		//the format is "#TYPE:ID:ACTION:DATATYPE:DATA"
		std::string getAllCmds() {
			for (int i = 0; i < allStages.size(); i++) {
				if (allStages[i] == mStage) {
					return allUIs[i].getAllCmds();
				}
			}
			return "NO COMMANDS CURRENTLY";
		}

		//Loops trougth the current commandstring looking for a specific command from a pressed botton. if CheckHover is true, it will accept the command from a botton hovered. returns true if found.
		bool hasCommand(std::string cmd, bool checkHover) {
			for (int i = 0; i < allStages.size(); i++) {
				if (allStages[i] == mStage) {
					return allUIs[i].hasCommand(cmd, checkHover);
				}
			}
			return false;
		}

		//returns the current text in a textfield.
		std::string getTxtFieldStr(int id) {
			for (int i = 0; i < allStages.size(); i++) {
				if (allStages[i] == mStage) {
					return allUIs[i].getTxtFieldStr(id);
				}
			}
			return "";
		}

		//returns the INT value of a slider.
		int getSliderInt(int id) {
			for (int i = 0; i < allStages.size(); i++) {
				if (allStages[i] == mStage) {
					return allUIs[i].getSliderInt(id);
				}
			}
			return -1;
		}

		//returns a float value between 0 and 100% based on the Sliders position.
		float getSliderFloat(int id) {
			for (int i = 0; i < allStages.size(); i++) {
				if (allStages[i] == mStage) {
					return allUIs[i].getSliderFloat(id);
				}
			}
			return -1;
		}

		//returns the objcts X position
		int getX(int id) {
			for (int i = 0; i < allStages.size(); i++) {
				if (allStages[i] == mStage) {
					return allUIs[i].getX(id);
				}
			}
			return -1;
		}

		//returns the objcts Y position
		int getY(int id) {
			for (int i = 0; i < allStages.size(); i++) {
				if (allStages[i] == mStage) {
					return allUIs[i].getY(id);
				}
			}
			return -1;
		}

		//returns the objcts Heigth
		int getH(int id) {
			for (int i = 0; i < allStages.size(); i++) {
				if (allStages[i] == mStage) {
					return allUIs[i].getH(id);
				}
			}
			return -1;
		}

		//returns the objcts Width
		int getW(int id) {
			for (int i = 0; i < allStages.size(); i++) {
				if (allStages[i] == mStage) {
					return allUIs[i].getW(id);
				}
			}
			return -1;
		}

		//returns the length of a slider
		int getLength(int id) {
			for (int i = 0; i < allStages.size(); i++) {
				if (allStages[i] == mStage) {
					return allUIs[i].getLength(id);
				}
			}
			return -1;
		}

		// Sets the X position of an object
		void setX(int id, int newX) {
			for (int i = 0; i < allStages.size(); i++) {
				if (allStages[i] == mStage) {
					allUIs[i].setX(id, newX);
				}
			}
		}

		// Sets the Y position of an object
		void setY(int id, int newY) {
			for (int i = 0; i < allStages.size(); i++) {
				if (allStages[i] == mStage) {
					allUIs[i].setY(id, newY);
				}
			}
		}

		// Sets Height of an object
		void setH(int id, int newH) {
			for (int i = 0; i < allStages.size(); i++) {
				if (allStages[i] == mStage) {
					allUIs[i].setH(id, newH);
				}
			}
		}

		// Sets Width of an object
		void setW(int id, int newW) {
			for (int i = 0; i < allStages.size(); i++) {
				if (allStages[i] == mStage) {
					allUIs[i].setW(id, newW);
				}
			}
		}

		//Sets teh length of a slider
		void setLength(int id, int newLength) {
			for (int i = 0; i < allStages.size(); i++) {
				if (allStages[i] == mStage) {
					allUIs[i].setLength(id, newLength);
				}
			}
		}

		//Set the position of a slider between min and max. and at step number for SteppingSliders
		void setValue(int id, int newValue) {
			for (int i = 0; i < allStages.size(); i++) {
				if (allStages[i] == mStage) {
					allUIs[i].setValue(id, newValue);
				}
			}
		}
	};

}


#endif
