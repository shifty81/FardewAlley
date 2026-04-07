#include "SaveSystem.h"
#include <fstream>
#include <cstdint>

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

    bool SaveSystem::SaveToDisk(const char* path, const SaveGameData& save) const
    {
        std::ofstream ofs(path, std::ios::binary | std::ios::trunc);
        if (!ofs.is_open())
        {
            return false;
        }

        // Header: magic + version
        // 0x57445246 = bytes 'W','D','R','F' on little-endian (WDRF in stored order)
        const std::uint32_t magic = 0x57445246u;
        const std::uint32_t version = 1u;
        ofs.write(reinterpret_cast<const char*>(&magic), sizeof(magic));
        ofs.write(reinterpret_cast<const char*>(&version), sizeof(version));

        // World state
        ofs.write(reinterpret_cast<const char*>(&save.world.dayNumber), sizeof(int));
        ofs.write(reinterpret_cast<const char*>(&save.world.clockMinuteOfDay), sizeof(int));
        ofs.write(reinterpret_cast<const char*>(&save.world.weatherType), sizeof(int));

        // Player slots
        for (int i = 0; i < 2; ++i)
        {
            const PlayerSaveData& p = save.players[i];
            const std::uint8_t occupied = static_cast<std::uint8_t>(p.occupied);
            ofs.write(reinterpret_cast<const char*>(&occupied), sizeof(occupied));
            ofs.write(reinterpret_cast<const char*>(&p.zone), sizeof(p.zone));
            ofs.write(reinterpret_cast<const char*>(&p.position.x), sizeof(p.position.x));
            ofs.write(reinterpret_cast<const char*>(&p.position.y), sizeof(p.position.y));
            ofs.write(reinterpret_cast<const char*>(&p.health), sizeof(p.health));
            ofs.write(reinterpret_cast<const char*>(&p.stamina), sizeof(p.stamina));
            ofs.write(reinterpret_cast<const char*>(&p.inventory), sizeof(p.inventory));
        }

        return ofs.good();
    }

    bool SaveSystem::LoadFromDisk(const char* path, SaveGameData& outSave) const
    {
        std::ifstream ifs(path, std::ios::binary);
        if (!ifs.is_open())
        {
            return false;
        }

        // Validate header
        std::uint32_t magic = 0u;
        std::uint32_t version = 0u;
        ifs.read(reinterpret_cast<char*>(&magic), sizeof(magic));
        ifs.read(reinterpret_cast<char*>(&version), sizeof(version));
        if (magic != 0x57445246u || version != 1u)
        {
            return false;
        }

        // World state
        ifs.read(reinterpret_cast<char*>(&outSave.world.dayNumber), sizeof(int));
        ifs.read(reinterpret_cast<char*>(&outSave.world.clockMinuteOfDay), sizeof(int));
        ifs.read(reinterpret_cast<char*>(&outSave.world.weatherType), sizeof(int));

        // Player slots
        for (int i = 0; i < 2; ++i)
        {
            PlayerSaveData& p = outSave.players[i];
            std::uint8_t occupied = 0u;
            ifs.read(reinterpret_cast<char*>(&occupied), sizeof(occupied));
            p.occupied = (occupied != 0u);
            ifs.read(reinterpret_cast<char*>(&p.zone), sizeof(p.zone));
            ifs.read(reinterpret_cast<char*>(&p.position.x), sizeof(p.position.x));
            ifs.read(reinterpret_cast<char*>(&p.position.y), sizeof(p.position.y));
            ifs.read(reinterpret_cast<char*>(&p.health), sizeof(p.health));
            ifs.read(reinterpret_cast<char*>(&p.stamina), sizeof(p.stamina));
            ifs.read(reinterpret_cast<char*>(&p.inventory), sizeof(p.inventory));
        }

        return ifs.good();
    }
}
