#pragma once

#include "SaveTypes.h"
#include "../Gameplay/Players/PlayerManager.h"

namespace atlas
{
    class SaveSystem
    {
    public:
        void CaptureFromWorld(const PlayerManager& playerManager, SaveGameData& outSave) const;
        void ApplyToWorld(const SaveGameData& save, PlayerManager& playerManager) const;

        bool SaveToDisk(const char* path, const SaveGameData& save) const;
        bool LoadFromDisk(const char* path, SaveGameData& outSave) const;
    };
}
