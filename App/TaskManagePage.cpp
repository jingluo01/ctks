#include "TaskManagePage.h"
#include <QVBoxLayout>
#include <QLabel>

TaskManagePage::TaskManagePage(QWidget* parent) : QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    QLabel* label = new QLabel(QStringLiteral("任务管理"), this);
    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label);
}
