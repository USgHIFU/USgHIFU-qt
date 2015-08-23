#ifndef SERVERPLAN_H
#define SERVERPLAN_H

class QTimer;

#include <QObject>
#include <QList>
#include <QLoggingCategory>
#include "serverplan_global.h"
#include "define_type.h"

Q_DECLARE_LOGGING_CATEGORY(TreatmentSession)

class SERVERPLANSHARED_EXPORT ServerPlan : public QObject
{
    Q_OBJECT

public:
    ServerPlan(QObject* parent=0);

    enum Action
    {
        Start,
        Stop,
        Pause,
        Resume
    };

    enum SessionType
    {
        DutyOn,
        DutyOff,
        Cooling
    };

    void setSpotCoordinate(QList<Spot3DCoordinate>);
    QList<Spot3DCoordinate> getSpotCoordinate();

    void setSonicationParam(SpotSonicationParam);
    SpotSonicationParam getSonicationParam();

    SessionRecorder getRecorder();

    void start();
    void stop();
    void pause();
    void resume();

signals:

public slots:
    void timerFcn();

private:

    QList<Spot3DCoordinate> m_spotCoordinate;
    SpotSonicationParam m_sonicationParam;
    SessionParam m_sessionParam;
    SessionRecorder m_recorder;
    SessionType m_currentType;

    QTimer* m_timer;

    void powerDutyOn();
    void powerDutyOff();
    void powerCooling();

    void changeSpot();

    void resetSessionRecorder();
};

#endif // SERVERPLAN_H
