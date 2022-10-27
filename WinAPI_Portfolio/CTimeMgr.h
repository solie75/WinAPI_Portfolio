#pragma once

class CTimeMgr
{
	SINGLE(CTimeMgr);

private:
	LARGE_INTEGER m_llPrevCount;
	LARGE_INTEGER m_llCurCount;
	LARGE_INTEGER m_llFrequency;

	UINT m_iCallCount;
	float m_fDeltaTime;
	float m_fTime;

public:
	void TimeMgrInit();
	void TimeMgrTick();
	void TimeMgrRender();

public:
	float GetDeltaTime() { return m_fDeltaTime; }
};



