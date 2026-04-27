#pragma once
#include <QObject>
#include <QtSql/QSqlDatabase>
#include<QCoreApplication>
#include <ctkPluginContext.h>
#include "IDatabaseService.h"

class DatabaseManagerImp : public QObject, public IDatabaseService
{
    Q_OBJECT
    Q_INTERFACES(IDatabaseService)
    // Q_PLUGIN_METADATA(IID "Ctk.IDatabaseService/1.0")

public:
    explicit DatabaseManagerImp(ctkPluginContext* context = nullptr);
    ~DatabaseManagerImp();

    bool    open()      override;
    void    close()     override;
    bool    isOpen()    override;
    QString lastError() override;

    QList<MijiRecord> queryAll()                             override;
    QList<MijiRecord> queryByKeyword(const QString& keyword) override;
    int               insert(const MijiRecord& rec)          override;
    bool              update(const MijiRecord& rec)          override;
    bool              deleteById(int id)                     override;
    bool              deleteByIds(const QList<int>& ids)     override;

private:
    ctkPluginContext* m_pluginContext;
    QSqlDatabase      m_database;
    QString           m_lastError;
};
