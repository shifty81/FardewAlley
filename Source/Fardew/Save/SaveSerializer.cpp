#include "SaveSerializer.h"
#include <sstream>

namespace Fardew
{
    std::string SaveSerializer::Serialize(const SaveGame& save) const
    {
        std::ostringstream stream;
        stream << "{\n";
        stream << "  \"slot\": \"" << save.Meta.SlotName << "\",\n";
        stream << "  \"version\": " << save.Meta.SaveVersion << ",\n";
        stream << "  \"day\": " << save.Meta.DayOfSeason << ",\n";
        stream << "  \"clockMinutes\": " << save.Meta.ClockMinutes << "\n";
        stream << "}\n";
        return stream.str();
    }
}
