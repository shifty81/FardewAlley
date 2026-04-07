#include "TimeSystem/TimeSystem.hpp"

#include <algorithm>
#include <iomanip>
#include <sstream>
#include <stdexcept>

namespace TimeSystem {

namespace {
constexpr int kMinutesPerHour = 60;

bool IsValidMinute(int minute, int minutesPerDay) {
    return minute >= 0 && minute < minutesPerDay;
}
} // namespace

WorldClock::WorldClock(TimeConfig config)
    : config_(config) {
    if (config_.minutesPerDay <= 0) {
        throw std::invalid_argument("minutesPerDay must be positive");
    }
    if (config_.realtimeSecondsPerGameMinute <= 0.0) {
        throw std::invalid_argument("realtimeSecondsPerGameMinute must be positive");
    }
    stamp_.dayIndex = 1;
    stamp_.minuteOfDay = std::clamp(config_.sunriseMinute, 0, config_.minutesPerDay - 1);
}

const TimeConfig& WorldClock::GetConfig() const {
    return config_;
}

const ClockStamp& WorldClock::GetStamp() const {
    return stamp_;
}

void WorldClock::SetPaused(bool paused) {
    paused_ = paused;
}

bool WorldClock::IsPaused() const {
    return paused_;
}

void WorldClock::SetTimeScale(double scale) {
    if (scale <= 0.0) {
        throw std::invalid_argument("time scale must be positive");
    }
    timeScale_ = scale;
}

double WorldClock::GetTimeScale() const {
    return timeScale_;
}

void WorldClock::SetStamp(const ClockStamp& stamp) {
    if (stamp.dayIndex <= 0) {
        throw std::invalid_argument("dayIndex must be >= 1");
    }
    if (!IsValidMinute(stamp.minuteOfDay, config_.minutesPerDay)) {
        throw std::invalid_argument("minuteOfDay out of range");
    }
    stamp_ = stamp;
    ResetDailyEvents();
    CheckAndQueueDailyEvents();
}

TickResult WorldClock::TickRealtime(double deltaSeconds) {
    TickResult result;
    if (paused_ || deltaSeconds <= 0.0) {
        return result;
    }

    accumulatedRealtimeSeconds_ += deltaSeconds * timeScale_;
    const double secondsPerGameMinute = config_.realtimeSecondsPerGameMinute;

    while (accumulatedRealtimeSeconds_ >= secondsPerGameMinute) {
        accumulatedRealtimeSeconds_ -= secondsPerGameMinute;
        AdvanceSingleMinute(result);
    }

    return result;
}

TickResult WorldClock::AdvanceGameMinutes(int deltaMinutes) {
    TickResult result;
    if (deltaMinutes <= 0) {
        return result;
    }

    for (int i = 0; i < deltaMinutes; ++i) {
        AdvanceSingleMinute(result);
    }
    return result;
}

DayPhase WorldClock::GetDayPhase() const {
    const int minute = stamp_.minuteOfDay;

    if (minute < config_.sunriseMinute) {
        return DayPhase::Night;
    }
    if (minute < config_.morningMinute) {
        return DayPhase::Dawn;
    }
    if (minute < config_.noonMinute) {
        return DayPhase::Morning;
    }
    if (minute < config_.afternoonMinute) {
        return DayPhase::Noon;
    }
    if (minute < config_.sunsetMinute) {
        return DayPhase::Afternoon;
    }
    if (minute < config_.nightMinute) {
        return DayPhase::Dusk;
    }
    return DayPhase::Night;
}

std::string WorldClock::FormatTime24h() const {
    const int hour = stamp_.minuteOfDay / kMinutesPerHour;
    const int minute = stamp_.minuteOfDay % kMinutesPerHour;

    std::ostringstream stream;
    stream << std::setw(2) << std::setfill('0') << hour
           << ':'
           << std::setw(2) << std::setfill('0') << minute;
    return stream.str();
}

std::string WorldClock::FormatStamp() const {
    std::ostringstream stream;
    stream << "Day " << stamp_.dayIndex << " " << FormatTime24h();
    return stream.str();
}

bool WorldClock::IsWithinWindow(const ScheduleWindow& window) const {
    if (window.startMinuteInclusive == window.endMinuteExclusive) {
        return true;
    }
    if (window.startMinuteInclusive < window.endMinuteExclusive) {
        return stamp_.minuteOfDay >= window.startMinuteInclusive &&
               stamp_.minuteOfDay < window.endMinuteExclusive;
    }
    return stamp_.minuteOfDay >= window.startMinuteInclusive ||
           stamp_.minuteOfDay < window.endMinuteExclusive;
}

void WorldClock::RegisterDailyEvent(const DailyEvent& eventDef) {
    dailyEvents_.push_back(eventDef);
    CheckAndQueueDailyEvents();
}

std::vector<std::string> WorldClock::ConsumeTriggeredEvents() {
    std::vector<std::string> out;
    out.swap(triggeredEvents_);
    return out;
}

double WorldClock::GetNormalizedDayProgress() const {
    return static_cast<double>(stamp_.minuteOfDay) /
           static_cast<double>(config_.minutesPerDay);
}

void WorldClock::AdvanceSingleMinute(TickResult& result) {
    const int previousMinute = stamp_.minuteOfDay;
    const int previousHour = previousMinute / kMinutesPerHour;

    stamp_.minuteOfDay += 1;
    result.crossedMinute = true;
    result.crossedMinuteCount += 1;

    if (stamp_.minuteOfDay >= config_.minutesPerDay) {
        stamp_.minuteOfDay = 0;
        stamp_.dayIndex += 1;
        result.crossedDay = true;
        result.crossedDayCount += 1;
        ResetDailyEvents();
    }

    const int currentHour = stamp_.minuteOfDay / kMinutesPerHour;
    if (currentHour != previousHour || result.crossedDay) {
        result.crossedHour = true;
        result.crossedHourCount += 1;
    }

    (void)previousMinute;
    CheckAndQueueDailyEvents();
}

void WorldClock::ResetDailyEvents() {
    for (auto& eventDef : dailyEvents_) {
        eventDef.hasFiredToday = false;
    }
}

void WorldClock::CheckAndQueueDailyEvents() {
    for (auto& eventDef : dailyEvents_) {
        const bool minuteMatch = (eventDef.triggerMinute == stamp_.minuteOfDay);
        if (!minuteMatch) {
            continue;
        }
        if (!eventDef.recurring && eventDef.hasFiredToday) {
            continue;
        }
        if (eventDef.hasFiredToday) {
            continue;
        }
        eventDef.hasFiredToday = true;
        triggeredEvents_.push_back(eventDef.id);
    }
}

} // namespace TimeSystem
