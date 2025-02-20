//
// Created by ryen on 12/23/24.
//

#pragma once

#include <cstdint>

namespace ME::time {
    class TimeSystem {
        private:
        double elapsed;
        double delta;
        double scale;
        uint64_t id;

        unsigned long int lastChecked;

        public:
        TimeSystem();

        inline double GetElapsed() const { return elapsed; }
        inline double GetDelta() const { return delta; }
        inline double GetScale() const { return scale; }
        inline void SetScale(const double value) { scale = value; }
        inline uint64_t GetID() const { return id; }

        void Update();
        void Reset();
    };
}
