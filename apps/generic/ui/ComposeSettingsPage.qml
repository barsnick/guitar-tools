/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                         *
 *  Copyright (C) 2016-2017 Simon Stuerz <stuerz.simon@gmail.com>          *
 *                                                                         *
 *  This file is part of guitar tools.                                     *
 *                                                                         *
 *  Guitar tools is free software: you can redistribute it and/or modify   *
 *  it under the terms of the GNU General Public License as published by   *
 *  the Free Software Foundation, version 3 of the License.                *
 *                                                                         *
 *  Guitar tools is distributed in the hope that it will be useful,        *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the           *
 *  GNU General Public License for more details.                           *
 *                                                                         *
 *  You should have received a copy of the GNU General Public License      *
 *  along with guitar tools. If not, see <http://www.gnu.org/licenses/>.   *
 *                                                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.2

import GuitarTools 1.0
import "components"

Page {
    id: root

    header: ToolBar {
        RowLayout {
            anchors.fill: parent

            IconToolButton {
                iconSource: dataDirectory + "/icons/back.svg"
                onClicked: pageStack.pop()
            }

            Label {
                text: qsTr("Song settings")
                elide: Label.ElideRight
                verticalAlignment: Qt.AlignVCenter
                Layout.fillWidth: true
            }
        }
    }

    Dialog {
        id: clearNotesDialog
        modal: true
        title: qsTr("Clear all notes")
        x: Math.round((root.width - width) / 2)
        y: Math.round((root.height - height) / 2)
        width: Math.min(root.width - 40, 420)

        contentItem: Label {
            width: clearNotesDialog.availableWidth
            text: qsTr("Are you sure you want to clear all notes in this song?")
            wrapMode: Text.WordWrap
        }

        footer: DialogButtonBox {
            standardButtons: DialogButtonBox.Cancel

            Button {
                text: qsTr("Clear")
                DialogButtonBox.buttonRole: DialogButtonBox.AcceptRole
                onClicked: {
                    clearNotesDialog.close()
                    Core.composeTool.clearNotes()
                }
            }
        }
    }

    Flickable {
        id: settingsFlickable
        anchors.fill: parent
        clip: true
        contentWidth: width
        contentHeight: settingsColumn.implicitHeight
        ScrollIndicator.vertical: ScrollIndicator { }

        ColumnLayout {
            id: settingsColumn
            width: settingsFlickable.width
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 10
            spacing: 8

            Item {
                Layout.fillWidth: true
                Layout.preferredHeight: 80

                ColumnLayout {
                    anchors.fill: parent

                    Label {
                        Layout.fillWidth: true
                        text: qsTr("Measures") + ": " + Core.composeTool.measureCount + " (" + Core.composeTool.songDurationString + ")"
                    }

                    RowLayout {
                        Layout.fillWidth: true

                        IconToolButton {
                            iconSource: dataDirectory + "/icons/remove.svg"
                            onClicked: measureSlider.value = measureSlider.from
                        }

                        Slider {
                            id: measureSlider
                            Layout.fillWidth: true
                            from: 1
                            to: 60
                            onValueChanged: {
                                Core.composeTool.measureCount = Math.round(value)
                                Core.composeTool.save()
                            }
                            Component.onCompleted: value = Core.composeTool.measureCount
                        }

                        IconToolButton {
                            iconSource: dataDirectory + "/icons/add.svg"
                            onClicked: measureSlider.value = measureSlider.to
                        }
                    }
                }
            }

            MenuSeparator { Layout.fillWidth: true }

            Item {
                Layout.fillWidth: true
                Layout.preferredHeight: 80

                ColumnLayout {
                    anchors.fill: parent

                    Label {
                        Layout.fillWidth: true
                        text: qsTr("Tracks") + " (" + Math.round(trackSlider.value) + ")"
                    }

                    RowLayout {
                        Layout.fillWidth: true

                        IconToolButton {
                            iconSource: dataDirectory + "/icons/remove.svg"
                            onClicked: trackSlider.value = trackSlider.from
                        }

                        Slider {
                            id: trackSlider
                            Layout.fillWidth: true
                            from: 1
                            to: 8
                            onValueChanged: {
                                Core.composeTool.trackCount = Math.round(value)
                                Core.composeTool.save()
                            }
                            Component.onCompleted: value = Core.composeTool.trackCount
                        }

                        IconToolButton {
                            iconSource: dataDirectory + "/icons/add.svg"
                            onClicked: trackSlider.value = trackSlider.to
                        }
                    }
                }
            }

            MenuSeparator { Layout.fillWidth: true }

            Item {
                Layout.fillWidth: true
                Layout.preferredHeight: 80

                ColumnLayout {
                    anchors.fill: parent

                    Label {
                        Layout.fillWidth: true
                        text: qsTr("Beats per minute") + " (" + Math.round(bpmSlider.value) + ")"
                    }

                    RowLayout {
                        Layout.fillWidth: true

                        IconToolButton {
                            iconSource: dataDirectory + "/icons/remove.svg"
                            onClicked: bpmSlider.value = bpmSlider.from
                        }

                        Slider {
                            id: bpmSlider
                            Layout.fillWidth: true
                            from: 40
                            to: 208
                            onValueChanged: {
                                Core.composeTool.bpm = Math.round(value)
                                Core.composeTool.save()
                            }
                            Component.onCompleted: value = Core.composeTool.bpm
                        }

                        IconToolButton {
                            iconSource: dataDirectory + "/icons/add.svg"
                            onClicked: bpmSlider.value = bpmSlider.to
                        }
                    }
                }
            }

            MenuSeparator { Layout.fillWidth: true }

            Label {
                Layout.fillWidth: true
                text: qsTr("Rhythm") + " (" + rhythmSelector.currentText + "/4)"
            }

            ComboBox {
                id: rhythmSelector
                Layout.fillWidth: true
                model: [2, 3, 4, 5, 6, 7, 8]
                onCurrentIndexChanged: {
                    if (currentIndex >= 0) {
                        Core.composeTool.rythmTicks = model[currentIndex]
                        Core.composeTool.save()
                    }
                }
                Component.onCompleted: currentIndex = Math.max(0, model.indexOf(Core.composeTool.rythmTicks))
            }

            MenuSeparator { Layout.fillWidth: true }

            Button {
                id: clearNotesButton
                text: qsTr("Clear all notes")
                Layout.fillWidth: true
                onClicked: clearNotesDialog.open()
            }
        }
    }
}
