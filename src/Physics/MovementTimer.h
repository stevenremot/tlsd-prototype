#ifndef PHYSICS_MOVEMENTTIMER_H
#define PHYSICS_MOVEMENTTIMER_H

namespace Physics
{
    class MovementTimer
    {
        public:
            MovementTimer():
                lastTime_(0),
                currentTime_(0),
                delay_(0)
                {}

            void updateCurrentTime();
            void updateLastTime();

            unsigned long getLastTime() const;
            unsigned long getDelay() const;

        private:
            unsigned long lastTime_, currentTime_, delay_;
    };
}

#endif // PHYSICS_MOVEMENTTIMER_H
