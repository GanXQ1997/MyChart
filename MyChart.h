#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QMainWindow>
#include <QGridLayout>
#include <QTreeWidget>
#include <QPushButton>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QToolBar>
#include <QDockWidget>
#include <QLabel>
#include <QStatusBar>

#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCore/QtMath>
//#include <QtCore/QRandomGenerator>
#include <QtCharts/QLineSeries>

#include <QDateTime>
#include <QTimer>

namespace Ui {
class MyChart;
}
QT_CHARTS_USE_NAMESPACE

//自定义主窗口
class MyChart : public QMainWindow
{
    Q_OBJECT
public:
    //构建主窗口界面
    MyChart();
    ~MyChart();
private:
    void SetMyStyle();
    void CreateToolBar();
    void CreateMenu();
    void CreateStatusBar();
    void CreateDockWidget();
    QWidget* CreateWidget();
    QWidget* CreateTriggerWidget();
    QWidget* CreateSampleWidget();
    QWidget* CreateDebugWidget();
    QWidget* CreateChanWidget();
    QChartView *CreateFreqChart();
    QChartView *CreateTimeChart();
    QLabel* TimerLabel;
public slots:
    void TimeUpdate();
};

#endif // MAINWIDGET_H
