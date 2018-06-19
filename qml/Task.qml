import QtQuick 2.0



Item {

    property var startPoint: Qt.point(10, 10)
    property var endPoint: Qt.point(100, 100)
    property var endPoint2: Qt.point(200, 100)
    property var curPoint: Qt.point(10, 10)

    property var pathData;



    function calcPathProgress(curPath)
    {
        if(finished)
        {
            return;
        }

        if(!pathEnded(curPath))
        {
            var velocity = 1;
            curPoint.x += velocity;
            curPoint.y += velocity;
        }
        else
        {
            curPathIndex++;
            if(curPathIndex < path1.length - 1)
            {
                startPoint = curPoint = getPathStartPoint(curPath);
                endPoint = getPathEndPoint(curPath);
            }
            else
            {
                finished = true;
            }
        }
    }

    function pathEnded(curPath)
    {
         console.log(curPathIndex, startPoint, curPoint, endPoint);
        var x = Math.pow(endPoint.x - curPoint.x, 2);
        var y = Math.pow(endPoint.y - curPoint.y, 2);
        var len =  Math.sqrt(x + y);
        var epsilon = 0.1;
        return len < epsilon;
    }





}
