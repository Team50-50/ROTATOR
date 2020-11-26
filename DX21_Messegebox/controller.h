/*=======================================================================================

	 コントローラー制御[controller.h]
												author:mgc
												date:2020/11/26
 -----------------------------------------------------------------------------------------

 =========================================================================================*/
#ifndef CONTROLLER_H_
#define CONTROLLER_H_

enum ButtonKind
{
	LStickUP,
	LStickDown,
	LStickLeft,
	LStickRight,

	RStickUP,
	RStickDown,
	RStickLeft,
	RStickRight,

	UpButton,
	DownButton,
	LeftButton,
	RightButton,

	ButtonY,
	ButtonB,
	ButtonA,
	ButtonX,

	ButtonLB,
	ButtonRB,
	ButtonLT,
	ButtonRT,

	Button_BACK,
	Button_START,
	ButtonKindMax,
};


enum ButtonState
{
	JoyStateNone,
	JoyStateDown,
	JoyStatePush,
	JoyStateUp,
	JoyStateMax,
};

void InitController(void);

void UpdateController(void);


bool JoystickPress(ButtonKind button);


bool JoystickRelease(ButtonKind button);


bool JoystickTrigger(ButtonKind button);

#endif // !CONTROLLER_H_

