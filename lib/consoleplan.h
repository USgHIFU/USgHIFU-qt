#ifndef CONSOLEPLAN_H
#define CONSOLEPLAN_H

#include "consoleplan_global.h"
#include "define_type.h"
#include <QObject>
#include <QList>
#include <QHash>

class CONSOLEPLANSHARED_EXPORT ConsolePlan : public QObject
{
    Q_OBJECT

public:
    ConsolePlan(QObject* parent = 0);
    enum PlanError
    {
        NoError,
        ErrorNoPlane,
        ErrorPlaneNoSpot,
        ErrorNoSpot,
        ErrorNotEnoughSonicationParameter
    };

    bool addPlane(float angle,QList<Plane2DCoordinate> coordinate);
    bool removePlane(float angle);

    bool addSpotInPlane(float angle,Plane2DCoordinate coordinate);
    bool removeSpotInPlane(float angle,Plane2DCoordinate coordinate);

    bool addSpotsInPlane(float angle, QList<Plane2DCoordinate> coordinates);
    bool removeSpotsInPlane(float angle,QList<Plane2DCoordinate> coordinates);

    QHash<float,QList<Plane2DCoordinate> > getPlane();
    QHash<float,QList<Spot3DCoordinate> > getSpot();
    void setSpotOrder(float angle, QList<int> order);
    QHash<float,QList<int> > getSpotOrder();
    void setSonicationParam(QString key, int value);
    QHash<QString,int> getSonicationParam();

signals:
    void error(PlanError);

private:
    QHash<float,QList<Plane2DCoordinate> > m_plane;
    QHash<float,QList<Spot3DCoordinate> > m_spot;
    QHash<float,QList<int> > m_spotOrder;
    QHash<QString,int> m_sonicationParam;

    QList<Spot3DCoordinate> transferCoordinate(float, QList<Plane2DCoordinate>);
    int containSpotInPlane(QList<Plane2DCoordinate>, Plane2DCoordinate);
    QHash<QString,int> resetSonicationParam();

};

#endif // CONSOLEPLAN_H
