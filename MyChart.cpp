#include "MyChart.h"
#include <QDebug>

MyChart::MyChart()
{
    //修改标题栏颜色方法：先隐藏标题栏，在菜单栏上绘制缩小放大关闭按钮
    CreateMenu();
    CreateToolBar();
    CreateStatusBar();

    QWidget* m_Widget = new QWidget();
    this->setCentralWidget(m_Widget);
    QGridLayout *GridLayout = new QGridLayout(m_Widget);

    QWidget *Left_Table_Box = CreateTree();
    QWidget *Right_Table_Box = CreateTree();
    QWidget *Bottom_Table_Box = CreateTree();
    QWidget *Chart_Table_Box = CreateChart();

    QDockWidget *Bottom_dockWidget = new QDockWidget(tr("配置信息"));   //创建锚接部件
    Bottom_dockWidget->setAllowedAreas(Qt::AllDockWidgetAreas);  //锚接部件 允许停靠的区域，左右
    Bottom_dockWidget->setWidget(Bottom_Table_Box);  //设置锚接部件的内容 TreeWidget
    addDockWidget(Qt::BottomDockWidgetArea, Bottom_dockWidget);

    this->setDockNestingEnabled(true);
    QDockWidget *Right_dockWidget = new QDockWidget(tr("配置信息"));   //创建锚接部件
    QDockWidget *Left_dockWidget = new QDockWidget(tr("配置信息"));   //创建锚接部件
    //dockWidget->setObjectName("dockWidget test"); //标识名
    Right_dockWidget->setAllowedAreas(Qt::RightDockWidgetArea | Qt::LeftDockWidgetArea);  //锚接部件 允许停靠的区域，左右
    Left_dockWidget->setAllowedAreas(Qt::RightDockWidgetArea | Qt::LeftDockWidgetArea);  //锚接部件 允许停靠的区域，左右
    Right_dockWidget->setWidget(Right_Table_Box);  //设置锚接部件的内容 TreeWidget
    Left_dockWidget->setWidget(Left_Table_Box);  //设置锚接部件的内容 TreeWidget
    addDockWidget(Qt::RightDockWidgetArea, Right_dockWidget);
    addDockWidget(Qt::LeftDockWidgetArea, Left_dockWidget);



    GridLayout->addWidget(Chart_Table_Box,0,0,3,3);
//    GridLayout->addWidget(Bottom_Table_Box,3,0,1,3);
//    GridLayout->addWidget(Left_Table_Box,0,0,4,1);
//    GridLayout->addWidget(Right_Table_Box,0,4,4,1);
//    GridLayout->addWidget(Bottom_Table_Box,3,1,1,3);
//    GridLayout->addWidget(Chart_Table_Box,0,1,3,3);

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

QWidget* MyChart::CreateTree()
{
        QWidget* m_Widget = new QWidget();
    QTreeWidget *m_tree = new QTreeWidget(m_Widget);

    QTreeWidgetItem* topitem = new QTreeWidgetItem;
    topitem->setText(0,"TopItem");
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

QChartView * MyChart::CreateChart()
{
    QLineSeries *series = new QLineSeries();
    for (int i = 0; i < 500; i++) {
        QPointF p((qreal) i, qSin(M_PI / 50 * i) * 100);
        p.ry() += QRandomGenerator::global()->bounded(20);
        *series << p;
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("My Chart");
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


