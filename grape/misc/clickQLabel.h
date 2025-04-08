#ifndef CLICKQLABEL_H
#define CLICKQLABEL_H

#include <QLabel>
#include <QWidget>
#include <Qt>

class ClickQLabel : public QLabel {
    Q_OBJECT

public:
    explicit ClickQLabel(QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
    ~ClickQLabel();

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent* event);

};

#endif // CLICKQLABEL_H
