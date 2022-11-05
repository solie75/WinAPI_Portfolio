#pragma once
class CTexture;

struct tCamEffect
{
	CAMERA_EFFECT	m_eCurEffect;
	float			m_fAccTime;
	float			m_fMaxTime;
};


class CCameraMgr
{
	SINGLE(CCameraMgr);

private:
	Vec m_vLook; // Camera position
	Vec m_vDiff; // difference of Vec within RealPos and renderPos

	list<tCamEffect> m_CamEffectList;
	float m_fRatio;

	CTexture* m_pBlindTex; // FADE_IN 과 FADE_OUT 에 사용되는 텍스쳐

public:
	void SetLook(Vec _vLook) { m_vLook = _vLook; }
	void FadeOut(float _fTerm);
	void FadeIn(float _fTerm);

public:
	void CameraMgrTick();
	void CameraMgrRender(HDC _dc);

public:
	Vec GetRenderPos(Vec _vRealPos)
	{
		return _vRealPos - m_vDiff;
	}

	Vec GetRealPos(Vec _vRenderPos)
	{
		return _vRenderPos + m_vDiff;
	}


};
