#pragma once

#include "ZoneTransition.h"

namespace atlas
{
    class ZoneManager
    {
    public:
        void Initialize();
        void Update(float dt);

        bool CanTransition(const ZoneTransition& transition, bool allPlayersReady) const;

    private:
        // TODO: active zone registry, tilemaps, entity lists, zone activation policy.
    };
}
