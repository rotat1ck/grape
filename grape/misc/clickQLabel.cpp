#include "../misc/clickQLabel.h"

ClickQLabel::ClickQLabel(QWidget* parent, Qt::WindowFlags f) : QLabel(parent) {
    setCursor(Qt::PointingHandCursor);
    setStyleSheet(
        "font-family: 'Julius Sans One';"
        "font-style: normal;"
        "font-weight: 400;"
        "font-size: 15px;"
        "line-height: 16px;"
        "color: #78A8FF;"
    );
}

ClickQLabel::~ClickQLabel() {}

void ClickQLabel::mousePressEvent(QMouseEvent* event) {
    emit clicked();
}
