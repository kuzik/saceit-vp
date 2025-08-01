// main.qml
import QtQuick
import QtQuick.Controls

// Головний елемент, що представляє вікно програми
ApplicationWindow {
    id: rootWindow
    title: "Простий QML додаток"
    width: 400
    height: 300
    visible: true

    // Властивість, яка буде змінюватися
    property color myColor: "gold"

    // Основний контейнер
    Rectangle {
        id: mainRect
        color: rootWindow.myColor // Прив'язка до властивості вікна
        width: parent.width
        height: parent.height

        // Текст по центру
        Text {
            id: myText
            text: "Натисніть кнопку"
            anchors.centerIn: parent
            font.pointSize: 18
            color: "white"
        }

        // Кнопка, що змінює колір
        Button {
            id: myButton
            text: "Змінити колір"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20

            onClicked: {
                console.log("clicked", rootWindow.myColor);
                // Логіка на JavaScript для зміни кольору

                if (Qt.colorEqual(rootWindow.myColor, "gold")) {
                    rootWindow.myColor = "blue";
                } else {
                    rootWindow.myColor = "gold";
                }
            }
        }
    }
}
