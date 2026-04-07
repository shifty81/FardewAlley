#include "CameraManager.h"

namespace atlas
{
    void CameraManager::Initialize()
    {
        for (int i = 0; i < 2; ++i)
        {
            m_cameras[i].zoom = 1.0f;
            m_cameras[i].smoothTime = 0.10f;
        }
    }

    void CameraManager::Update(const PlayerManager& playerManager, float dt)
    {
        const float followStrength = dt * 10.0f;

        for (int i = 0; i < 2; ++i)
        {
            const PlayerState& player = playerManager.GetPlayer(i);
            Camera2D& camera = m_cameras[i];

            if (!player.isActive)
            {
                continue;
            }

            camera.currentZone = player.zone;
            camera.targetPosition = player.position;
            camera.position.x += (camera.targetPosition.x - camera.position.x) * followStrength;
            camera.position.y += (camera.targetPosition.y - camera.position.y) * followStrength;

            // TODO: dead zone handling, zone clamping, interior framing, dungeon framing.
        }
    }

    Camera2D& CameraManager::GetCamera(int playerIndex)
    {
        return m_cameras[playerIndex];
    }

    const Camera2D& CameraManager::GetCamera(int playerIndex) const
    {
        return m_cameras[playerIndex];
    }
}
