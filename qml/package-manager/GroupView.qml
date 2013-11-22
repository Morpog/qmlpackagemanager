/*
 * This file is part of mg-package-manager
 *
 * Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
 * Copyright (C) 2013 Timo Hannukkala <timo.hannukkala@nomovok.com>
 *
 * Contact: Kyösti Ranto <kyosti.ranto@digia.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * version 2.1 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301 USA
 *
 */

import QtQuick 2.0
import com.nokia.meego 2.0
import "utils.js" as Utils

AppPageWithActionMenu {
    id: view

    signal groupSelected(string groupName)

    pageTitle: "Available Package Groups"

    property int buttonWidth: 150 //view.width / 3 - 30

    onGroupSelected: {
        selectedGroupName = groupName;
        window.pushPage("AvailableView");
    }

    Flickable {
        contentHeight: buttonGrid.height
        contentWidth: buttonGrid.width
        width: buttonGrid.width
        anchors.centerIn: view
        height: Math.min(buttonGrid.height, parent.height)

        Grid {
            id: buttonGrid
            anchors.horizontalCenter: parent.horizontalCenter
            columns: 3 //Math.min(view.width / buttonWidth, 3)
            spacing:  10

            Repeater {
                model: packageGroups

                Button {
                    height: 50
                    width: view.width/3 - 10
                    text: Utils.groupName(modelData.group)
                    platformStyle: ButtonStyle {
                        fontPixelSize: 16
                    }
                    onClicked: {
                        groupSelected(text);
                        packageManager.refreshAvailable(modelData.group);
                    }
                }
            }
        }
    }
    tools: currentTools
    ToolBarLayout {
        id: currentTools
        visible: true
        ToolIcon {
            platformIconId: "toolbar-back"
            onClicked: pageStack.pop()
        }

    }
}
