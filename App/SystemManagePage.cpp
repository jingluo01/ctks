#include "SystemManagePage.h"
#include <QVBoxLayout>
#include <QLabel>

SystemManagePage::SystemManagePage(QWidget* parent) : QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    QLabel* label = new QLabel(QStringLiteral("系统管理"), this);
    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label);
}
