#include "workerthread.h"
#include <QDebug>
#include <QThread>
#include <QSemaphore>

extern QSemaphore gaugeSemaphore;

workerThread::workerThread(int threadID, int delayTime,
                           QObject *parent) :
    QObject(parent)
{

    m_myWorkerTaskID = threadID;
    m_myDelayTime    = delayTime;
    qDebug() << "Hey!! I received your parameters" ;
    qDebug() << "My ID is: " << m_myWorkerTaskID << "and delay is: "
                                                 << m_myDelayTime ;
}

workerThread::workerThread(QObject *parent) :
    QObject(parent)
{

}


void workerThread::Start()
{

      while(true)
      {
         qDebug() << "Hey!! I'm Working. My ID is :" << m_myWorkerTaskID ;
         QThread::sleep(m_myDelayTime);

         if(gaugeSemaphore.tryAcquire(0,SEMAPHORE_TIMEOUT))
         {
             QString notifyMessage = "GAUGE SEMAPHORE TAKED BY THREAD: ";
             notifyMessage += QString::number(m_myWorkerTaskID);
             qDebug() << notifyMessage;
             QVariant f = notifyMessage ;


             int MAX_VALUE = 280, MIN_VALUE = 0;
             int randomValue = qrand() % ((MAX_VALUE + 1) - MIN_VALUE) + MIN_VALUE;

             emit updateValueOfGauge(randomValue);
             emit sendMessageToQML(f);   //emit signal for qml
             gaugeSemaphore.release(0);
         }
         else
         {
             qDebug() << "GAUGE SEMAPHORE TAKE FAILED WITH THREAD: " << m_myWorkerTaskID ;
         }
}
}

void workerThread::stopWorkerTask()
{
   this->deleteLater();
}
