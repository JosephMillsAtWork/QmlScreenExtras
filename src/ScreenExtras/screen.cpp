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


#include "screen.h"
#include <QCoreApplication>
#include <qmath.h>
#include <QScreen>
#include <QGuiApplication>
#include <QDebug>


/*!
   \qmltype ScreenExtras
   \inqmlmodule QmlScreenExtras
   \brief A Signleton that is used to gather information about screens and set up things like Font sizes and scale sizes

   Example of using the font

     \code
     Text{
        font.pixelSize: ScreenExtras.font(ScreenExtras.NORMAL)
     }
     \endcode


     Example of setting width or height

     this would set the width of the Rectangle to 16 px if the scale size is 1

     \code
     Rectangle{
        width ScreenExtras.gu(2)
     }
    \endcode
*/

ScreenExtras::ScreenExtras(QObject *parent) :
    QObject(parent),
    m_bInitialized(false),
    m_gridUnit(8),
    m_designResolution(QGuiApplication::primaryScreen ()->availableGeometry ()),
    m_scaleSize(1.0),
    m_formFactor("desktop"),
    m_androidDpi(),
    m_windowsDesktopScale(1.0),
    m_androidScale(1.0),
    m_tempMacVersion(6.0)
{
    QScreen *desktop = QGuiApplication::primaryScreen();


    //FIXME need to add a update handler here for
    // QGuiApplication::::primaryScreenChanged(QScreen *screen)
    // QGuiApplication::screenAdded(QScreen *screen)
    // QGuiApplication::screenRemoved(QScreen *screen)

    initialize(desktop);

}

/*!
  \qmlproperty string ScreenExtras::formFactor
  returns the current formfactor as a string for the device that is being used

  There are 5 values

  \list
  \li desktop
  \li tv
  \li phablet
  \li tablet
  \li phone
  \endlist

 */

QString ScreenExtras::formFactor() const
{
    return m_formFactor;
}


bool ScreenExtras::isInitialized()
{
    return m_bInitialized;
}

void ScreenExtras::initialize(QScreen *screen)
{

    m_devicePixelRatio = screen->devicePixelRatio();
    m_desktopGeometry = screen->geometry();

    setDesktopHeight(screen->availableGeometry().height() );
    setDesktopWidth(screen->availableGeometry().width() );

    setVirtualHeight( screen->availableVirtualGeometry().height() );
    setVirtualWidth(screen->availableVirtualGeometry().width());

    setNumberOfScreens(QGuiApplication::screens().length());
    setDevicePixelRatio(screen->devicePixelRatio());

    setPrimaryScreenName(screen->name());

    updateFormFactor();
    m_bInitialized = true;
}

void ScreenExtras::setGridUnit(const double &unit)
{
    if( m_gridUnit == unit )
    {
        return;
    }
    else
    {
        m_gridUnit = (unit * m_gridUnit) ;
        emit gridUnitChanged();
    }
    updateFonts();
}

double ScreenExtras::gridUnit() const
{
    return m_gridUnit;
}

/*!
 \qmlproperty int ScreenExtras::desktopWidth
    Returns the Screens width. This is without the Window managers padding.
    if you would like to get the screens width minus what the window manager is taking up see
    designWidth

    \sa virtualWidth
*/
int ScreenExtras::desktopWidth() const
{
    return m_desktopWidth;
}

void ScreenExtras::setDesktopWidth(const int &desktopWidth)
{
    if(m_desktopWidth == desktopWidth)
        return;
    m_desktopWidth = desktopWidth;
    emit desktopWidthChanged();
}

/*!
 \qmlproperty int ScreenExtras::desktopHeight
    Returns the Screens height.  This is without the Window managers padding.
    designHeight

    \sa virtualHeight
*/
int ScreenExtras::desktopHeight() const
{
    return m_desktopHeight;
}


void ScreenExtras::setDesktopHeight(const int &desktopHeight)
{
    if(m_desktopHeight == desktopHeight)
        return;
    m_desktopHeight = desktopHeight;
    emit desktopHeightChanged();
}


/*!
 \qmlproperty int ScreenExtras::virtualWidth
    This property holds the available width of the Screen minus what the
    windowmanager is taking up
 */
int ScreenExtras::virtualWidth() const
{
    return m_virtualWidth;
}

void ScreenExtras::setVirtualWidth(const int &virtualWidth)
{
    if ( m_virtualWidth == virtualWidth )
        return;
    m_virtualWidth = virtualWidth ;
    emit virtualWidthChanged();
}

/*!
 \qmlproperty int ScreenExtras::virtualHeight
    This property holds the available width of the Screen minus what the
    windowmanager is taking up
 */
int ScreenExtras::virtualHeight() const
{
    return m_virtualHeight;
}

void ScreenExtras::setVirtualHeight(const int &virtualHeight)
{
    if ( m_virtualHeight == virtualHeight )
        return;
    m_virtualHeight = virtualHeight ;
    emit virtualHeightChanged();
}

/*!
\qmlproperty int ScreenExtras::numberOfScreens
    Returns a number of all the screens associated with the windowing
system the application is connected to.
*/
int ScreenExtras::numberOfScreens() const
{
    return m_numberOfScreens;
}

void ScreenExtras::setNumberOfScreens(const int &numberOfScreens)
{
    if(m_numberOfScreens == numberOfScreens)
        return;
    m_numberOfScreens = numberOfScreens;
    emit numberOfScreensChanged();
}



double ScreenExtras::displaySize() const
{
    return m_displayDiagonalSize;
}

/*!
\qmlproperty string ScreenExtras::primaryScreenName
    Returns a common name fro the primary screen.
*/
QString ScreenExtras::primaryScreenName() const
{
    return  m_primaryScreenName;
}

void ScreenExtras::setPrimaryScreenName(const QString &primaryScreenName)
{
    if(m_primaryScreenName == primaryScreenName)
        return;
    m_primaryScreenName = primaryScreenName;
    emit primaryScreenNameChanged();
}

double ScreenExtras::devicePixelRatio() const
{
    return m_devicePixelRatio;
}

void ScreenExtras::setDevicePixelRatio(const double &devicePixelRatio)
{
    if (m_devicePixelRatio == devicePixelRatio)
        return;
    m_devicePixelRatio = devicePixelRatio;
    emit devicePixelRatioChanged();
}

/*!
 \qmlmethod ScreenExtras::gu( int units)
    Returns the grid units that are used per device. This is by far one of the best features of
This helper class.

Each grid unit by default it 8px the example below show what a rectangles height
should be at 80px. So in other words it multiplys the passed in int by 8 if there is no scale size.

Example:

\code
    Rectangle {
        id: simpleRec
        width: parent.width
        // Rectangle at 10 gu for the height
        height: ScreenExtras.gu(10)
    }
\endcode

\sa scaleSize
 */
double ScreenExtras::gu(double units)
{
    return units * m_gridUnit;
}

double ScreenExtras::pxToGu(double px)
{
    return px / m_gridUnit;
}

/*!
 \qmlmethod  ScreenExtras::screenNameAt(int screenNumber)
 returns the name of a a screen at a given int
 */

QString ScreenExtras::screenNameAt(const int &screenNumber)
{
    return QGuiApplication::screens().at(screenNumber)->name();
}

/*!
 \qmlmethod ScreenExtras::screenRefreshRateAt(int screenNUmber)
    Returns the refresh rate of a screen at its interger,

    Example:  say that I have for screens attached to a machine and I want to get teh
    refresh rate of the screen that is the 3rd one.

\code
    ScreenExtras.screenRefreshRateAt(2)
\endcode

\sa numberOfScreens
 */
qreal ScreenExtras::screenRefreshRateAt(const int &screenNumber)
{
    return QGuiApplication::screens().at(screenNumber)->refreshRate();
}

/*!
    \qmlmethod ScreenExtras::font(Font)
     FontSize

     This is used to set the font size here is a example

     \code
     Text{
        font.pixelSize: ScreenExtras.font(ScreenExtras.NORMAL)
     }
     \endcode

     see also the types of font sizes
 */

double ScreenExtras::font(ScreenExtras::Font fontSize)
{
    return m_fonts[fontSize];
}

void ScreenExtras::finalFormFactor(
        const QString &systemType,
        const double &versionORscaleSize,
        const double diagonal )
{
    //FIXME SHould be getters and setters

    m_systemType = systemType;
    m_displayDiagonalSize = diagonal;

    // IOS

    if ( systemType == "ios"){
        if (diagonal >= 3.5 && diagonal < 5) {
            m_formFactor = "phone";
        }
        //iPhone 1st generation to phablet
        else if (diagonal >= 5 && diagonal < 6.5) {
            m_formFactor = "phablet";
        }
        else if (diagonal >= 6.5 && diagonal < 10.1) {
            m_formFactor = "tablet";
        }
        // apple TV
        else if (diagonal > 10.1 ){
            m_formFactor  = "tv";
        }
        setGridUnit(versionORscaleSize);
        setScaleSize(versionORscaleSize);
    }

    // ANDROID
    else if (systemType == "android" ){
        if (diagonal >= 3.5 && diagonal < 5) {
            m_formFactor = "phone";
        }
        //iPhone 1st generation to phablet
        else if (diagonal >= 5 && diagonal < 6.5) {
            m_formFactor = "phablet";
        }
        else if (diagonal >= 6.5 && diagonal < 10.1) {
            m_formFactor = "tablet";
        }
        // android TV
        else if (diagonal > 10.1 ){
            m_formFactor  = "tv";
        }
        setGridUnit(versionORscaleSize);
        setScaleSize(versionORscaleSize);
    }

    // WINDOWS
    else if ( systemType == "winrt"
              || systemType == "wince"
              || systemType == "windows"
              ){
        if (diagonal >= 3.5 && diagonal < 5) {
            m_formFactor = "phone";
        }
        //iPhone 1st generation to phablet
        else if (diagonal >= 5 && diagonal < 6.5) {
            m_formFactor = "phablet";
        }
        else if (diagonal >= 6.5 && diagonal < 10.1) {
            m_formFactor = "tablet";
        }
        // FIXME TV
        else if (diagonal > 10.1  ){
            m_formFactor  = "desktop";
        }
        setGridUnit(versionORscaleSize);
        setScaleSize(versionORscaleSize);
    }

    //OSX
    if ( systemType == "osx"){
        if (diagonal >= 3.5 && diagonal < 5) {
            m_formFactor = "phone";
        }
        //iPhone 1st generation to phablet
        else if (diagonal >= 5 && diagonal < 6.5) {
            m_formFactor = "phablet";
        }
        else if (diagonal >= 6.5 && diagonal < 10.1) {
            m_formFactor = "tablet";
        }
        // apple TV
        else if (diagonal > 10.1 ){
            m_formFactor  = "desktop";
        }
        setGridUnit(versionORscaleSize);
        setScaleSize(versionORscaleSize);
    }


    if ( systemType == "linux"){
        if (diagonal >= 3.5 && diagonal < 5) {
            m_formFactor = "phone";
        }
        //iPhone 1st generation to phablet
        else if (diagonal >= 5 && diagonal < 6.5) {
            m_formFactor = "phablet";
        }
        else if (diagonal >= 6.5 && diagonal < 10.1) {
            m_formFactor = "tablet";
        }
        // apple TV
        else if (diagonal > 10.1 ){
            m_formFactor  = "desktop";
        }
        setGridUnit(versionORscaleSize);
        setScaleSize(versionORscaleSize);
    }



}

double ScreenExtras::checkIphoneScaleSize(
        const int &width,
        const int &height,
        const double &iPhoneVersion )
{
    if( iPhoneVersion >= 4 )
    {
        if (width >= 320 && width < 321&& height < 567 ){
            return 1.0;
        }
        else if (height >  567 && height < 569 && width  == 320){
            return 1.0;
        }
        else if (height >  665  && height < 668 && width  == 375)
        {
            return 1.0;
        }
        else if (width >= 374  && height  >= 665 )
        {
            return 1.0;
        }
    }
    else
    {
        return 1.0;
    }
    return 1.0;
}

void ScreenExtras::updateFormFactor()
{
    QScreen* m_screen = QGuiApplication::primaryScreen();
    QSysInfo sysInfo;

    double m_169 = qSqrt(
                pow((m_screen->physicalSize().width()), 2) +
                qPow((m_screen->physicalSize().height()), 2)) * 0.039370;

    // Check to see if this is a ios

    if ( sysInfo.productType () == "ios")
    {
        // IOS - now what version?

        if (sysInfo.MacintoshVersion == QSysInfo::MV_IOS_4_3){
            m_tempMacVersion = 4.3;
        }
        else if (sysInfo.MacintoshVersion == QSysInfo::MV_IOS_5_0){
            m_tempMacVersion =  5.0;
        }
        else if (sysInfo.MacintoshVersion ==  QSysInfo::MV_IOS_5_1){
            m_tempMacVersion =  5.1;
        }
        else if (sysInfo.MacintoshVersion ==   QSysInfo::MV_IOS_6_0){
            m_tempMacVersion =  6.0;
        }
        else if (sysInfo.MacintoshVersion ==  QSysInfo::MV_IOS_6_1){
            m_tempMacVersion =  6.1;
        }
        else if (sysInfo.MacintoshVersion ==  QSysInfo::MV_IOS_7_0){
            m_tempMacVersion =  7.0;
        }
        else if (sysInfo.MacintoshVersion == QSysInfo::MV_IOS_7_1){
            m_tempMacVersion =   7.1;
        }
        else if (sysInfo.MacintoshVersion ==  QSysInfo::MV_IOS_8_0){
            m_tempMacVersion =  8.0;
        }
        else if (sysInfo.MacintoshVersion == QSysInfo::MV_IOS_8_1){
            m_tempMacVersion =   8.1;
        }
        else if (sysInfo.MacintoshVersion == QSysInfo::MV_IOS_8_2){
            m_tempMacVersion = 8.2;
        }
        else if (sysInfo.MacintoshVersion == QSysInfo::MV_IOS_8_3){
            m_tempMacVersion =  8.3;
        }
        else if (sysInfo.MacintoshVersion == QSysInfo::MV_IOS_8_4){
            m_tempMacVersion =  8.4;
        }
        else if (sysInfo.MacintoshVersion == QSysInfo::MV_IOS_9_0){
            m_tempMacVersion =  9.0;
        }

        finalFormFactor( "ios",
                         checkIphoneScaleSize(
                             m_screen->size().width(),
                             m_screen->size().height(),
                             m_tempMacVersion),
                         m_169 );
        return;
    }
    // ANDROID / LINUX
    else  if( sysInfo.productType () == "android")
    {
        // Check the BuildArch to see if arm or arm 64.
        // Also look at x86_64 android
        if( sysInfo.buildCpuArchitecture() == "arm"
                ||  sysInfo.buildCpuArchitecture() == "arm64")
        {
            // SOURCE:
            // https://developer.android.com/guide/practices/screens_support.html
            //(low) 120dpi

            if(m_screen->logicalDotsPerInch () <= 120)
            {
                m_androidDpi = "ldpi";
                m_androidScale = 1.0;
            }

            else if (m_screen->logicalDotsPerInch() <= 160)
            {
                m_androidDpi = "mdpi";
                m_androidScale = 1.5;
            }
            //(high) ~240dpi
            else if (m_screen->logicalDotsPerInch() <= 240)
            {
                m_androidDpi = "hdpi";
                m_androidScale = 2.0;
            }
            //(high) ~240dpi
            else if (m_screen->logicalDotsPerInch()  <= 320)
            {
                m_androidDpi = "xhdpi" ;
                m_androidScale = 3.0;
            }
            // (extra-high) ~320dpi
            else if (m_screen->logicalDotsPerInch() <= 480)
            {
                m_androidDpi = "xxhdpi" ;
                m_androidScale  = 4.0;
            }

            // (extra-extra-high) ~480dpi
            else if (m_screen->logicalDotsPerInch() <= 640 )
            {
                m_androidDpi = "xxxhdpi";
                m_androidScale = 5.0;
            }

            //(extra-extra-extra-high) ~640dpi
            else //if (m_screen->logicalDotsPerInch() >= 640)
            {
                m_androidDpi = "xxxhdpi";
                m_androidScale = 5.0;
            }
        }
        else
        {
            qDebug() << "we know that it is android but we do not know the DPI so we have to make another work around";
            return;
        }
        finalFormFactor( "android" , m_androidScale, m_169 );

        return;
    }

    // WINDOWS PHONE

    else if ( sysInfo.productType() == "winphone"){
        // FIXME
    }
    // WINDOWS LOOK FOR DPI
    else if( sysInfo.productType () == "winrt"
             || sysInfo.productType () == "wince"
             || sysInfo.productType () == "windows" )
    {
        m_windowsDesktopScale = 1.0;
        // SOURCE
        // https://msdn.microsoft.com/en-us/library/windows/desktop/dn469266(v=vs.85).aspx
        if (m_169 <= 10.5){
            qDebug() << "This is small to small !";
        }
        else if (m_169 >=  10.6 && m_169 <=  11.5){
            if (m_screen->size().width() >= 1920 && m_screen->size().height() >= 1080){
                m_windowsDesktopScale = 1.5;
            }
        }
        else if (m_169 >=  11.6 && m_169 <= 13.2){
            if (m_screen->size().width() >= 1920 && m_screen->size().height() >= 1200){
                m_windowsDesktopScale = 1.5;
            }
        }
        else if (m_169 >=  13.3 && m_169 <= 15.3){
            if(m_screen->logicalDotsPerInch() >= 192 && m_screen->logicalDotsPerInch() >145) {
                m_windowsDesktopScale = 2.0;
            }
        }
        else if (m_169 >=  15.4 && m_169 <= 16.9){
            if ( m_screen->logicalDotsPerInch() >= 120 && m_screen->logicalDotsPerInch()  < 192){
                m_windowsDesktopScale = 1.25;
            }
            else if (m_screen->logicalDotsPerInch() >= 192  )
            {
                m_windowsDesktopScale = 2.0;
            }
        }
        else if (m_169 >=  23 && m_169 < 24){
            if (m_screen->logicalDotsPerInch() >= 192){
                m_windowsDesktopScale = 2.0;
            }
        }
        else if (m_169 >=  23 && m_169 < 24){
            if (m_screen->logicalDotsPerInch() == 120 ){
                m_windowsDesktopScale = 1.25;
            }
        }
        else {
            finalFormFactor ("windows" , 1.0,m_169);
            return;
        }
        finalFormFactor ("windows", m_windowsDesktopScale,m_169);
        return;
    }
    // END WINDOWS

    // MACOSX

    if(sysInfo.productType() == "osx"){
        finalFormFactor ("osx", 1 , m_169);
        return;
    }
    // START LINUX (SOMETIMES ANDROID COes back as Linux)
    // if ( sysInfo.buildCpuArchitecture() === "arm" || systemInfo.buildCpuArchitecture == "arm64" && systemInfo.productType() == "android" || sysInfo.productType () == "linux")
    //{
    //  // Ok know that we know that we are on a armv7 lets look deeper
    //}

    if( sysInfo.kernelType() == "linux" && sysInfo.productType() != "android")
    {
        finalFormFactor ("linux", 1 , m_169);
        return;
    }

}

/*!
 \qmlproperty double ScreenExtras::scaleSize
  returns what QScreen thinks the scaleSize should be set to.  I would not use this.
 */

double ScreenExtras::scaleSize() const
{
    return m_scaleSize;
}

void ScreenExtras::setScaleSize(const double &size)
{
    if( m_scaleSize == size) return;
    m_scaleSize = size;
    emit scaleSizeChanged();
}

void ScreenExtras::updateFonts()
{
    if (m_formFactor == "desktop")
    {
        m_fonts[XXLARGE] = gu(5);
        m_fonts[XLARGE] = gu(4.7);
        m_fonts[LARGE] = gu(4);
        m_fonts[MEDIUM] = gu(3.5);
        m_fonts[NORMAL] = gu(2.5);
        m_fonts[SMALL] = gu(2);
        m_fonts[TINY] = gu(1.2);
    }
    else if (m_formFactor == "tv")
    {
        m_fonts[XXLARGE] = gu(10);
        m_fonts[XLARGE] = gu(8);
        m_fonts[LARGE] = gu(6);
        m_fonts[MEDIUM] = gu(4.5);
        m_fonts[NORMAL] = gu(3.5);
        m_fonts[SMALL] = gu(3);
        m_fonts[TINY] = gu(2);
    }
    // FIXME make this with android and iphone options
    else if (m_formFactor == "tablet")
    {
        m_fonts[XXLARGE] = gu(5);
        m_fonts[XLARGE] = gu(4.7);
        m_fonts[LARGE] = gu(4);
        m_fonts[MEDIUM] = gu(3.5);
        m_fonts[NORMAL] = gu(2.5);
        m_fonts[SMALL] = gu(2);
        m_fonts[TINY] = gu(1.2);
    }
    else if (m_formFactor == "phone" && m_systemType == "ios")
    {
        m_fonts[XXLARGE] = gu(5);
        m_fonts[XLARGE] = gu(4.6);
        m_fonts[LARGE] = gu(3.0);
        m_fonts[MEDIUM] = gu(2.8);
        m_fonts[NORMAL] = gu(2.0);
        m_fonts[SMALL] = gu(1.5);
        m_fonts[TINY] = gu(.5);
    }
    else if (m_formFactor == "phone" && m_systemType == "android")
    {
        m_fonts[XXLARGE] = gu(6);
        m_fonts[XLARGE] = gu(5.6);
        m_fonts[LARGE] = gu(4.3);
        m_fonts[MEDIUM] = gu(3.8);
        m_fonts[NORMAL] = gu(3.0);
        m_fonts[SMALL] = gu(2.5);
        m_fonts[TINY] = gu(1.2);
    }
}

