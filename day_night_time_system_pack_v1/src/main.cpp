#include "TimeSystem/TimeSystem.hpp"

#include <iostream>
#include <string>
#include <vector>

using namespace TimeSystem;

static std::string ToString(DayPhase phase) {
    switch (phase) {
        case DayPhase::Night: return "Night";
        case DayPhase::Dawn: return "Dawn";
        case DayPhase::Morning: return "Morning";
        case DayPhase::Noon: return "Noon";
        case DayPhase::Afternoon: return "Afternoon";
        case DayPhase::Dusk: return "Dusk";
    }
    return "Unknown";
}

static void PrintEvents(WorldClock& clock) {
    for (const auto& eventId : clock.ConsumeTriggeredEvents()) {
        std::cout << "  Event Triggered: " << eventId << '\n';
    }
}

int main() {
    TimeConfig config;
    config.realtimeSecondsPerGameMinute = 0.05;

    WorldClock clock(config);
    clock.SetStamp({1, 350});
    clock.RegisterDailyEvent({"CropGrowthTick", 360, true, false});
    clock.RegisterDailyEvent({"ShopOpen", 540, true, false});
    clock.RegisterDailyEvent({"NightSettlementPass", 1200, true, false});

    std::cout << "Initial: " << clock.FormatStamp()
              << " Phase=" << ToString(clock.GetDayPhase()) << '\n';

    const TickResult preDawn = clock.AdvanceGameMinutes(15);
    std::cout << "After 15 minutes: " << clock.FormatStamp()
              << " Phase=" << ToString(clock.GetDayPhase())
              << " MinuteCrossings=" << preDawn.crossedMinuteCount
              << " HourCrossings=" << preDawn.crossedHourCount << '\n';
    PrintEvents(clock);

    const TickResult dayAdvance = clock.AdvanceGameMinutes(190);
    std::cout << "After 190 minutes: " << clock.FormatStamp()
              << " Phase=" << ToString(clock.GetDayPhase())
              << " MinuteCrossings=" << dayAdvance.crossedMinuteCount
              << " HourCrossings=" << dayAdvance.crossedHourCount << '\n';
    PrintEvents(clock);

    clock.SetPaused(false);
    clock.SetTimeScale(4.0);
    for (int i = 0; i < 25; ++i) {
        clock.TickRealtime(0.05);
    }

    std::cout << "After realtime ticks: " << clock.FormatStamp()
              << " Phase=" << ToString(clock.GetDayPhase()) << '\n';
    PrintEvents(clock);

    const TickResult overnight = clock.AdvanceGameMinutes(900);
    std::cout << "After overnight advance: " << clock.FormatStamp()
              << " Phase=" << ToString(clock.GetDayPhase())
              << " DayCrossings=" << overnight.crossedDayCount << '\n';
    PrintEvents(clock);

    ScheduleWindow cropWindow{360, 1080};
    std::cout << "Crop work window active: "
              << (clock.IsWithinWindow(cropWindow) ? "yes" : "no") << '\n';

    std::cout << "Normalized day progress: "
              << clock.GetNormalizedDayProgress() << '\n';

    return 0;
}
