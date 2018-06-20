import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Item {
    id:root;

    property double nextAttentionValue: 0.0;
    property double nextMeditationValue: 0.0;

    property double alphaInvis: 0.2;

    Connections
    {
        target:mind;
        onAttentionChanged:
        {
            nextAttentionValue = mind.attention / 100.0;
            attentionAnim.to = nextAttentionValue;
            attentionAnim.duration = 1000;
            attentionAnim.start();
        }

        onMeditationChanged:
        {
            nextMeditationValue = mind.meditation / 100.0;
            meditationAnim.to = nextMeditationValue;
            meditationAnim.duration = 1000;
            meditationAnim.start();
        }

        onPoorSignalLevelChanged:
        {
            console.log("mind.poorSignalColor()  ", mind.poorSignalColor());
            signalLevel.color = mind.poorSignalColor();
        }
    }

    ColumnLayout
    {
        spacing: 20;
        RowLayout {
            spacing: 6;
            Text {
                text: "Mindwave data";
                font.family: "Helvetica"
                font.pixelSize: 18
                color: "#009900"
            }
        }

        RowLayout {
            spacing: 6;
            Text {
                id:signalLevel
                text: "Signal level: " + mind.poorSignalLevel;
                font.family: "Helvetica"
                font.pixelSize: 12
                color: "#999999"
            }
        }

        RowLayout
        {
            opacity: 0.2;//core.gameStrategy == 2? root.alphaInvis : 1;
            Text {
                text: "Attention";
                font.family: "Helvetica"
                font.pixelSize: 12
                color: "#990000"
            }
            spacing: 6;
            ProgressBar
            {
                id:attentionProgressBar;
                value: 0.0;
                style: ProgressBarStyle {
                    background: Rectangle {
                        radius: 2
                        color: "lightgray"
                        border.color: "gray"
                        border.width: 1
                        implicitWidth: 300
                        implicitHeight: 24
                    }
                    progress: Rectangle {
                        color:  "#990000"
                        border.color: "steelblue"
                    }
                }
            }

            PropertyAnimation
            {
                id: attentionAnim;
                target: attentionProgressBar;
                property: "value";
                to: 100;
                duration: 500
            }
        }

        RowLayout
        {
            visible: false
            opacity: core.gameStrategy == 1? root.alphaInvis : 1;
            Text {
                text: "Meditation";
                font.family: "Helvetica"
                font.pixelSize: 12
                color: "#000099"
            }
            spacing: 6;
            ProgressBar
            {
                id:meditationProgressBar;
                value: 0.0
                style: ProgressBarStyle {
                    background: Rectangle {
                        radius: 2
                        color: "lightgray"
                        border.color: "gray"
                        border.width: 1
                        implicitWidth: 400
                        implicitHeight: 24
                    }
                    progress: Rectangle {
                        color: "#000099"
                        border.color: "steelblue"
                    }
                }
            }
            PropertyAnimation
            {
                id: meditationAnim;
                target: meditationProgressBar;
                property: "value";
                to: 100;
                duration: 500
            }
        }


        RowLayout
        {
            visible: false
            spacing: 6;
            ExclusiveGroup { id: tabPositionGroup }
            RadioButton {
                id: btn1
                text: "Attention"
                checked: true
                exclusiveGroup: tabPositionGroup
                onCheckedChanged:
                {
                    core.gameStrategy = btn1.checked ? 1 : 2;
                }
            }
            RadioButton {
                id: btn2
                text: "Meditation"
                checked: false
                exclusiveGroup: tabPositionGroup
            }
        }

        RowLayout
        {
            visible: false
            spacing: 6;
            Text {
                text: "Difficult level";
                font.family: "Helvetica"
                font.pixelSize: 12
            }
            ExclusiveGroup { id: tabDiff }

            RadioButton {
                id: diff0
                text: "0"
                checked: false
                exclusiveGroup: tabDiff
                onCheckedChanged:
                {
                   resetParams();
                }
            }

            RadioButton {
                id: diff1
                text: "1"
                checked: false
                exclusiveGroup: tabDiff
                onCheckedChanged:
                {
                   resetParams();
                }
            }
            RadioButton {
                id: diff2
                text: "2"
                checked: false
                exclusiveGroup: tabDiff
                onCheckedChanged:
                {
                   resetParams();
                }
            }
            RadioButton {
                id: diff3
                text: "3"
                checked: true
                exclusiveGroup: tabDiff
                onCheckedChanged:
                {
                   resetParams();
                }
            }
            RadioButton {
                id: diff4
                text: "4"
                checked: false
                exclusiveGroup: tabDiff
                onCheckedChanged:
                {
                   resetParams();
                }
            }
        }
    }

    function resetParams()
    {
        core.backMove = true;

        if(diff0.checked)
        {
            core.dataThresholdMin = 40;
            core.backMove = false;
        }
        else if(diff1.checked)
        {
            core.dataThresholdMin = 40;
        }
        else if (diff2.checked)
        {
            core.dataThresholdMin = 50;
        }
        else if (diff3.checked)
        {
            core.dataThresholdMin = 60;
        }
        else if (diff4.checked)
        {
            core.dataThresholdMin = 70;
        }
    }

}
