#include "pch.h"
#include "CGround.h"

CGround::CGround(Vec _pStart, Vec _pEnd)
	: StartPoint(_pStart)
	, EndPoint(_pEnd)
{
	//CreateCollider(StartPoint, EndPoint);
}

CGround::~CGround()
{
}

void CGround::ObjectTick()
{
}

void CGround::ObjectRender(HDC _dc, wstring _string)
{
}

void CGround::GroundSave(FILE* _pFile)
{
}

void CGround::GroundLoad(FILE* _pFile)
{
}


