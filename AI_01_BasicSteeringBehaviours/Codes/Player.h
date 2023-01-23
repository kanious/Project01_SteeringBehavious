#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "GameObject.h"
#include "EngineStruct.h"

namespace Engine
{
	class CMesh;
	class CInputDevice;
}
class Player : public Engine::CGameObject
{
private:
	Engine::CMesh*				m_pMesh;
	Engine::CInputDevice*		m_pInputDevice;
	glm::vec3					m_vOriginPosition;
	glm::vec3					m_vVelocity;
	_float						m_fSpeed;
	_float						m_fRotSpeed;

private:
	explicit Player();
	virtual ~Player();

public:
	glm::vec3 GetVelocity() { return m_vVelocity; }
	glm::vec3 GetOriginPosition() { return m_vOriginPosition; }
private:
	void KeyCheck(const _float& dt);
	void CheckBoundary(glm::vec3& vPos);

public:
	virtual void Update(const _float& dt);
	virtual void Render();
private:
	virtual void Destroy();
	RESULT Ready(_uint sTag, _uint lTag, _uint oTag, Engine::CLayer* pLayer, std::string meshID,
		glm::vec3 vPos, glm::vec3 vRot, glm::vec3 vScale, int dir);
public:
	static Player* Create(_uint sTag, _uint lTag, _uint oTag, Engine::CLayer* pLayer, std::string meshID,
		glm::vec3 vPos, glm::vec3 vRot, glm::vec3 vScale, int dir = 0);
};


#endif //_PLAYER_H_