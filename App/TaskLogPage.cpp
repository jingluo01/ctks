#include "TaskLogPage.h"
#include <QVBoxLayout>
#include <QLabel>

TaskLogPage::TaskLogPage(QWidget* parent) : QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    QLabel* label = new QLabel(QStringLiteral("任务日志"), this);
    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label);
}
