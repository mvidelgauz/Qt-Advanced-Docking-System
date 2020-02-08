#include <MainWindow.h>
#include <QString>
#include <QFile>
#include <QApplication>
#include <QDebug>

#include <memory>


const char* QtMsgTypeToText(QtMsgType type)
{
    switch (type) {
    case QtDebugMsg:
        return "Debug";
    case QtInfoMsg:
        return "Info";
    case QtWarningMsg:
        return "Warning";
    case QtCriticalMsg:
        return "Critical";
    case QtFatalMsg:
        return "Fatal";
    default:
        return "Unknown";
    }

}
void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    
    fprintf(stdout, "%s: %s", QtMsgTypeToText(type), localMsg.constData());
    //fprintf(stdout, "(%s:%u, %s)", context.file, context.line, context.function);
    fprintf(stdout, "\n");
    
    if(QtFatalMsg == type)
    {
        abort();
    }

    fflush(stderr);
    fflush(stdout);
}

int main(int argc, char *argv[])
{
	QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
#if QT_VERSION >= 0x050600
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
	std::shared_ptr<int> b;
	QApplication a(argc, argv);
	a.setQuitOnLastWindowClosed(true);

	QFile StyleSheetFile(":/adsdemo/app.css");
	StyleSheetFile.open(QIODevice::ReadOnly);
	QTextStream StyleSheetStream(&StyleSheetFile);
	a.setStyleSheet(StyleSheetStream.readAll());
	StyleSheetFile.close();

	qInstallMessageHandler(myMessageOutput);
	qDebug() << "Message handler test";

	CMainWindow mw;
	mw.show();
	return a.exec();
}
