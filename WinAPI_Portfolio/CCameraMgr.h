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

	// whether camera work on or off
	bool m_bCameraWorkCol;
	bool m_bCameraWorkRow;

	list<tCamEffect> m_CamEffectList;
	float m_fRatio;

	CTexture* m_pBlindTex; // FADE_IN 과 FADE_OUT 에 사용되는 텍스쳐

public:
	
	/*void FadeOut(float _fTerm);
	void FadeIn(float _fTerm);*/

	void SetCameraWorkCol(bool _b) { m_bCameraWorkCol = _b; }
	void SetCameraWorkRow(bool _b) { m_bCameraWorkRow = _b; }
	bool GetCameraWorkCol() { return m_bCameraWorkCol; }
	bool GetCameraWorkRow() { return m_bCameraWorkRow; }

	Vec GetCameraLook() { return m_vLook; }
	void SetLookRow(float _vLookx) {
		if (m_bCameraWorkRow)
		{
			m_vLook.x = _vLookx;
		}
	}
	void SetLookCol(float _vLooky) {
		if (m_bCameraWorkCol)
		{
			m_vLook.y = _vLooky;
		}
	}
	void SetLook(Vec _v)
	{
		m_vLook = _v;
	}

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
