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

#ifndef SCREENEXTRAS_H
#define SCREENEXTRAS_H

#include <QObject>
#include <QtQml>
#include <QObject>
#include <QtQml>
#include <QScreen>
#include <QSysInfo>
#include <QString>

class ScreenExtras : public QObject
{
    Q_OBJECT

    Q_PROPERTY( int desktopWidth READ desktopWidth NOTIFY desktopWidthChanged )
    Q_PROPERTY( int desktopHeight READ desktopHeight NOTIFY desktopHeightChanged )
    Q_PROPERTY( int virtualWidth READ virtualWidth NOTIFY virtualWidthChanged )
    Q_PROPERTY( int virtualHeight READ virtualHeight NOTIFY virtualHeightChanged )
    Q_PROPERTY( int numberOfScreens READ numberOfScreens NOTIFY numberOfScreensChanged)
    Q_PROPERTY( double displaySize READ displaySize NOTIFY displaySizeChanged )
    Q_PROPERTY( double devicePixelRatio READ devicePixelRatio NOTIFY devicePixelRatioChanged )
    Q_PROPERTY( double gridUnit READ gridUnit NOTIFY gridUnitChanged )
    Q_PROPERTY( double scaleSize READ scaleSize NOTIFY scaleSizeChanged )
    Q_PROPERTY( QString primaryScreenName READ primaryScreenName NOTIFY primaryScreenNameChanged )
    Q_PROPERTY( QString formFactor READ formFactor NOTIFY formFactorChanged )
    Q_ENUMS( Font )



public:

    explicit ScreenExtras( QObject *parent = 0 );
    QString formFactor() const;

    enum Font
    {
        NOTSET,
        XXLARGE,
        XLARGE,
        LARGE,
        MEDIUM,
        NORMAL,
        SMALL,
        TINY
    };


    double gridUnit()const;
    void setGridUnit(const double &unit);

    double scaleSize()const;
    void setScaleSize(const double &size);

    int desktopWidth() const;
    void setDesktopWidth(const int &desktopWidth);

    int desktopHeight() const;
    void setDesktopHeight(const int &desktopHeight);

    int virtualWidth() const;
    void setVirtualWidth(const int &designWidth);

    int virtualHeight() const;
    void setVirtualHeight(const int &designHeight);

    int numberOfScreens()const;
    void setNumberOfScreens(const int &numberOfScreens);

    double displaySize()const;
    void setDisplaySize(const double &displaySize);

    QString primaryScreenName()const;
    void setPrimaryScreenName(const QString &primaryScreenName);

    double devicePixelRatio()const;
    void setDevicePixelRatio(const double &devicePixelRatio);

    Q_INVOKABLE double gu(double units);
    Q_INVOKABLE double pxToGu(double px);
    Q_INVOKABLE QString screenNameAt(const int &screenNumber);
    Q_INVOKABLE qreal screenRefreshRateAt(const int &screenNumber);
    Q_INVOKABLE double font(Font fontSize);


protected:
    // internal


    void finalFormFactor( const QString &systemType, const double &versionORscaleSize ,
                          const double diagonal);

    double checkIphoneScaleSize( const int &width, const int &height,
                                 const double &iPhoneVersion);

    void updateFormFactor();
    void updateFonts();
    bool isInitialized();

protected slots:
     void initialize(QScreen *screen);

signals:
    void gridUnitChanged();
    void scaleSizeChanged();
    void formFactorChanged();
    void dpChanged();
    void displaySizeChanged();
    void devicePixelRatioChanged();

    void desktopWidthChanged();
    void desktopHeightChanged();
    void virtualWidthChanged();
    void virtualHeightChanged();
    void numberOfScreensChanged();
    void primaryScreenNameChanged();

private:
    bool m_bInitialized;

    double m_gridUnit;
    double m_defaultGrid;
    double m_devicePixelRatio;
    double m_displayDiagonalSize;


    int m_desktopWidth;
    int m_desktopHeight;
    int m_virtualWidth;
    int m_virtualHeight;

    int m_numberOfScreens;

    QRect m_desktopGeometry;
    QRect m_designResolution;

    QMap<Font,double> m_fonts;

    double m_scaleSize;

    QString m_formFactor;
    QString m_androidDpi;

    double m_windowsDesktopScale;
    double m_androidScale;
    double m_tempMacVersion;

    QString m_systemType;
    QString m_primaryScreenName;

};

#endif

