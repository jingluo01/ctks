#include "DatabaseManagerImp.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

DatabaseManagerImp::DatabaseManagerImp(ctkPluginContext* context)
    : m_pluginContext(context)
{
    m_database = QSqlDatabase::addDatabase("QSQLITE", "MainConnection");
    m_database.setDatabaseName(QCoreApplication::applicationDirPath() + "/system.db");

}

DatabaseManagerImp::~DatabaseManagerImp()
{
    close();
}


bool DatabaseManagerImp::open()
{
    if (m_database.isOpen()) return true;
    // Try to open the database, retry once if failed
    for (int attempt = 0; attempt < 2; ++attempt) {
        if (m_database.open()) {
            return true;
        }
        m_lastError = m_database.lastError().text();
        qDebug() << "[DB] open failed (attempt" << (attempt + 1) << "):" << m_lastError;
        if (attempt == 0) {
            // Close and try again
            m_database.close();
        }
    }
    return false;
}

void DatabaseManagerImp::close()
{
    if (m_database.isOpen())
        m_database.close();
}

bool DatabaseManagerImp::isOpen()
{
    return m_database.isOpen();
}

QString DatabaseManagerImp::lastError()
{
    return m_lastError;
}

QList<MijiRecord> DatabaseManagerImp::queryAll()
{
    return queryByKeyword({});
}

QList<MijiRecord> DatabaseManagerImp::queryByKeyword(const QString& keyword)
{
    QList<MijiRecord> result;
    QSqlQuery q(m_database);
    if (keyword.trimmed().isEmpty()) {
        q.exec("SELECT id,name,short_name,level,save_days,timeout_mins,is_show,description "
               "FROM mijis ORDER BY level DESC");
    } else {
        const QString like = "%" + keyword.trimmed() + "%";
        q.prepare("SELECT id,name,short_name,level,save_days,timeout_mins,is_show,description "
                  "FROM mijis WHERE name LIKE :kw OR short_name LIKE :kw OR description LIKE :kw "
                  "ORDER BY level DESC");
        q.bindValue(":kw", like);
        q.exec();
    }
    while (q.next()) {
        MijiRecord r;
        r.id          = q.value(0).toInt();
        r.name        = q.value(1).toString();
        r.shortName   = q.value(2).toString();
        r.level       = q.value(3).toInt();
        r.saveDays    = q.value(4).toInt();
        r.timeoutMins = q.value(5).toInt();
        r.isShow      = q.value(6).toString();
        r.description = q.value(7).toString();
        result << r;
    }
    return result;
}

int DatabaseManagerImp::insert(const MijiRecord& rec)
{
    QSqlQuery q(m_database);
    q.prepare("INSERT INTO mijis (name,short_name,level,save_days,timeout_mins,is_show,description) "
              "VALUES (:name,:sn,:lv,:sd,:tm,:is,:desc)");
    q.bindValue(":name", rec.name);
    q.bindValue(":sn",   rec.shortName);
    q.bindValue(":lv",   rec.level);
    q.bindValue(":sd",   rec.saveDays);
    q.bindValue(":tm",   rec.timeoutMins);
    q.bindValue(":is",   rec.isShow);
    q.bindValue(":desc", rec.description);
    return q.exec() ? q.lastInsertId().toInt() : -1;
}

bool DatabaseManagerImp::update(const MijiRecord& rec)
{
    QSqlQuery q(m_database);
    q.prepare("UPDATE mijis SET name=:name,short_name=:sn,level=:lv,"
              "save_days=:sd,timeout_mins=:tm,is_show=:is,description=:desc WHERE id=:id");
    q.bindValue(":name", rec.name);
    q.bindValue(":sn",   rec.shortName);
    q.bindValue(":lv",   rec.level);
    q.bindValue(":sd",   rec.saveDays);
    q.bindValue(":tm",   rec.timeoutMins);
    q.bindValue(":is",   rec.isShow);
    q.bindValue(":desc", rec.description);
    q.bindValue(":id",   rec.id);
    return q.exec();
}

bool DatabaseManagerImp::deleteById(int id)
{
    return deleteByIds({id});
}

bool DatabaseManagerImp::deleteByIds(const QList<int>& ids)
{
    if (ids.isEmpty()) return true;
    QStringList ph;
    for (int i = 0; i < ids.size(); ++i) ph << "?";
    QSqlQuery q(m_database);
    q.prepare(QString("DELETE FROM mijis WHERE id IN (%1)").arg(ph.join(",")));
    for (int id : ids) q.addBindValue(id);
    return q.exec();
}
