#pragma once
#include "CComponent.h"

#include "CTexture.h"

class CAnim;


class CAnimator2D :
    public CComponent
{
private:
    map<wstring, CAnim*>    m_mapAnim;
    CAnim*                  m_CurAnim;
    wstring                 m_CurAnimKey;
    wstring                 m_NextAnimKey;
    bool                    m_bRepeat;
    bool                    m_bNextRepeat;

public:
    virtual void finaltick() override;

    void UpdateData();
    static void Clear();

    // _LeftTop, _SliceSize, _Offset : Pixel Unit
    void Create(const wstring& _strKey, Ptr<CTexture> _AltasTex, Vec2 _LeftTop, Vec2 _vSliceSize, Vec2 _OffsetSize, Vec2 _Background, int _FrmCount, float _FPS, bool _bRp);
    void CreateFromFile();
    void CreateFromFile(const wstring& _strPath);

    CAnim* FindAnim(const wstring& _strAnimName);
    void Play(const wstring& _strAnimName, bool _bRepeat = true);
    void PlayToPlay(const wstring& _strAnimName, const wstring& _strAnimName_Second, bool _bRepeat = true);

    const wstring GetCurAnimKey() { return m_CurAnimKey; }
    const vector<wstring> GetAnimKey()
    {
        map<wstring, CAnim*>::iterator iter = m_mapAnim.begin();

        vector<wstring> vAnimkey;

        for (; iter != m_mapAnim.end(); iter++)
        {
            vAnimkey.push_back(iter->first.c_str());
        }


        return vAnimkey;
    }

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;
    CLONE(CAnimator2D);
public:
    CAnimator2D();
    CAnimator2D(const CAnimator2D& _OriginAnimator);
    ~CAnimator2D();
};

