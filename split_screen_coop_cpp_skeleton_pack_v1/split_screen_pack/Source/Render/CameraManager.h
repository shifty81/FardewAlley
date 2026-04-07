#pragma once

#include "Camera2D.h"
#include "../Gameplay/Players/PlayerManager.h"

namespace atlas
{
    class CameraManager
    {
    public:
        void Initialize();
        void Update(const PlayerManager& playerManager, float dt);

        Camera2D& GetCamera(int playerIndex);
        const Camera2D& GetCamera(int playerIndex) const;

    private:
        Camera2D m_cameras[2]{};
    };
}
