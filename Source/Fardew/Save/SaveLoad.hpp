#pragma once

#include "WorldTypes.hpp"

#include <filesystem>
#include <fstream>
#include <iomanip>
#include <optional>
#include <sstream>
#include <stdexcept>
#include <string>

namespace atlas {

class SaveLoadService {
public:
    static bool SaveToFile(const WorldState& world, const std::filesystem::path& path) {
        std::ofstream out(path, std::ios::binary | std::ios::trunc);
        if (!out) {
            return false;
        }

        out << "ATLAS_WORLD_SAVE_V1\n";
        out << "saveVersion=" << world.saveVersion << '\n';
        out << "saveName=" << Escape(world.saveName) << '\n';
        out << "clock.day=" << world.clock.dayNumber << '\n';
        out << "clock.minute=" << world.clock.minuteOfDay << '\n';
        out << "clock.timeScale=" << std::fixed << std::setprecision(3) << world.clock.timeScale << '\n';
        out << "clock.paused=" << (world.clock.paused ? 1 : 0) << '\n';

        out << "crops.count=" << world.crops.size() << '\n';
        for (std::size_t i = 0; i < world.crops.size(); ++i) {
            const auto& crop = world.crops[i];
            out << "crop." << i << ".tileX=" << crop.tile.x << '\n';
            out << "crop." << i << ".tileY=" << crop.tile.y << '\n';
            out << "crop." << i << ".cropId=" << Escape(crop.cropId) << '\n';
            out << "crop." << i << ".planted=" << (crop.planted ? 1 : 0) << '\n';
            out << "crop." << i << ".wateredToday=" << (crop.wateredToday ? 1 : 0) << '\n';
            out << "crop." << i << ".harvestReady=" << (crop.harvestReady ? 1 : 0) << '\n';
            out << "crop." << i << ".growthDays=" << crop.growthDays << '\n';
            out << "crop." << i << ".requiredGrowthDays=" << crop.requiredGrowthDays << '\n';
        }

        out << "worldItems.count=" << world.worldItems.size() << '\n';
        for (std::size_t i = 0; i < world.worldItems.size(); ++i) {
            const auto& item = world.worldItems[i];
            out << "worldItem." << i << ".entityId=" << item.entityId << '\n';
            out << "worldItem." << i << ".itemId=" << Escape(item.stack.itemId) << '\n';
            out << "worldItem." << i << ".quantity=" << item.stack.quantity << '\n';
            out << "worldItem." << i << ".tileX=" << item.tile.x << '\n';
            out << "worldItem." << i << ".tileY=" << item.tile.y << '\n';
            out << "worldItem." << i << ".persistent=" << (item.persistent ? 1 : 0) << '\n';
            out << "worldItem." << i << ".lifetimeSeconds=" << std::fixed << std::setprecision(3) << item.lifetimeSeconds << '\n';
        }

        out << "inventory.count=" << world.inventory.slots.size() << '\n';
        for (std::size_t i = 0; i < world.inventory.slots.size(); ++i) {
            const auto& stack = world.inventory.slots[i];
            out << "inventory." << i << ".itemId=" << Escape(stack.itemId) << '\n';
            out << "inventory." << i << ".quantity=" << stack.quantity << '\n';
        }

        return true;
    }

    static std::optional<WorldState> LoadFromFile(const std::filesystem::path& path, std::string* errorOut = nullptr) {
        std::ifstream in(path, std::ios::binary);
        if (!in) {
            SetError(errorOut, "Could not open save file.");
            return std::nullopt;
        }

        std::string line;
        if (!std::getline(in, line) || line != "ATLAS_WORLD_SAVE_V1") {
            SetError(errorOut, "Invalid save header.");
            return std::nullopt;
        }

        WorldState world;
        std::vector<std::string> lines;
        while (std::getline(in, line)) {
            if (!line.empty()) {
                lines.push_back(line);
            }
        }

        try {
            world.saveVersion = static_cast<std::uint32_t>(GetInt(lines, "saveVersion"));
            world.saveName = Unescape(GetString(lines, "saveName"));
            world.clock.dayNumber = GetInt64(lines, "clock.day");
            world.clock.minuteOfDay = static_cast<std::int32_t>(GetInt(lines, "clock.minute"));
            world.clock.timeScale = GetDouble(lines, "clock.timeScale");
            world.clock.paused = GetInt(lines, "clock.paused") != 0;

            const int cropCount = GetInt(lines, "crops.count");
            world.crops.reserve(static_cast<std::size_t>(cropCount));
            for (int i = 0; i < cropCount; ++i) {
                CropTileState crop;
                crop.tile.x = GetInt(lines, Prefix(i, "crop", ".tileX"));
                crop.tile.y = GetInt(lines, Prefix(i, "crop", ".tileY"));
                crop.cropId = Unescape(GetString(lines, Prefix(i, "crop", ".cropId")));
                crop.planted = GetInt(lines, Prefix(i, "crop", ".planted")) != 0;
                crop.wateredToday = GetInt(lines, Prefix(i, "crop", ".wateredToday")) != 0;
                crop.harvestReady = GetInt(lines, Prefix(i, "crop", ".harvestReady")) != 0;
                crop.growthDays = GetInt(lines, Prefix(i, "crop", ".growthDays"));
                crop.requiredGrowthDays = GetInt(lines, Prefix(i, "crop", ".requiredGrowthDays"));
                world.crops.push_back(crop);
            }

            const int worldItemCount = GetInt(lines, "worldItems.count");
            world.worldItems.reserve(static_cast<std::size_t>(worldItemCount));
            for (int i = 0; i < worldItemCount; ++i) {
                WorldItemEntity item;
                item.entityId = static_cast<std::uint64_t>(GetInt64(lines, Prefix(i, "worldItem", ".entityId")));
                item.stack.itemId = Unescape(GetString(lines, Prefix(i, "worldItem", ".itemId")));
                item.stack.quantity = GetInt(lines, Prefix(i, "worldItem", ".quantity"));
                item.tile.x = GetInt(lines, Prefix(i, "worldItem", ".tileX"));
                item.tile.y = GetInt(lines, Prefix(i, "worldItem", ".tileY"));
                item.persistent = GetInt(lines, Prefix(i, "worldItem", ".persistent")) != 0;
                item.lifetimeSeconds = GetDouble(lines, Prefix(i, "worldItem", ".lifetimeSeconds"));
                world.worldItems.push_back(item);
            }

            const int inventoryCount = GetInt(lines, "inventory.count");
            world.inventory.slots.reserve(static_cast<std::size_t>(inventoryCount));
            for (int i = 0; i < inventoryCount; ++i) {
                ItemStack stack;
                stack.itemId = Unescape(GetString(lines, Prefix(i, "inventory", ".itemId")));
                stack.quantity = GetInt(lines, Prefix(i, "inventory", ".quantity"));
                world.inventory.slots.push_back(stack);
            }
        } catch (const std::exception& ex) {
            SetError(errorOut, ex.what());
            return std::nullopt;
        }

        return world;
    }

private:
    static std::string Escape(const std::string& value) {
        std::string out;
        out.reserve(value.size());
        for (const char c : value) {
            switch (c) {
                case '\\': out += "\\\\"; break;
                case '\n': out += "\\n"; break;
                case '=': out += "\\e"; break;
                default: out += c; break;
            }
        }
        return out;
    }

    static std::string Unescape(const std::string& value) {
        std::string out;
        out.reserve(value.size());
        bool escape = false;
        for (const char c : value) {
            if (!escape) {
                if (c == '\\') {
                    escape = true;
                } else {
                    out += c;
                }
            } else {
                switch (c) {
                    case '\\': out += '\\'; break;
                    case 'n': out += '\n'; break;
                    case 'e': out += '='; break;
                    default: out += c; break;
                }
                escape = false;
            }
        }
        if (escape) {
            out += '\\';
        }
        return out;
    }

    static std::string Prefix(int index, const std::string& section, const std::string& suffix) {
        return section + "." + std::to_string(index) + suffix;
    }

    static std::string GetString(const std::vector<std::string>& lines, const std::string& key) {
        const std::string prefix = key + "=";
        for (const auto& line : lines) {
            if (line.rfind(prefix, 0) == 0) {
                return line.substr(prefix.size());
            }
        }
        throw std::runtime_error("Missing key: " + key);
    }

    static int GetInt(const std::vector<std::string>& lines, const std::string& key) {
        return std::stoi(GetString(lines, key));
    }

    static std::int64_t GetInt64(const std::vector<std::string>& lines, const std::string& key) {
        return std::stoll(GetString(lines, key));
    }

    static double GetDouble(const std::vector<std::string>& lines, const std::string& key) {
        return std::stod(GetString(lines, key));
    }

    static void SetError(std::string* errorOut, const std::string& value) {
        if (errorOut != nullptr) {
            *errorOut = value;
        }
    }
};

} // namespace atlas
