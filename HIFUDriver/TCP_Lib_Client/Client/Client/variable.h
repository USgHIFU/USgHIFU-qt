#ifndef VARIABLE
#define VARIABLE

#define Coordinate float

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

struct SessionRecorder
{
    int spotIndex;
    int periodIndex;
};

struct SessionParameter
{
    int spotCount;
    int periodCount;
    int dutyOn;
    int dutyOff;
    int coolingTime;
};

#endif // VARIABLE

