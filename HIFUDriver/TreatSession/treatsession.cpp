#include "treatsession.h"
#include "header.h"
#include "phaseinfo.c"

#include <QTimer>
#include <QDebug>

Q_LOGGING_CATEGORY(Session,"TREAT SESSION")

TreatSession::TreatSession(QObject *parent) : QObject(parent)
{
    m_pa = new PowerAmp(this);
    m_do = new DOController(this);

    resetSessionRecorder();
    setActionString();
    setErrorString();

    // used for testing here
//    m_sessionParam.spotCount = TEST_SPOT_COUNT;

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
    }
    m_currPlane = spots.begin().key();
    m_sessionParam.spotCount = spots.begin().value().count();
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
        /*
         * old version of power amplifier
        if (m_pa->isSerialPortExist())
        {
            m_pa->startAllPowerAmp((double)m_sonicationParam.volt);
        }
        */

        if (m_pa->exist())
        {
            if (m_pa->startAll((VOLT)m_sonicationParam.volt))
            {
                //  TODO
                //  Display information
            }
        }

    //  start the treat session with the first spot in the plan

    m_currType = ON;

    if (m_do->isDoExist())
    {
        m_do->enableDO();
    }


    //  deliver the acoustic energy at a given spot

    m_timer->start(m_sessionParam.dutyOn);

    qCWarning(Session()) << Session().categoryName()
                         << printLastAction(START)+printLastError(NoError);

    qCWarning(Session()) << "==============================================";
}

void TreatSession::onDuty()
{
    m_currType = OFF;
    //  stop delivering the acoustic energy here
    if (m_do->isDoExist())
    {
        m_do->disableDO();
    }

    m_timer->start(m_sessionParam.dutyOff);
    qCDebug(Session()) << Session().categoryName()
                       << "Status: finish the stage of duty on.";

}

void TreatSession::offDuty()
{
    m_recorder.periodIndex++;

    qCDebug(Session()) << Session().categoryName()
                       << "Status: finish the stage of duty off.";

    qCDebug(Session()) << Session().categoryName()
                       << "The #" << m_recorder.periodIndex
                       << " duty is finished.";

    if (m_recorder.periodIndex < m_sessionParam.periodCount)
    {
        m_currType = ON;
        //  deliver the acoustic energy here at the same spot
        if (m_do->isDoExist())
        {
            m_do->enableDO();
        }

        m_timer->start(m_sessionParam.dutyOn);
    }else
    {
        m_recorder.spotIndex++;
        m_recorder.periodIndex = 0;

        m_currType = COOLING;
        //  deliver a cooling period here
        if (m_do->isDoExist())
        {
            m_do->disableDO();
        }

        m_timer->start(m_sessionParam.coolingTime);
        qCDebug(Session()) << Session().categoryName()
                           << "The #" << m_recorder.spotIndex
                           << " spot is finished.";
        changeSpot();
    }
}

void TreatSession::cooling()
{
    qCDebug(Session()) << Session().categoryName()
                       << "status: finish the stage of cooling.";
    qCDebug(Session()) << "==============================================";

    if (m_recorder.spotIndex < m_sessionParam.spotCount)
    {
        // start delivering the acoustic energy at the next spot

        m_currType = ON;
        if (m_do->isDoExist())
        {
            m_do->enableDO();
        }

        m_timer->start(m_sessionParam.dutyOn);
    }else
    {
        // finish the current session

        qCDebug(Session()) << Session().categoryName()
                           << "All the spots have been sonicated.";
        qCDebug(Session()) << "==========================================";

        resetSessionRecorder();
        /*
         * old version of power amplifiers
        if (m_pa->isSerialPortExist())
        {
            m_pa->resetAllPowerAmp();
        }
        */
        if (m_pa->exist())
        {
            if (m_pa->resetAll())
            {
                //  TODO
                //  Display the information
            }
        }
    }
}

void TreatSession::timeoutFcn()
{
    switch (m_currType)
    {
    case ON:
        onDuty();
        break;
    case OFF:
        offDuty();        
        break;
    case COOLING:
        cooling();
        break;
    }
}

void TreatSession::stop()
{
    //  stop delivering the acoustic energy
    if (m_do->isDoExist())
    {
        qDebug() << "DOController exists";
        m_do->disableDO();
    }else
    {
        qDebug() << "DOController not exists";
    }

    if (m_timer->isActive())
    {
        m_timer->stop();
        qDebug() << "Timer is stopped";
    }else
    {
        qDebug() << "Timer not started";
    }

    /*
     * old version of power amplifiers
    if (m_pa->isSerialPortExist())
    {
        m_pa->resetAllPowerAmp();
        qDebug() << "PowerAmp is reset";
    }else
    {
        qDebug() << "PowerAmp not existed";
    }
    */
    if (m_pa->exist())
    {
        if (m_pa->resetAll())
        {
            qDebug() << "PowerAmp is reset";
        }
    }else
    {
        qDebug() << "PowerAmp not existed";
    }

    qCWarning(Session()) << Session().categoryName()
                              << printLastAction(STOP)+printLastError(NoError);
    qCWarning(Session()) << Session().categoryName()
                              << "The spot #" << m_recorder.spotIndex
                              << ", duty #" << m_recorder.periodIndex
                              << " is finished.";
    qCWarning(Session()) << "==========================================";

    //  reset the session param
    resetSessionRecorder();
}

void TreatSession::pause()
{
    // stop delivering the acoustic energy
    if (m_do->isDoExist())
    {
        m_do->disableDO();
    }

    if (m_timer->isActive())
    {
        m_timer->stop();
    }
    qCWarning(Session()) << Session().categoryName()
                              << printLastAction(PAUSE)+printLastError(NoError);
    qCWarning(Session()) << Session().categoryName()
                              << "The spot #" << m_recorder.spotIndex
                              << ", duty #" << m_recorder.periodIndex
                              << " is finished.";
    qCWarning(Session()) << "==========================================";
}

void TreatSession::resume()
{
    qCWarning(Session()) << Session().categoryName()
                              << printLastAction(RESUME)+printLastError(NoError);
    qCWarning(Session()) << Session().categoryName()
                              << "The spot #" << m_recorder.spotIndex
                              << ", duty #" << m_recorder.periodIndex
                              << " is started, again.";
    qCWarning(Session()) << "==========================================";

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
    Coordinate x,y,z;
    if (spots.size())
    {
        qDebug() << m_spots.size() << "planes left.";
        qDebug() << spots.size() << " spots left in the current plane.";
        x = spots.at(0).x;
        y = spots.at(0).y;
        z = spots.at(0).z;
        spots.removeAt(0);
        m_spots.insert(m_currPlane,spots);
    }else
    {
        m_spots.remove(m_currPlane);
        qDebug() << m_spots.size() << "planes left.";
        resetSessionRecorder();
        if (m_spots.size())
        {
            qDebug() << spots.size() << " spots left in the current plane.";
            m_currPlane = m_spots.begin().key();
            m_sessionParam.spotCount = m_spots.begin().value().size();
            spots = m_spots.value(m_currPlane);
            x = spots.at(0).x;
            y = spots.at(0).y;
            z = spots.at(0).z;
            spots.removeAt(0);
            m_spots.insert(m_currPlane,spots);
        }else
        {
            m_sessionParam.spotCount = 0;
            return;
        }
    }

    //  compute the phases for the spot
    FocusCount num = 1;

    real_T volt[144];
    real_T angle[144];

    PhaseInfo(num,(real_T)x,(real_T)y,(real_T)z,volt,angle);
    qDebug() << Session().categoryName();
    for (int i=0;i<TRANSDUCER_COUNT;i++)
    {
        qDebug() << "#" << i << ": " << angle[i];
//          load the phases for the spot
        if (m_do->isDoExist())
        {
            m_do->sendPhase(i,angle[i]);
            m_do->loadPhase();
        }
    }
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
    str += m_actionString[iType - 1];
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
    /*
     * old version of power amplifiers
    if (m_pa->isSerialPortExist())
    {
        m_pa->startAllPowerAmp(10);
    }
    */

    if (m_pa->exist())
    {
        if (m_pa->startAll(10))
        {

        }
    }
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
        if (m_do->isDoExist())
        {
            m_do->enableDO();
        }
}
