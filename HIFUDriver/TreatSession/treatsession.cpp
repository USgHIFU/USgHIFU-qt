#include <QTimer>
#include "treatsession.h"
#include "header.h"
#include "phaseinfo.c"

Q_LOGGING_CATEGORY(Session,"TREAT SESSION")

TreatSession::TreatSession(QObject *parent) : QObject(parent)
{
    m_pa = new PowerAmp(this);
    m_do = new DOController(this);

    resetSessionRecorder();
    setActionString();
    setErrorString();

    // used for testing here
    m_sessionParam.spotCount = TEST_SPOT_COUNT;

    m_timer = new QTimer(this);
    m_timer->setSingleShot(true);
    connect(m_timer,SIGNAL(timeout()),this,SLOT(timeoutFcn()));
}

void TreatSession::setSpots(QHash<float,QList<Spot3DCoordinate> > spots)
{
    m_spots.clear();
    QHash<float,QList<Spot3DCoordinate> >::iterator i;
    for (i=spots.begin();i!=spots.end();i++)
    {
        m_spots.insert(i.key(),i.value());
        m_currPlane = i.key();
        m_sessionParam.spotCount = i.value().count();
    }
}

//QList<Spot3DCoordinate> ServerPlan::getSpotCoordinate()
//{
//    return m_spotCoordinate;
//}

void TreatSession::setSonicationParam(SpotSonicationParameter params)
{
    m_sonicationParam.volt = params.volt;
    m_sonicationParam.totalTime = params.totalTime;
    m_sonicationParam.period = params.period;
    m_sonicationParam.dutyCycle = params.dutyCycle;
    m_sonicationParam.coolingTime = params.coolingTime;

    //  converted into session parameters
    m_sessionParam.dutyOn = params.period * params.dutyCycle / PERCENT_UNIT;
    m_sessionParam.dutyOff = params.period - m_sessionParam.dutyOn;
    m_sessionParam.periodCount = params.totalTime * MS_UNIT / m_sessionParam.dutyOn;
    m_sessionParam.coolingTime = params.coolingTime * MS_UNIT;

    //  TEST CODES
//    qDebug() << m_sessionParam.spotCount <<
//                m_sessionParam.dutyOn <<
//                m_sessionParam.dutyOff <<
//                m_sessionParam.periodCount <<
//                m_sessionParam.coolingTime;
}

//SpotSonicationParam ServerPlan::getSonicationParam()
//{
//    return m_sonicationParam;
//}

void TreatSession::start()
{
    //  TODO: fix the type of variable of volt (double => float)
    //  start the power amplifiers
        changeSpot();
//        m_pa->startAllPowerAmp((double)m_sonicationParam.volt);
    //  TODO: display the status
    //  finish

    //  start the treat session with the first spot in the plan


    m_currType = ON;

    m_do->enableDO();

    //  deliver the acoustic energy at a given spot

    m_timer->start(m_sessionParam.dutyOn);

//    qCWarning(STARTPA()) << STARTPA().categoryName()
//                              << printLastAction(START)+printLastError(NoError);

//    qCWarning(STARTPA()) << "==============================================";
}

void TreatSession::onDuty()
{
    m_currType = OFF;
    //  stop delivering the acoustic energy here
    m_do->disableDO();

    m_timer->start(m_sessionParam.dutyOff);
}

void TreatSession::offDuty()
{
    m_recorder.periodIndex++;

    qDebug() << "Period #" << m_recorder.periodIndex;

//    qCDebug(Session()) << Session().categoryName()
//                            << "The #" << m_recorder.periodIndex
//                            << " duty is finished.";

    if (m_recorder.periodIndex < m_sessionParam.periodCount)
    {
        m_currType = ON;
        //  deliver the acoustic energy here at the same spot
        m_do->enableDO();

        m_timer->start(m_sessionParam.dutyOn);
    }else
    {
        m_recorder.spotIndex++;
        m_recorder.periodIndex = 0;

        m_currType = COOLING;
        //  deliver a cooling period here
        m_do->disableDO();

        m_timer->start(m_sessionParam.coolingTime);
        changeSpot();
    }
}

void TreatSession::cooling()
{
//    qCDebug(Session()) << Session().categoryName()
//                            << "The #" << m_recorder.spotIndex
//                            << " spot is finished.";
//    qCDebug(Session()) << "==============================================";

    qDebug() << "Spot #" << m_recorder.spotIndex;

    if (m_recorder.spotIndex < m_sessionParam.spotCount)
    {
        // start delivering the acoustic energy at the next spot

        m_currType = ON;
        m_do->enableDO();
        m_timer->start(m_sessionParam.dutyOn);
    }else
    {
        // finish the current session

//        qCDebug(Session()) << Session().categoryName()
//                                << "All the spots have been sonicated.";
//        qCDebug(Session()) << "==========================================";

        qDebug() << "All the spots have been sonicated.";

        resetSessionRecorder();
    }
}

void TreatSession::timeoutFcn()
{
    switch (m_currType)
    {
    case ON:
        onDuty();
//        qCDebug(Session()) << Session().categoryName()
//                                << "status: finish the stage of duty on.";
        qDebug() << "status: finish the stage of duty on.";
        break;
    case OFF:
        offDuty();
//        qCDebug(Session()) << Session().categoryName()
//                                << "status: finish the stage of duty off.";
        qDebug() << "status: finish the stage of duty off.";
        break;
    case COOLING:
        cooling();
//        qCDebug(Session()) << Session().categoryName()
//                                << "status: finish the stage of cooling.";
        qDebug() << "status: finish the stage of cooling.";
        break;
    }
}

void TreatSession::stop()
{
    //  stop delivering the acoustic energy
    m_do->disableDO();
    if (m_timer->isActive())
    {
        m_timer->stop();
    }

//    m_pa->resetAllPowerAmp();

//    qCWarning(STARTPA()) << STARTPA().categoryName()
//                              << printLastAction(STOP)+printLastError(NoError);
//    qCWarning(Session()) << Session().categoryName()
//                              << "The spot #" << m_recorder.spotIndex
//                              << ", duty #" << m_recorder.periodIndex
//                              << " is finished.";
//    qCWarning(Session()) << "==========================================";

    //  reset the session param
    resetSessionRecorder();
}

void TreatSession::pause()
{
    // stop delivering the acoustic energy
    m_do->disableDO();
    if (m_timer->isActive())
    {
        m_timer->stop();
    }
//    qCWarning(Session()) << Session().categoryName()
//                              << printLastAction(PAUSE)+printLastError(NoError);
//    qCWarning(Session()) << Session().categoryName()
//                              << "The spot #" << m_recorder.spotIndex
//                              << ", duty #" << m_recorder.periodIndex
//                              << " is finished.";
//    qCWarning(Session()) << "==========================================";
}

void TreatSession::resume()
{
//    qCWarning(Session()) << Session().categoryName()
//                              << printLastAction(RESUME)+printLastError(NoError);
//    qCWarning(Session()) << Session().categoryName()
//                              << "The spot #" << m_recorder.spotIndex
//                              << ", duty #" << m_recorder.periodIndex
//                              << " is started, again.";
//    qCWarning(Session()) << "==========================================";

    timeoutFcn();
}

void TreatSession::resetSessionRecorder()
{
    m_recorder.periodIndex = 0;
    m_recorder.spotIndex = 0;
}

SessionRecorder TreatSession::getRecorder()
{
    return m_recorder;
}

void TreatSession::changeSpot()
{
    //  determine whether the count of spots is 0

    QList<Spot3DCoordinate> spots = m_spots.value(m_currPlane);
    if (spots.count())
    {
        float x = spots.at(0).x;
        float y = spots.at(0).y;
        float z = spots.at(0).z;
        spots.removeAt(0);
        m_spots.insert(m_currPlane,spots);
    }else
    {
        m_spots.remove(m_currPlane);
        if (m_spots.size())
        {
//            QHash<float,QList<Spot3DCoordinate> >::iterator i;
//            i = m_spots.begin();
//            m_currPlane = i.key();
            m_currPlane = m_spots.begin().key();
//            m_sessionParam.spotCount = i.value().count();
            m_sessionParam.spotCount = m_spots.begin().value().count();
            spots = m_spots.value(m_currPlane);
            float x = spots.at(0).x;
            float y = spots.at(0).y;
            float z = spots.at(0).z;
            spots.removeAt(0);
            m_spots.insert(m_currPlane,spots);
        }else
        {
            m_sessionParam.spotCount = 0;
            return;
        }
    }

    //  compute the phases for the spot
//    FocusCount num = 1;
//    real_T x = 0;
//    real_T y = 0.005;
//    real_T z = 0.14;

//    real_T volt[112];
//    real_T angle[112];

//    PhaseInfo(num,x,y,z,volt,angle);
//    qDebug() << Session().categoryName();
//    for (int i=0;i<TRANSDUCER_COUNT;i++)
//    {
//        qDebug() << "#" << i << ": " << angle[i];
        //  load the phases for the spot
//        m_do->sendPhase(i,angle[i]);
//        m_do->loadPhase();
//    }
}

void TreatSession::setActionString()
{
    m_actionString << "Start a treat session"
                   << "Stop the running treat session"
                   << "Pause the running treat session"
                   << "Resume the previous treat session";
}

void TreatSession::setErrorString()
{
    m_errorString << "Done successfully.";
}

QString TreatSession::printLastAction(cmdType iType)
{
    QString str = "ACTION: ";
    str += m_actionString[iType];
    str += " ";
    return str;
}

QString TreatSession::printLastError(SessionError i)
{
    QString str = "RESULT: ";
    str += m_errorString[i];
    return str;
}

//  for the test of PA and DOController
void TreatSession::testPA()
{
    m_pa->startAllPowerAmp(10);
}

void TreatSession::testDOController()
{
//    qDebug() << "Port number: 4, "
//             << "Value: 10";
//    m_do->writeData(4,10);

//    for (int i=0;i<144;i++)
//        {
//            m_do->sendPhase(i,quint8(3*i));
//            m_do->loadPhase();
//        }
//    m_do->enableDO();

        changeSpot();
        m_do->enableDO();
}
