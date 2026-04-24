#include "DeviceManagePage.h"
#include <QVBoxLayout>
#include <QLabel>

DeviceManagePage::DeviceManagePage(QWidget* parent) : QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    QLabel* label = new QLabel(QStringLiteral("设备管理"), this);
    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label);
}
