TEMPLATE = subdirs

SUBDIRS += \
    Qliblzma \
    app

Qliblzma.subdir = lib/Qliblzma
app.subdir      = app

app.depends = Qliblzma
