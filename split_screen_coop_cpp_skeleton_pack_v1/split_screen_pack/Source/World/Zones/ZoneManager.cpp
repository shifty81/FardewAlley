#include "ZoneManager.h"

namespace atlas
{
    void ZoneManager::Initialize()
    {
    }

    void ZoneManager::Update(float)
    {
        // TODO: zone streaming, coarse tick for unloaded zones, per-zone entity activation.
    }

    bool ZoneManager::CanTransition(const ZoneTransition& transition, bool allPlayersReady) const
    {
        if (transition.requirement == TransitionRequirement::AllPlayersReady)
        {
            return allPlayersReady;
        }

        return true;
    }
}
