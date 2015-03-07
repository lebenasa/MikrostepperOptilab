import QtQuick 2.3
import QtQuick.Controls 1.2

Item {
    property int length: h2.y - h1.y
    property real realLength
    property int _index: cbUnit.currentIndex
    property real _tlength: tLength.text
//    anchors.fill: parent

    property real profileLength

    function updateProfile() {
        profileLength = appsettings.readProfileHeight(appsettings.profileId)
        updateText()
    }

    function updateText() {
        var mod = 0
        switch(_index) {
        case 0:
            mod = 1
            break
        case 1:
            mod = 0.001
            break
        case 2:
            mod = 0.0001
            break
        default:
            mod = 1
            break
        }
        var rl = (length / root.height) * profileLength * mod
        tLength.text = Math.round(rl)
    }

    function getRealLength() {
        var mod = 0
        switch(_index) {
        case 0:
            mod = 1
            break
        case 1:
            mod = 1000
            break
        case 2:
            mod = 10000
            break
        default:
            mod = 1
            break
        }
        return mod * _tlength
    }

    Connections {
        target: appsettings
        onProfileIdChanged: updateProfile()
    }
    onVisibleChanged: updateProfile()

    onLengthChanged: updateText()
    on_IndexChanged: updateText()

    LineWidget {
        id: h1
        y: parent.height/2 - 60
        min: 50
        max: h2.y - 20
    }
    LineWidget {
        id: h2
        y: parent.height/2 + 60
        min: h1.y + 20
        max: parent.height - 20
    }
    Rectangle {
        id: hOrnament
        color: "#0500ff00"
        width: parent.width
        anchors.top: h1.bottom
        anchors.bottom: h2.top
        ComboBox {
            id: cbUnit
            anchors {
                right: parent.right; rightMargin: 10
                verticalCenter: parent.verticalCenter
            }
            width: 55
            onCurrentIndexChanged: realLength = getRealLength()
            model: [ "μm", "mm", "cm" ]
            currentIndex: 0

        }
        TextField {
            id: tLength
            anchors {
                right: cbUnit.left; rightMargin: 5
                verticalCenter: parent.verticalCenter
            }
            horizontalAlignment: Text.AlignRight
            width: 60
            font.pointSize: 10
            text: "100"
            validator: IntValidator { }
            onTextChanged: realLength = getRealLength()
            onFocusChanged: realLength = getRealLength()
        }
    }
}
