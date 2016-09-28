include(docs/docs.pri)

TEMPLATE = subdirs
CONFIG += ordered
SUBDIRS += \
    $$PWD/src \
    $$PWD/example

OTHER_FILES += \
    $$PWD/LICENSE \
    $$PWD/README.md \
    $$PWD/com_github_JosephMillsAtWork_QmlScreenExtras.pri \
    $$PWD/qpm.json
