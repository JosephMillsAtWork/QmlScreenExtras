/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2016 Joseph Mills <josephjamesmills@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE
*/

import QtQuick 2.3
import QtQuick.Window 2.2
import QmlScreenExtras 1.0



Window {
    visible: true
    width: ScreenExtras.gu(80)
    height: ScreenExtras.desktopHeight
    title: qsTr("Extra Screen Info")


    Rectangle {
        id: simpleRec
        width: parent.width
        height: ScreenExtras.gu(10)
        color: "darkBlue"
        Text {
            text: qsTr("Rectangle at 10 gu for the height")
            font.pixelSize: ScreenExtras.font(ScreenExtras.NORMAL);
            anchors.fill: parent
            color: "white"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            wrapMode: Text.WordWrap
        }

    }

    Column{

        width: parent.width
        height: parent.height - ScreenExtras.gu(10)
        anchors{
            top: simpleRec.bottom
            topMargin: ScreenExtras.gu(.5)
        }



        Text {
            text: qsTr("ScreenExtras.formFactor = %1").arg(ScreenExtras.formFactor)
            width: parent.width
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: ScreenExtras.font(ScreenExtras.NORMAL);
        }
        Text {
            text: qsTr("ScreenExtras.desktopWidth = %1").arg(ScreenExtras.desktopWidth)
            width: parent.width
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: ScreenExtras.font(ScreenExtras.NORMAL);
        }
        Text {
            text: qsTr("ScreenExtras.desktopHeight = %1").arg(ScreenExtras.desktopHeight)
            width: parent.width
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: ScreenExtras.font(ScreenExtras.NORMAL);
        }

        Text {
            text: qsTr("ScreenExtras.virtualWidth = %1").arg(ScreenExtras.virtualWidth)
            width: parent.width
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: ScreenExtras.font(ScreenExtras.NORMAL);
        }
        Text {
            text: qsTr("ScreenExtras.virtualHeight = %1").arg(ScreenExtras.virtualHeight)
            width: parent.width
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: ScreenExtras.font(ScreenExtras.NORMAL);
        }

        Text {
            text: qsTr("ScreenExtras.primaryScreenName = %1").arg(ScreenExtras.primaryScreenName)
            width: parent.width
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: ScreenExtras.font(ScreenExtras.NORMAL);
        }



        Text {
            text: qsTr("ScreenExtras.numberOfScreens = %1").arg(ScreenExtras.numberOfScreens)
            width: parent.width
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: ScreenExtras.font(ScreenExtras.NORMAL);
        }

        Text {
            text: qsTr("ScreenExtras.screenNameAt(0) = %1").arg(ScreenExtras.screenNameAt(0))
            width: parent.width
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: ScreenExtras.font(ScreenExtras.NORMAL);
        }
        Text {
            text: qsTr("ScreenExtras.screenRefreshRateAt(0) = %1 fps").arg(ScreenExtras.screenRefreshRateAt(0))
            width: parent.width
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: ScreenExtras.font(ScreenExtras.NORMAL);
        }

        Text {
            text: qsTr("ScreenExtras.scaleSize = %1").arg(ScreenExtras.scaleSize)
            width: parent.width
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: ScreenExtras.font(ScreenExtras.NORMAL);
        }
        Text {
            text: qsTr("ScreenExtras.devicePixelRatio = %1").arg(ScreenExtras.devicePixelRatio)
            width: parent.width
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: ScreenExtras.font(ScreenExtras.NORMAL);
        }
        Text {
            text: qsTr("ScreenExtras.gridUnit = %1").arg(ScreenExtras.gridUnit)
            width: parent.width
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: ScreenExtras.font(ScreenExtras.NORMAL);
        }

        Text {
            text: qsTr("ScreenExtras.displaySize = %1").arg(ScreenExtras.displaySize)
            width: parent.width
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: ScreenExtras.font(ScreenExtras.NORMAL);
        }


        Rectangle {
            width: parent.width
            height: ScreenExtras.gu(5)
            color: "darkBlue"
            Text {
                text: qsTr("Font Size's")
                font.pixelSize: ScreenExtras.font(ScreenExtras.NORMAL);
                anchors.fill: parent
                color: "white"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                wrapMode: Text.WordWrap
            }

        }


        Text {
            text: qsTr("ScreenExtras.TINY")
            width: parent.width
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: ScreenExtras.font(ScreenExtras.TINY);
        }

        Text {
            text: qsTr("ScreenExtras.SMALL")
            width: parent.width
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: ScreenExtras.font(ScreenExtras.SMALL);
        }
        Text {
            text: qsTr("ScreenExtras.NORMAL")
            width: parent.width
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: ScreenExtras.font(ScreenExtras.NORMAL);
        }
        Text {
            text: qsTr("ScreenExtras.MEDIUM")
            width: parent.width
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: ScreenExtras.font(ScreenExtras.MEDIUM);
        }
        Text {
            text: qsTr("ScreenExtras.LARGE")
            width: parent.width
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: ScreenExtras.font(ScreenExtras.LARGE);
        }

        Text {
            text: qsTr("ScreenExtras.XLARGE")
            width: parent.width
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: ScreenExtras.font(ScreenExtras.XLARGE);
        }
        Text {
            text: qsTr("ScreenExtras.XXLARGE")
            width: parent.width
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: ScreenExtras.font(ScreenExtras.XXLARGE);
        }



    }



}
