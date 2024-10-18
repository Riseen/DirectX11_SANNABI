#pragma once
#include <Engine/CScript.h>

enum class CAMERA_SHAKE_TYPE
{
    NO,
    LB_TO_RT,
    LT_TO_RB,
    FOURDIR_LT,
    TOP_TO_BOTTOM,
    LEFT_TO_RIGHT,
    FOURDIR_TOP,
};

class CCameraScript :
    public CScript
{
private:
    CAMERA_SHAKE_TYPE m_CurShakeState;
    CGameObject* m_pFadeInOutObj;
    Vec3 m_vZoomPos;

    Vec3 m_vMinMovePos;
    Vec3 m_vMaxMovePos;

    float m_fAccTime;
    float m_fShakeValue;
    float m_fShakeTime;

    float m_fZoomAccTime;
    float m_fZoomTime;
    float m_fZoomValue;

    float m_fFirstScale;

    bool  m_bShake;
    bool  m_bTimeZoom;
    bool  m_bZoomIn;
    bool  m_bZoomOut;

    bool  m_bCameraMoveDistLock;

private:
    void Shake(float _fValue, float& _fDuration);
    void Move();
    void Zoom();
    void MoveLock();

public:
    void ZoomIn(float _fValue);
    void ZoomIn(float _fValue, Vec3 _vZoomPos);
    void ZoomIn(float _fValue, CGameObject* _ZoomObject);
    void ZoomOut(float _fValue);
    void ZoomOut(float _fValue, Vec3 _vZoomPos);
    void ZoomOut(float _fValue, CGameObject* _ZoomObject);

    void ZoomInWithTime(float _fValue, float _fTime);
    void ZoomInWithTime(float _fValue, float _fTime, Vec3 _vZoomPos);
    void ZoomInWithTime(float _fValue, float _fTime, CGameObject* _ZoomObject);

    void ZoomOutWithTime(float _fValue, float _fTime);
    void ZoomOutWithTime(float _fValue, float _fTime, Vec3 _vZoomPos);
    void ZoomOutWithTime(float _fValue, float _fTime, CGameObject* _ZoomObject);

    void CameraMoveDistLock(Vec3 _vMin, Vec3 _vMax);

    void FadeIn(float _fDuration, Vec3 _vColor);
    void FadeOut(float _fDuration);
    void FadeInOut(float _fDuration, Vec3 _vColor);

    void SetFocus(Vec3 _vPos);
    void SetFocus(CGameObject* _pObj);

    void SetShakeOnOff(bool _bOn, float _fShakeTime, float _fValue, CAMERA_SHAKE_TYPE _ShakeType) 
    { 
        m_bShake = _bOn;
        if (_fShakeTime > m_fShakeTime)
            m_fShakeTime = _fShakeTime;
        if (_fValue > m_fShakeValue)
            m_fShakeValue = _fValue;
        m_CurShakeState = _ShakeType;
    }
    

public:
    virtual void begin() override;
    virtual void tick() override;


    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;
    CLONE(CCameraScript);
public:
    CCameraScript();
    ~CCameraScript();
};

