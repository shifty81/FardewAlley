#pragma once

#include <cstdint>
#include <optional>
#include <string>
#include <vector>

namespace TimeSystem {

enum class DayPhase {
    Night,
    Dawn,
    Morning,
    Noon,
    Afternoon,
    Dusk
};

struct TimeConfig {
    int minutesPerDay = 1440;
    int sunriseMinute = 360;   // 06:00
    int morningMinute = 480;   // 08:00
    int noonMinute = 720;      // 12:00
    int afternoonMinute = 780; // 13:00
    int sunsetMinute = 1080;   // 18:00
    int nightMinute = 1200;    // 20:00
    double realtimeSecondsPerGameMinute = 1.0;
};

struct ClockStamp {
    int dayIndex = 1;
    int minuteOfDay = 360;
};

struct TickResult {
    bool crossedMinute = false;
    bool crossedHour = false;
    bool crossedDay = false;
    int crossedMinuteCount = 0;
    int crossedHourCount = 0;
    int crossedDayCount = 0;
};

struct ScheduleWindow {
    int startMinuteInclusive = 0;
    int endMinuteExclusive = 0;
};

struct DailyEvent {
    std::string id;
    int triggerMinute = 360;
    bool recurring = true;
    bool hasFiredToday = false;
};

class WorldClock {
public:
    explicit WorldClock(TimeConfig config = {});

    const TimeConfig& GetConfig() const;
    const ClockStamp& GetStamp() const;

    void SetPaused(bool paused);
    bool IsPaused() const;

    void SetTimeScale(double scale);
    double GetTimeScale() const;

    void SetStamp(const ClockStamp& stamp);
    TickResult TickRealtime(double deltaSeconds);
    TickResult AdvanceGameMinutes(int deltaMinutes);

    DayPhase GetDayPhase() const;
    std::string FormatTime24h() const;
    std::string FormatStamp() const;
    bool IsWithinWindow(const ScheduleWindow& window) const;

    void RegisterDailyEvent(const DailyEvent& eventDef);
    std::vector<std::string> ConsumeTriggeredEvents();

    double GetNormalizedDayProgress() const;

private:
    void AdvanceSingleMinute(TickResult& result);
    void ResetDailyEvents();
    void CheckAndQueueDailyEvents();

    TimeConfig config_;
    ClockStamp stamp_{};
    bool paused_ = false;
    double timeScale_ = 1.0;
    double accumulatedRealtimeSeconds_ = 0.0;
    std::vector<DailyEvent> dailyEvents_;
    std::vector<std::string> triggeredEvents_;
};

} // namespace TimeSystem
