#ifndef DRAWINGCANVAS_H
#define DRAWINGCANVAS_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QPushButton>

class DrawingCanvas : public QWidget
{
    Q_OBJECT
public:
    explicit DrawingCanvas(QWidget *parent = nullptr);
    void setValue(bool v);
    void ClearCanvas();
    void SlowConvex();
    void CalculateConvexHull();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    bool value = true;
    int iteration = 0;
    QVector<QPoint> dots;
    QVector<QPoint> UpperHull;
    QVector<QPoint> LowerHull;
    QVector<QPoint> FullConvex;
    QVector<QPair<QPoint, QPoint>> Edges;
};

#endif // DRAWINGCANVAS_H
