#include "SaveSystem.h"

namespace atlas
{
    void SaveSystem::CaptureFromWorld(const PlayerManager& playerManager, SaveGameData& outSave) const
    {
        for (int i = 0; i < 2; ++i)
        {
            const PlayerState& player = playerManager.GetPlayer(i);
            auto& playerSave = outSave.players[i];
            playerSave.occupied = player.isActive;
            playerSave.zone = player.zone;
            playerSave.position = player.position;
            playerSave.health = player.health;
            playerSave.stamina = player.stamina;
            playerSave.inventory = player.inventory;
        }

        // TODO: serialize world state.
    }

    void SaveSystem::ApplyToWorld(const SaveGameData& save, PlayerManager& playerManager) const
    {
        for (int i = 0; i < 2; ++i)
        {
            const auto& playerSave = save.players[i];
            if (!playerSave.occupied)
            {
                playerManager.DeactivatePlayer(i);
                continue;
            }

            playerManager.ActivatePlayer(i, playerSave.zone, playerSave.position);
            PlayerState& player = playerManager.GetPlayer(i);
            player.health = playerSave.health;
            player.stamina = playerSave.stamina;
            player.inventory = playerSave.inventory;
        }

        // TODO: restore world state.
    }

    bool SaveSystem::SaveToDisk(const char*, const SaveGameData&) const
    {
        // TODO: implement binary or JSON serialization.
        return false;
    }

    bool SaveSystem::LoadFromDisk(const char*, SaveGameData&) const
    {
        // TODO: implement binary or JSON deserialization.
        return false;
    }
}
