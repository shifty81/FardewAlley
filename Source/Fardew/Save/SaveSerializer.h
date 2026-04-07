#pragma once

#include "SaveGame.h"

namespace Fardew
{
    class SaveSerializer
    {
    public:
        [[nodiscard]] std::string Serialize(const SaveGame& save) const;
    };
}
