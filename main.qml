import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import FontEditor 1.0
import QtQuick.Controls.Material 2.3
ApplicationWindow {
    visible: true
    width: 1200
    height: 800
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
                text: "B"
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
                text: "Point size:"
            }
            
            SpinBox {
                id: _sizeSpinner
                Component.onCompleted: {
                    value = 12;
                }
            }
        }
    }
    
    RowLayout {
        anchors.fill: parent
        
        GridView {
            id: glyphGrid
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.minimumWidth: 600
            model: 255
            cellHeight: Math.max(_selector.fontHeight + 12, 40)
            cellWidth: Math.max(_selector.fontWidth + 12, 40)
            
            delegate: Item {
                width: glyphGrid.cellWidth  
                height: glyphGrid.cellHeight
                property bool isCurrent: GridView.isCurrentItem
                Rectangle {
                    width: glyphGrid.cellWidth - 8
                    height: glyphGrid.cellHeight - 8
                    anchors.centerIn: parent
                    color: index >= 32 ? "#fff" : "#888"
                    border.width: isCurrent ? 4 : 1
                    border.color: isCurrent ? "#0FF" : "#000"
                    Glyph {
                        anchors.centerIn: parent
                        charCode: index
                        color: "#000"
                        fontSelector: _selector
                    }
                }
                MouseArea {
                    anchors.fill: parent
                    enabled: true
                    onClicked: {
                        console.log("Clicked", glyphGrid.currentIndex, index)   
                        glyphGrid.currentIndex = index
                    }
                }
            }
        }
        
        ColumnLayout {
            Layout.minimumWidth: 380
            Layout.fillWidth: false
        }
    }
    
    
    
    
}
