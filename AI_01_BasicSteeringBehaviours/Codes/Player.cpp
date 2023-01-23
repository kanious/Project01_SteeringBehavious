#include "Player.h"
#include "ComponentMaster.h"
#include "Layer.h"
#include "Function.h"

#include "Component.h"
#include "Transform.h"
#include "Mesh.h"
#include "Renderer.h"
#include "BoundingBox.h"
#include "OpenGLDefines.h"
#include "OpenGLDevice.h"
#include "SoundMaster.h"
#include "LightMaster.h"
#include "Shader.h"
#include "LightMaster.h"
#include "Light.h"
#include "InputDevice.h"


USING(Engine)
USING(glm)
USING(std)

Player::Player()
	: m_pMesh(nullptr), m_vVelocity(vec3(0.f)), m_vOriginPosition(vec3(0.f)), m_fSpeed(5.f), m_fRotSpeed(40.f)
{
	m_bDebug = false;
	m_pInputDevice = CInputDevice::GetInstance(); m_pInputDevice->AddRefCnt();
}

Player::~Player()
{
}

void Player::KeyCheck(const _float& dt)
{
	m_vVelocity = vec3(0.f);

	if (m_pInputDevice->IsKeyDown(GLFW_KEY_W))
	{
		vec3 vDir = m_pTransform->GetLookVector();
		m_vVelocity += vDir * dt * m_fSpeed;
	}

	if (m_pInputDevice->IsKeyDown(GLFW_KEY_S))
	{
		vec3 vDir = m_pTransform->GetLookVector();
		m_vVelocity -= vDir * dt * m_fSpeed;
	}

	if (m_pInputDevice->IsKeyDown(GLFW_KEY_A))
	{
		vec3 vRight = m_pTransform->GetRightVector();
		m_vVelocity += vRight * dt * m_fSpeed;
	}

	if (m_pInputDevice->IsKeyDown(GLFW_KEY_D))
	{
		vec3 vRight = m_pTransform->GetRightVector();
		m_vVelocity -= vRight * dt * m_fSpeed;
	}

	static _bool isLeftShiftDown = false;
	if (m_pInputDevice->IsKeyDown(GLFW_KEY_LEFT_SHIFT))
	{
		if (!isLeftShiftDown)
		{
			isLeftShiftDown = true;

			if (20.f == m_fSpeed)
				m_fSpeed = 5.f;
			else
				m_fSpeed = 20.f;

			if (80.f == m_fRotSpeed)
				m_fRotSpeed = 40.f;
			else
				m_fRotSpeed = 80.f;
		}
	}
	else
		isLeftShiftDown = false;

	m_vOriginPosition = m_pTransform->GetPosition();
	vec3 vPos = m_pTransform->GetPosition();
	vPos += m_vVelocity;
	CheckBoundary(vPos);
	m_pTransform->SetPosition(vPos);

	if (m_pInputDevice->IsKeyDown(GLFW_KEY_Q))
	{
		_float fAngle = m_pTransform->GetRotationY();
		fAngle += dt * m_fRotSpeed;
		if (fAngle > 360.f)
			fAngle -= 360.f;
		m_pTransform->SetRotationY(fAngle);
	}

	if (m_pInputDevice->IsKeyDown(GLFW_KEY_E))
	{
		_float fAngle = m_pTransform->GetRotationY();
		fAngle -= dt * m_fRotSpeed;
		if (fAngle < 0.f)
			fAngle += 360.f;
		m_pTransform->SetRotationY(fAngle);
	}
}

void Player::CheckBoundary(vec3& vPos)
{
	if (vPos.x > 50.f)
		vPos.x = 50.f;
	else if (vPos.x < -50.f)
		vPos.x = -50.f;

	if (vPos.z > 50.f)
		vPos.z = 50.f;
	else if (vPos.z < -50.f)
		vPos.z = -50.f;
}

void Player::Update(const _float& dt)
{
	if (m_bEnable)
	{
		KeyCheck(dt);

		CGameObject::Update(dt);

		if (nullptr != m_pRenderer)
			m_pRenderer->AddRenderObj(this);
	}
}

void Player::Render()
{
	CGameObject::Render();
}

void Player::Destroy()
{
	SafeDestroy(m_pInputDevice);

	CGameObject::Destroy();
}

RESULT Player::Ready(_uint sTag, _uint lTag, _uint oTag, CLayer* pLayer, string meshID, vec3 vPos, vec3 vRot, vec3 vScale, int dir)
{
	SetupGameObject(sTag, lTag, oTag);
	m_pLayer = pLayer;
	m_meshName = meshID;

	//Clone.Mesh
	m_pMesh = CloneComponent<CMesh*>(meshID);
	if (nullptr != m_pMesh)
	{
		AttachComponent("Mesh", m_pMesh);
		m_pMesh->SetTransform(m_pTransform);
		m_pBoundingBox = m_pMesh->GetBoundingBox();
		if (nullptr != m_pBoundingBox)
			m_pBoundingBox->SetTransform(m_pTransform);
		m_pMesh->SetWireFrame(false);
		m_pMesh->SetDebugBox(false);
	}

	if (nullptr != m_pTransform)
	{
		m_pTransform->SetPosRotScale(vPos, vRot, vScale);
		m_pTransform->Update(0);
	}

	return PK_NOERROR;
}

Player* Player::Create(_uint sTag, _uint lTag, _uint oTag, CLayer* pLayer, string meshID, vec3 vPos, vec3 vRot, vec3 vScale, int dir)
{
	Player* pInstance = new Player();
	if (PK_NOERROR != pInstance->Ready(sTag, lTag, oTag, pLayer, meshID, vPos, vRot, vScale, dir))
	{
		pInstance->Destroy();
		pInstance = nullptr;
	}

	return pInstance;
}
