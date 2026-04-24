#include "AuthManagePage.h"
#include <QVBoxLayout>
#include <QLabel>

AuthManagePage::AuthManagePage(QWidget* parent) : QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    QLabel* label = new QLabel(QStringLiteral("授权管理"), this);
    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label);
}
