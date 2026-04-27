#include "TaskParamsPage.h"
#include <QCheckBox>
#include <QDialog>
#include <QFormLayout>
#include <QSpinBox>
#include <QComboBox>
#include <QTextEdit>
#include <QMessageBox>
#include <ctkPluginContext.h>
#include <ctkServiceReference.h>

TaskParamsPage::TaskParamsPage(QSharedPointer<ctkPluginFramework> framework, QWidget* parent)
    : QWidget(parent), m_framework(framework)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    if (m_framework && m_framework->getPluginContext()) {
        ctkServiceReference ref = m_framework->getPluginContext()->getServiceReference<IDatabaseService>();
        if (ref) {
            m_dbService = qobject_cast<IDatabaseService*>(
                m_framework->getPluginContext()->getService(ref));
            if (m_dbService && !m_dbService->isOpen())
                m_dbService->open();
        }
    }

    setupUI();
}

void TaskParamsPage::setupUI()
{
    mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);

    QTabWidget* tabs = new QTabWidget(this);
    tabs->setObjectName("tabWidget");

    QWidget* tab1 = new QWidget(); tab1->setObjectName("tab1");
    QWidget* tab2 = new QWidget(); tab2->setObjectName("tab2");
    QWidget* tab3 = new QWidget(); tab3->setObjectName("tab3");
    QWidget* tab4 = new QWidget(); tab4->setObjectName("tab4");
    QWidget* tab5 = new QWidget(); tab5->setObjectName("tab5");

    tabs->addTab(tab1, QStringLiteral("密级设置"));
    tabs->addTab(tab2, QStringLiteral("审批员配置"));
    tabs->addTab(tab3, QStringLiteral("打印流水号"));
    tabs->addTab(tab4, QStringLiteral("刻录流水号"));
    tabs->addTab(tab5, QStringLiteral("条码设置"));
    tabs->tabBar()->setExpanding(true);
    tabs->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);


    initTab(tab1);
    if (m_dbService)
        initTableData(m_dbService->queryAll());
    mainLayout->addWidget(tabs);
}

void TaskParamsPage::initTab(QWidget* tab)
{
    QVBoxLayout* layout = new QVBoxLayout(tab);
    layout->setContentsMargins(0, 15, 0, 0);
    layout->setSpacing(15);

    QWidget* toolbar = new QWidget(tab);
    toolbar->setObjectName("tab1ToolsWidget");
    QHBoxLayout* tLay = new QHBoxLayout(toolbar);
    tLay->setContentsMargins(0, 0, 0, 0);
    tLay->setSpacing(15);

    tLay->addWidget(new QLabel(QStringLiteral("关键字："), toolbar));

    m_keywordEdit = new QLineEdit(toolbar);
    m_keywordEdit->setObjectName("KeywordEdit");
    m_keywordEdit->setPlaceholderText(QStringLiteral("请输入关键字搜索"));
    tLay->addWidget(m_keywordEdit);

    QPushButton* searchBtn = new QPushButton(QStringLiteral("搜索"), toolbar);
    QPushButton* resetBtn  = new QPushButton(QStringLiteral("重置"), toolbar);
    QPushButton* addBtn    = new QPushButton(QStringLiteral("新增"), toolbar);
    QPushButton* deleteBtn = new QPushButton(QStringLiteral("删除"), toolbar);
    searchBtn->setObjectName("searchBtn");
    resetBtn->setObjectName("resetBtn");
    addBtn->setObjectName("addBtn");
    deleteBtn->setObjectName("deleteBtn");

    connect(searchBtn, &QPushButton::clicked, this, &TaskParamsPage::onSearchClicked);
    connect(resetBtn,  &QPushButton::clicked, this, &TaskParamsPage::onResetClicked);
    connect(addBtn,    &QPushButton::clicked, this, &TaskParamsPage::onAddClicked);
    connect(deleteBtn, &QPushButton::clicked, this, &TaskParamsPage::onDeleteClicked);

    tLay->addWidget(searchBtn);
    tLay->addWidget(resetBtn);
    tLay->addWidget(addBtn);
    tLay->addWidget(deleteBtn);
    tLay->addStretch();
    layout->addWidget(toolbar);

    m_table = new QTableWidget(tab);
    m_table->setObjectName("tableWidget");
    m_table->setColumnCount(9);

    CheckBoxHeader* cbHeader = new CheckBoxHeader(Qt::Horizontal, m_table);
    m_table->setHorizontalHeader(cbHeader);

    connect(cbHeader, &CheckBoxHeader::checkStateChanged, this, [this](int state) {
        for (int i = 0; i < m_table->rowCount(); ++i) {
            QWidget* w = m_table->cellWidget(i, 0);
            if (!w) continue;
            QCheckBox* cb = w->findChild<QCheckBox*>();
            if (cb) cb->setChecked(state == Qt::Checked);
        }
    });

    m_table->setHorizontalHeaderLabels({
        " ",
        QStringLiteral("密级"),           QStringLiteral("密级简写"),
        QStringLiteral("密集等级"),       QStringLiteral("内容保存天数"),
        QStringLiteral("任务超时分钟数"), QStringLiteral("是否显示"),
        QStringLiteral("密级说明"),       QStringLiteral("操作")
    });
    m_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_table->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    m_table->verticalHeader()->setVisible(false);

    layout->addWidget(m_table);
}

void TaskParamsPage::initTableData(const QList<MijiRecord>& records)
{
    m_table->setRowCount(records.size());

    for (int i = 0; i < records.size(); ++i) {
        const MijiRecord& rec = records[i]; 

        QCheckBox* cb = new QCheckBox();
        cb->setProperty("recordId", rec.id);
        QWidget* cbWidget = new QWidget();
        QHBoxLayout* cbLayout = new QHBoxLayout(cbWidget);
        cbLayout->addWidget(cb);
        cbLayout->setAlignment(Qt::AlignCenter);
        cbLayout->setContentsMargins(0, 0, 0, 0);
        m_table->setCellWidget(i, 0, cbWidget);

        m_table->setItem(i, 1, new QTableWidgetItem(rec.name));
        m_table->setItem(i, 2, new QTableWidgetItem(rec.shortName));
        m_table->setItem(i, 3, new QTableWidgetItem(QString::number(rec.level)));
        m_table->setItem(i, 4, new QTableWidgetItem(QString::number(rec.saveDays)));
        m_table->setItem(i, 5, new QTableWidgetItem(QString::number(rec.timeoutMins)));
        m_table->setItem(i, 6, new QTableWidgetItem(rec.isShow));
        m_table->setItem(i, 7, new QTableWidgetItem(rec.description));

        QWidget* btnWidget = new QWidget();
        QHBoxLayout* btnLayout = new QHBoxLayout(btnWidget);
        btnLayout->setContentsMargins(0, 0, 0, 0);
        btnLayout->setSpacing(10);

        QPushButton* editBtn   = new QPushButton(QStringLiteral("编辑"));
        QPushButton* deleteBtn = new QPushButton(QStringLiteral("删除"));
        editBtn->setProperty("recordId", rec.id);
        deleteBtn->setProperty("recordId", rec.id);
        connect(editBtn,   &QPushButton::clicked, this, &TaskParamsPage::onEditClicked);
        connect(deleteBtn, &QPushButton::clicked, this, &TaskParamsPage::onDeleteRowClicked);

        btnLayout->addWidget(editBtn);
        btnLayout->addWidget(deleteBtn);
        btnLayout->addStretch();
        m_table->setCellWidget(i, 8, btnWidget);
    }
}

// 只负责渲染对话框，用户确认后将表单数据写回 rec，取消返回 false
bool TaskParamsPage::showDialog(MijiRecord& rec)
{
    QDialog dlg(this);
    dlg.setWindowTitle(rec.id == -1 ? QStringLiteral("新增密级") : QStringLiteral("编辑密级"));
    dlg.setMinimumWidth(400);
    dlg.setModal(true);

    QVBoxLayout* root = new QVBoxLayout(&dlg);
    root->setSpacing(16);
    root->setContentsMargins(24, 20, 24, 20);

    QFormLayout* form = new QFormLayout();
    form->setSpacing(12);
    form->setLabelAlignment(Qt::AlignRight);

    QLineEdit* nameEdit      = new QLineEdit(rec.name, &dlg);
    QLineEdit* shortNameEdit = new QLineEdit(rec.shortName, &dlg);
    nameEdit->setMinimumWidth(200);
    shortNameEdit->setMinimumWidth(200);
    QSpinBox*  levelSpin     = new QSpinBox(&dlg);
    QSpinBox*  saveDaysSpin  = new QSpinBox(&dlg);
    QSpinBox*  timeoutSpin   = new QSpinBox(&dlg);
    QComboBox* isShowCombo   = new QComboBox(&dlg);
    QTextEdit* descEdit      = new QTextEdit(rec.description, &dlg);

    for (QSpinBox* s : {levelSpin, saveDaysSpin, timeoutSpin})
        s->setRange(0, 9999);
    levelSpin->setValue(rec.level);
    saveDaysSpin->setValue(rec.saveDays);
    timeoutSpin->setValue(rec.timeoutMins);

    isShowCombo->addItem(QStringLiteral("是"), "1");
    isShowCombo->addItem(QStringLiteral("否"), "0");
    int idx = isShowCombo->findData(rec.isShow);
    if (idx >= 0) isShowCombo->setCurrentIndex(idx);

    descEdit->setFixedHeight(80);

    form->addRow(QStringLiteral("密级："),          nameEdit);
    form->addRow(QStringLiteral("密级简写："),       shortNameEdit);
    form->addRow(QStringLiteral("密级等级："),       levelSpin);
    form->addRow(QStringLiteral("内容保存天数："),   saveDaysSpin);
    form->addRow(QStringLiteral("任务超时分钟数："), timeoutSpin);
    form->addRow(QStringLiteral("是否显示："),       isShowCombo);
    form->addRow(QStringLiteral("密级说明："),       descEdit);
    root->addLayout(form);

    QHBoxLayout* btnLay = new QHBoxLayout();
    btnLay->addStretch();
    QPushButton* saveBtn   = new QPushButton(QStringLiteral("保存"), &dlg);
    QPushButton* cancelBtn = new QPushButton(QStringLiteral("取消"), &dlg);
    saveBtn->setFixedWidth(80);
    cancelBtn->setFixedWidth(80);
    btnLay->addWidget(saveBtn);
    btnLay->addWidget(cancelBtn);
    root->addLayout(btnLay);

    connect(cancelBtn, &QPushButton::clicked, &dlg, &QDialog::reject);
    connect(saveBtn,   &QPushButton::clicked, &dlg, [&]() {
        if (nameEdit->text().trimmed().isEmpty()) { nameEdit->setFocus(); return; }
        dlg.accept();
    });

    if (dlg.exec() != QDialog::Accepted) return false;

    // 将表单数据写回 rec，由调用方决定如何持久化
    rec.name        = nameEdit->text().trimmed();
    rec.shortName   = shortNameEdit->text().trimmed();
    rec.level       = levelSpin->value();
    rec.saveDays    = saveDaysSpin->value();
    rec.timeoutMins = timeoutSpin->value();
    rec.isShow      = isShowCombo->currentData().toString();
    rec.description = descEdit->toPlainText().trimmed();
    return true;
}

void TaskParamsPage::onSearchClicked()
{
    if (!m_dbService) return;
    QString kw = m_keywordEdit->text().trimmed();
    initTableData(kw.isEmpty() ? m_dbService->queryAll() : m_dbService->queryByKeyword(kw));
}

void TaskParamsPage::onResetClicked()
{
    m_keywordEdit->clear();
    onSearchClicked();
}

void TaskParamsPage::onAddClicked()
{
    if (!m_dbService) return;
    MijiRecord rec;
    rec.id = -1;
    if (!showDialog(rec)) return;

    if (m_dbService->insert(rec) <= 0)
        QMessageBox::warning(this, QStringLiteral("错误"), QStringLiteral("新增失败：") + m_dbService->lastError());
    else
        onResetClicked();
}

void TaskParamsPage::onDeleteClicked()
{
    if (!m_dbService) return;
    QList<int> ids;
    for (int i = 0; i < m_table->rowCount(); ++i) {
        QWidget* w = m_table->cellWidget(i, 0);
        if (!w) continue;
        QCheckBox* cb = w->findChild<QCheckBox*>();
        if (cb && cb->isChecked())
            ids.append(cb->property("recordId").toInt());
    }
    if (ids.isEmpty()) return;
    if (!m_dbService->deleteByIds(ids))
        QMessageBox::warning(this, QStringLiteral("错误"), QStringLiteral("删除失败：") + m_dbService->lastError());
    else
        onResetClicked();
}

void TaskParamsPage::onEditClicked()
{
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    if (!btn || !m_dbService) return;

    int id = btn->property("recordId").toInt();
    MijiRecord rec;
    bool found = false;
    for (const MijiRecord& r : m_dbService->queryAll()) {
        if (r.id == id) { rec = r; found = true; break; }
    }
    if (!found) return;

    if (!showDialog(rec)) return;

    if (!m_dbService->update(rec))
        QMessageBox::warning(this, QStringLiteral("错误"), QStringLiteral("编辑失败：") + m_dbService->lastError());
    else
        onResetClicked();
}

void TaskParamsPage::onDeleteRowClicked()
{
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    if (!btn || !m_dbService) return;
    int id = btn->property("recordId").toInt();
    if (!m_dbService->deleteById(id))
        QMessageBox::warning(this, QStringLiteral("错误"), QStringLiteral("删除失败：") + m_dbService->lastError());
    else
        onResetClicked();
}
