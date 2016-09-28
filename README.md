## QmlScreenExtras

Simple singleton that is used to gather info about device and setup gridunits based on
the device and what formfactor it is the size of the screen. Also has some font propertys
that can be handy.

#### Building and Installing
````
    qmake
    make
    make install
````

#### Using it

All the gu stuff is set at 8px by default then pushed up based on the device.

Example:

Say that I have a rectangle that is 200px wide on the width.  so 200 dived by 8 = 25 so this is what I would set the units to


````qml

    Rectangle{
        width: ScreenExtras.gu(25)
    }

````


This will make it so that on every divice that there is it will 'look' like it is 200px wide

there is also a font enum that can be used the values are as foillows.

* NOTSET
* XXLARGE
* XLARGE
* LARGE
* MEDIUM
* NORMAL
* SMALL
* TINY

These also conform to device size.  Below is a example of how to use the Font

**Note** One can also manual set pixel size with the gu if you do not like the font sizes

````qml

    Text{
        text: qsTr("Some Large Text")
        font.pixelSize: ScreenExtras.font(ScreenExtras.LARGE)
    }

````


 There are other misc propertys that one might like to use like formFactor or scale size.



Please see the Example for more info. After running make install you can open the example up from qtcreator if you like


#### Getting it via qpm

Coming soon


#### Docs

Building the docs are also built into the qmake system. You can view the docs on the gh-pages
located [here]()

Below this will make all the html docs and install the qch file into your qt system

````make
 qmake
 make docs
 make install qch_docs

````

Other extra make commands

* install_docs
* html_docs
* qch_docs
* docs


