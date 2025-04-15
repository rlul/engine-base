#pragma once
#include "game/ibaseentity.h"
#include "game/irenderable.h"
#include "gamemath.h"
#include <memory>

class ISprite;

class CBaseEntity : public IBaseEntity
{
public:
	CBaseEntity();
	virtual ~CBaseEntity() override = default;

	virtual void Spawn() override;

	virtual void Update(float dt) override;
	virtual void Render() override;

	virtual bool MakeMove(MoveInfo_t& cmd) override;

	virtual void GetPos(float& x, float& y) override;
	virtual Vector2D_t GetPos() const override;
	virtual void GetBounds(Vector2D_t& mins, Vector2D_t& maxs) const override;
	virtual void GetWorldBounds(Vector2D_t& mins, Vector2D_t& maxs) const override;
	virtual void GetSize(float& width, float& height) const override;
	virtual Vector2D_t GetSize() const override;
	virtual int GetLayer() const override;

	virtual void SetPos(float x, float y) override;
	virtual void SetPos(Vector2D_t& pos) override;
	virtual void SetSize(float width, float height) override;
	virtual void SetSize(Vector2D_t& size) override;
	virtual void SetScale(float scale) override;
	virtual void SetScale(float scale_x, float scale_y) override;
	virtual void SetLayer(int id) override;

	bool ShouldRender() const override;
	std::shared_ptr<ISprite> GetSprite() const override;
	void GetRenderBounds(Vector2D_t& mins, Vector2D_t& maxs) const override;

	IRenderable* GetRenderable() override;

protected:
	// Transform stuff
	Vector2D_t m_Position;
	Vector2D_t m_BoundsMins, m_BoundsMaxs;
	Vector2D_t m_Scale;

	int m_iLayerOrdinal;
	Vector2D_t m_Velocity;
	ViewDirection_t m_ViewDirection;
	std::shared_ptr<ISprite> m_pSprite;
	float m_flSpawnTime;
};

typedef IBaseEntity* (*CreateEntityFn)();

class CEntityRegistry
{
public:
	CEntityRegistry(const char* name, CreateEntityFn fn);
	virtual ~CEntityRegistry() = default;

	static CreateEntityFn GetEntityFactory(const char* name);

public:
	const char* m_pszName;
	CreateEntityFn m_fnFactory;
	CEntityRegistry* m_pNext;
};

#define REGISTER_ENTITY( name, class ) \
	static CEntityRegistry __g_EntityRegistry##entity(name, []() -> IBaseEntity* { \
			return new class; \
		}); \
