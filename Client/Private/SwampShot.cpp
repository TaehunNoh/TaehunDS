#include "pch.h"
#include "..\Public\SwampShot.h"

#include "GameInstance.h"
#include "SoundMgr.h"
#include "EffectPlayer.h"

#include "AtkCollManager.h"

#include "Player.h"
#include "PlayerManager.h"

#include "SwampManager.h"

CSwampShot::CSwampShot(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CGameObject(pDevice, pContext)
{
}

CSwampShot::CSwampShot(const CSwampShot& rhs)
	: CGameObject(rhs)
{
}

HRESULT CSwampShot::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CSwampShot::Initialize(void* pArg)
{
	if (nullptr != pArg)
	{
		memcpy(&m_ShotDesc, pArg, sizeof m_ShotDesc);
	}

	if (FAILED(__super::Initialize(&m_ShotDesc.WorldInfo)))
		return E_FAIL;

	if (FAILED(Add_Components()))
		return E_FAIL;
	
	if (nullptr != pArg)
	{
		//�ʱ� ��ġ ����
		m_pTransformCom->Scaling(_float3{1.0f, 1.0f, 1.0f});
		
		m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMLoadFloat4(&m_WorldInfo.vPosition));
	}

	return S_OK;
}

void CSwampShot::Tick(_double dTimeDelta)
{
	__super::Tick(dTimeDelta);

	// 0:�̱�, 1:����, 2:ū����, 3:������
	if (m_ShotDesc.iType == 0)
		Tick_Type_Single(dTimeDelta);
	else if (m_ShotDesc.iType == 1)
		Tick_Type_Quad(dTimeDelta);
	else if (m_ShotDesc.iType == 2)
		Tick_Type_Big(dTimeDelta);
	else if (m_ShotDesc.iType == 3)
		Tick_Type_Swamping(dTimeDelta);


	m_dDelay_All += dTimeDelta;
	if (m_dDelay_All > 10.0)
		m_isDead = true;
	if (true == m_isDead)
		return;
}

void CSwampShot::LateTick(_double dTimeDelta)
{
	__super::LateTick(dTimeDelta);


#ifdef _DEBUG
	/*if (FAILED(m_pRendererCom->Add_DebugGroup(m_pNavigationCom)))
		return;*/
#endif
}

HRESULT CSwampShot::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	return S_OK;
}

void CSwampShot::Make_AttackColl(const _tchar* pLayerTag, _float3 Size, _float3 Pos, _double DurationTime, 
	CAtkCollider::ATK_TYPE AtkType, _vector vDir, _float fDmg, 
	CAtkCollider::BULLET_TYPE eBulletType)
{
	CAtkCollider::ATKCOLLDESC AtkCollDesc;
	ZeroMemory(&AtkCollDesc, sizeof AtkCollDesc);

	AtkCollDesc.ColliderDesc.vSize = Size;
	AtkCollDesc.ColliderDesc.vPosition = Pos;

	AtkCollDesc.dLifeTime = DurationTime;

	AtkCollDesc.pParentTransform = m_pTransformCom;

	AtkCollDesc.eAtkType = AtkType;
	AtkCollDesc.eBulletType = eBulletType;

	AtkCollDesc.fDamage = fDmg;

	AtkCollDesc.bBullet = false;

	XMStoreFloat4(&AtkCollDesc.AtkDir, XMVector4Normalize(vDir));
	CAtkCollManager::GetInstance()->Reuse_Collider(pLayerTag, &AtkCollDesc);
}

void CSwampShot::Tick_Type_Single(_double dTimeDelta)
{
	_vector AtkDir = { 0.0f, 0.0f, 1.0f, 0.0f };
	if (m_isFirst)
	{
		m_isFirst = false;

		_vector AtkDir = { 0.0f, 0.0f, 1.0f, 0.0f };
		Make_AttackColl(TEXT("Layer_MonsterAtk"), _float3(1.0f, 1.0f, 1.0f), _float3(0.f, 0.0f, 0.0f), 10.0,
			CAtkCollider::TYPE_SWAMP, AtkDir, 3.0f);
	}
}

void CSwampShot::Tick_Type_Quad(_double dTimeDelta)
{
	_vector AtkDir = { 0.0f, 0.0f, 1.0f, 0.0f };
	if (m_isFirst)
	{
		m_isFirst = false;

		_vector AtkDir = { 0.0f, 0.0f, 1.0f, 0.0f };
		Make_AttackColl(TEXT("Layer_MonsterAtk"), _float3(1.0f, 1.0f, 1.0f), _float3(0.f, 0.0f, 0.0f), 10.0,
			CAtkCollider::TYPE_SWAMP, AtkDir, 3.0f);
	}

	if (m_dDelay_All < 1.3f)
	{

	}
	else if (1.5f <= m_dDelay_All && m_dDelay_All < 2.0f)
	{
		m_pTransformCom->Go_Dir(dTimeDelta, -Calculate_Dir_From_Pos(m_ShotDesc.MonsterPos));
	}
	else if (2.0f <= m_dDelay_All && m_dDelay_All < 6.0f)
	{
		CGameInstance* pGameInstance = CGameInstance::GetInstance();
		Safe_AddRef(pGameInstance);

		_int PlayerIndex = CPlayerManager::GetInstance()->Get_PlayerIndex();
		CPlayer* pPlayer = dynamic_cast<CPlayer*>(pGameInstance->Get_GameObject(pGameInstance->Get_CurLevelIdx(), TEXT("Layer_Player"), PlayerIndex));
		_vector vPlayerPos = (pPlayer->Get_TransformCom())->Get_State(CTransform::STATE_POSITION);
		_float4 PlayerPos;
		XMStoreFloat4(&PlayerPos, vPlayerPos);

		m_pTransformCom->LerpVector(Calculate_Dir_From_Pos(PlayerPos), 0.0001f);
		m_pTransformCom->Go_Dir(dTimeDelta, Calculate_Dir_From_Pos(PlayerPos));

		Safe_Release(pGameInstance);
	}
}

void CSwampShot::Tick_Type_Big(_double dTimeDelta)
{
	_vector AtkDir = { 0.0f, 0.0f, 1.0f, 0.0f };
	if (m_isFirst)
	{
		m_isFirst = false;

		_vector AtkDir = { 0.0f, 0.0f, 1.0f, 0.0f };
		Make_AttackColl(TEXT("Layer_MonsterAtk"), _float3(3.0f, 3.0f, 3.0f), _float3(0.f, 0.0f, 0.0f), 10.0,
			CAtkCollider::TYPE_SWAMP, AtkDir, 3.0f);
	}
	
}

void CSwampShot::Tick_Type_Swamping(_double dTimeDelta)
{
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	_int PlayerIndex = CPlayerManager::GetInstance()->Get_PlayerIndex();
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(pGameInstance->Get_GameObject(pGameInstance->Get_CurLevelIdx(), TEXT("Layer_Player"), PlayerIndex));
	_vector vPlayerPos = (pPlayer->Get_TransformCom())->Get_State(CTransform::STATE_POSITION);

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, vPlayerPos);

	Safe_Release(pGameInstance);
}

_vector CSwampShot::Calculate_Dir_From_Pos(_float4 Pos)
{
	_vector vMyPos = m_pTransformCom->Get_State(CTransform::STATE_POSITION);

	_float4 MyPos;
	XMStoreFloat4(&MyPos, vMyPos);

	Pos.y = MyPos.y;
	_vector vTarget = XMLoadFloat4(&Pos);

	return XMVector3Normalize(vTarget - vMyPos);
}

HRESULT CSwampShot::Add_Components()
{
	
	CTransform::TRANSFORMDESC TransformDesc;
	TransformDesc.dSpeedPerSec = 5.0;
	TransformDesc.dRadianRotationPerSec = (_double)XMConvertToRadians(90.f);
	// for.Com_Transform 
	if (FAILED(__super::Add_Component(LEVEL_STATIC, TEXT("Prototype_Component_Transform"),
		TEXT("Com_Transform"), (CComponent**)&m_pTransformCom, &TransformDesc)))
	{
		MSG_BOX("Failed to Add_Com_Transform : CSwampShot");
		return E_FAIL;
	}


	return S_OK;
}

CSwampShot* CSwampShot::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CSwampShot* pInstance = new CSwampShot(pDevice, pContext);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CSwampShot");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject* CSwampShot::Clone(void* pArg)
{
	CSwampShot* pInstance = new CSwampShot(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CSwampShot");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CSwampShot::Free()
{
	Safe_Release(m_pTransformCom);

	__super::Free();
}