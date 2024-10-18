#pragma once

#define SINGLE(classtype)  	private:\
								classtype();\
								~classtype();\
							friend class CSingleton<classtype>;

#define DEVICE CDevice::GetInst()->GetDevice()
#define CONTEXT CDevice::GetInst()->GetContext()

#define KEY_CHECK(Key, State) CKeyMgr::GetInst()->GetKeyState(Key) == State
#define DT	CTimeMgr::GetInst()->GetDeltaTime()
#define DTd	CTimeMgr::GetInst()->GetDeltaTime_d()

#define DT_ENGINE	CTimeMgr::GetInst()->GetEngineDeltaTime()
#define DTd_ENGINE	CTimeMgr::GetInst()->GetEngineDeltaTime_d()


#define KEY_TAP(Key) KEY_CHECK(Key, TAP)
#define KEY_PRESSED(Key) KEY_CHECK(Key, PRESSED)
#define KEY_RELEASED(Key) KEY_CHECK(Key, RELEASED)
#define KEY_NONE(Key) KEY_CHECK(Key, NONE)

#define LAYER_MAX 32

#define CLONE(TYPE) virtual TYPE* Clone() { return new TYPE(*this); }
#define CLONE_DISABLE(TYPE) TYPE* Clone() { return nullptr; assert(nullptr); }\
							TYPE(const TYPE& _OriginBuffer) = delete;

enum class DIR_TYPE
{
	RIGHT,
	UP,
	FRONT,
};


enum class ASSET_TYPE
{
	MESH,
	MESHDATA,
	PREFAB,
	TEXTURE,
	MATERIAL,
	SOUND,
	COMPUTE_SHADER,
	GRAPHICS_SHADER,
	FSM,
	END,
};

enum class COMPONENT_TYPE
{
	TRANSFORM,	// ������Ʈ�� ��ġ,ũ��,ȸ��

	COLLIDER2D,	// 2���� �浹ü
	COLLIDER3D, // 3���� �浹ü

	ANIMATOR2D,	// ��������Ʈ Animation
	ANIMATOR3D,	// Bone Skinning Animation

	LIGHT2D,	// 2���� ����
	LIGHT3D,	// 3���� ����

	CAMERA,		// ī�޶� ���

	STATEMACHINE, // ���¸ӽ�

	// Render Component
	MESHRENDER,
	TILEMAP,
	PARTICLESYSTEM,
	SKYBOX,
	DECAL,
	LANDSCAPE,

	RIGIDBODY,
	GRAVITY,

	END,

	SCRIPT,
};


extern const char* ASSET_TYPE_STRING[(UINT)ASSET_TYPE::END];
extern const char* COMPONENT_TYPE_STRING[(UINT)COMPONENT_TYPE::END];

enum class LEVEL_TYPE
{
	MAIN,
	STAGE1,
	BOSS
};

enum class ENEMY_STATE
{
	IDLE,
	POPUP,
	ALERT,
	AIMING,
	SHOOTING,
	HOLDING,
	DEAD,
};

enum class BOSS_STATE
{
	IDLE,
	INVISIBLE,
	SEARCH,
	APPEAR_FIRST,
	APPEAR_SECOND,
	APPEAR_THIRD,
	BATTLEINIT,
	BATTLEINIT_END,
	Phase1_Pattern1_ALERT,
	Phase1_Pattern1_IDLE,
	Phase1_Pattern1_EXCHOLDED,
	Phase1_Pattern1_DAMAGE,
	Phase1_Pattern1_DOWN,
	Phase1_Pattern2_ALERT,
	Phase1_Pattern2_MOVING,
	Phase1_Pattern2_DOWN,
	Phase1_Pattern6_ALERT,
	Phase1_Pattern6_MOVING,
	Phase1_Pattern6_GROGGY,
	Phase1_Pattern6_EXCHOLDED,
	Phase1_Pattern6_DAMAGE,
	Phase1_Pattern6_DOWN,
	Phase1_PatternLast_ALERT,
	Phase1_PatternLast_IDLE,
	Phase1_PatternLast_DOWN,
	Phase1_PatternLast_END,
	Phase1_NextPhase,
	Phase1_NextPhase_END,
	Phase2_Pattern1_ALERT,
	Phase2_Pattern1_IDLE,
	Phase2_Pattern1_EXCHOLDED,
	Phase2_Pattern1_DAMAGE,
	Phase2_Pattern1_DOWN,
	Phase2_Pattern2_ALERT,
	Phase2_Pattern2_MOVING,
	Phase2_Pattern2_DOWN,
	Phase2_Pattern6_ALERT,
	Phase2_Pattern6_MOVING,
	Phase2_Pattern6_GROGGY,
	Phase2_Pattern6_EXCHOLDED,
	Phase2_Pattern6_DAMAGE,
	Phase2_Pattern6_DOWN,
	Phase2_PatternLast_ALERT,
	Phase2_PatternLast_IDLE,
	Phase2_PatternLast_DOWN,
	Phase2_PatternLast_END,
	PhaseFinal_1stHooked,
	PhaseFinal_2ndHooked,
	PhaseFinal_3rdHooked,
	PhaseFinal_1stPoundingReady,
	PhaseFinal_1stPounding,
	PhaseFinal_2ndPoundingReady,
	PhaseFinal_2ndPoundingReady_Two,
	PhaseFinal_2ndPounding,
	PhaseFinal_3rdPoundingReady,
	PhaseFinal_3rdPoundingReady_Two,
	PhaseFinal_3rdPoundingReady_Three,
	PhaseFinal_3rdPounding,
	PhaseFinal_BeforePounding,
	PhaseFinal_Execution,
	PhaseFinal_Execution_Start,
	PhaseFinal_Execution_Ready,
	PhaseFinal_Execution_End,
	PhaseFinal_Execution_After,

};

enum class DefenderBOMB_STATE
{
	Appear,
	MOVE,
	EXPLODE_READY,
	EXPLODE
};

enum class Tile_TYPE
{
	NOT,
	Default,
	Special,
	Damage
};


// ������� ����
enum class CB_TYPE
{
	TRANSFORM,
	MATERIAL_CONST,
	ANIM2D_DATA,
	GLOBAL_DATA,
	ANIMATION,	

	END,
};


// Rasterizer State Type
enum class RS_TYPE
{
	CULL_BACK,
	CULL_FRONT,
	CULL_NONE,
	WIRE_FRAME,

	END,
};

// DepthStencil State Type
enum class DS_TYPE
{
	LESS,				// ������ ���			���� ��� O
	LESS_EQUAL,			// �۰ų� ������ ���		���� ��� O

	GRATER,				// �� �ָ� ���			���� ��� O
	GRATER_EQUAL,		// �� �ְų� ������ ���	���� ��� O

	NO_TEST,			// ���� �׽�Ʈ X			���� ��� O
	NO_WRITE,			// ���� �׽�Ʈ O			���� ��� X

	NO_TEST_NO_WRITE,	// ���� �׽�Ʈ X			���� ��� X

	END,
};

// Blend State
enum class BS_TYPE
{
	DEFAULT,

	ALPHA_BLEND,

	ONE_ZERO,

	ONE_ONE, 

	END,
};


// ScalarParam
enum class SCALAR_PARAM
{
	INT_0,
	INT_1,
	INT_2,
	INT_3,

	FLOAT_0,
	FLOAT_1,
	FLOAT_2,
	FLOAT_3,

	VEC2_0,
	VEC2_1,
	VEC2_2,
	VEC2_3,

	VEC4_0,
	VEC4_1,
	VEC4_2,
	VEC4_3,

	MAT_0,
	MAT_1,
	MAT_2,
	MAT_3,
};

enum class TEX_PARAM
{
	TEX_0,
	TEX_1,
	TEX_2,
	TEX_3,
	TEX_4,
	TEX_5,

	TEXCUBE_0,
	TEXCUBE_1,

	TEXARR_0,
	TEXARR_1,

	END,
};

enum class SCRIPT_PARAM
{
	INT,
	FLOAT,
	VEC2,
	VEC3,
	VEC4,
	OBJECT,
};



enum class DEBUG_SHAPE
{
	RECT,
	CIRCLE,
	CROSS,

	CUBE,
	SPHERE,
};

enum class LIGHT_TYPE
{
	DIRECTIONAL,
	POINT,
	SPOT,
};

enum class SHADER_DOMAIN
{
	DOMAIN_OPAQUE,			// ������
	DOMAIN_MASKED,			// ������ or ����
	DOMAIN_TRANSPARENT,		// ������
	DOMAIN_POSTPROCESS,		// ��ó��

	DOMAIN_DEBUG,
};

enum class PARTICLE_MODULE
{
	SPAWN,			// ��ƼŬ ���� ����
	DRAG,			// ���� ���� ���
	SCALE,			// ũ�� ��ȭ ���
	ADD_VELOCITY,	// �ʱ� �ӵ� ���� ���
	NOISE_FORCE,
	CALCULATE_FORCE,// �־��� ���� ����ϴ� ���

	RENDER,			// ������ ���� �ɼ� ����

	END,
};


enum class LEVEL_STATE
{
	PLAY,
	PAUSE,
	STOP,
	NONE,
};