#include "mainwindow.hpp"

#include <collapsiblepane.hpp>

#include <QCheckBox>
#include <QDoubleSpinBox>
#include <QGridLayout>
#include <QLabel>
#include <QScrollArea>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    QScrollArea* scrollArea = new QScrollArea(this);
    QWidget* scrollContents = new QWidget(scrollArea);

    QVBoxLayout* layout = new QVBoxLayout(scrollContents);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);

    setCentralWidget(scrollArea);
    scrollArea->setWidget(scrollContents);
    scrollArea->setWidgetResizable(true);

    CollapsiblePane* collapsiblePane[5];
    QWidget* widget[5];
    QGridLayout* gridLayout[5];
    QCheckBox* clip_shadow_above[5];
    QCheckBox* fade[5];
    QCheckBox* shadow[5];
    QCheckBox* redir_ignore[5];
    QCheckBox* full_shadow[5];
    QCheckBox* focus[5];
    QDoubleSpinBox* opacity[5];
    QLabel* opacity_label[5];

    for (int i = 0; i < 5; ++i) {
        collapsiblePane[i] = new CollapsiblePane(scrollContents);
        scrollContents->layout()->addWidget(collapsiblePane[i]);
        widget[i] = new QWidget();
        gridLayout[i] = new QGridLayout(widget[i]);
        gridLayout[i]->setContentsMargins(10, 10, 10, 10);
        clip_shadow_above[i] = new QCheckBox("Clip shadow above", widget[i]);
        fade[i] = new QCheckBox("Fade", widget[i]);

        opacity[i] = new QDoubleSpinBox(widget[i]);
        opacity[i]->setMaximum(1.00);
        opacity[i]->setSingleStep(0.05);

        shadow[i] = new QCheckBox("Shadow", widget[i]);
        redir_ignore[i] = new QCheckBox("Ignore redirection", widget[i]);
        full_shadow[i] = new QCheckBox("Full shadow", widget[i]);
        focus[i] = new QCheckBox("Focus", widget[i]);
        opacity_label[i] = new QLabel("Opacity:", widget[i]);

        gridLayout[i]->addWidget(fade[i], 0, 0, 1, 1);
        gridLayout[i]->addWidget(focus[i], 0, 1, 1, 1);
        gridLayout[i]->addWidget(redir_ignore[i], 0, 2, 1, 1);
        gridLayout[i]->addWidget(shadow[i], 1, 0, 1, 1);
        gridLayout[i]->addWidget(full_shadow[i], 1, 1, 1, 1);
        gridLayout[i]->addWidget(clip_shadow_above[i], 1, 2, 1, 1);
        gridLayout[i]->addWidget(opacity_label[i], 2, 0, 1, 1);
        gridLayout[i]->addWidget(opacity[i], 2, 1, 1, 2);

        collapsiblePane[i]->setText(QString("Effects for widget %1").arg(i + 1));
        collapsiblePane[i]->setWidget(widget[i]);
    }
}
