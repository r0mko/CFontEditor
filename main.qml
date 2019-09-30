import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import FontEditor 1.0
import QtGraphicalEffects 1.0
ApplicationWindow {
    visible: true
    width: 1200
    height: 960
    title: qsTr("CFont editor")
    
    FontSelector {
        id: _selector
        fontIndex: _fontCbox.currentIndex
        encoding: _encodingBox.currentText
        pointSize: _sizeSpinner.value
        bold: _bold.checked
    }
    
    header: ToolBar {
        id: _toolbar
        RowLayout {
            Label {
                text: "Font:"
            }
            ComboBox {
                id: _fontCbox
                Layout.minimumWidth: 300
                model: _selector.fonts
                editable: true
                onAccepted: {
                    focus = false
                }
            }
            
            ToolButton {
                id: _bold
                text: "Bold"
                checkable: true
            }
            
            Label {
                text: "Encoding:"
            }
            
            ComboBox {
                id: _encodingBox
                model: _selector.encodings
                editable: true
                onAccepted: {
                    focus = false
                }
            }
            Label {
                text: "Pixel size:"
            }
            
            SpinBox {
                id: _sizeSpinner
                Component.onCompleted: {
                    value = 20;
                }
            }
        }
    }
    
    RowLayout {
        anchors.fill: parent
        
        //        ColumnLayout {
        //            id: zoomView
        //            Layout.minimumWidth: glyphGrid.currentItem.glyph.width * 10
        //            Glyph {
        //                Layout.minimumWidth: glyphGrid.currentItem.glyph.width * 10
        //                Layout.minimumHeight: glyphGrid.currentItem.glyph.height * 10
        //                charCode: glyphGrid.currentItem.glyph.charCode
        //            }
        //        }
        
        GridLayout {
            id: glyphGrid
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.minimumWidth: 600
            columnSpacing: 2
            rowSpacing: 2
            columns: 16
            rows: 16
            
            Repeater {
                model: 255 - 32
                delegate: Rectangle {
                    implicitHeight: Math.max(_selector.fontHeight + 22, 60)
                    implicitWidth: Math.max(_selector.fontWidth + 8, 40)
                    
                    property bool isCurrent: GridView.isCurrentItem
                    property alias glyph: _glyph
                    color: "#ddd"
                    border.width: isCurrent ? 4 : 1
                    border.color: isCurrent ? "#0FF" : "#000"
                    
                    
                    Text {
                        id: _heading
                        text: _glyph.glyph + " (" + _glyph.charCode + ")"
                        width: parent.width
                        horizontalAlignment: Qt.AlignHCenter
                        font.pointSize: 10
                    }
                    
                    Rectangle {
                        width: _selector.fontWidth + 4
                        height: _selector.fontHeight + 4
                        border.color: "#0f0"
                        border.width: 1
                        anchors.centerIn: parent
                        anchors.verticalCenterOffset: _heading.paintedHeight / 2
                        color: _glyph.backgroundColor
                        Glyph {
                            id: _glyph
                            //                                anchors.centerIn: parent
                            anchors.centerIn: parent
                            charCode: index + 32
                            fontSelector: _selector
                            color: "#fff"
                            backgroundColor: "#333"
                        }
                    }
                    
                    //                    MouseArea {
                    //                        anchors.fill: parent
                    //                        enabled: true
                    //                        onClicked: {
                    //                            console.log("Clicked", glyphGrid.currentIndex, index)   
                    //                            glyphGrid.currentIndex = index
                    //                        }
                    //                    }
                }
                
            }
            
            
            
            
        }
        
        
    }
}
