#include "pch.h"
#include "CGrabScript.h"

#include "CGrabTailScript.h"

/*
	GRAB

	�ʱ��

	�÷��̾ ���콺�������� ������ �߻�Ǵ� Object
	prefab���� ������ ���� & ������ �ݺ��ϴ°� ���ϳ��ƺ��̱��ѵ�

	���� ������ ���� �����̶� ������ ������ ����


	���� 
	�÷��̾� - �κ��� - �׷�

	1. �κ��ȿ��� �׻� ���콺�������� Ž������
	2. Ž���켱������ 
	   1. Enemy				
	   2. ������ ����
	   3. �̵��� ������ ����� ���콺 ��ǥ ��
	   4. �̵��� �����ߴ� (����ص�) ��
	   5. �� ��Ȳ ��������� �ش���������� ��� �����

	2-1. ���� ����ó��
	   - Enemy�ϰ�� ������ ��� & Enemy�� ���� Outline���
	   - ������ ������ ��� �Ϲ� ��� & ������ ������ �Ϲ� Outline���

	2-2. �̵� ����
		- Ž���Ÿ� > ���� �׷� ��Ÿ� �̱⿡ ���� �׷���Ÿ� ���� Ž���Ÿ��� ���� ª�� �뽬�� �׷��߻�& �浹�Ǿ����
		- Enemy�� ��쿡�� ����ϰ� �����̵Ǵµ� �ð��� ��� �������� �ܻ󳲱��� �����̵�

	2-3. ���� �׼�
		- ������ ó���ɾ����� �̵� ���⸸ŭ�� ���� ����.
		- ������ �ɾ����� �����뽬 �ѹ� ��밡��
		- A D Ű�� �¿� ���� �ִ°� �����ϸ� ��������������� ������ ���� �������� �¿� �ݺ�

*/

CGrabScript::CGrabScript()
	: CScript(GRABSCRIPT)
	, m_fSpeed(5000.f)
	, m_fCurDist (0.f)
	, m_bNone(false)
{
}

CGrabScript::~CGrabScript()
{
}

void CGrabScript::begin()
{
	AddScriptParam(SCRIPT_PARAM::FLOAT, "Grab Speed", &m_fSpeed);
	AddScriptParam(SCRIPT_PARAM::FLOAT, "dist", &m_fCurDist);


	AddScriptParam(SCRIPT_PARAM::VEC3, "StartPos", &m_vStartPos);
	AddScriptParam(SCRIPT_PARAM::VEC3, "Direction", &m_vDir);
	AddScriptParam(SCRIPT_PARAM::VEC3, "ArrivalPos", &m_vArriPos);

	Ptr<CTexture> pAltasTex;

	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Spr_SNBGrab_Flying (lp).png", L"texture\\Spr_SNBGrab_Flying (lp).png");
	Animator2D()->Create(L"GRAB_FLYING", pAltasTex, Vec2(0.f, 0.f), Vec2(64.f, 125.f), Vec2(0.f, 0.f), Vec2(114.f, 175.f), 1, 10, false);


	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Spr_SNBGrab_Grabbing.png", L"texture\\Spr_SNBGrab_Grabbing.png");
	Animator2D()->Create(L"GRABING_LP", pAltasTex, Vec2(0.f, 0.f), Vec2(64.f, 125.f), Vec2(0.f, 0.f), Vec2(114.f, 175.f), 12, 10, false);
	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Spr_SNBGrab_Grabbing_rp.png", L"texture\\Spr_SNBGrab_Grabbing_rp.png");
	Animator2D()->Create(L"GRABING_RP", pAltasTex, Vec2(768.f, 0.f), Vec2(64.f, 125.f), Vec2(0.f, 0.f), Vec2(114.f, 175.f), 12, 10, true);

	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Spr_SNBGrab_Return.png", L"texture\\Spr_SNBGrab_Return.png");
	Animator2D()->Create(L"GRABING_RETURN", pAltasTex, Vec2(0.f, 0.f), Vec2(64.f, 125.f), Vec2(0.f, 0.f), Vec2(114.f, 175.f), 3, 10, false);

	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\NONE.png", L"texture\\NONE.png");
	Animator2D()->Create(L"NONE", pAltasTex, Vec2(0.f, 0.f), Vec2(16.f, 16.f), Vec2(0.f, 0.f), Vec2(30.f, 30.f), 1, 10, false);

	GetRenderComponent()->GetDynamicMaterial();




	Animator2D()->Play(L"NONE");
}

void CGrabScript::tick()
{
	if (m_CurState == GRAB_STATE::FLYING)
	{

		Vec3 vPos = Transform()->GetRelativePos();

		m_vDir = m_vArriPos - m_vStartPos;
		float fCurMaxDist = m_vDir.Length();
		Vec3 vCurDist = m_vStartPos - vPos;
		m_vDir.Normalize();


		vPos.x += m_fSpeed * m_vDir.x * DT;
		vPos.y += m_fSpeed * m_vDir.y * DT;

		float fCur = pow((vPos.x - m_vArriPos.x), 2);
		float fArri = pow((vPos.y - m_vArriPos.y), 2);

		m_fCurDist = sqrt(fCur + fArri);

		if (m_vArriPos.x > m_vStartPos.x)
			m_bLp = true;
		else
			m_bLp = false;


		if (vCurDist.Length() > fCurMaxDist)
		{
			float f = vCurDist.Length();

			if (m_bNone)
				m_CurState = GRAB_STATE::GRABRETURN;
			else
				m_CurState = GRAB_STATE::GRABING;

			Transform()->SetRelativePos(m_vArriPos);
		}
		else
			Transform()->SetRelativePos(vPos);
	}
	else if (m_CurState == GRAB_STATE::GRABING)
	{

	}
	else if (m_CurState == GRAB_STATE::GRABRETURN)
	{
		Vec3 vPos = Transform()->GetRelativePos();

		m_vDir = m_vStartPos - m_vArriPos;
		float fCurMaxDist = m_vDir.Length();
		Vec3 vCurDist = m_vArriPos - vPos;
		m_vDir.Normalize();


		vPos.x += m_fSpeed * m_vDir.x * DT;
		vPos.y += m_fSpeed * m_vDir.y * DT;

		float fCur = pow((vPos.x - m_vArriPos.x), 2);
		float fArri = pow((vPos.y - m_vArriPos.y), 2);

		m_fCurDist = sqrt(fCur + fArri);
	


		if (vCurDist.Length() > fCurMaxDist - 200.f)
		{
			m_CurState = GRAB_STATE::NOT;

			Transform()->SetRelativePos(m_vStartPos);
		}
		else
			Transform()->SetRelativePos(vPos);
	}

	ChangeState();

	m_PrevState = m_CurState;
}


void CGrabScript::SaveToFile(FILE* _File)
{
	fwrite(&m_fSpeed, sizeof(float), 1, _File);
}

void CGrabScript::LoadFromFile(FILE* _File)
{
	fread(&m_fSpeed, sizeof(float), 1, _File);
}

void CGrabScript::ChangeState()
{
	if (m_CurState == m_PrevState)
		return;

	switch (m_CurState)
	{
	case GRAB_STATE::NOT:
		Animator2D()->Play(L"NONE");
		break;
	case GRAB_STATE::FLYING:
		Animator2D()->Play(L"GRAB_FLYING");
		break;
	case GRAB_STATE::GRABING:
		if(m_bLp)
			Animator2D()->Play(L"GRABING_LP", false);
		else 
			Animator2D()->Play(L"GRABING_RP", false);
		break;
	case GRAB_STATE::GRABRETURN:
	{
		Animator2D()->Play(L"GRABING_RETURN", false);
		GamePlayStatic::Play2DSound(L"sound\\Player\\SFX_SNB_ReturnWtihClang.wav", 1, 0.1f);
	}
		break;
	default:
		break;
	}

}

void CGrabScript::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CGrabScript::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CGrabScript::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}


