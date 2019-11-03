import QtQuick 2.12
import QtQuick.Window 2.13
import QtQuick.Controls.Material 2.3
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import FontEditor 1.0
import QtGraphicalEffects 1.0

ApplicationWindow {
    visible: true
    width: 1200
    height: 960
    title: qsTr("CFont editor")
    menuBar: MenuBar {
        Menu {
            title: "File"
            MenuItem {
                text: "New font..."
//                shortcut: StandardKey.New
            }
        }
    }
    
    FontSelector {
        id: _selector
        fontIndex: _fontCbox.currentIndex
        encoding: _encodingBox.currentText
        pointSize: _sizeSpinner.value
        antialiased: _antialiasing.checked
    }
    
     ToolBar {
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
            ComboBox {
                id: _weightCombo
                model: ["Thin", "ExtraLight", "Light", "Normal", "Medium", "DemiBold", "Bold", "ExtraBold", "Black"]
                property var weights: [Font.Thin, Font.ExtraLight, Font.Light, Font.Normal, Font.Medium, Font.DemiBold, Font.Bold, Font.ExtraBold, Font.Black]
                onCurrentIndexChanged: {
                    _selector.weight = weights[currentIndex]
                }
            }
            
            ToolButton {
                id: _antialiasing
                text: "AA"
                checkable: true
            }
            
            Label {
                text: "Encoding:"
            }
            
            ComboBox {
                id: _encodingBox
                model: _selector.encodings
                editable: true
                width: 300
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
            
            ToolButton {
                id: _renderAsText
                checkable: true
                text: "Render as text"
            }
            
            Label {
                text: _selector.fontSize.width + "x" + _selector.fontSize.height
            }
            
        }
    }
    
    RowLayout {
        anchors.fill: parent
        anchors.margins: 8
        anchors.topMargin: _toolbar.height + 8
        
        //        ColumnLayout {
        //            id: zoomView
        //            Layout.minimumWidth: glyphGrid.currentItem.glyph.width * 10
        //            Glyph {
        //                Layout.minimumWidth: glyphGrid.currentItem.glyph.width * 10
        //                Layout.minimumHeight: glyphGrid.currentItem.glyph.height * 10
        //                charCode: glyphGrid.currentItem.glyph.charCode
        //            }
        //        }
        
        Flow {
            id: glyphGrid
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.minimumWidth: 600
            spacing: 4
            //            columnSpacing: 2
            //            rowSpacing: 2
            //            columns: 16
            //            rows: 16
            
            Repeater {
                model: 255 - 32
                
                delegate: Glyph {
                    id: _glyph
                    
                    width: implicitWidth * 2
                    height: fontSelector.fontHeight * 2
                    transform: Scale {
                        xScale: 2.0
                        yScale: 2.0
                        origin.x: 0
                        origin.y: 0
                    }
                    
                    //                                anchors.centerIn: parent
                    charCode: index + 32
                    fontSelector: _selector
                    color: "#008"
                    backgroundColor: "#fff"
                    renderAsText: _renderAsText.checked
                }
                
                //                    Rectangle {
                //                    clip: true
                //                    implicitHeight: Math.max(_selector.fontHeight + 22, 60)
                //                    implicitWidth: Math.max(_selector.fontWidth + 8, 48)
                
                //                    property bool isCurrent: GridView.isCurrentItem
                //                    property alias glyph: _glyph
                //                    color: "#ddd"
                //                    border.width: isCurrent ? 4 : 1
                //                    border.color: isCurrent ? "#0FF" : "#000"
                
                //                    Text {
                //                        id: _heading
                //                        text: _glyph.glyph + " (" + _glyph.charCode + ")"
                //                        width: parent.width
                //                        horizontalAlignment: Qt.AlignHCenter
                //                        font.pointSize: 8
                //                    }
                
                //                    Rectangle {
                //                        width: _selector.fontWidth + 4
                //                        height: _selector.fontHeight + 4
                //                        border.color: "#0f0"
                //                        border.width: 1
                //                        anchors.centerIn: parent
                //                        anchors.verticalCenterOffset: _heading.paintedHeight / 2
                //                        color: _glyph.backgroundColor
                
                //                    }
                
                //                    //                    MouseArea {
                //                    //                        anchors.fill: parent
                //                    //                        enabled: true
                //                    //                        onClicked: {
                //                    //                            console.log("Clicked", glyphGrid.currentIndex, index)
                //                    //                            glyphGrid.currentIndex = index
                //                    //                        }
                //                    //                    }
                //                }
                
            }
            
            
            
            
        }
        
        
    }
}
