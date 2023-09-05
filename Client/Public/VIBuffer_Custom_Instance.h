#pragma once
#include "Client_Defines.h"
#include "VIBuffer_Point_Instance.h"

BEGIN(Engine)
END

BEGIN(Client)

class CVIBuffer_CustomParticle final : public CVIBuffer_Point_Instance
{
public:
	typedef struct tagVIB_CustomParticleDesc
	{
		_ubyte	bChangeOption = { 1 };
		_int	iSizeOption = { 1 };
		_int3	vDirOption = { 1, 1, 1 };
		CVIBuffer_Point_Instance::INSTANCEDESC		InstanceDesc;
	}VIB_CUSTOMPARTDESC;
private:
	CVIBuffer_CustomParticle(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CVIBuffer_CustomParticle(const CVIBuffer_CustomParticle& rhs);
	virtual ~CVIBuffer_CustomParticle() = default;

public:
	HRESULT Reset_Particle(void* pArg);

public:
	virtual HRESULT Initialize_Prototype(_uint iNumInstance);
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Tick(_double dTimeDelta) override;

private:
	VIB_CUSTOMPARTDESC	m_CustomPartDesc;

private:
	void Change_Size(_double dTimeDelta);
	void Change_Dir(_double dTimeDelta);

	void Change_Size_Dir(_double dTimeDelta);

public:
	static CVIBuffer_CustomParticle* Create(ID3D11Device * pDevice, ID3D11DeviceContext * pContext, _uint iNumInstance);
	virtual CComponent* Clone(void* pArg) override;
	virtual void Free() override;
};

END