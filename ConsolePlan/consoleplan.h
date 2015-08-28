#ifndef CONSOLEPLAN_H
#define CONSOLEPLAN_H

#include <QObject>
#include <QList>
#include <QHash>
//#include <QStringList>
#include <QLoggingCategory>
#include "consoleplan_global.h"
#include "variable.h"

Q_DECLARE_LOGGING_CATEGORY(PlanGenerator)

class CONSOLEPLANSHARED_EXPORT ConsolePlan : public QObject
{
    Q_OBJECT

public:
    ConsolePlan(QObject* parent = 0);

    enum PlanError
    {
        NoError,
        ErrorNoSuchPlane,
        ErrorOverwriteExistingPlane,
        ErrorPlaneNoSuchSpot,
        ErrorSuchSpotExists,
        ErrorNoSpot,
        ErrorNotEnoughSonicationParameter
    };

    enum Action
    {
        AddPlane,
        RemovePlane,
        AddSpot,
        RemoveSpot,
        AddSpots,
        RemoveSpots,
        MoveSpot
    };

    bool addPlane(float angle,QList<Plane2DCoordinate> coordinates);
    bool removePlane(float angle);

    bool addSpot(float angle,Plane2DCoordinate coordinate);
    bool removeSpot(float angle,Plane2DCoordinate coordinate);

    //  TODO: move the single spot in the specified
    bool moveSpot(float angle,Plane2DCoordinate coordinate);

    bool addSpots(float angle, QList<Plane2DCoordinate> coordinates);
    bool removeSpots(float angle,QList<Plane2DCoordinate> coordinates);

    void getPlaneSpots();
    void getSpots();

    void setSpotOrder(float angle, QList<int> order);
    QHash<float,QList<int> > getSpotOrder();

    void setSonicationParam(SpotSonicationParameter param);
    SpotSonicationParameter getSonicationParam();

signals:
    void error(PlanError);
    void updatePlaneSpots(QHash<float,QList<Plane2DCoordinate> >);
    void updateSpots(QHash<float,QList<Spot3DCoordinate> >);

private:
    QHash<float,QList<Plane2DCoordinate> > m_planeSpots;
    QHash<float,QList<Spot3DCoordinate> > m_spots;
    QHash<float,QList<int> > m_spotOrder;
    SpotSonicationParameter m_sonicationParam;

    QStringList m_errorString;
    QStringList m_actionString;

    QList<Spot3DCoordinate> transferCoordinate(float, QList<Plane2DCoordinate>);
    int containSpot(QList<Plane2DCoordinate>, Plane2DCoordinate);
    void resetSonicationParam();
    void setErrorString();
    void setActionString();
    QString printLastAction(Action);
    QString printLastError(PlanError);
};

#endif // CONSOLEPLAN_H
