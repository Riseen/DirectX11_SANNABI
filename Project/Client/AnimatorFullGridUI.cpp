#include "pch.h"
#include "AnimatorFullGridUI.h"
#include "AnimatorEditorUI.h"

AnimatorFullGridUI::AnimatorFullGridUI()
	: UI("AnimatorFullGridUI", "##AnimatorFullGridUI")
	, m_vGridSize{ 1600.f, 900.f }
	, m_vCrossSize{ 100.f , 100.f }
{
	Deactivate();
	SetModal(false);
}

AnimatorFullGridUI::~AnimatorFullGridUI()
{
}


void AnimatorFullGridUI::render_update()
{

	ImGuiIO& io = ImGui::GetIO();
	AnimatorEditorUI* pAnimEditor = (AnimatorEditorUI*)CImGuiMgr::GetInst()->FindUI("##AnimatorEditorUI");

	// Animation
	{


		ImVec2 m_vAnimPanelLT = ImGui::GetWindowPos();

		ImVec2 m_vAnimPanleRB = ImVec2(m_vAnimPanelLT.x + m_vGridSize.x, m_vAnimPanelLT.y + m_vGridSize.y);

		// 테두리와 배경색을 그립니다.
		ImDrawList* draw_list = ImGui::GetWindowDrawList();
		// 배경색
		draw_list->AddRectFilled(m_vAnimPanelLT, m_vAnimPanleRB, IM_COL32(50, 50, 50, 255));
		// 테두리
		draw_list->AddRect(m_vAnimPanelLT - ImVec2(1.f, 1.f), m_vAnimPanleRB + ImVec2(1.f, 1.f), IM_COL32(255, 255, 255, 255));

		// 캔버스에 그리드 + 모든 선을 그립니다
		draw_list->PushClipRect(m_vAnimPanelLT, m_vAnimPanleRB, true);



		if (pAnimEditor->isImageLoad() && pAnimEditor->isAnim())
		{
			// Image 크기
			ImVec2 vMaxSize = ImVec2(pAnimEditor->GetCurAnim().vSlice.x - pAnimEditor->GetCurAnim().vLeftTop.x,
				pAnimEditor->GetCurAnim().vSlice.y - pAnimEditor->GetCurAnim().vLeftTop.y);

			ImVec2 vPanelLT = ImVec2((m_vGridSize.x / 2.f) - ((pAnimEditor->GetCurAnim().vSlice.x - pAnimEditor->GetCurAnim().vLeftTop.x) / 2.f),
				(m_vGridSize.y / 2.f) - ((pAnimEditor->GetCurAnim().vSlice.y - pAnimEditor->GetCurAnim().vLeftTop.y) / 2.f));


			draw_list->AddImage((void*)(pAnimEditor->GetTexture()->GetSRV().Get()),
				m_vAnimPanelLT + vPanelLT,
				vMaxSize + m_vAnimPanelLT + vPanelLT,
				pAnimEditor->GetCurAnim().vImageLtUV,
				pAnimEditor->GetCurAnim().vImageRbUV);

		}



		// 중앙 십자선 그리기
		draw_list->AddLine(ImVec2(m_vAnimPanelLT.x + (m_vGridSize.x / 2.f), (m_vAnimPanelLT.y + ((m_vGridSize.y - m_vCrossSize.y) / 2.f))),
			ImVec2(m_vAnimPanelLT.x + (m_vGridSize.x / 2.f), (m_vAnimPanleRB.y - ((m_vGridSize.y - m_vCrossSize.y) / 2.f))), IM_COL32(0, 255, 0, 255));

		draw_list->AddLine(ImVec2((m_vAnimPanelLT.x + ((m_vGridSize.x - m_vCrossSize.x) / 2.f)), m_vAnimPanelLT.y + (m_vGridSize.y / 2.f)),
			ImVec2((m_vAnimPanleRB.x - ((m_vGridSize.x - m_vCrossSize.x) / 2.f)), m_vAnimPanelLT.y + (m_vGridSize.y / 2.f)), IM_COL32(0, 255, 0, 255));



		draw_list->PopClipRect();




	}
}

void AnimatorFullGridUI::Deactivate()
{
	UI::Deactivate();
	ImGui::SetWindowFocus(nullptr);
}

