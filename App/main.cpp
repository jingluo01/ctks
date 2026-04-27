#include "MainWindow.h"
#include <QtWidgets/QApplication>
#include <QDir>
#include <QDebug>
#include <ctkPluginFrameworkFactory.h>
#include <ctkPluginFramework.h>
#include <ctkPluginException.h>
#include <ctkPluginContext.h>
#include <ctkPluginFrameworkLauncher.h>

void loadPluginPath(const QString &strPluginPath, QSharedPointer<ctkPluginFramework> framework)
{
    QDir dir(strPluginPath);

    // 设置过滤器：只保留 DLL 文件（不递归子目录）
    dir.setFilter(QDir::Files | QDir::NoDotAndDotDot);
    dir.setNameFilters(QStringList("*.dylib"));

    // 遍历目录中的文件
    QFileInfoList fileList = dir.entryInfoList();
    for (const QFileInfo &fileInfo : fileList)
    {
        QString pluginFile = fileInfo.absoluteFilePath();
        QUrl url = QUrl::fromLocalFile(pluginFile);
        QSharedPointer<ctkPlugin> plugin;
        try
        {
            plugin = framework->getPluginContext()->installPlugin(url);

            QHash<QString, QString> headers = plugin->getHeaders();
            // 获取MANIFEST.MF中的数据
            // QHash<QString, QString> headers = plugin->getHeaders();
            ctkVersion version = ctkVersion::parseVersion(headers.value(ctkPluginConstants::PLUGIN_VERSION));
            QString name = headers.value(ctkPluginConstants::PLUGIN_NAME);
        }
        catch (ctkPluginException e)
        {
            qDebug() << e.message() << e.getType();
        }
        try
        {
            if (plugin)
                plugin->start(ctkPlugin::START_TRANSIENT); // 表示立即启用插件，不设置参数的话加载后也不会立即打印输出
        }
        catch (ctkPluginException e)
        {
            qDebug() << e.message() << e.getType();
        }
    }
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QFile file(":/Qss/style.qss"); // 资源文件
    if (file.open(QFile::ReadOnly))
    {
        QString styleSheet = QLatin1String(file.readAll());
        qApp->setStyleSheet(styleSheet);
    }

    // 启动框架
    QString path = QCoreApplication::applicationDirPath() + "/ctkPlugins";
    ctkPluginFrameworkLauncher::addSearchPath(path, true);
    ctkPluginFrameworkFactory frameworkFactory;
    QSharedPointer<ctkPluginFramework> framework = frameworkFactory.getFramework();

    // 初始化并启动插件框架
    try
    {
        framework->init();
        framework->start();
        qDebug() << "CTK plugin framework start...";
    }
    catch (const ctkPluginException &e)
    {
        qDebug() << "CTK plugin framework init err: " << e.what();
        return -1;
    }
    loadPluginPath(QCoreApplication::applicationDirPath() + "/ctkPlugins", framework);

    MainWindow w(framework);
    w.show();

    return app.exec();
}
