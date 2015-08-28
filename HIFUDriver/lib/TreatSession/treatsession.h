#ifndef TREATSESSION_H
#define TREATSESSION_H

class QTimer;

#include <QObject>
#include <QHash>
#include <QList>
#include <QLoggingCategory>
#include <QStringList>
#include "variable.h"
#include "constant.h"
#include "poweramp.h"
#include "docontroller.h"
#include "treatsession_global.h"


Q_DECLARE_LOGGING_CATEGORY(Session)

class TREATSESSIONSHARED_EXPORT TreatSession : public QObject
{
    Q_OBJECT

public:
    TreatSession(QObject* parent = 0);
//    ~TreatSession();

    enum SessionType
    {
        ON,
        OFF,
        COOLING
    };

    enum SessionError
    {
        NoError
    };

//  TODO: get spots of different planes
    void setSpots(QHash<float,QList<Spot3DCoordinate> > spots);
//    QList<Spot3DCoordinate> getSpot();

    void setSonicationParam(SpotSonicationParameter params);
//    SpotSonicationParam getSonicationParam();

    SessionRecorder getRecorder();

    void start();
    void stop();
    void pause();
    void resume();

    void testPA();
    void testDOController();

public slots:

signals:

private slots:
    void timeoutFcn();

private:
    //  data from the receiver
    QHash<float,QList<Spot3DCoordinate> > m_spots;
    QHash<float,QList<int> > m_spotOrder;
    SpotSonicationParameter m_sonicationParam;
    float m_currPlane;

    //  the parameters used for the treat session
    SessionParameter m_sessionParam;
    SessionRecorder m_recorder;
    SessionType m_currType;



    QTimer* m_timer;
    QStringList m_actionString;
    QStringList m_errorString;

    PowerAmp* m_pa;
    DOController* m_do;

    void onDuty();
    void offDuty();
    void cooling();

    void changeSpot();
    void resetSessionRecorder();

    void setActionString();
    void setErrorString();
    QString printLastAction(cmdType);
    QString printLastError(SessionError);
};

#endif // TREATSESSION_H
