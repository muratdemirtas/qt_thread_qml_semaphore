Using Semaphore On Qt Using QThreads,WorkerTasks,Signal-Slots and QML
======================

Overview
--------

A semaphore is a synchronization object that controls access by multiple processes to a common resource in a parallel programming environment. Semaphores are widely used to control access to files and shared memory. The three basic functionalities associated with semaphores are set, check and wait until it clears to set it again. |

Semaphores are used to address benchmark synchronization problems.

The concept of semaphore was put forth by the Dutch computer scientist Edsger Dijkstra.

Watch the console output to see if it works.

Installation
------------

This program requires a working Qt5 installation. It was tested with version 5.3 and 5.4.

In order to compile and run the program, execute the following commands.

~~~
qmake qt_threads_semaphores_qml.pro
make
./qt_threads_semaphores_qml
~~~

Alternatively, the project can be loaded into Qt Creator and started from there.

![alt tag](http://image-store.slidesharecdn.com/4aeb7fb9-a3a1-45c9-b028-f655a05537e6-original.png)
