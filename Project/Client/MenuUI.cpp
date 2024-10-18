#include "pch.h"
#include "MenuUI.h"



#include <Engine/CPathMgr.h>
#include <Engine/CTaskMgr.h>

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CLayer.h>
#include <Engine/CGameObject.h>
#include <Engine/components.h>

#include <Scripts/CScriptMgr.h>
#include <Engine/CScript.h>

#include "CImGuiMgr.h"
#include "Inspector.h"
#include "CLevelSaveLoad.h"
#include "LevelOptUI.h"


MenuUI::MenuUI()
	: UI("Menu", "##Menu")
{
}

MenuUI::~MenuUI()
{
}

void MenuUI::render()
{
    if (ImGui::BeginMainMenuBar())
    {     
        render_update();

        ImGui::EndMainMenuBar();
    }
}

void MenuUI::render_update()
{
    File();

    Level();

    GameObject();
    
    Asset();
}

void MenuUI::File()
{
    if (ImGui::BeginMenu("File"))
    {
        if (ImGui::MenuItem("Save Level", ""))
        {
            wchar_t szSelect[256] = {};

            OPENFILENAME ofn = {};

            ofn.lStructSize = sizeof(ofn);
            ofn.hwndOwner = nullptr;
            ofn.lpstrFile = szSelect;
            ofn.lpstrFile[0] = '\0';
            ofn.nMaxFile = sizeof(szSelect);
            ofn.lpstrFilter = L"ALL\0*.*\0Level\0*.lv"; // 필터
            ofn.nFilterIndex = 1;
            ofn.lpstrFileTitle = NULL;
            ofn.nMaxFileTitle = 0;

            // 탐색창 초기 위치 지정
            wstring strInitPath = CPathMgr::GetContentPath();
            strInitPath += L"level\\";
            ofn.lpstrInitialDir = strInitPath.c_str();

            ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

            if (GetSaveFileName(&ofn))  // 확인 -> true반환, 취소 -> false반환
            {                
                CLevelSaveLoad::SaveLevel(CLevelMgr::GetInst()->GetCurrentLevel(), CPathMgr::GetRelativePath(szSelect));
            }
        }

        if (ImGui::MenuItem("Load Level", ""))
        {
            wchar_t szSelect[256] = {};

            OPENFILENAME ofn = {};

            ofn.lStructSize = sizeof(ofn);
            ofn.hwndOwner = nullptr;
            ofn.lpstrFile = szSelect;
            ofn.lpstrFile[0] = '\0';
            ofn.nMaxFile = sizeof(szSelect);
            ofn.lpstrFilter = L"ALL\0*.*\0Level\0*.lv";
            ofn.nFilterIndex = 1;
            ofn.lpstrFileTitle = NULL;
            ofn.nMaxFileTitle = 0;

            // 탐색창 초기 위치 지정
            wstring strInitPath = CPathMgr::GetContentPath();
            strInitPath += L"level\\";
            ofn.lpstrInitialDir = strInitPath.c_str();

            ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

            if (GetOpenFileName(&ofn)) // 확인 -> true반환, 취소 -> false반환
            {                
                CLevel* pLevel = CLevelSaveLoad::LoadLevel(CPathMgr::GetRelativePath(szSelect));
                CLevelMgr::GetInst()->ChangeLevel(pLevel, LEVEL_STATE::STOP);

                // Inspector 의 타겟정보를 nullptr 로 되돌리기
                Inspector* pInspector = (Inspector*)CImGuiMgr::GetInst()->FindUI("##Inspector");
                pInspector->SetTargetObject(nullptr);
            }
        }

        ImGui::EndMenu();
    }
}

void MenuUI::Level()
{
    if (ImGui::BeginMenu("Level"))
    {
        CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();

        LEVEL_STATE State = pCurLevel->GetState();

        // 버튼 비활성화용 bool값
        bool PlayEnable = false;
        bool PauseEnable = false;
        bool StopEnable = false;

        if (LEVEL_STATE::STOP == State || LEVEL_STATE::PAUSE == State)
            PlayEnable = true;
        else
            PlayEnable = false;

        if (LEVEL_STATE::PLAY == State)
            PauseEnable = true;
        else
            PauseEnable = false;

        if (LEVEL_STATE::PLAY == State || LEVEL_STATE::PAUSE == State)
            StopEnable = true;
        else
            StopEnable = false;

        
        // Play시 Play직전의 레벨 저장
        if (ImGui::MenuItem("Play", nullptr, nullptr, PlayEnable))
        {   
            // Pause가 아닌 STOP이였을때만 저장
            if (LEVEL_STATE::STOP == pCurLevel->GetState())
            {
               /*LEVEL_TYPE ltype = CLevelMgr::GetInst()->GetCurLevelType();

               switch (ltype)
               {
               case LEVEL_TYPE::MAIN:
                   CLevelSaveLoad::SaveLevel(pCurLevel, L"Level//temp.lv");
                   break;
               case LEVEL_TYPE::STAGE1:
                   CLevelSaveLoad::SaveLevel(pCurLevel, L"Level//Stage1_5.lv");
                   break;
               case LEVEL_TYPE::BOSS:
                   CLevelSaveLoad::SaveLevel(pCurLevel, L"Level//temp.lv");
                   break;
               default:
                   break;
               }*/
            }
            CLevelMgr::GetInst()->ChangeLevelState(LEVEL_STATE::PLAY);
        }

        if (ImGui::MenuItem("Pause", nullptr, nullptr, PauseEnable))
        {
            CLevelMgr::GetInst()->ChangeLevelState(LEVEL_STATE::PAUSE);
        }

        if (ImGui::MenuItem("Stop", nullptr, nullptr, StopEnable))
        {
            // 레벨 로드시 STOP으로 만들어주기
            LEVEL_TYPE ltype = CLevelMgr::GetInst()->GetCurLevelType();
            CLevel* pLoadedLevel = nullptr;

            switch (ltype)
            {
            case LEVEL_TYPE::MAIN:
                pLoadedLevel = CLevelSaveLoad::LoadLevel(L"Level//Boss.lv");
                break;
            case LEVEL_TYPE::STAGE1:
                pLoadedLevel = CLevelSaveLoad::LoadLevel(L"Level//Stage1_5.lv");
                break;
            case LEVEL_TYPE::BOSS:
                pLoadedLevel = CLevelSaveLoad::LoadLevel(L"Level//Boss.lv");
                break;
            default:
                break;
            }

            CLevelMgr::GetInst()->ChangeLevel(pLoadedLevel, LEVEL_STATE::STOP);

            // Inspector 의 타겟정보를 nullptr 로 되돌리기
            Inspector* pInspector = (Inspector*)CImGuiMgr::GetInst()->FindUI("##Inspector");
            pInspector->SetTargetObject(nullptr);
        }

        if (ImGui::MenuItem("Manager", nullptr, nullptr, PlayEnable))
        {
            LevelOptUI* pLevelOptUI = (LevelOptUI*)CImGuiMgr::GetInst()->FindUI("##LevelOptUI");
            pLevelOptUI->Activate();
        }

        ImGui::EndMenu();
    }
}

void MenuUI::GameObject()
{
    if (ImGui::BeginMenu("GameObject"))
    {
        if (ImGui::MenuItem("Create Empty Object", ""))
        {
            CGameObject* pNewObj = new CGameObject;
            pNewObj->SetName(L"New GameObject");
            pNewObj->AddComponent(new CTransform);
            GamePlayStatic::SpawnGameObject(pNewObj, 0);
        }
        ImGui::Separator();

        if (ImGui::BeginMenu("Add Component", ""))
        {
            for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
            {
                if (ImGui::MenuItem(COMPONENT_TYPE_STRING[i]))
                {
                    Inspector* inspector = (Inspector*)CImGuiMgr::GetInst()->FindUI("##Inspector");
                    if (nullptr != inspector->GetTargetObject())
                    {
                        inspector->GetTargetObject()->AddComponent(GetComponent(*COMPONENT_TYPE_STRING[i]));
                    }
                }
            }

            ImGui::EndMenu();
        }


        //if (ImGui::BeginMenu("Delete Component", ""))
        //{
        //    for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
        //    {
        //        if (ImGui::MenuItem(COMPONENT_TYPE_STRING[i]))
        //        {
        //            Inspector* inspector = (Inspector*)CImGuiMgr::GetInst()->FindUI("##Inspector");
        //            if (nullptr != inspector->GetTargetObject())
        //            {
        //                inspector->GetTargetObject()->DeleteComponent(i);
        //            }
        //        }
        //    }
        //
        //    ImGui::EndMenu();
        //}
        

        if (ImGui::BeginMenu("Script", ""))
        {
            vector<wstring> vecScriptName;
            CScriptMgr::GetScriptInfo(vecScriptName);

            for (size_t i = 0; i < vecScriptName.size(); ++i)
            {
                if (ImGui::MenuItem(ToString(vecScriptName[i]).c_str()))
                {
                    Inspector* inspector = (Inspector*)CImGuiMgr::GetInst()->FindUI("##Inspector");
                    if (nullptr != inspector->GetTargetObject())
                    {                     
                        inspector->GetTargetObject()->AddComponent(CScriptMgr::GetScript(vecScriptName[i]));
                    }
                }
            }

            ImGui::EndMenu();
        }

        ImGui::EndMenu();
    }
}

void MenuUI::Asset()
{
    if (ImGui::BeginMenu("Asset"))
    {
        if (ImGui::MenuItem("Create Empty Material"))
        {
            wchar_t szPath[255] = {};            
            wstring FilePath = CPathMgr::GetContentPath();
            
            int num = 0;
            while (true)
            {                
                swprintf_s(szPath, L"Material//New Material_%d.mtrl", num);
                if (!exists(FilePath + szPath))
                    break;
                ++num;
            }

            CMaterial* pMtrl = new CMaterial;
            pMtrl->SetName(szPath);
            pMtrl->Save(szPath);
            GamePlayStatic::AddAsset(pMtrl);
        }

        if (ImGui::BeginMenu("ADD State", ""))
        {



            ImGui::EndMenu();
        }

        ImGui::EndMenu();
    }
}

CComponent* MenuUI::GetComponent(const char& _ComponentName)
{
    if ("TRANSFORM" == &_ComponentName)
    {
        return new CTransform;
    }
    if ("COLLIDER2D" == &_ComponentName)
    {
        return new CCollider2D;
    }
    if ("COLLIDER3D" == &_ComponentName)
    {
        return nullptr;
    }
    if ("ANIMATOR2D" == &_ComponentName)
    {
        return new CAnimator2D;
    }
    if ("ANIMATOR3D" == &_ComponentName)
    {
        return nullptr;
    }
    if ("LIGHT2D" == &_ComponentName)
    {
        return new CLight2D;
    }
    if ("LIGHT3D" == &_ComponentName)
    {
        return nullptr;
    }
    if ("CAMERA" == &_ComponentName)
    {
        return new CCamera;
    }
    if ("STATEMACHINE" == &_ComponentName)
    {
        return new CStateMachine;
    }
    if ("MESHRENDER" == &_ComponentName)
    {
        return new CMeshRender;
    }
    if ("TILEMAP" == &_ComponentName)
    {
        return new CTileMap;
    }
    if ("PARTICLESYSTEM" == &_ComponentName)
    {
        return new CParticleSystem;
    }
    if ("SKYBOX" == &_ComponentName)
    {
        return nullptr;
    }
    if ("DECAL" == &_ComponentName)
    {
        return nullptr;
    }
    if ("LANDSCAPE" == &_ComponentName)
    {
        return nullptr;
    }
    if ("RIGIDBODY" == &_ComponentName)
    {
        return new CRigidBody;
    }
    if ("GRAVITY" == &_ComponentName)
    {
        return new CGravity;
    }
    return nullptr;
}

