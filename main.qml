import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Extras 1.4

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("QT/QML QThread Semaphore Example V1.0")

        CircularGauge {
            id: circularGauge
            x: 130
            y: 44
            width: 407
            height: 273
            opacity: 1
            clip: true
            visible: true
            maximumValue: 280
            enabled: true
            smooth: true
        }

        Label {
            id: threadInfo
            x: 130
            y: 342
            width: 407
            height: 20
            text: qsTr("Label")
        }


    function setTextField(text)
    {
        threadInfo.text = text;
    }

    function updateGaugeValue(value)
    {
        circularGauge.value = value;
    }

    footer: TabBar {
        id: tabBar
        TabButton {
            text: qsTr("First Page")
        }
        TabButton {
            text: qsTr("Second Page")
        }
    }
}
