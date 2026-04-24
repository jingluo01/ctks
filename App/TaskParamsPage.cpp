#include "TaskParamsPage.h"
#include <QCheckBox>

TaskParamsPage::TaskParamsPage(QWidget* parent)
    : QWidget(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setObjectName("pageWidget");

    QVBoxLayout* root = new QVBoxLayout(this);
    root->setContentsMargins(24, 12, 24, 16);
    root->setSpacing(10);

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

    setupMijiTab(tab1);
    root->addWidget(tabs);
}

void TaskParamsPage::setupMijiTab(QWidget* tab)
{
    QVBoxLayout* layout = new QVBoxLayout(tab);
    layout->setContentsMargins(0, 15, 0, 0);
    layout->setSpacing(15);

    // 工具栏
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
    tLay->addWidget(searchBtn);
    tLay->addWidget(resetBtn);
    tLay->addWidget(addBtn);
    tLay->addWidget(deleteBtn);
    tLay->addStretch();
    layout->addWidget(toolbar);

    // 表格
    m_table = new QTableWidget(tab);
    m_table->setObjectName("tableWidget");
    m_table->setColumnCount(9);

    CheckBoxHeader* cbHeader = new CheckBoxHeader(Qt::Horizontal, m_table);
    m_table->setHorizontalHeader(cbHeader);

    QStringList headers = {
        " ",
        QStringLiteral("密级"),           QStringLiteral("密级简写"),
        QStringLiteral("密集等级"),       QStringLiteral("内容保存天数"),
        QStringLiteral("任务超时分钟数"), QStringLiteral("是否显示"),
        QStringLiteral("密级说明"),       QStringLiteral("操作")
    };
    m_table->setHorizontalHeaderLabels(headers);
    m_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_table->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    m_table->verticalHeader()->setVisible(false);

    layout->addWidget(m_table);
}
