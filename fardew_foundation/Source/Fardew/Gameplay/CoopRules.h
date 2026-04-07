#pragma once

#include "PlayerState.h"
#include <array>
#include <optional>

namespace Fardew
{
    constexpr std::size_t kMaxLocalPlayers = 2;

    enum class SplitScreenLayout : std::uint8_t
    {
        Fullscreen,
        HorizontalTwoPlayer
    };

    struct CoopSessionState
    {
        std::array<std::optional<PlayerState>, kMaxLocalPlayers> Players;
        SplitScreenLayout Layout = SplitScreenLayout::Fullscreen;
        bool SharedModalOpen = false;
    };

    class CoopRulesService
    {
    public:
        void RefreshLayout(CoopSessionState& session) const;
        [[nodiscard]] bool CanOpenSharedModal(const CoopSessionState& session, PlayerId requestingPlayerId) const;
        [[nodiscard]] bool TryJoin(CoopSessionState& session, const PlayerState& templateState) const;
    };
}
