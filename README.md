# olcPGEX_UI
extension for the olcPixelGameEngine with focus on easy implementation of a UI or GUI system.

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
	GitHub:		https://github.com/gameBear/olcPGEX_UI/tree/master

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
