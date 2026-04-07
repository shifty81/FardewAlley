#include "CoopRules.h"

namespace Fardew
{
    void CoopRulesService::RefreshLayout(CoopSessionState& session) const
    {
        int activePlayers = 0;
        for (const auto& player : session.Players)
        {
            if (player.has_value())
            {
                ++activePlayers;
            }
        }
        session.Layout = activePlayers > 1 ? SplitScreenLayout::HorizontalTwoPlayer : SplitScreenLayout::Fullscreen;
    }

    bool CoopRulesService::CanOpenSharedModal(const CoopSessionState& session, PlayerId requestingPlayerId) const
    {
        for (const auto& player : session.Players)
        {
            if (player.has_value() && player->Id == requestingPlayerId)
            {
                return player->Viewport.IsHost && !session.SharedModalOpen;
            }
        }
        return false;
    }

    bool CoopRulesService::TryJoin(CoopSessionState& session, const PlayerState& templateState) const
    {
        for (auto& slot : session.Players)
        {
            if (!slot.has_value())
            {
                slot = templateState;
                RefreshLayout(session);
                return true;
            }
        }
        return false;
    }
}
