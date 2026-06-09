#pragma once

#include <chrono>
#include <optional>

namespace plotter {

    /**
     * Класс для замера времени
     */
    class Timer {
    public:
        using Clock = std::chrono::steady_clock;

        /**
         * @brief  Конструктор.
         * @param start Запустить таймер при вызове конструктора?
         */
        explicit Timer(bool start = false)
            : start_time_(std::nullopt)
            , stop_time_(std::nullopt)
        {
            if (start) {
                start_time_ = Clock::now();
            }
        }

        /**
         * @brief Запускает таймер.
         * @note Вызывать, если таймер не запущен.
         */
        void Start();

        /**
         * @brief Останавливает таймер.
         * @note Вызывать, если таймер запущен.
         */
        void Stop();

        /**
         * @brief Сбрасывает время и перезапускает таймер.
         */
        void Restart();

        /**
         * @brief Возвращает замеренное время.
         * @return Время замеренное таймером в микросекундах.
         */
        [[nodiscard]] long long GetDuration() const;

    private:
        std::optional<Clock::time_point> start_time_;
        std::optional<Clock::time_point> stop_time_;
    };

}
