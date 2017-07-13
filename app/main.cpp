#include <QApplication>
#include <QDebug>

#include "mainwindow.h"

MainWindow * pw;

void (*oldMH)(QtMsgType, const QMessageLogContext &, const QString &);


void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    oldMH(type,context,msg);
    //(void)context;
    QByteArray localMsg = msg.toLocal8Bit();

    switch (type) {
    case QtDebugMsg:
        pw->appendLog(QString("Debug: ") + localMsg.constData());
//        fprintf(stderr, "Debug: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtInfoMsg:
        pw->appendLog(QString("Info: ") + localMsg.constData());
//        fprintf(stderr, "Info: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtWarningMsg:
        pw->appendLog(QString("Warning: ") + localMsg.constData());
//        fprintf(stderr, "Warning: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtCriticalMsg:
        pw->appendLog(QString("Critical: ") + localMsg.constData());
//        fprintf(stderr, "Critical: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtFatalMsg:
        pw->appendLog(QString("Fatal: ") + localMsg.constData());
//        fprintf(stderr, "Fatal: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        abort();
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    pw = &w;
    oldMH = qInstallMessageHandler(myMessageOutput); // Install the handler
    w.show();

#define Q(x) #x
#define QUOTE(x) Q(x)
    qInfo() << "############################################";
    qInfo() << "       " QUOTE(APP_NAME);
    qInfo() << "  Ver. " QUOTE(APP_VERSION) "  -  " __DATE__;
    qInfo() << "  "      QUOTE(APP_REVISION);
    qInfo() << "############################################";

    return a.exec();
}

