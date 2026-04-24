#pragma once
#include <QString>
#include <QList>
#include <QtPlugin>

struct MijiRecord {
    int     id          = 0;
    QString name;
    QString shortName;
    int     level       = 0;
    int     saveDays    = 0;
    int     timeoutMins = 0;
    QString isShow;
    QString description;
};

class IDatabaseService
{
public:
    IDatabaseService() = default;
    IDatabaseService(const IDatabaseService&) = delete;
    IDatabaseService& operator=(const IDatabaseService&) = delete;
    virtual ~IDatabaseService() = default;

    virtual bool    open()      = 0;
    virtual void    close()     = 0;
    virtual bool    isOpen()    = 0;
    virtual QString lastError() = 0;

    virtual QList<MijiRecord> queryAll()                            = 0;
    virtual QList<MijiRecord> queryByKeyword(const QString& keyword)= 0;
    virtual int               insert(const MijiRecord& rec)         = 0;
    virtual bool              update(const MijiRecord& rec)         = 0;
    virtual bool              deleteById(int id)                    = 0;
    virtual bool              deleteByIds(const QList<int>& ids)    = 0;
};

Q_DECLARE_INTERFACE(IDatabaseService, "Ctk.IDatabaseService/1.0")
