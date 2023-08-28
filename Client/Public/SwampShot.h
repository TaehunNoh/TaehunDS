#pragma once

#include "Client_Defines.h"
#include "Monster.h"

BEGIN(Engine)

END

BEGIN(Client)

class CSwampShot final : public CGameObject
{
public:
	typedef struct tagShotDesc
	{
		_float4		MonsterPos = { 0.0f, 0.0f, 0.0f ,1.0f };
		CGameObject::WORLDINFO		WorldInfo;
		_int	iType; // 0:�̱�, 1:����, 2:ū����, 3:������
		
	}SHOTDESC;
private:
	CSwampShot(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CSwampShot(const CSwampShot& rhs);
	virtual ~CSwampShot() = default;

public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* pArg) override;
	virtual void	Tick(_double dTimeDelta) override;
	virtual void	LateTick(_double dTimeDelta) override;
	virtual HRESULT Render() override;
	
	void	Make_AttackColl(const _tchar* pLayerTag, _float3 Size, _float3 Pos, _double DurationTime, CAtkCollider::ATK_TYPE AtkType, _vector vDir, _float fDmg, CAtkCollider::BULLET_TYPE eBulletType = CAtkCollider::TYPE_DEFAULT);

	void	Tick_Type_Single(_double dTimeDelta);
	void	Tick_Type_Quad(_double dTimeDelta);
	void	Tick_Type_Big(_double dTimeDelta);
	void	Tick_Type_Swamping(_double dTimeDelta);

	_vector	Calculate_Dir_From_Pos(_float4 Pos);
	

private:
	CTransform* m_pTransformCom = { nullptr };

private:
	SHOTDESC	m_ShotDesc;

	_bool		m_isFirst = { true };

	_double		m_dDelay_All = { 0.0 };

private:
	PrimitiveBatch<DirectX::VertexPositionColor>* m_pPrimitiveBatch = { nullptr };
	BoundingSphere* m_pSphere = { nullptr };

private:
	HRESULT Add_Components();

public:
	static CSwampShot* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END