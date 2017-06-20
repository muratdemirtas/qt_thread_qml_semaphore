#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QObject>
#include "workerthread.h"
#include <QObject>
#include <QThread>
#include <QQuickWindow>
#include <QSemaphore>



QSemaphore gaugeSemaphore;

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    qmlRegisterType<workerThread>("com.thread.demo", 1, 0, "thread");

    QObject *topLevel = engine.rootObjects().value(0);

    QQuickWindow *window = qobject_cast<QQuickWindow *>(topLevel);

        // connect our C++ signal to our QML slot
        // NOTE: if we want to pass an parameter to our QML slot, it has to be
        // a QVariant.


    if (gaugeSemaphore.tryAcquire(0,1))
        qDebug() << "gauge semaphore taked on startup";

    else
    {
        qDebug() << "gauge semaphore take failed on startup";
        exit(SEMAPHORE_FAIL);
    }

    QThread* task1 = new QThread;
    QThread* task2 = new QThread;

    workerThread* workertask1 = new workerThread(FIRST_WORKER_ID,
                                              FIRST_WORKER_DELAY);
    workerThread* workertask2 = new workerThread(SECOND_WORKER_ID,
                                              SECOND_WORKER_DELAY);

    workertask1->moveToThread(task1);
    workertask2->moveToThread(task2);

    task1->start();
    task2->start();


    QObject::connect(task1,SIGNAL(started()),workertask1,SLOT(Start()));
    QObject::connect(task2,SIGNAL(started()),workertask2,SLOT(Start()));
    QObject::connect(task1,SIGNAL(finished()),workertask1,SLOT(deleteLater()));
    QObject::connect(task2,SIGNAL(finished()),workertask2,SLOT(deleteLater()));

    QObject::connect(workertask1, SIGNAL(sendMessageToQML(QVariant)),
                                  window, SLOT(setTextField(QVariant)));

    QObject::connect(workertask2, SIGNAL(sendMessageToQML(QVariant)),
                                  window, SLOT(setTextField(QVariant)));

    QObject::connect(workertask1, SIGNAL(updateValueOfGauge(QVariant)),
                                  window, SLOT(updateGaugeValue(QVariant)));

    QObject::connect(workertask2, SIGNAL(updateValueOfGauge(QVariant)),
                                  window, SLOT(updateGaugeValue(QVariant)));

    return app.exec();
}
