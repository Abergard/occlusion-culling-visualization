#include "FpsCounter.hpp"

#include <vlCore/Time.hpp>

namespace ocv
{
void FpsCounter::update()
{
    if (vl::Time::currentTime() - lastTimePoint > 0.500f)
    {
        double secs = (vl::Time::currentTime() - lastTimePoint);
        fps = frameCount / secs;
        frameCount = 0;
        lastTimePoint = vl::Time::currentTime();
    }
    frameCount++;
}

double FpsCounter::get() const
{
    return fps;
}
}
