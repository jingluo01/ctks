
#include "MainWindow.h"
#include <QMenu>
#include <QListWidget>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    setupUI();
}

MainWindow::~MainWindow()
{
}


void MainWindow::setupUI()
{
    this->setFixedSize(1320, 700);
    mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    leftWidget = buildLeft();
    leftWidget->setObjectName("leftWidget");
    rightWidget = buildRight();
    rightWidget->setObjectName("rightWidget");

    mainLayout->addWidget(leftWidget);
    mainLayout->addWidget(rightWidget);
}

QWidget *MainWindow::buildLeft()
{
    QWidget *widget = new QWidget(this);
    widget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    widget->setFixedWidth(150);
    leftLayout = new QVBoxLayout(widget);
    leftLayout->setContentsMargins(0, 0, 0, 0);
    leftLayout->setSpacing(0);
    QLabel *logo = new QLabel(widget);
    logo->setText(QStringLiteral("Logo"));
    logo->setAlignment(Qt::AlignCenter);
    leftLayout->addWidget(logo);
    QListWidget *list = new QListWidget(widget);
    list->setObjectName("sideList");
    list->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    list->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    const QStringList items = {
        QStringLiteral("任务参数"), QStringLiteral("设备管理"),
        QStringLiteral("任务日志"), QStringLiteral("任务管理"),
        QStringLiteral("授权管理"), QStringLiteral("系统管理")};
    const QStringList iconPaths = {
        ":/Res/Res/images/taskarg.png", ":/Res/Res/images/equipManage.png",
        ":/Res/Res/images/log.png", ":/Res/Res/images/taskManage.png",
        ":/Res/Res/images/authManage.png", ":/Res/Res/images/sysManage.png"};
    for (int i = 0; i < items.size(); ++i)
    {
        QListWidgetItem *listItem = new QListWidgetItem(list);
        listItem->setSizeHint(QSize(0, 62));

        QWidget *itemWidget = new QWidget();
        QVBoxLayout *itemLayout = new QVBoxLayout(itemWidget);
        itemLayout->setAlignment(Qt::AlignCenter);
        itemLayout->setContentsMargins(0, 6, 0, 6);
        itemLayout->setSpacing(4);

        QLabel *iconLabel = new QLabel(itemWidget);
        iconLabel->setAlignment(Qt::AlignCenter);
        iconLabel->setPixmap(QPixmap(iconPaths[i]).scaled(18, 18, Qt::KeepAspectRatio, Qt::SmoothTransformation));

        QLabel *label = new QLabel(items[i], itemWidget);
        label->setObjectName("navItemText");
        label->setAlignment(Qt::AlignCenter);

        itemLayout->addWidget(iconLabel);
        itemLayout->addWidget(label);
        list->setItemWidget(listItem, itemWidget);
    }
    leftLayout->addWidget(list);

    return widget;
}

QWidget *MainWindow::buildRight()
{
    QWidget *widget = new QWidget(this);
    rightLayout = new QVBoxLayout(widget);
    rightLayout->setContentsMargins(12, 12, 12, 12);
    rightLayout->setSpacing(8);

    QWidget *header = buildRightHeader();
    rightLayout->addWidget(header);

    taskParamsPage = new TaskParamsPage(widget);
    taskParamsPage->setObjectName("taskParamsPage");
    DeviceManagePage* deviceManagePage = new DeviceManagePage(widget);
    deviceManagePage->setObjectName("deviceManagePage");    
    TaskLogPage* taskLogPage = new TaskLogPage(widget);
    taskLogPage->setObjectName("taskLogPage");  
    TaskManagePage* taskManagePage = new TaskManagePage(widget);
    taskManagePage->setObjectName("taskManagePage");
    AuthManagePage* authManagePage = new AuthManagePage(widget);
    authManagePage->setObjectName("authManagePage");
    SystemManagePage* systemManagePage = new SystemManagePage(widget);
    systemManagePage->setObjectName("systemManagePage");
    QStackedWidget *stackedWidget = new QStackedWidget(widget);
    stackedWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    stackedWidget->addWidget(taskParamsPage);
    stackedWidget->addWidget(deviceManagePage);
    stackedWidget->addWidget(taskLogPage);
    stackedWidget->addWidget(taskManagePage);
    stackedWidget->addWidget(authManagePage);
    stackedWidget->addWidget(systemManagePage);
    rightLayout->addWidget(stackedWidget, 1);
    connect(leftWidget->findChild<QListWidget*>("sideList"), &QListWidget::currentRowChanged,
        stackedWidget, &QStackedWidget::setCurrentIndex);
    return widget;
}

QWidget *MainWindow::buildRightHeader()
{
    QWidget *header = new QWidget(this);
    header->setFixedHeight(56);
    header->setObjectName("page1Header");

    QHBoxLayout *lay = new QHBoxLayout(header);
    lay->setContentsMargins(16, 0, 16, 0);

    QLabel *title = new QLabel(
        QStringLiteral("停安打印刻录安全监控与审计系统(国产通用平台版)V5.3"), header);
    title->setObjectName("titleLabel");
    lay->addStretch();
    lay->addWidget(title);
    lay->addStretch();

    QPushButton *userBtn = new QPushButton(QStringLiteral("用户1▼"), header);
    userBtn->setObjectName("userBtn");
    QMenu *userMenu = new QMenu(userBtn);
    userMenu->addAction(QStringLiteral("个人中心"));
    userMenu->addAction(QStringLiteral("修改密码"));
    userMenu->addAction(QStringLiteral("退出登录"));
    userBtn->setMenu(userMenu);
    lay->addWidget(userBtn);

    QWidget *btnGroup = new QWidget(header);
    btnGroup->setObjectName("headerBtnWidget");
    QHBoxLayout *bLay = new QHBoxLayout(btnGroup);
    bLay->setContentsMargins(0, 0, 0, 0);
    bLay->setSpacing(10);

    QPushButton *setBtn = new QPushButton(QStringLiteral("≡"), btnGroup);
    setBtn->setObjectName("setBtn");
    QMenu *settingMenu = new QMenu(setBtn);
    settingMenu->addAction(QStringLiteral("1"));
    settingMenu->addAction(QStringLiteral("2"));
    settingMenu->addAction(QStringLiteral("3"));
    setBtn->setMenu(settingMenu);
    bLay->addWidget(setBtn);

    QPushButton *minBtn = new QPushButton(QStringLiteral("-"), btnGroup);
    minBtn->setObjectName("minBtn");
    connect(minBtn, &QPushButton::clicked, this, &QWidget::showMinimized);
    bLay->addWidget(minBtn);

    QPushButton *closeBtn = new QPushButton(QStringLiteral("x"), btnGroup);
    closeBtn->setObjectName("closeBtn");
    connect(closeBtn, &QPushButton::clicked, this, &QWidget::close);
    bLay->addWidget(closeBtn);

    lay->addWidget(btnGroup);
    return header;
}
