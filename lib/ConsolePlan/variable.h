#ifndef VARIABLE
#define VARIABLE

#define Coordinate float

struct Plane2DCoordinate
{
    Coordinate x;
    Coordinate y;
};

struct Spot3DCoordinate
{
    Coordinate x;
    Coordinate y;
    Coordinate z;
};

struct SpotSonicationParameter
{
    float volt;
    int totalTime;
    int period;
    int dutyCycle;
    int coolingTime;
};

#endif // VARIABLE

