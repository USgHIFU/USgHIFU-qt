#include "consoleplan.h"
#include "math.h"

Q_LOGGING_CATEGORY(PlanGenerator,"PLAN GENERATOR")

ConsolePlan::ConsolePlan(QObject* parent):QObject(parent)
{
    resetSonicationParam();
    setErrorString();
    setActionString();
}

bool ConsolePlan::addPlane(float angle, QList<Plane2DCoordinate> coordinates)
{
    QString str;
    if (m_planeSpots.contains(angle))
    {
        //  overwrite the existed plane
        m_planeSpots.insert(angle,coordinates);
        str = printLastAction(AddPlane) + printLastError(ErrorOverwriteExistingPlane);
        qCWarning(PlanGenerator()) << PlanGenerator().categoryName() << str;
        return false;
    }else
    {
        m_planeSpots.insert(angle,coordinates);
        str = printLastAction(AddPlane) + printLastError(NoError);
        qCDebug(PlanGenerator()) << PlanGenerator().categoryName() << str;
        return true;
    }
}

bool ConsolePlan::removePlane(float angle)
{
    QString str;
    if (m_planeSpots.contains(angle))
    {
        m_planeSpots.remove(angle);
        str = printLastAction(RemovePlane) + printLastError(NoError);
        qCDebug(PlanGenerator()) << PlanGenerator().categoryName() << str;
        return true;
    }else
    {
        emit error(ErrorNoSuchPlane);
        str = printLastAction(RemovePlane) + printLastError(ErrorNoSuchPlane);
        qCWarning(PlanGenerator()) << PlanGenerator().categoryName() << str;
        return false;
    }
}

bool ConsolePlan::addSpot(float angle, Plane2DCoordinate coordinate)
{
    QString str;
    if (m_planeSpots.contains(angle))
    {
        QList<Plane2DCoordinate> coordinates = m_planeSpots.value(angle);
        if (containSpot(coordinates,coordinate) >= 0)
        {
            str = printLastAction(AddSpot) + printLastError(ErrorSuchSpotExists);
            qCWarning(PlanGenerator()) << PlanGenerator().categoryName() << str;
            return false;
        }else
        {
            coordinates.append(coordinate);
            m_planeSpots.insert(angle,coordinates);
            str = printLastAction(AddSpot) + printLastError(NoError);
            qCDebug(PlanGenerator()) << PlanGenerator().categoryName() << str;
            return true;
        }
    }else
    {
        str = printLastAction(AddSpot) + printLastError(ErrorNoSuchPlane);
        qCWarning(PlanGenerator()) << PlanGenerator().categoryName() << str;
        emit error(ErrorNoSuchPlane);
        return false;
    }
}

bool ConsolePlan::addSpots(float angle, QList<Plane2DCoordinate> coordinates)
{
    QString str;
    if (m_planeSpots.contains(angle))
    {

        QList<Plane2DCoordinate> planeSpots = m_planeSpots.value(angle);
        for (int i = 0;i < coordinates.size();i++)
        {
            if (containSpot(planeSpots,coordinates.at(i)) >= 0)
            {
                str = printLastAction(AddSpot) + printLastError(ErrorSuchSpotExists);
                qCWarning(PlanGenerator()) << PlanGenerator().categoryName() << str;
                return false;
            }
        }
        for (int i = 0;i < coordinates.size();i++)
        {
            addSpot(angle,coordinates.at(i));
        }

        str = printLastAction(AddSpot) + printLastError(NoError);
        qCDebug(PlanGenerator()) << PlanGenerator().categoryName() << str;
        return true;
    }else
    {
        str = printLastAction(AddSpot) + printLastError(ErrorNoSuchPlane);
        qCWarning(PlanGenerator()) << PlanGenerator().categoryName() << str;
        emit error(ErrorNoSuchPlane);
        return false;
    }
}

bool ConsolePlan::removeSpot(float angle, Plane2DCoordinate coordinate)
{
    QString str;
    if (m_planeSpots.contains(angle))
    {
        QList<Plane2DCoordinate> coordinates = m_planeSpots.value(angle);
        int i = containSpot(coordinates,coordinate);
        if (i >= 0)
        {
            coordinates.removeAt(i);
            if (coordinates.size() == 0)
            {
                m_planeSpots.remove(angle);
            }else
            {
                m_planeSpots.insert(angle,coordinates);
            }

            str = printLastAction(RemoveSpot) + printLastError(NoError);
            qCDebug(PlanGenerator()) << PlanGenerator().categoryName() << str;
            return true;
        }else
        {
            str = printLastAction(RemoveSpot) + printLastError(ErrorPlaneNoSuchSpot);
            qCDebug(PlanGenerator()) << PlanGenerator().categoryName() << str;
            return false;
        }
    }else
    {
        str = printLastAction(RemoveSpot) + printLastError(ErrorNoSuchPlane);
        qCWarning(PlanGenerator()) << PlanGenerator().categoryName() << str;
        emit error(ErrorNoSuchPlane);
        return false;
    }
}

bool ConsolePlan::removeSpots(float angle, QList<Plane2DCoordinate> coordinates)
{
    QString str;
    if (m_planeSpots.contains(angle))
    {
        QList<Plane2DCoordinate> planeSpots = m_planeSpots.value(angle);
        for (int i = 0;i < coordinates.size();i++)
        {
            if (containSpot(planeSpots,coordinates.at(i)) == -1)
            {
                str = printLastAction(RemoveSpots) + printLastError(ErrorPlaneNoSuchSpot);
                qCWarning(PlanGenerator()) << PlanGenerator().categoryName() << str;
                return false;
            }
        }
        for (int i = 0;i < coordinates.size();i++)
        {
            removeSpot(angle,coordinates.at(i));
        }
        str = printLastAction(RemoveSpots)+printLastError(NoError);
        qCDebug(PlanGenerator()) << PlanGenerator().categoryName() << str;
        return true;
    }else
    {
        str = printLastAction(RemoveSpots)+printLastError(ErrorNoSuchPlane);
        qCWarning(PlanGenerator()) << PlanGenerator().categoryName() << str;
        emit error(ErrorNoSuchPlane);
        return false;
    }
}

bool ConsolePlan::moveSpot(float angle, Plane2DCoordinate coordinate)
{
    //  TODO

    return true;
}

int ConsolePlan::containSpot(QList<Plane2DCoordinate> coordinates, Plane2DCoordinate coordinate)
{
    for (int i = 0;i < coordinates.size();i++)
    {
        if ((coordinates.at(i).x == coordinate.x) &&
            (coordinates.at(i).y == coordinate.y))
        {
            return i;
        }
    }
    //  No such spot in the plane
    return -1;
}

QList<Spot3DCoordinate> ConsolePlan::transferCoordinate(float angle, QList<Plane2DCoordinate> planeSpots)
{
    QList<Spot3DCoordinate> spots;
    Spot3DCoordinate coordinate;
    for (int i = 0;i < planeSpots.size();i++)
    {
        coordinate.x = planeSpots.at(i).x * cos(angle);
        coordinate.y = planeSpots.at(i).y * sin(angle);
        coordinate.z = (coordinate.x + coordinate.y) / 2;
        spots.append(coordinate);
    }
    return spots;
}

void ConsolePlan::getPlaneSpots()
{
    emit updatePlaneSpots(m_planeSpots);
}

void ConsolePlan::getSpots()
{
    m_spots.clear();

    if (m_planeSpots.size() == 0)
    {
        emit error(ErrorPlaneNoSuchSpot);
    }else
    {
        QHash<float,QList<Plane2DCoordinate> >::iterator i;
        for (i = m_planeSpots.begin();i != m_planeSpots.end();i++)
        {
            m_spots.insert(i.key(),transferCoordinate(i.key(),i.value()));
        }
    }

    emit updateSpots(m_spots);
}

void ConsolePlan::setSpotOrder(float angle, QList<int> order)
{
    if (m_planeSpots.contains(angle))
    {
        m_spotOrder.insert(angle,order);
    }else
    {
        emit error(ErrorNoSuchPlane);
    }
}

QHash<float,QList<int> > ConsolePlan::getSpotOrder()
{
    return m_spotOrder;
}

void ConsolePlan::setSonicationParam(QString key, int value)
{
    if (m_sonicationParam.contains(key) && (value != 0))
    {
        m_sonicationParam.insert(key,value);
    }
}

QHash<QString,int> ConsolePlan::getSonicationParam()
{
    QHash<QString,int>::iterator i;
    for(i = m_sonicationParam.begin();i != m_sonicationParam.end();i++)
    {
        if (i.value() == 0)
        {
            emit error(ErrorNotEnoughSonicationParameter);
        }
    }

    return m_sonicationParam;
}

void ConsolePlan::resetSonicationParam()
{
    m_sonicationParam.clear();
    m_sonicationParam.insert("Time",0);
    m_sonicationParam.insert("Period",0);
    m_sonicationParam.insert("Duty Cycle",0);
    m_sonicationParam.insert("Cooling Time",0);
}

QString ConsolePlan::printLastAction(Action i)
{
    QString action = "ACTION: ";
    action += m_actionString[i];
    action += " ";
    return action;
}

QString ConsolePlan::printLastError(PlanError i)
{
    QString error = "RESULT: ";
    error += m_errorString[i];
    return error;
}

void ConsolePlan::setErrorString()
{
    m_errorString << "Done successfully."
                  << "Cannot find such plane."
                  << "Overwrite the existing plane."
                  << "Cannot find such spot in the specified plane."
                  << "Such spot exists."
                  << "No spot exists."
                  << "Not enough sonication parameters exist.";
}

void ConsolePlan::setActionString()
{
    m_actionString << "Add a new plane"
                   << "Remove the existed plane"
                   << "Add a new spot in the specified plane"
                   << "Remove the existed spot in the specified plane"
                   << "Add several new spots in the specified plane"
                   << "Remove the existed spots in the specified plane"
                   << "Move the existed in the specified plane";
}
