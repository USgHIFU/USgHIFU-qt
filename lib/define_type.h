#ifndef DEFINE_TYPE
#define DEFINE_TYPE

struct Plane2DCoordinate
{
    float x;
    float y;
};

struct Spot3DCoordinate
{
    float x;
    float y;
    float z;
};

struct SpotSonicationParameter
{
    float volt;
    int totalTime;
    int period;
    int dutyCycle;
    int coolingTime;
};

#endif // DEFINE_TYPE

