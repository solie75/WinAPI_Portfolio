#pragma once

struct Vec
{
	float x;
	float y;

public:

	bool IsZero()
	{
		return x == 0.f && y == 0.f;
	}

	void Normalize()
	{
		float fDist = sqrtf(x * x + y * y);
		x /= fDist;
		y /= fDist;
	}

	float CountVectorScale()
	{
		return sqrtf(x * x + y * y);
	}

	Vec operator + (Vec _vOther)
	{
		return Vec(x + _vOther.x, y + _vOther.y);
	}

	void operator += (Vec _vOther)
	{
		x += _vOther.x;
		y += _vOther.y;
	}

	Vec operator - (Vec _vOther)
	{
		return Vec(x - _vOther.x, y - _vOther.y);
	}

	void operator -= (Vec _vOther)
	{
		x -= _vOther.x;
		y -= _vOther.y;
	}

	Vec operator -()
	{
		return Vec(-x, -y);
	}

	Vec operator / (float _f)
	{
		return Vec(x / _f, y / _f);
	}

	void operator /= (float _f)
	{
		x /= _f;
		y /= _f;
	}

	Vec operator / (Vec _vOther)
	{
		return Vec(x / _vOther.x, y / _vOther.y);
	}

	void operator /= (Vec _vOther)
	{
		x /= _vOther.x;
		y /= _vOther.y;
	}

	Vec operator * (Vec _vOther)
	{
		return Vec(x * _vOther.x, y * _vOther.y);
	}

	Vec operator * (float _f)
	{
		return Vec(x * _f, y * _f);
	}

	void operator *= (float _f)
	{
		x *= _f, y *= _f;
	}

public:
	Vec()
		: x(0.f)
		, y(0.f)
	{}

	Vec(float _x, float _y)
		: x(_x), y(_y)
	{}

	Vec(UINT _x, UINT _y)
		: x((float)_x)
		, y((float)_y)
	{}

	Vec(POINT _pt)
		: x((float)_pt.x)
		, y((float)_pt.y)
	{

	}

	~Vec()
	{}
};

struct tEvent
{
	EVENT_TYPE eType;
	DWORD_PTR wPARAM;
	DWORD_PTR lPARAM;
};

struct tAnimFrame
{
	Vec vLeftTop; // bring animation frame's lefttop in atlas
	Vec vSize; // frame size
	Vec vOffset;
	float fDuration; // perframe duration time
};