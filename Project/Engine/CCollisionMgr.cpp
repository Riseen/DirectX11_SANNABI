#include "pch.h"
#include "CCollisionMgr.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "CLayer.h"
#include "CTransform.h"
#include "CEngine.h"
#include "CTileMap.h"

#include "CGameObject.h"
#include "CCollider2D.h"

CCollisionMgr::CCollisionMgr()
	: m_matrix{}
{

}

CCollisionMgr::~CCollisionMgr()
{

}

void CCollisionMgr::tick()
{
	for (UINT iRow = 0; iRow < LAYER_MAX; ++iRow)
	{
		for (UINT iCol = iRow; iCol < LAYER_MAX; ++iCol)
		{
			if (!(m_matrix[iRow] & (1 << iCol)) )			
				continue;
			
			// iRow 레이어와 iCol 레이어는 서로 충돌검사를 진행한다.
			CollisionBtwLayer(iRow, iCol);
		}
	}
}

void CCollisionMgr::CollisionBtwLayer(UINT _left, UINT _right)
{
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();

	


	CLayer* pLeftLayer = pCurLevel->GetLayer(_left);
	CLayer* pRightLayer = pCurLevel->GetLayer(_right);

	const vector<CGameObject*>& vecLeft = pLeftLayer->GetLayerObjects();
	const vector<CGameObject*>& vecRight = pRightLayer->GetLayerObjects();

	//static int TileLTIndex = 0;
	//static int TileLBIndex = 0;
	//
	//if (_left == 27 && vecLeft.size() > 0)
	//{
	//	TileCurLTIndex(TileLTIndex, TileLBIndex);
	//}
	//if (_right == 27 && vecRight.size() > 0)
	//{
	//	TileCurLTIndex(TileLTIndex, TileLBIndex);
	//}

	for (size_t i = 0; i < vecLeft.size(); ++i)
	{
		// 충돌체가 없는 경우
		if (nullptr == vecLeft[i]->Collider2D())
			continue;

		//if (_left == 27)
		//{
		//	wstring wName = vecLeft[i]->GetName();
		//	wstring Number = wName.substr(12, 17);
		//	int iCurNumer = std::stoi(Number);
		//
		//	if (iCurNumer < TileLTIndex || iCurNumer > TileLBIndex)
		//		continue;
		//}

				
		size_t j = 0;
		if (_left == _right) // Left, Right 동일 레이어인 경우, 이중 검사를 피하기 위함
		{
			j = i + 1;
		}

		for (; j < vecRight.size(); ++j)
		{
			// 충돌체를 보유하고 있지 않거나, 충돌을 진행시킬 두 대상이 동일한 오브젝트인 경우
			if (nullptr == vecRight[j]->Collider2D())// || vecLeft[i] == vecRight[j] )
				continue;

			//if (_right == 27)
			//{
			//	wstring wName = vecRight[j]->GetName();
			//	wstring Number = wName.substr(12, 17);
			//	int iCurNumer = std::stoi(Number);
			//
			//	if (iCurNumer < TileLTIndex || iCurNumer > TileLBIndex)
			//		continue;
			//}
			
			// 두 충돌체의 아이디를 조합
			CollisionID ID = {};
			ID.LeftID = vecLeft[i]->Collider2D()->GetID();
			ID.RightID = vecRight[j]->Collider2D()->GetID();

			// 이전 프레임 충돌 확인
			map<UINT_PTR, bool>::iterator iter = m_mapPrevInfo.find(ID.id);
			if (iter == m_mapPrevInfo.end())
			{
				m_mapPrevInfo.insert(make_pair(ID.id, false));
				iter = m_mapPrevInfo.find(ID.id);
			}


			bool bDead = vecLeft[i]->IsDead() || vecRight[j]->IsDead();

			// 지금 겹쳐있다.
			if (CollisionBtwCollider(vecLeft[i]->Collider2D(), vecRight[j]->Collider2D()))
			{
				// 이전에도 겹쳐있었다.
				if (iter->second)
				{
					if (bDead)
					{
						vecLeft[i]->Collider2D()->EndOverlap(vecRight[j]->Collider2D());
						vecRight[j]->Collider2D()->EndOverlap(vecLeft[i]->Collider2D());
					}
					else
					{
						vecLeft[i]->Collider2D()->Overlap(vecRight[j]->Collider2D());
						vecRight[j]->Collider2D()->Overlap(vecLeft[i]->Collider2D());
					}					
				}

				// 이전에 충돌한 적이 없다.
				else
				{
					// 둘중 하나라도 Dead 상태면, 충돌을 없었던 것으로 한다.
					if (!bDead)
					{
						vecLeft[i]->Collider2D()->BeginOverlap(vecRight[j]->Collider2D());
						vecRight[j]->Collider2D()->BeginOverlap(vecLeft[i]->Collider2D());
						iter->second = true;
					}					
				}
			}

			// 지금 떨어져 있다.
			else
			{
				// 이전에는 겹쳐있었다.
				if (iter->second)
				{					
					vecLeft[i]->Collider2D()->EndOverlap(vecRight[j]->Collider2D());
					vecRight[j]->Collider2D()->EndOverlap(vecLeft[i]->Collider2D());
					iter->second = false;
				}				
			}			
		}
	}
}

bool CCollisionMgr::CollisionBtwCollider(CCollider2D* _pLeft, CCollider2D* _pRight)
{
	const Matrix& matLeft = _pLeft->GetColliderWorldMat();
	const Matrix& matRight = _pRight->GetColliderWorldMat();

	// Rect Local
	// 0 -- 1
	// |    |
	// 3 -- 2
	static Vec3 arrRect[4] = { Vec3(-0.5f, 0.5f, 0.f)
							  , Vec3(0.5f, 0.5f, 0.f)
							  , Vec3(0.5f, -0.5f, 0.f)
							  , Vec3(-0.5f, -0.5f, 0.f) };

	Vec3 arrProj[4] = {};
	
	arrProj[0] = XMVector3TransformCoord(arrRect[1], matLeft) - XMVector3TransformCoord(arrRect[0], matLeft);
	arrProj[1] = XMVector3TransformCoord(arrRect[3], matLeft) - XMVector3TransformCoord(arrRect[0], matLeft);

	arrProj[2] = XMVector3TransformCoord(arrRect[1], matRight) - XMVector3TransformCoord(arrRect[0], matRight);
	arrProj[3] = XMVector3TransformCoord(arrRect[3], matRight) - XMVector3TransformCoord(arrRect[0], matRight);

	Vec3 vCenter = XMVector3TransformCoord(Vec3(0.f, 0.f, 0.f), matRight) - XMVector3TransformCoord(Vec3(0.f, 0.f, 0.f), matLeft);
	
	// i 번째 투영축으로 4개의 표면벡터를 투영시킨다.
	for (int i = 0; i < 4; ++i)
	{		
		// i 번째 표면백터를 투영축으로 삼는다
		Vec3 vProj = arrProj[i];

		// 단위벡터로 만들어서 내적할 경우 투영된 길이를 구할 수 있게 한다.
		vProj.Normalize(); 

		// 투영된 길이를 누적시킬 변수
		float ProjAcc = 0.f;

		// 반복문 돌면서 4개의 표면벡터를 지정된 투영축으로 투영시켜서 길이를 누적받는다.
		for (int j = 0; j < 4; ++j)
		{
			ProjAcc += abs(vProj.Dot(arrProj[j]));
		}

		// 투영된 길이의 절반씩 합친 길이가 필요하기 때문에 전체 합친길이를 2 로 나눈다
		ProjAcc /= 2.f;

		// 두 충돌체의 중심을 이은 벡터도 투영시킨다.
		float fCenterDist = abs(vProj.Dot(vCenter));

		// 중심을 이은 벡터를 투영시킨 길이가, 표면을 투영시킨 길이의 절반보다 크다면 
		// 둘을 분리시킬 수 있다.
		if (ProjAcc < fCenterDist)
		{
			return false;
		}
	}

	// 4번의 테스트동안 분리할 수 없었다.
	return true;
}




void CCollisionMgr::TileCurLTIndex(int& _iLTIndex, int& _iRBIndex)
{
	CGameObject* pMainCamera = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"MainCamera");
	CGameObject* pTileMap = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"TileMap");
	Vec3 vCameraPos = pMainCamera->Transform()->GetRelativePos();
	Vec2 vResolution = CEngine::GetInst()->GetResolution();

	Vec3 vTilePos = pTileMap->Transform()->GetRelativePos();
	Vec3 vTileLTPos = Vec3(vTilePos.x - (pTileMap->Transform()->GetRelativeScale().x / 2.f), vTilePos.y + (pTileMap->Transform()->GetRelativeScale().y / 2.f), vTilePos.z);

	Vec3 vCurLTPos = Vec3(vCameraPos.x - (vResolution.x / 2.f), vCameraPos.y + (vResolution.y / 2.f), vCameraPos.z);
	//Vec3 vCurLBPos = Vec3(vCameraPos.x + (vResolution.x / 2.f), vCameraPos.y + (vResolution.y / 2.f), vCameraPos.z);

	Vec3 vTileCurLTPos = Vec3(abs(vTileLTPos.x) - abs(vCurLTPos.x), vTileLTPos.y - vCurLTPos.y, vTileLTPos.z);

	if (vTileCurLTPos.x < 0.f)
		vTileCurLTPos.x = 0.f;
	else if (vTileCurLTPos.x > vTilePos.x + (pTileMap->Transform()->GetRelativeScale().x / 2.f))
		vTileCurLTPos.x = vTilePos.x + (pTileMap->Transform()->GetRelativeScale().x / 2.f);

	if (vTileCurLTPos.y < vTilePos.y - (pTileMap->Transform()->GetRelativeScale().y / 2.f))
		vTileCurLTPos.y = vTilePos.y - (pTileMap->Transform()->GetRelativeScale().y / 2.f);
	else if(vTileCurLTPos.y > pTileMap->Transform()->GetRelativeScale().y)
		vTileCurLTPos.y = pTileMap->Transform()->GetRelativeScale().y;


	Vec2 vRenderScale = pTileMap->TileMap()->GetTileRenderSize();
	

	int iTileX = vTileCurLTPos.x / vRenderScale.x;
	int iTileY = vTileCurLTPos.y / vRenderScale.y;

	int iRBTileX = iTileX + (vResolution.x / vRenderScale.x);
	int iRBTileY = iTileY + (vResolution.y / vRenderScale.y);

	_iLTIndex = pTileMap->TileMap()->GetFaceX() * iTileY + iTileX;
	_iRBIndex = pTileMap->TileMap()->GetFaceX() * iRBTileY + iRBTileX;
}

void CCollisionMgr::LayerCheck(UINT _left, UINT _right)
{
	UINT iRow = (UINT)_left;
	UINT iCol = (UINT)_right;

	if (iRow > iCol)
	{
		UINT iTemp = iCol;
		iCol = iRow;
		iRow = iTemp;
	}

	m_matrix[iRow] |= (1 << iCol);
}

void CCollisionMgr::LayerCheck(const wstring& _LeftLayer, const wstring& _RightLayer)
{
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	CLayer* pLeftLayer = pCurLevel->GetLayer(_LeftLayer);
	CLayer* pRightLayer = pCurLevel->GetLayer(_RightLayer);

	// 이름에 해당하는 Layer 가 존재하지 않으면
	assert(pLeftLayer && pRightLayer);

	LayerCheck(pLeftLayer->GetLayerIdx(), pRightLayer->GetLayerIdx());
}