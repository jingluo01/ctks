#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QTabWidget>
#include <QHeaderView>
#include <QPainter>
#include <QMouseEvent>
#include <QShowEvent>
#include <QResizeEvent>
#include <QCheckBox>
#include <QStyleOptionButton>
#include <ctkPluginFramework.h>
#include "DatabaseManager/IDatabaseService.h"

class CheckBoxHeader : public QHeaderView
{
    Q_OBJECT
public:
    explicit CheckBoxHeader(Qt::Orientation orientation, QWidget* parent = nullptr)
        : QHeaderView(orientation, parent)
    {
        setSectionsClickable(true);
        m_checkBox = new QCheckBox(this);
        connect(m_checkBox, &QCheckBox::stateChanged, this, &CheckBoxHeader::checkStateChanged);
    }

    void updateCheckBox()
    {
        int w = sectionSize(0);
        int s = m_checkBox->sizeHint().width();
        int x = sectionViewportPosition(0) + (w - s) / 2;
        int y = (height() - s) / 2;
        m_checkBox->setGeometry(x, y, s, s);
    }

signals:
    void checkStateChanged(int state);

protected:
    void paintSection(QPainter* painter, const QRect& rect, int logicalIndex) const override
    {
        QHeaderView::paintSection(painter, rect, logicalIndex);
    }

    void showEvent(QShowEvent* e) override
    {
        QHeaderView::showEvent(e);
        updateCheckBox();
    }

    void resizeEvent(QResizeEvent* e) override
    {
        QHeaderView::resizeEvent(e);
        updateCheckBox();
    }

private:
    QCheckBox* m_checkBox = nullptr;
};

class TaskParamsPage : public QWidget
{
    Q_OBJECT
public:
    explicit TaskParamsPage(QSharedPointer<ctkPluginFramework> framework, QWidget* parent = nullptr);

private slots:
    void onSearchClicked();
    void onResetClicked();
    void onAddClicked();
    void onDeleteClicked();
    void onEditClicked();
    void onDeleteRowClicked();

private:
    void setupUI();
    void initTab(QWidget* tab);
    void initTableData(const QList<MijiRecord>& records);
    bool showDialog(MijiRecord& rec);

    QSharedPointer<ctkPluginFramework> m_framework;
    IDatabaseService* m_dbService = nullptr;

    QVBoxLayout* mainLayout;
    
    
    QLineEdit*    m_keywordEdit = nullptr;
    QTableWidget* m_table       = nullptr;
};
