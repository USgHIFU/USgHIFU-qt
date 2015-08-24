#ifndef MAINWINDOW_H
#define MAINWINDOW_H

class QLineEdit;
class QPushButton;
class QLabel;

#include <QMainWindow>
#include "consoleplan.h"
#include "server.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void btnAdd_Click();
    void btnAddSpot_Click();
    void btnRemove_Click();
    void btnRemoveSpot_Click();
    void btnDispPlane_Click();
    void btnDispSpot_Click();
    void btnSendPlan_Click();
    void btnStart_Click();
    void btnPause_Click();
    void btnStop_Click();
    void btnResume_Click();
    void setPlaneSpots(QHash<float,QList<Plane2DCoordinate> >);
    void setSpots(QHash<float,QList<Spot3DCoordinate> >);

private:
    ConsolePlan* m_plan;
    QHash<float,QList<Plane2DCoordinate> > m_planeSpots;
    QHash<float,QList<Spot3DCoordinate> > m_spots;
    SpotSonicationParameter m_param;

    Server* m_server;

    QLabel *m_labelAngle,*m_labelX,*m_labelY;
    QLabel *m_labelVolt,*m_labelTotalTime,*m_labelPeriod,*m_labelDutyCycle,*m_labelCoolingTime;
    QLineEdit *m_angle,*m_x,*m_y;
    QLineEdit*m_volt,*m_totalTime,*m_period,*m_dutyCycle,*m_coolingTime;
    QPushButton* m_add;
    QPushButton* m_addSpot;
    QPushButton* m_remove;
    QPushButton* m_removeSpot;
    QPushButton* m_dispPlane;
    QPushButton* m_dispSpot;

    QPushButton *m_sendPlan,*m_start,*m_stop,*m_pause,*m_resume;

    QLabel* m_status;
};

#endif // MAINWINDOW_H
