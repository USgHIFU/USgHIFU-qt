#ifndef DEFINE_TYPE
#define DEFINE_TYPE

#define VOLTAGE 14
#define MS_UNIT 1000
#define PERCENT_UNIT 100
#define TEST_SPOT_COUNT 20

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

struct SpotSonicationParam
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

struct SessionParam
{
    int spotCount;
    int periodCount;
    int dutyOn;
    int dutyOff;
    int coolingTime;
};

#endif // DEFINE_TYPE

