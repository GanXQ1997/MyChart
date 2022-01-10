#include "MyChart.h"
#include <QDebug>

MyChart::MyChart()
{
    //修改标题栏颜色方法：先隐藏标题栏，在菜单栏上绘制缩小放大关闭按钮
    CreateMenu();
    CreateToolBar();
    CreateStatusBar();
    CreateDockWidget();
}
MyChart::~MyChart()
{

}

void MyChart::SetMyStyle()
{
    setWindowIcon(QIcon(":/Resources/myosc.ico"));
    QPalette  palette;
    palette.setBrush(QPalette::Background, QBrush(0xFFFFFF));
    /*ColdEvening, CleanMirror, SnowAgain*/
    //palette.setBrush(QPalette::Background, QBrush(QGradient(QGradient::ColdEvening)));
    this->setPalette(palette);
    this->setWindowTitle("JNOSC");
    this->resize(1000,600);
    this->setMinimumSize(600,400);
}

void MyChart::CreateDockWidget()
{
    //this->setCentralWidget(m_Widget);

    QWidget *Left_Table_Box = CreateTriggerWidget();
    QWidget *Right_Table_Box = CreateSampleWidget();
    QWidget *Debug_Table_Box = CreateDebugWidget();
    QWidget *Chan_Table_Box = CreateChanWidget();
    QChartView *TChart_Table_Box = CreateTimeChart();
    QChartView *FChart_Table_Box = CreateFreqChart();

    this->setDockNestingEnabled(true);

    QDockWidget *Left_dockWidget = new QDockWidget(tr("触发配置"));   //创建锚接部件
    Left_dockWidget->setAllowedAreas(Qt::RightDockWidgetArea | Qt::LeftDockWidgetArea);  //锚接部件 允许停靠的区域，左右
    Left_dockWidget->setWidget(Left_Table_Box);  //设置锚接部件的内容 TreeWidget
    addDockWidget(Qt::LeftDockWidgetArea, Left_dockWidget);

    QDockWidget *Right_dockWidget = new QDockWidget(tr("采集配置"));
    //dockWidget->setObjectName("dockWidget test"); //标识名
    Right_dockWidget->setAllowedAreas(Qt::RightDockWidgetArea | Qt::LeftDockWidgetArea);
    Right_dockWidget->setWidget(Right_Table_Box);
    addDockWidget(Qt::RightDockWidgetArea, Right_dockWidget);

    QDockWidget *Time_dockWidget = new QDockWidget(tr("波形显示"));
    Time_dockWidget->setAllowedAreas(Qt::TopDockWidgetArea | Qt::BottomDockWidgetArea);
    Time_dockWidget->setWidget(TChart_Table_Box);
    addDockWidget(Qt::TopDockWidgetArea, Time_dockWidget);

    QDockWidget *Freq_dockWidget = new QDockWidget(tr("频率显示"));
    Freq_dockWidget->setAllowedAreas(Qt::TopDockWidgetArea | Qt::BottomDockWidgetArea);
    Freq_dockWidget->setWidget(FChart_Table_Box);
    addDockWidget(Qt::TopDockWidgetArea, Freq_dockWidget);

    QDockWidget *Debug_dockWidget = new QDockWidget(tr("调试配置"));
    Debug_dockWidget->setAllowedAreas(Qt::TopDockWidgetArea | Qt::BottomDockWidgetArea);
    Debug_dockWidget->setWidget(Debug_Table_Box);
    addDockWidget(Qt::BottomDockWidgetArea, Debug_dockWidget);

    QDockWidget *Chan_dockWidget = new QDockWidget(tr("通道配置"));
    Chan_dockWidget->setAllowedAreas(Qt::TopDockWidgetArea | Qt::BottomDockWidgetArea);
    Chan_dockWidget->setWidget(Debug_Table_Box);
    addDockWidget(Qt::BottomDockWidgetArea, Chan_dockWidget);


    splitDockWidget(Left_dockWidget,Time_dockWidget,Qt::Horizontal);
    splitDockWidget(Time_dockWidget,Right_dockWidget,Qt::Horizontal);
    splitDockWidget(Time_dockWidget,Debug_dockWidget,Qt::Vertical);
    tabifyDockWidget(Time_dockWidget, Freq_dockWidget);
    tabifyDockWidget(Debug_dockWidget, Chan_dockWidget);
}

void MyChart::CreateToolBar()
{
    QAction *startAct = new QAction(QIcon( "" ), tr( "开始" ), this );
    startAct->setShortcut(tr("Ctrl+N" ));        //快捷键
    startAct->setStatusTip(tr("" ));      //状态提示
    QAction *aboutAct = new QAction(QIcon( "" ), tr( "关于" ), this );
    QAction *showAct = new QAction(QIcon( "" ), tr( "显示" ), this );//关闭锚接部件后打开部件
    //startAct->setShortcut(tr("Ctrl+N" ));        //快捷键
    startAct->setStatusTip(tr("关于" ));      //状态提示
    QToolBar* fileToolBar = addToolBar(tr("新建"));
    fileToolBar->addAction(startAct);
    fileToolBar->addAction(showAct);
    fileToolBar->addAction(aboutAct);

}

void MyChart::CreateMenu()
{
    QMenu* m_Menu = new QMenu;
    //填充菜单子节点
    QAction *newAct = new QAction(QIcon( "" ), tr( "新建" ), this );
    newAct->setShortcut(tr("Ctrl+N" ));        //快捷键
    newAct->setStatusTip(tr("新建文件" ));      //状态提示
    m_Menu = this->menuBar()->addMenu(tr("文件"));
    m_Menu->addAction(newAct);
    m_Menu->addSeparator();  //添加分割线

    this->menuBar()->addMenu(tr("窗口"));//关闭锚接部件后打开部件
    this->menuBar()->addMenu(tr("关于"));

}

void MyChart::CreateStatusBar()
{
    //状态栏 最多只有一个
    QStatusBar *m_StBar = statusBar();
    //设置到窗口
    this->setStatusBar(m_StBar);

    QLabel *label2 = new QLabel("设备未连接",this);
    m_StBar->addPermanentWidget(label2);

    TimerLabel = new QLabel; // 创建QLabel控件
    TimeUpdate();
    m_StBar->addWidget(TimerLabel); //在状态栏添加此控件
    QTimer *timer = new QTimer(this);
    timer->start(1000); //每隔1000ms发送timeout的信号
    this->connect(timer, SIGNAL(timeout()),this,SLOT(TimeUpdate()));
}

void MyChart::TimeUpdate()
{
    QDateTime m_time = QDateTime::currentDateTime();
    QString timestr = m_time.toString( "yyyy年MM月dd日 hh:mm:ss"); //设置显示的格式
    TimerLabel->setText(timestr); //设置label的文本内容为时间
}

QWidget* MyChart::CreateWidget()
{
    QWidget* m_widget = new QWidget;

    QPushButton* m_but = new QPushButton("Button",m_widget);
    m_but->setGeometry(100,100,100,100);
    return m_widget;
}

QWidget* MyChart::CreateTriggerWidget()
{
    QWidget* m_Widget = new QWidget();
    QTreeWidget *m_tree = new QTreeWidget(m_Widget);

    QTreeWidgetItem* topitem = new QTreeWidgetItem;
    topitem->setText(0,"触发信息");
    m_tree->addTopLevelItem(topitem);
    QStringList  str;
    str << "ChildItem1";
    QTreeWidgetItem* childItem1 = new QTreeWidgetItem(topitem, str);
    m_tree->setHeaderHidden(true);
    //m_tree->setHeaderLabel("配置信息");
    m_tree->setRootIsDecorated( false ); //去掉虚线边框
    m_tree->setFrameStyle(QFrame::NoFrame); //去掉边框
    m_tree->setStyleSheet("QTreeView::branch {image:none;}"); //去掉子节点的虚框
    return m_tree;
}

QWidget* MyChart::CreateSampleWidget()
{
    QWidget* m_Widget = new QWidget();
    QTreeWidget *m_tree = new QTreeWidget(m_Widget);

    QTreeWidgetItem* topitem = new QTreeWidgetItem;
    topitem->setText(0,"采集信息");
    m_tree->addTopLevelItem(topitem);
    QStringList  str;
    str << "ChildItem1";
    QTreeWidgetItem* childItem1 = new QTreeWidgetItem(topitem, str);
    m_tree->setHeaderHidden(true);
    //m_tree->setHeaderLabel("配置信息");
    m_tree->setRootIsDecorated( false ); //去掉虚线边框
    m_tree->setFrameStyle(QFrame::NoFrame); //去掉边框
    m_tree->setStyleSheet("QTreeView::branch {image:none;}"); //去掉子节点的虚框
    return m_tree;
}

QWidget* MyChart::CreateDebugWidget()
{
    QWidget* m_Widget = new QWidget();
    QTreeWidget *m_tree = new QTreeWidget(m_Widget);

    QTreeWidgetItem* topitem = new QTreeWidgetItem;
    topitem->setText(0,"调试信息");
    m_tree->addTopLevelItem(topitem);
    QStringList  str;
    str << "ChildItem1";
    QTreeWidgetItem* childItem1 = new QTreeWidgetItem(topitem, str);
    m_tree->setHeaderHidden(true);
    //m_tree->setHeaderLabel("配置信息");
    m_tree->setRootIsDecorated( false ); //去掉虚线边框
    m_tree->setFrameStyle(QFrame::NoFrame); //去掉边框
    m_tree->setStyleSheet("QTreeView::branch {image:none;}"); //去掉子节点的虚框
    return m_tree;
}

QWidget* MyChart::CreateChanWidget()
{
    QWidget* m_Widget = new QWidget();
    QTreeWidget *m_tree = new QTreeWidget(m_Widget);

    QTreeWidgetItem* topitem = new QTreeWidgetItem;
    topitem->setText(0,"通道设置");
    m_tree->addTopLevelItem(topitem);
    QStringList  str;
    str << "ChildItem1";
    QTreeWidgetItem* childItem1 = new QTreeWidgetItem(topitem, str);
    m_tree->setHeaderHidden(true);
    //m_tree->setHeaderLabel("配置信息");
    m_tree->setRootIsDecorated( false ); //去掉虚线边框
    m_tree->setFrameStyle(QFrame::NoFrame); //去掉边框
    m_tree->setStyleSheet("QTreeView::branch {image:none;}"); //去掉子节点的虚框
    return m_tree;
}

QChartView * MyChart::CreateTimeChart()
{
    //QWidget* m_Widget = new QWidget();
    QLineSeries *series = new QLineSeries();
    for (int i = 0; i < 500; i++) {
        QPointF p((qreal) i, qSin(M_PI / 50 * i) * 100);
        //p.ry() += QRandomGenerator::global()->bounded(20);
        *series << p;
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("时域波形");
    //chart->setAnimationOptions(QChart::AllAnimations);
    chart->legend()->hide();
    chart->createDefaultAxes();

    QChartView *chartView = new QChartView();
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setChart(chart);

//    QMainWindow* m_chart = new QMainWindow();
//    m_chart->setCentralWidget(chartView);
//    m_chart->resize(400, 300);
//    m_chart->grabGesture(Qt::PanGesture);
//    m_chart->grabGesture(Qt::PinchGesture);
    //m_chart->show();

    return chartView;
}

QChartView * MyChart::CreateFreqChart()
{
    QLineSeries *series = new QLineSeries();
    for (int i = 0; i < 500; i++) {
        QPointF p((qreal) i, qSin(M_PI / 50 * i) * 100);
        //p.ry() += QRandomGenerator::global()->bounded(20);
        *series << p;
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("频域波形");
    //chart->setAnimationOptions(QChart::AllAnimations);
    chart->legend()->hide();
    chart->createDefaultAxes();

    QChartView *chartView = new QChartView();
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setChart(chart);

//    QMainWindow* m_chart = new QMainWindow();
//    m_chart->setCentralWidget(chartView);
//    m_chart->resize(400, 300);
//    m_chart->grabGesture(Qt::PanGesture);
//    m_chart->grabGesture(Qt::PinchGesture);
    //m_chart->show();

    return chartView;
}


