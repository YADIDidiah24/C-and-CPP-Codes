import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15


Window {
    width: 350
    height: 600
    visible: true
    title: qsTr("Weather Widget")

    property int weatherState: 0 // 0: Clear, 1: Frosty, 2: Hot

    signal weatherChanged(int state)

    Rectangle {
        id: container
        width: parent.width
        height: parent.height
        radius: 10
        color: "transparent"
        // border.color: "black"

        // Backgrounds
        Rectangle {
            id: nightBg
            anchors.fill: parent
            opacity: weatherState == 0 ? 1 : 0
            GradientStop { position: 0.0; color: "#0F2129" }
            GradientStop { position: 1.0; color: "#47334A" }
            // Behavior on opacity { NumberAnimation { duration: 1000 } }
        }
        Rectangle {
            id: frostyBg
            anchors.fill: parent
            gradient: Gradient {
                GradientStop { position: 0; color: "#29386f" }
                GradientStop { position: 1; color: "#b8f5ff" }
            }
            opacity: weatherState == 1 ? 1 : 0
            Behavior on opacity { NumberAnimation { duration: 1000 } }
        }
        Rectangle {
            id: sunnyBg
            anchors.fill: parent
            gradient: Gradient {
                GradientStop { position: 0; color: "#ffbd3f" }
                GradientStop { position: 1; color: "#fff097" }
            }
            opacity: weatherState == 2 ? 1 : 0
            Behavior on opacity { NumberAnimation { duration: 1000 } }
        }

        // Text container
        Column {
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 10
            Text {
                id: degrees
                font.pixelSize: 100
                font.bold: true
                color: weatherState == 0 ? "#4F787D" : weatherState == 1 ? "#a8ddff" : "#fff5b8"
                text: weatherState == 0 ? "+24" : weatherState == 1 ? "-13" : "+32"
                anchors.horizontalCenter: parent.horizontalCenter
            }
            Text {
                id: place
                font.pixelSize: 30
                color: weatherState == 0 ? "#694c6d" : weatherState == 1 ? "#4497bf" : "#f7a526"
                text: weatherState == 0 ? "Madrid" : weatherState == 1 ? "Moscow" : "Ankara"
                anchors.horizontalCenter: parent.horizontalCenter
            }
            Text {
                id: weather
                font.pixelSize: 30
                color: "white"
                text: weatherState == 0 ? "Clear" : weatherState == 1 ? "Frosty" : "Hot"
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }

        // Ground
        Rectangle {
            id: ground
            width: parent.width
            height: parent.height * 0.2
            anchors.bottom: parent.bottom
            color: weatherState == 0 ? "#2f2b3c" : weatherState == 1 ? "#f3ffff" : "#e0d7a4"
            gradient: Gradient {
                GradientStop { position: 0; color: weatherState == 0 ? "#2f2b3c" : weatherState == 1 ? "#f3ffff" : "#e0d7a4" }
                GradientStop { position: 1; color: weatherState == 0 ? "#091B21" : weatherState == 1 ? "#9af2ff" : "#e7c77a" }
            }
            Behavior on color { ColorAnimation { duration: 1000 } }
            Behavior on gradient { ColorAnimation { duration: 1000 } }
        }

        // Circles
        Item {
            id: circleContainer
            width: 300
            height: 300

            Rectangle {
                id: circle
                width: 60
                height: 60
                radius: width / 2
                color: "#BCAE76"
                border.color: "#BCAE76"
                border.width: 0
                smooth: true
                antialiasing: true
                z: 2
                Behavior on color { ColorAnimation { duration: 2000 } }
                Behavior on x { PropertyAnimation { duration: 2000 } }
                Behavior on y { PropertyAnimation { duration: 2000 } }
            }

            Rectangle {
                width: 90
                height: 90
                radius: width / 2
                color: "#BCAE76"
                opacity: 0.1
                z: 1
                Behavior on color { ColorAnimation { duration: 2000 } }
                Behavior on x { PropertyAnimation { duration: 2000 } }
                Behavior on y { PropertyAnimation { duration: 2000 } }
            }

            Rectangle {
                width: 110
                height: 110
                radius: width / 2
                color: "#BCAE76"
                opacity: 0.1
                z: 1
                Behavior on color { ColorAnimation { duration: 2000 } }
                Behavior on x { PropertyAnimation { duration: 2000 } }
                Behavior on y { PropertyAnimation { duration: 2000 } }
            }

            Rectangle {
                width: 130
                height: 130
                radius: width / 2
                color: "#BCAE76"
                opacity: 0.1
                z: 1
                Behavior on color { ColorAnimation { duration: 2000 } }
                Behavior on x { PropertyAnimation { duration: 2000 } }
                Behavior on y { PropertyAnimation { duration: 2000 } }
            }

            states: [
                State {
                    name: "state1"
                    PropertyChanges {
                        target: circle
                        color: "#feffdf"
                        x: 80
                        y: -200
                    }
                },
                State {
                    name: "state2"
                    PropertyChanges {
                        target: circle
                        color: "#ffdb50"
                        x: 100
                        y: -150
                    }
                },
                State {
                    name: "state3"
                    PropertyChanges {
                        target: circle
                        color: "#BCAE76"
                        x: 120
                        y: -100
                    }
                }
            ]

            transitions: [
                Transition {
                    ColorAnimation {
                        properties: "color"
                        duration: 2000
                    }
                    ParallelAnimation {
                        NumberAnimation {
                            properties: "x"
                            duration: 2000
                        }
                        NumberAnimation {
                            properties: "y"
                            duration: 2000
                        }
                    }
                }
            ]

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    switch (circle.state) {
                        case "state1":
                            circle.state = "state2"
                            break;
                        case "state2":
                            circle.state = "state3"
                            break;
                        case "state3":
                            circle.state = "state1"
                            break;
                    }
                }
            }
        }


        // Current Time and Date
        Text {
            id: time
            font.pixelSize: 20
            color: "white"
            text: Qt.formatDateTime(new Date(), "dddd hh:mm:ss")
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.margins: 10
        }

        Timer {
            interval: 1000; running: true; repeat: true
            onTriggered: time.text = Qt.formatDateTime(new Date(), "dddd hh:mm:ss")
        }
    }
}
