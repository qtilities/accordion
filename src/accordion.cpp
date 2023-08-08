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
#include "accordion.hpp"

#include <QPainter>
#include <QStyleOption>
#include <QVBoxLayout>

#include <QToolButton>

namespace Qtilities {

class ArrowButton : public QToolButton
{
    Q_OBJECT

public:
    explicit ArrowButton(QWidget *parent = nullptr);

private:
    void paintEvent(QPaintEvent *) override;
    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;
};

#include "accordion.moc"

ArrowButton::ArrowButton(QWidget *parent)
    : QToolButton(parent)
{
    /*
        Drawing arrow and borders using paintEvent, strange issues when using css:
        1. set the border color on :pressed or :checked selectors doesn't work
        2. the arrow is painted at the center over the label
        3. using images for arrows with state/color changes is not great
    */
    setCheckable(true);
    setStyleSheet("border: none");
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
}

void ArrowButton::paintEvent(QPaintEvent *event)
{
    QToolButton::paintEvent(event);

    QPainter painter(this);
    QStyleOption option;
    option.initFrom(this);
    style()->drawPrimitive(QStyle::PE_Widget, &option, &painter, this);

    painter.setRenderHint(QPainter::Antialiasing);

    int arrowSize = fontMetrics().height() / 2;
    QPalette pal = palette();
    QPolygon arrow;
    QRect r = rect();
    QRect arrowRect(r.x() + arrowSize, (r.height() - arrowSize) / 2, arrowSize, arrowSize);
    QPoint p1 = arrowRect.topLeft(), p2, p3;

    if (isChecked()) {
        p2 = arrowRect.topRight();
        p3 = (arrowRect.bottomLeft() + arrowRect.bottomRight()) / 2;
    } else {
        p2 = (arrowRect.topRight() + arrowRect.bottomRight()) / 2;
        p3 = arrowRect.bottomLeft();
    }

    painter.setPen(pal.color(QPalette::Light));
    painter.drawLine(r.topLeft(), r.topRight());
    painter.drawLine(r.topRight(), r.bottomRight());
    painter.setPen(pal.color(QPalette::Dark));
    painter.drawLine(r.bottomLeft(), r.bottomRight());
    painter.drawLine(r.topLeft(), r.bottomLeft());

    QColor c = pal.color(pal.currentColorGroup(), QPalette::ButtonText);
    painter.setBrush(c);
    painter.setPen(c);

    arrow.clear();
    arrow << p1 << p2 << p3;

    painter.drawPolygon(arrow);
}

QSize ArrowButton::minimumSizeHint() const
{
    int arrowSize = fontMetrics().height() / 2;
    return QSize(fontMetrics().horizontalAdvance(text()) + (arrowSize * 5), arrowSize * 3);
}

QSize ArrowButton::sizeHint() const
{
    return minimumSizeHint();
}
} // namespace Qtilities

Qtilities::Accordion::Accordion(QWidget *parent)
    : QWidget(parent)
    , layout_(new QVBoxLayout(this))
    , button_(new ArrowButton(this))
    , widget_(nullptr)
{
    layout_->setContentsMargins(0, 0, 0, 0);
    layout_->setSpacing(0);
    layout_->addWidget(button_);
    setLayout(layout_);
}

void Qtilities::Accordion::setText(const QString &text) { button_->setText(text); }

void Qtilities::Accordion::setWidget(QWidget *widget)
{
    if (widget_) {
        disconnect(button_, &QAbstractButton::toggled, this, &Accordion::onExpandWidget);
        layout_->removeWidget(widget_);
        widget_->deleteLater();
    }
    if (widget) {
        layout_->addWidget(widget);
        widget->hide();
        connect(button_, &QAbstractButton::toggled, this, &Accordion::onExpandWidget);
    }
    widget_ = widget;
}

void Qtilities::Accordion::onExpandWidget(bool visible)
{
    widget_->setVisible(visible);
}
