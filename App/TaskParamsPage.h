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
#include <QStyleOptionButton>

class CheckBoxHeader : public QHeaderView
{
    Q_OBJECT
public:
    explicit CheckBoxHeader(Qt::Orientation orientation, QWidget* parent = nullptr)
        : QHeaderView(orientation, parent), m_state(Qt::Unchecked)
    {
        setSectionsClickable(true);
    }

signals:
    void checkStateChanged(int state);

protected:
    void paintSection(QPainter* painter, const QRect& rect, int logicalIndex) const override
    {
        QHeaderView::paintSection(painter, rect, logicalIndex);
        if (logicalIndex == 0) {
            QStyleOptionButton opt;
            const int s = 16;
            opt.rect  = QRect(rect.center().x() - s/2, rect.center().y() - s/2, s, s);
            opt.state = QStyle::State_Enabled;
            if      (m_state == Qt::Checked)          opt.state |= QStyle::State_On;
            else if (m_state == Qt::PartiallyChecked) opt.state |= QStyle::State_NoChange;
            else                                      opt.state |= QStyle::State_Off;
            style()->drawControl(QStyle::CE_CheckBox, &opt, painter);
        }
    }

    void mousePressEvent(QMouseEvent* event) override
    {
        if (logicalIndexAt(event->pos()) == 0) {
            int p = sectionViewportPosition(0), w = sectionSize(0);
            const int s = 16;
            QRect cb(QRect(p, 0, w, height()).center().x() - s/2,
                     QRect(p, 0, w, height()).center().y() - s/2, s, s);
            if (cb.contains(event->pos())) {
                m_state = (m_state == Qt::Unchecked) ? Qt::Checked : Qt::Unchecked;
                emit checkStateChanged((int)m_state);
                updateSection(0);
                return;
            }
        }
        QHeaderView::mousePressEvent(event);
    }

private:
    Qt::CheckState m_state;
};

class TaskParamsPage : public QWidget
{
    Q_OBJECT
public:
    explicit TaskParamsPage(QWidget* parent = nullptr);

private:
    void setupMijiTab(QWidget* tab);

    QLineEdit*    m_keywordEdit = nullptr;
    QTableWidget* m_table       = nullptr;
};
