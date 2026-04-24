#pragma once

#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtCore/QFile>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QMenu>
#include <QtCore/QDebug>
#include "TaskParamsPage.h"
#include "DeviceManagePage.h"
#include "TaskLogPage.h"
#include "TaskManagePage.h"
#include "AuthManagePage.h"
#include "SystemManagePage.h"
// #include "TaskParamsPage.h"


class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();


private:
    void setupUI();
    QWidget* buildLeft();         // 左侧导航栏
    QWidget* buildRight();          // 右侧内容区
    QWidget* buildRightHeader();    // 右侧内容区的头部（标题 + 操作按钮）
    
    QHBoxLayout*        mainLayout;
    QWidget*            leftWidget;
    QVBoxLayout*        leftLayout;
    QWidget*            rightWidget;
    QVBoxLayout*        rightLayout;
    TaskParamsPage*     taskParamsPage;
    DeviceManagePage*   deviceManagePage;
    TaskLogPage*        taskLogPage;
    TaskManagePage*     taskManagePage;
    AuthManagePage*     authManagePage;
    SystemManagePage*   systemManagePage;

};
