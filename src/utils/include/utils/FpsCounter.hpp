#pragma once

namespace ocv
{
class FpsCounter
{
public:
    void update();
    double get() const;

private:
    double lastTimePoint{0};
    double fps{0};
    int frameCount{0};
};
}
