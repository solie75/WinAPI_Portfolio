#pragma once
enum class KEY
{
	UP,		// VK_UP
	DOWN,
	LEFT,
	RIGHT,

	SPACE,
	ENTER,
	ESC,
	LALT,
	LCTRL,
	LSHIFT,
	TAB,

	LBTN,
	RBTN,

	Q,
	W,
	E,
	R,

	A,
	S,
	D,
	F,

	K,
	L,

	_0,
	_1,
	_2,
	_3,
	_4,
	_5,
	_6,
	_7,
	_8,
	_9,

	END,
};

enum class KEY_STATE
{
	TAP,
	PRESSED,
	RELEASE,
	NONE,
};


struct tKeyInfo
{
	KEY			key;
	KEY_STATE	state;
	bool		bPrev;
};


class CKeyMgr
{
	SINGLE(CKeyMgr);

private:
	vector<tKeyInfo> m_vecKey;
	Vec m_vMousePos;

public:
	void KeyMgrInit();
	void KeyMgrTick();

public:
	KEY_STATE GetKeyState(KEY _key)
	{
		return m_vecKey[(UINT)_key].state;
	}
	Vec GetMousePos() { return m_vMousePos; }

	bool AllKeyNoneState() {
		for (UINT i = 0; i < (UINT)KEY::END; ++i)
		{
			if (m_vecKey[i].state != KEY_STATE::NONE)
			{
				return false;
			}
		}
		return true;
	}
};

