#include "pch.h"
#include "CRigidBody.h"

#include "CTimeMgr.h"

#include "CLevelMgr.h"
#include "CLevel.h"


CRigidBody::CRigidBody()
	: CComponent(COMPONENT_TYPE::RIGIDBODY)
	, m_fMass(1.f)
	, m_fFricCoeff(100.f)
	, m_vVelocity {}
	, m_vPrevVelocity {}
	, m_vSwingVelcity {}
	, m_vMaxVelocity(Vec2(600.f, 1000.f))
	, m_fCurAngle(0.f)
	, m_CurState(RIGIDBODY_STATE::DEFAULT)
	, m_PrevState(RIGIDBODY_STATE::DEFAULT)
	, m_fLowGravityAcc (0.f)
	, m_CurUpDownState(RIGIDBODY_UPDOWNSTATE::GROUND)
	, m_PrevUpDownState(RIGIDBODY_UPDOWNSTATE::GROUND)
	, m_vSwingStartPos {}
	, m_vSwingEndPos {}
{
}

CRigidBody::~CRigidBody()
{
}


void CRigidBody::begin()
{
}

void CRigidBody::finaltick()
{
	// ���� ũ��
	float fForce = m_vForce.Length();

	if (0.f != fForce)
	{
		// ���� ����
		m_vForce.Normalize();

		// ���ӵ��� ũ��
		float m_fAccel = fForce / m_fMass;

		// ���ӵ�
		m_vAccel = m_vForce * m_fAccel; //m_vForce / m_fMass;

	}

	// �߰� ���ӵ� 
	m_vAccel += m_vAccelA;

	// �ӵ�
	m_vVelocity += m_vAccel * DT;


	// �����¿����� �ݴ���������� ���ӵ�
	if (m_vVelocity.x != 0.f && m_CurState == RIGIDBODY_STATE::SWING)
	{
		Vec2 vFricDir = -m_vVelocity;
		vFricDir.Normalize();

		Vec2 vFriction = vFricDir * m_fFricCoeff * DT;
		if (m_vVelocity.Length() <= vFriction.Length())
		{
			// ���� ���ӵ��� ���� �ӵ����� �� ū ���
			m_vVelocity = Vec2(0.f, 0.f);
		}
		else
		{
 			m_vVelocity += vFriction;
		}
	}
	

	// �ӵ� ���� �˻�
	if (abs(m_vMaxVelocity.x) < abs(m_vVelocity.x))
	{
		m_vVelocity.x = (m_vVelocity.x / abs(m_vVelocity.x)) * abs(m_vMaxVelocity.x);
	}

	if (abs(m_vMaxVelocity.y) < abs(m_vVelocity.y))
	{
		m_vVelocity.y = (m_vVelocity.y / abs(m_vVelocity.y)) * abs(m_vMaxVelocity.y);
	}

	if (m_PrevState == RIGIDBODY_STATE::SWING && m_CurState != RIGIDBODY_STATE::SWING)
	{
		m_CurState = RIGIDBODY_STATE::SWINGJUMP;
		//SetVelocityForAngle();
		//SwingDir();

		Transform()->SetRelativeRotation(Vec3(Transform()->GetRelativeRotation().x,
			Transform()->GetRelativeRotation().y,
			0.f));

		m_fLowGravityAcc = 0.f;

		//Gravity()->SetGravity(-300.f);
	}
	else if (m_CurState == RIGIDBODY_STATE::SWINGJUMP)
	{

	}
	else if (m_CurState != RIGIDBODY_STATE::SWINGJUMP && m_PrevState == RIGIDBODY_STATE::SWINGJUMP)
	{
		m_bHolding = false;
	}

	// �ӵ��� ���� �̵�
	Move();


	// ������ ������Ʈ�� ���������� ���� 0���� 
	// ���������ӿ��� ���� ��� �������ٵ� ����ϰ� ����Ϸ��� finalupdate���� �ʱ�ȭ �������
	m_vForce = Vec2(0.f, 0.f);

	// �߰� ���ӵ� �ʱ�ȭ
	m_vAccel = Vec2(0.f, 0.f);
	m_vAccelA = Vec2(0.f, 0.f);

	if (m_vVelocity.y > 15.f && !Gravity()->IsSideGround())
		m_CurUpDownState = RIGIDBODY_UPDOWNSTATE::JUMPING;
	else if (m_vVelocity.y < -15.f && !Gravity()->IsSideGround())
		m_CurUpDownState = RIGIDBODY_UPDOWNSTATE::FALLING;
	else
		m_CurUpDownState = RIGIDBODY_UPDOWNSTATE::GROUND;

	m_vPrevVelocity = m_vVelocity;
	m_PrevState = m_CurState;
}

void CRigidBody::SaveToFile(FILE* _File)
{
	fwrite(&m_vForce, sizeof(Vec2), 1, _File);
	fwrite(&m_vAccel, sizeof(Vec2), 1, _File);
	fwrite(&m_vAccelA, sizeof(Vec2), 1, _File);
	fwrite(&m_vVelocity, sizeof(Vec2), 1, _File);
	fwrite(&m_vMaxVelocity, sizeof(Vec2), 1, _File);
	fwrite(&m_fMass, sizeof(float), 1, _File);
	fwrite(&m_fFricCoeff, sizeof(float), 1, _File);
}

void CRigidBody::LoadFromFile(FILE* _File)
{
	fread(&m_vForce, sizeof(Vec2), 1, _File);
	fread(&m_vAccel, sizeof(Vec2), 1, _File);
	fread(&m_vAccelA, sizeof(Vec2), 1, _File);
	fread(&m_vVelocity, sizeof(Vec2), 1, _File);
	fread(&m_vMaxVelocity, sizeof(Vec2), 1, _File);
	fread(&m_fMass, sizeof(float), 1, _File);
	fread(&m_fFricCoeff, sizeof(float), 1, _File);
}




void CRigidBody::SwingDir()
{
	Vec3 vDir = m_vSwingEndPos - m_vSwingStartPos;
	vDir.Normalize();

	m_vSwingDir = vDir;
}

void CRigidBody::Move()
{
	// �̵� �ӷ�
	float fSpeed = m_vVelocity.Length();

	if (0.f != fSpeed)
	{

		// �̵� ����
		switch (m_CurState)
		{
		case RIGIDBODY_STATE::DEFAULT:
		{
			Vec3 vPos = Transform()->GetRelativePos();

			vPos = Vec3(vPos.x + m_vVelocity.x * DT,
				vPos.y + m_vVelocity.y * DT, vPos.z);

			Transform()->SetRelativePos(vPos);
		}
			break;
		case RIGIDBODY_STATE::SWING:
		{
			SetAccelAlpha(Vec2(0.f, 0.f));

			m_vSwingVelcity = m_vVelocity;

			float fx = Transform()->GetRelativePos().x - m_vGrabPos.x;
			float fy = Transform()->GetRelativePos().y - m_vGrabPos.y;

			// ��ü�� �÷��̾��� �Ÿ�
			float fCurDist = Transform()->GetRelativePos() - m_vGrabPos;

			// ���簢��
			m_fCurAngle = atan2f(fy, fx);

			float fCurRadian = XMConvertToRadians(m_vSwingVelcity.x);
			m_fCurAngle += fCurRadian * DT;
			
			float fDe = XMConvertToDegrees(m_fCurAngle);
			fDe += 90.f;

			Transform()->SetRelativePos(Vec3(m_vGrabPos.x + cos(m_fCurAngle) * fCurDist,
				m_vGrabPos.y + sin(m_fCurAngle) * fCurDist,
				Transform()->GetRelativePos().z));

			Transform()->SetRelativeRotation(Vec3(Transform()->GetRelativeRotation().x,
				Transform()->GetRelativeRotation().y,
				XMConvertToRadians(fDe)));

		}
			break;
		case RIGIDBODY_STATE::SWINGJUMP:
		{
			m_fLowGravityAcc += DT;
			
			if (m_fLowGravityAcc > 1.f)
			{
 				m_CurState = RIGIDBODY_STATE::DEFAULT;
			}


			Vec3 vPos = Transform()->GetRelativePos();


			if (m_bHolding)
			{
				vPos = Vec3(vPos.x + m_vVelocity.x * DT,
					vPos.y + m_vVelocity.y * DT, 
					vPos.z);
			}
			else
			{
				vPos = Vec3(vPos.x + (abs(m_vVelocity.x) * (m_vSwingDir.x * 2.f) * DT),
					vPos.y + (m_vVelocity.y * DT), 
					vPos.z);
			}

			 

			Transform()->SetRelativePos(vPos);
		}
			break;
		default:
			break;
		}
	}
}
