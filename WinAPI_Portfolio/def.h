#pragma once

#define SINGLE(type) public:\
					 static type* GetInst()\
					 {\
						 static type inst;\
						 return &inst;\
					 }\
					 private:\
						type();\
						~type();

#define DT CTimeMgr::GetInst()->GetDeltaTime()

#define PI 3.1415926535f

#define DEL(p) if(nullptr != p) {delete p;}

#define IsTap(key) CKeyMgr::GetInst()->GetKeyState(key) == KEY_STATE::TAP
#define IsPressed(key) CKeyMgr::GetInst()->GetKeyState(key) == KEY_STATE::PRESSED
#define IsRelease(key) CKeyMgr::GetInst()->GetKeyState(key) == KEY_STATE::RELEASE
#define IsNone(key) CKeyMgr::GetInst()->GetKeyState(key) == KEY_STATE::NONE
#define MOUSE_POS CKeyMgr::GetInst()->GetMousePos()

#define CLONE(type) virtual type* Clone() {return new type(*this);}
#define CLONE_DEACTIVATE(type) virtual type* Clone() { assert(nullptr); return nullptr;}


enum class LEVEL_TYPE
{
	START,
	DEATHOFFICE,
	GHOSTSTAGE,
	BOSS_MRGORDONGRIMES,
	SOLDIERSTAGE,
	BOSS_MAJORWARRENPLISKHAN,
	END = 6
};

enum class PEN_TYPE
{
	RED,
	GREEN,
	BLUE,

	END,
};

enum class LAYER
{
	BACKGROUND,
	BACKGROUNDOBJECT,
	GROUNDPLATFORM,
	TRIGGER,
	NPC,
	MONSTER,
	PLAYER,
	PLAYER_EFFECT,
	PLAYER_PROJECTILE,
	MONSTER_PROJECTILE,
	UI,

	BLIND,
	DIALOG,
	
	//DEFAULT,
	//FORCE,


	END
};

enum class EVENT_TYPE
{
	CREATE_OBJECT, // wParam : Object Adress lPARAM : layer Type
	DELETE_OBJECT, // wParam : Object Adress
	LEVEL_CHANGE, // wParam : LEVEL_TYPE(Next Level Type)
};

enum class CAMERA_EFFECT
{
	FADE_IN,
	FADE_OUT,
	NONE
};

enum class COLLIDER_TYPE
{
	//LINE
	LINE,

	//SQUARE
	OBJECT,
	PLAYERATTACK,
	TRIGGER,
	UNKNOWN,

	END = 6
};