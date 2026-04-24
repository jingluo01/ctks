#include "PluginActivator.h"
#include <QDebug>
#include <ctkPluginContext.h>
 
PluginActivator::PluginActivator()
{
 
}
void PluginActivator::start(ctkPluginContext *context)
{
    //构建数据库管理服务
	m_databaseMgr.reset(new DatabaseManagerImp(context));
	

	// 注册数据库管理服务
	ctkDictionary dic;
	context->registerService<IDatabaseService>(m_databaseMgr.get(), dic);
}
 
void PluginActivator::stop(ctkPluginContext *context)
{
	// 注销数据库管理服务
	ctkServiceReference  ref = context->getServiceReference<IDatabaseService>();
	context->ungetService(ref);
}