import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4

Item {
    id:instruction
    anchors.fill: parent

    function reset()
    {
        swipeView.currentIndex = 0;
    }

    //anchors.centerIn: parent
  //  anchors.horizontalCenter: parent.horizontalCenter

        SwipeView {
            id: swipeView;

            currentIndex: 0
            anchors.fill: parent
            //anchors.horizontalCenter: parent.horizontalCenter

            Rectangle
            {
                color: "white"
                width: 400;
                height: 400;
                Text
                {
                    id:mainText;
                    anchors.centerIn: parent
                   // anchors.fill: view

                   // Layout.alignment : Qt.AlignHCenter
                    text: "Инструкция1";
                    font.family: "Helvetica"
                    font.pixelSize: 25
                    color: "#999999"
                }
            }

            Rectangle
            {
                color: "white"
                width: 400;
                height: 400;
                Text
                {
                    id:mainText2;
                    anchors.centerIn: parent
                   // anchors.fill: view

                   // Layout.alignment : Qt.AlignHCenter
                    text: "Инструкция2";
                    font.family: "Helvetica"
                    font.pixelSize: 25
                    color: "#999999"
                }
            }

            Rectangle
            {
                color: "white"
                width: 400;
                height: 400;
                Text
                {
                    id:mainText3;
                    anchors.centerIn: parent
                   // anchors.fill: view

                   // Layout.alignment : Qt.AlignHCenter
                    text: "Инструкция3";
                    font.family: "Helvetica"
                    font.pixelSize: 25
                    color: "#999999"
                }

                Button
                {
                    text: "StartGame"
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: mainText3.bottom
                    onClicked:
                    {

                    }
                }
            }


        }

        PageIndicator {
            id: indicator

            count: view.count
            currentIndex: view.currentIndex

            anchors.bottom: view.bottom
            anchors.horizontalCenter: parent.horizontalCenter
        }

}
