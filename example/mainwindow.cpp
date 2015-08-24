#include "mainwindow.h"
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    m_plan = new ConsolePlan(this);
    m_server = new Server;

    m_labelAngle = new QLabel("angle: ",this);
    m_labelX = new QLabel("x: ",this);
    m_labelY = new QLabel("y: ",this);

    //  line edit
    m_angle = new QLineEdit(this);
    m_x = new QLineEdit(this);
    m_y = new QLineEdit(this);

    QHBoxLayout* editLayout = new QHBoxLayout;
    editLayout->addWidget(m_labelAngle);
    editLayout->addWidget(m_angle);
    editLayout->addWidget(m_labelX);
    editLayout->addWidget(m_x);
    editLayout->addWidget(m_labelY);
    editLayout->addWidget(m_y);

    m_labelVolt = new QLabel("volt: ",this);
    m_labelTotalTime = new QLabel("total time: ",this);
    m_labelPeriod = new QLabel("period: ",this);
    m_labelDutyCycle = new QLabel("duty cycle: ",this);
    m_labelCoolingTime = new QLabel("cooling time: ",this);

    m_volt = new QLineEdit("15",this);
    m_totalTime = new QLineEdit("12",this);
    m_period = new QLineEdit("500",this);
    m_dutyCycle = new QLineEdit("60",this);
    m_coolingTime = new QLineEdit("300",this);

    QHBoxLayout* editParamLayout = new QHBoxLayout;
    editParamLayout->addWidget(m_labelVolt);
    editParamLayout->addWidget(m_volt);
    editParamLayout->addWidget(m_labelTotalTime);
    editParamLayout->addWidget(m_totalTime);
    editParamLayout->addWidget(m_labelPeriod);
    editParamLayout->addWidget(m_period);
    editParamLayout->addWidget(m_labelDutyCycle);
    editParamLayout->addWidget(m_dutyCycle);
    editParamLayout->addWidget(m_labelCoolingTime);
    editParamLayout->addWidget(m_coolingTime);

    //  plan action
    m_add = new QPushButton("add plane",this);
    m_addSpot = new QPushButton("add spot",this);
    m_remove = new QPushButton("remove plane",this);
    m_removeSpot = new QPushButton("remove spot",this);
    m_dispPlane = new QPushButton("display plane",this);
    m_dispSpot = new QPushButton("display spot",this);

    QHBoxLayout* btnPlanLayout = new QHBoxLayout;
    btnPlanLayout->addWidget(m_add);
    btnPlanLayout->addWidget(m_addSpot);
    btnPlanLayout->addWidget(m_remove);
    btnPlanLayout->addWidget(m_removeSpot);
    btnPlanLayout->addWidget(m_dispPlane);
    btnPlanLayout->addWidget(m_dispSpot);

    //  server action
    m_sendPlan = new QPushButton("send plan",this);
    m_start = new QPushButton("start",this);
    m_stop = new QPushButton("stop",this);
    m_pause = new QPushButton("pause",this);
    m_resume = new QPushButton("reume",this);

    QHBoxLayout* btnServerLayout = new QHBoxLayout;
    btnServerLayout->addWidget(m_sendPlan);
    btnServerLayout->addWidget(m_start);
    btnServerLayout->addWidget(m_stop);
    btnServerLayout->addWidget(m_pause);
    btnServerLayout->addWidget(m_resume);

    //
    m_status = new QLabel(this);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addLayout(editLayout);
    layout->addLayout(editParamLayout);
    layout->addLayout(btnPlanLayout);
    layout->addLayout(btnServerLayout);
    layout->addWidget(m_status);

    QWidget* widget = new QWidget;
    widget->setLayout(layout);

    setCentralWidget(widget);

    connect(m_add,SIGNAL(clicked(bool)),SLOT(btnAdd_Click()));
    connect(m_addSpot,SIGNAL(clicked(bool)),SLOT(btnAddSpot_Click()));
    connect(m_remove,SIGNAL(clicked(bool)),SLOT(btnRemove_Click()));
    connect(m_removeSpot,SIGNAL(clicked(bool)),SLOT(btnRemoveSpot_Click()));
    connect(m_dispPlane,SIGNAL(clicked(bool)),SLOT(btnDispPlane_Click()));
    connect(m_dispSpot,SIGNAL(clicked(bool)),SLOT(btnDispSpot_Click()));
    connect(m_plan,SIGNAL(updatePlaneSpots(QHash<float,QList<Plane2DCoordinate> >)),
            SLOT(setPlaneSpots(QHash<float,QList<Plane2DCoordinate> >)));
    connect(m_plan,SIGNAL(updateSpots(QHash<float,QList<Spot3DCoordinate> >)),
            SLOT(setSpots(QHash<float,QList<Spot3DCoordinate> >)));
}

MainWindow::~MainWindow()
{

}

void MainWindow::btnAdd_Click()
{
    if (m_angle->text().isEmpty() ||
        m_x->text().isEmpty() ||
        m_y->text().isEmpty())
    {
        m_status->setText("Warning: not enough parameters");
        return;
    }

    float angle = m_angle->text().toFloat();
    Plane2DCoordinate coordinate = {m_x->text().toFloat(),m_y->text().toFloat()};

    QList<Plane2DCoordinate> planeCoordinate;
    planeCoordinate.append(coordinate);

    if (m_plan->addPlane(angle,planeCoordinate))
    {
        m_status->setText(QString("The plane is added.\nAngle: %1 X: %2 Y: %3").arg(m_angle->text())
                                                                               .arg(m_x->text())
                                                                               .arg(m_y->text()));
    }else
    {
        m_status->setText("The plane of such angle existed.");
    }


}

void MainWindow::btnRemove_Click()
{
    if (m_angle->text().isEmpty())
    {
        m_status->setText("No plane is removed.");
        return;
    }

    if (m_plan->removePlane(m_angle->text().toFloat()))
    {
        m_status->setText("The required plane is removed.");
    }else
    {
        m_status->setText("Warning: no plane is found.");
    }
}

void MainWindow::btnDispPlane_Click()
{
    m_plan->getPlaneSpots();

    QString str = "";
    QHash<float,QList<Plane2DCoordinate> >::iterator i;

    if (m_planeSpots.size())
    {
        for(i = m_planeSpots.begin();i != m_planeSpots.end(); i++)
        {
            for(int j=0;j<i.value().size();j++)
            {
                str += QString("plane: angle, %1, x, %2, y, %3\n").arg(i.key())
                                                                  .arg(i.value().at(j).x)
                                                                  .arg(i.value().at(j).y);
            }
        }
        m_status->setText(str);
    }else
    {
        m_status->setText("No plane existed.");
    }
}

void MainWindow::btnAddSpot_Click()
{
    if (m_angle->text().isEmpty() ||
        m_x->text().isEmpty() ||
        m_y->text().isEmpty())
    {
        m_status->setText("Warning: not enough parameters");
        return;
    }

    float angle = m_angle->text().toFloat();
    Plane2DCoordinate coordinate = {m_x->text().toFloat(),m_y->text().toFloat()};

    if (m_plan->addSpot(angle,coordinate))
    {
        m_status->setText(QString("The plane of angle: %1 is added.\n X: %2 Y: %3")
                          .arg(angle)
                          .arg(coordinate.x)
                          .arg(coordinate.y));
    }else
    {
        m_status->setText(QString("The plane of angle: %1 is not found.").arg(angle));
    }
}

void MainWindow::btnRemoveSpot_Click()
{
    if (m_angle->text().isEmpty() ||
        m_x->text().isEmpty() ||
        m_y->text().isEmpty())
    {
        m_status->setText("Warning: not enough parameters");
        return;
    }

    float angle = m_angle->text().toFloat();
    Plane2DCoordinate coordinate = {m_x->text().toFloat(),m_y->text().toFloat()};

    if (m_plan->removeSpot(angle,coordinate))
    {
        m_status->setText(QString("The plane of angle: %1 is removed.\n X: %2 Y: %3")
                          .arg(angle)
                          .arg(coordinate.x)
                          .arg(coordinate.y));
    }else
    {
        m_status->setText(QString("The plane of angle: %1 is not found.").arg(angle));
    }
}

void MainWindow::btnDispSpot_Click()
{
    m_plan->getSpots();

    if (m_spots.size())
    {
        QString str = "";
        QHash<float,QList<Spot3DCoordinate> >::iterator i;
        for (i = m_spots.begin();i != m_spots.end();i++)
        {
            for (int j = 0;j < i.value().size();j++)
            {
                str += QString("plane: angle, %1, x, %2, y, %3, z %4\n").arg(i.key())
                                                                        .arg(i.value().at(j).x)
                                                                        .arg(i.value().at(j).y)
                                                                        .arg(i.value().at(j).z);
            }
        }
        m_status->setText(str);
    }else
    {
        m_status->setText("No spot existed.");
    }
}

void MainWindow::setPlaneSpots(QHash<float, QList<Plane2DCoordinate> > planeSpots)
{
    m_planeSpots = planeSpots;
}

void MainWindow::setSpots(QHash<float, QList<Spot3DCoordinate> > spots)
{
    m_spots = spots;
}

void MainWindow::btnSendPlan_Click()
{
    m_plan->getSpots();

    m_plan->setSonicationParam("TotalTime",m_totalTime->text().toInt());
    m_plan->setSonicationParam("Period",m_period->text().toInt());
    m_plan->setSonicationParam("DutyCycle",m_dutyCycle->text().toInt());
    m_plan->setSonicationParam("CoolintTime",m_coolingTime->text().toInt());

    m_server->setCoordinate(m_spots);

    m_server->setSpotOrder(m_plan->getSpotOrder());

    m_server->setParameter(m_plan->getSonicationParam());

    m_server->sendPlanHash();

}

void MainWindow::btnStart_Click()
{

}

void MainWindow::btnStop_Click()
{

}

void MainWindow::btnPause_Click()
{

}

void MainWindow::btnResume_Click()
{

}
