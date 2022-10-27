#pragma once

class CObject;

class CEventMgr
{
	SINGLE(CEventMgr);
private:
	vector<tEvent> m_vecEvent;
	vector<CObject*> m_vecGarbage;

public:
	void AddEvent(const tEvent& _event) { m_vecEvent.push_back(_event); }

	void EventMgrTick();
};