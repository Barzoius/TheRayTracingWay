#ifndef RANGE_HPP
#define RANGE_HPP

class range
{
public:
    double min, max;

    range() : min(+INF), max(-INF) {}

    range(double min, double max) : min(min), max(max) {}

    double size() const 
    {
        return max - min;
    }

    bool contains(double x) const {
        return min <= x && x <= max;
    }

    bool surrounds(double x) const {
        return min < x && x < max;
    }

    static const range empty, universe;
};

const range range::empty    = range(+INF, -INF);
const range range::universe = range(-INF, +INF);

#endif