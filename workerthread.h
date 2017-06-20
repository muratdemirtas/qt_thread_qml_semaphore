#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QObject>
#include <QVariant>

#define FIRST_WORKER_ID         1
#define SECOND_WORKER_ID        2
#define FIRST_WORKER_DELAY      2
#define SECOND_WORKER_DELAY     3
#define SEMAPHORE_TIMEOUT       1

enum
{
    SEMAPHORE_FAIL,
    SEMAPHORE_OK,
    THREAD_FAIL
}errCodes;


class workerThread : public QObject
{
    Q_OBJECT
public:
    explicit workerThread(int threadID,int delayTime,
                          QObject *parent = 0);

    explicit workerThread(QObject *parent = 0);

public slots:
    void Start();
    void stopWorkerTask();
private:
    int  m_myWorkerTaskID;
    int  m_myDelayTime;
signals:
    void sendMessageToQML(QVariant threadID);
    void updateValueOfGauge(QVariant gaugeValue);

};

#endif // WORKERTHREAD_H
