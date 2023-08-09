#pragma once

#include "Client_Defines.h"
#include "Monster.h"

BEGIN(Engine)

END

BEGIN(Client)

class CBoss_Akaza final : public CMonster
{
public:
	
	enum PHASE
	{
		BEGIN, PHASE_1, PHASE_2, PHASE_3
	};
	enum STATE
	{
		STATE_IDLE, STATE_BEGIN,
		STATE_ESCAPE, STATE_DASHPUNCH, STATE_GUARD, STATE_AIRGUN, STATE_PUSHAWAY, STATE_COMBO_PUNCH,
		STATE_JUMPSTOMP, STATE_DASHKICK, STATE_JUMPAIRGUN, STATE_DASH_COMBO_PUNCH, STATE_UPPERKICK,
		STATE_NEXTPHASE2,STATE_NEXTPHASE3,
		STATE_HEAL,
		STATE_AWAKE,STATE_AWAKE_COMBOPUNCH,
		
		STATE_NACHIM, STATE_NACHIM_COMBOPUNCH, STATE_NACHIM_AIRGUN
		
	};

#pragma region AnimIndex
	enum ANIM {
		////////////////// �⺻ MOVE///////////////////

		ANIM_IDEL = 0,
		ANIM_BATTLE_START = 4, // �ڷ� �ѹ��� ���� ������
		ANIM_BATTLE_END = 1, // 2,3
		ANIM_RUN = 66,
		ANIM_RUN_END = 67,
		ANIM_JUMP_BEHIND = 68, // ����
		ANIM_JUMP_FRONT = 69, // ����
		ANIM_JUMP_LEFT = 70, // ����
		ANIM_JUMP_RIGHT = 71, // ����
		ANIM_STEP_BEHIND = 72, // �޽���
		ANIM_STEP_FRONT = 73, // �ս���
		ANIM_STEP_LEFT = 74, // �½���
		ANIM_STEP_LEFT2 = 75, // �½���2
		ANIM_STEP_RIGHT = 76, // �콺��
		ANIM_STEP_RIGHT2 = 77, // �콺��2
		ANIM_DASH = 38, // �뽬
		ANIM_RUNDASH = 50, // ���� �޸���?
		ANIM_JUMPROOP = 61, // ��������
		ANIM_JUMPLAND = 44, // ÷������

		////////////////// ��ų ///////////////////////

		ANIM_HEAL = 5, // ü�� 0 �ǰ� �ٽ� ����
		ANIM_CHARGE = 6, // 7,8 //�������
		ANIM_CHARGE_ROOP = 7,
		ANIM_CHARGE_END = 8,
		ANIM_COMBO1 = 12,
		ANIM_COMBO2 = 13,
		ANIM_COMBO3 = 14,
		ANIM_COMBO_DOWN = 15, // �߷� �� �������
		ANIM_COMBO_PIST = 16, // 18 �ָ� �ʹٴٴ� -> COMBO1234
		ANIM_COMBO_UP = 17, // �ϴܹ����� �� �÷�����
		ANIM_COMBO_PIST2 = 18,

		ANIM_AWAKE_COMBO_PIST = 28, // 28~32 ��������? ���� ��
		
		ANIM_AREA_COMBO = 20, // 21 ���������� �� �ȿ� ������ ����

		ANIM_AIRGUN = 22, // 23,24 ��ǳ
		ANIM_AIRGUN2 = 23,
		ANIM_AIRGUN3 = 24, 

		ANIM_JUMPAIRGUN = 25, // 26,27
		ANIM_JUMPAIRGUN2 = 26,
		ANIM_JUMPAIRGUN3 = 27,

		ANIM_NACHIM = 63, // ������ħ

		ANIM_SKILL_UP = 34, // ���۵��� �ö�
		ANIM_SKILL_DOWN = 35, // 34�� ���� �������� ����
		ANIM_SKILL_DOWNEND = 36, // 35�� ���� �������� ���̵鵿�� �̾���

		ANIM_DASH_PUNCH = 39, // �뽬�� �����

		ANIM_SUPERARMOR = 40, //41,42 �ڼ��� ��� �ָ� �ѹ�
		ANIM_SUPERARMOR2 = 41,
		ANIM_SUPERARMOR3 = 42,

		ANIM_LANDING = 44, // 43�� ������� ���� �� ����

		ANIM_AWAKE_PUSHAWAY = 47, // ȸõ

		////////////////// ��Ʈ��� ///////////////////

		ANIM_HIT_BLOW = 79, // 80 �ڷ� ���ư� 
		ANIM_HIT_BLOW_END = 81, // �ڷ� ���ư� ��
		ANIM_HIT_POWER_BLOW = 82, // 105 ������ ���� ����
		ANIM_HIT_MIDDLE_BLOW = 83, // 105 ����
		ANIM_HIT_BOUNCD = 84, // 85 105 �ٿ��
		ANIM_HIT_DMGFALL = 86, // 87= IDLE
		ANIM_HIT_FALL = 89, // �𸣰��� HIT�� �³�? ���߿��� ��ũ���� ���� IDLE����

		ANIM_HIT_GUARDBREAK = 90,
		ANIM_HIT_SPIN = 91, // 92, 93
		ANIM_HIT_POWER_GUARDBREAK = 94, // �ް����� ��
		ANIM_HIT_RETURN_BIG = 95, // ���� ���� ���� ���¿��� ���ƿ�
		ANIM_HIT_RETURN_SMALL = 96, // �۰���? ���ƿ�

		ANIM_HIT_SMALL_AIR = 97, // 79,80 C�ڰ����� ������ ���ư�
		ANIM_HIT_AIR_UPPER = 98, // ���� �°� ������
		ANIM_HIT_SMALL = 99,
		ANIM_HIT_UPPER = 100, // ����

		ANIM_HIT_STUN = 101, // 102
		ANIM_HIT_GETUP_DIZZY = 103, // 104�� ���� ������ �ٵ� 95�� ������ �´µ�
		ANIM_HIT_DOWNSTATE = 105, // ��������
		ANIM_HIT_GETUP_SPIN = 106, // 107

		////////////////// ������ ///////////////////

		////////////////// �ƽŸ�� ///////////////////
		ANIM_AWAKE_COMBO_PIST_CUT = 19, // ���ǰ��� ���� �� ������ ��Ÿ �� �ƽŸ�� ����
		ANIM_FINAL_CUTSCENE = 111, // ���̳� �ƽ� 
		ANIM_AWAKE_START = 48, // ���� �ƽ�
		ANIM_AWAKE_END = 49,
		ANIM_AWAKE_COMBOPUNCH_Start = 29,
		ANIM_AWAKE_COMBOPUNCH = 30,
		ANIM_AWAKE_COMBOPUNCH_ROOP = 31,
		ANIM_AWAKE_COMBOPUNCH_END = 32,

		ANIM_DEATH = 78, // ���
		ANIM_JUMP_PIST = 33, // �Ⱦ���


	};
#pragma endregion
private:
	CBoss_Akaza(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CBoss_Akaza(const CBoss_Akaza& rhs);
	virtual ~CBoss_Akaza() = default;
#pragma region Tick
public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* pArg) override;
	virtual void	Tick(_double dTimeDelta) override;
	virtual void	LateTick(_double dTimeDelta) override;
	virtual HRESULT Render() override;
	virtual HRESULT Render_ShadowDepth();
#pragma endregion
#pragma region Trigger
#ifdef _DEBUG
	void Debug_State(_double dTimeDelta);
#endif //_DEBUG

	void Update_AnimIndex(_uint iAnimIndex);
	void Update_Trigger(_double dTimeDelta);
	void Update_TriggerTime(_double dTimeDelta);
	void Update_Reset(_double dTimeDelta);
//	void Update_Begin(_double dTimeDelta);
	void Update_Phase_1(_double dTimeDelta);
	void Update_Phase_2(_double dTimeDelta);
	void Update_Phase_3(_double dTimeDelta);

	void Trigger_Idle();
	void Trigger_Begin();
	void Trigger_Escape();
	void Trigger_DashPunch();//
	void Trigger_Guard();
	void Trigger_AirGun();//
	void Trigger_PushAway();//
	void Trigger_Nachim();//
	void Trigger_ComboPunch();
	void Trigger_JumpStomp();
	void Trigger_DashKick();
	void Trigger_JumpAirGun();
	void Trigger_Dash_ComboPunch();
	void Trigger_UpperKick();
	void Trigger_NextPhase2();
	void Trigger_NextPhase3();
	void Trigger_Heal();
	void Trigger_Awake();
	void Trigger_Awake_ComboPunch();

	void Trigger_Nachim_ComboPunch();
	void Trigger_Nachim_AirGun();

#pragma endregion

#pragma region Pattern
private: //���� �Լ���
	void Update_State(_double dTimeDelta);
	void Update_Idle(_double dTimeDelta);
	void Update_Begin(_double dTimeDelta);
	void Update_Escape(_double dTimeDelta);
	void Update_DashPunch(_double dTimeDelta);
	void Update_Guard(_double dTimeDelta);
	void Update_AirGun(_double dTimeDelta);
	void Update_PushAway(_double dTimeDelta);
	void Update_Nachim(_double dTimeDelta);
	void Update_ComboPunch(_double dTimeDelta);
	void Update_JumpStomp(_double dTimeDelta);
	void Update_DashKick(_double dTimeDelta);
	void Update_JumpAirGun(_double dTimeDelta);
	void Update_Dash_ComboPunch(_double dTimeDelta);
	void Update_UpperKick(_double dTimeDelta);
	void Update_NextPhase2(_double dTimeDelta);
	void Update_NextPhase3(_double dTimeDelta);
	void Update_Heal(_double dTimeDelta);
	void Update_Awake(_double dTimeDelta);
	void Update_Awake_ComboPunch(_double dTimeDelta);
	
	void Update_Nachim_ComboPunch(_double dTimeDelta);
	void Update_Nachim_AirGun(_double dTimeDelta);

private: /* Calculate */
	/*_float Calculate_Distance();
	_vector Calculate_Dir();
	_vector Calculate_Dir_FixY();*/


#pragma endregion
private: // _bool
	_bool	m_bStart = { false };

	_bool	m_bAnimFinish = { false };
	
	_bool	m_bHit = { false };

	_bool	m_bDashPunch = { false };
	_bool	m_bCharge = { false };
	_bool	m_bStep_B = { false };
	_bool	m_bRunPunch = { false };
	_bool	m_bDashOn = { false };

	_bool	m_bHeal = { false };
	
	_bool	m_bJump = { false };

	_bool	m_bTrigger = { false };

	_bool	m_bPatternStart = { false };

	//_bool	m_bNextPhase = { false };
	
private: // time
	_double	m_dJumpStompTime = { 0.0 };
	_double m_dAwakePunchTime = { 0.0 };

	_double m_dTriggerTime = { 0.0 };

private:
	_uint	m_iRandomDirNum = { 0 };
	_uint	m_iRandomPatternNum = { 0 };
	_uint	m_iPunchCount = { 0 };
	_uint	m_iIdleCnt = { 0 };

	_uint	m_iTriggerCnt = { 0 };

	_uint	m_iHp = { 100 }; // �ӽ�

private:
	PHASE   m_eCurPhase = PHASE_1;
	STATE	m_eCurstate = STATE_IDLE;
	ANIM    m_eCurAnimIndex = ANIM_IDEL;
	ANIM	m_ePreAnimIndex = ANIM_IDEL;

#pragma region Render
private: // ���� �ƿ�����
	// Outline Default
	_float	m_fOutlineThickness = 0.9f;
	// Outline Face
	_float	m_fOutlineFaceThickness = 0.3f;
	/* �ӽ� �ڵ� */
	_uint	m_iNumAnim = { 0 };
	// ���� Ȯ�ο�
	_uint	m_iMeshNum = { 0 };
#pragma endregion
private:
	//CTransform* m_pPlayerTransformCom = { nullptr };
	
private:
	HRESULT Add_Components();
	HRESULT	SetUp_ShaderResources();

public:
	static CBoss_Akaza* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END