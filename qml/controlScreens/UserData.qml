import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Item {

    function setCompletionProgressText(taskNumber, allTaskCount)
    {
        completionText.text = "Completion " + taskNumber + "/" + allTaskCount;
    }

    //TODO on loading
    Timer
    {
        interval: 500; running: true; repeat: false
        onTriggered:
        {
            setCompletionProgressText(0, gameTaskManager.getTaskCount());
        }
    }

    Connections
    {
        target:gameTaskManager;

        onTaskComleteEvent:
        {
            setCompletionProgressText(taskNumber, allTaskCount);
        }

        onAllTaskComleteEvent:
        {

        }

        onTaskStartEvent:
        {

        }
    }

    ColumnLayout
    {
        spacing: 10;
        Text
        {
            text: "User data";
            font.family: "Helvetica"
            font.pixelSize: 20
            color: "#000099"
        }

        Text
        {
            text: "UserName: User1";
            font.family: "Helvetica"
            font.pixelSize: 15
            color: "#999999"
        }

        Text
        {
            id:cleanTimeText;
            text: "CleanGameTaskTime: 0";
            font.family: "Helvetica"
            font.pixelSize: 15
            color: "#999999"
        }

        Text
        {
            id:stageText;
            text: "CurrentStage:";
            font.family: "Helvetica"
            font.pixelSize: 15
            color: "#999999"
        }
        Text
        {
            id:completionText;
            text: "Completion 0/0";
            font.family: "Helvetica"
            font.pixelSize: 15
            color: "#999999"
        }
    }
}
