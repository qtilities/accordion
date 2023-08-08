/*
    MIT License

    Copyright (c) 2021-2023 Andrea Zanellato <redtid3@gmail.com>

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to
    deal in the Software without restriction, including without limitation the
    rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
    sell copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
    IN THE SOFTWARE.
*/
#include "mainwindow.hpp"
#include <QApplication>
#include <QScreen>

QScreen *screenAt(const QPoint &pos)
{
#if QT_VERSION >= QT_VERSION_CHECK(5, 10, 0)
    return qApp->screenAt(pos);
#else
    const QList<QScreen *> screens = QGuiApplication::screens();
    for (QScreen *screen : screens) {
        if (screen->geometry().contains(pos))
            return screen;
    }
    return nullptr;
#endif
}

void centerOnScreen(QWidget *widget)
{
    if (const QScreen *screen = screenAt(QCursor::pos())) {
        QRect rct = screen->geometry();
        widget->move((rct.width() - widget->width()) / 2,
                     (rct.height() - widget->height()) / 2);
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Accordion");
    w.resize(512, 256);
    w.show();
    centerOnScreen(&w);
    return a.exec();
}
