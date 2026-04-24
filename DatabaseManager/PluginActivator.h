#pragma once
#include <qobject.h>
#include "ctkPluginActivator.h"
#include "ctkPluginContext.h"
#include "DatabaseManagerImp.h"
 
class PluginActivator : public QObject, ctkPluginActivator
{
	Q_OBJECT
	Q_INTERFACES(ctkPluginActivator)
	Q_PLUGIN_METADATA(IID "Ctk.IDatabaseService/1.0")
public:
	PluginActivator();
	void start(ctkPluginContext *context);
	void stop(ctkPluginContext *context);
private:
	QScopedPointer<DatabaseManagerImp> m_databaseMgr; //数据库管理服务实现
};
 