include(docs/docs.pri)

TEMPLATE = subdirs
CONFIG += ordered
SUBDIRS += \
    $$PWD/src \
    $$PWD/example

OTHER_FILES += \
    $$PWD/LICENSE \
    $$PWD/README.md
