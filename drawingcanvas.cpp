#include "drawingcanvas.h"

DrawingCanvas::DrawingCanvas(QWidget *parent)
    : QWidget{parent}
{}

void DrawingCanvas::setValue(bool v)
{
    value = v;
    update();
}

void DrawingCanvas::ClearCanvas()
{
    dots.clear();
    UpperHull.clear();
    LowerHull.clear();
    FullConvex.clear();
    Edges.clear();
    iteration = 0;
    update();
}

void DrawingCanvas::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        dots.append(event->pos());
        FullConvex.clear();
        Edges.clear();
        iteration = 0;
        update();
    }
}

void DrawingCanvas::SlowConvex()
{
    Edges.clear();
    FullConvex.clear();
    iteration = 0;

    for (int i = 0; i < dots.size(); i++) {
        for (int j = 0; j < dots.size(); j++) {
            if (i == j) continue;
            QPoint p = dots[i];
            QPoint q = dots[j];

            bool valid = true;

            for (int k = 0; k < dots.size(); ++k) {
                if (k == i || k == j) continue;
                QPoint r = dots[k];

                iteration++;

                if (((q.x() - p.x()) * (r.y() - p.y()) -
                     (q.y() - p.y()) * (r.x() - p.x())) > 0) {
                    valid = false;
                    break;
                }
            }
            if (valid)
                Edges.append(qMakePair(p, q));
        }
    }

    if (!Edges.isEmpty()) {
        QPoint start = Edges[0].first;
        for (const auto &e : Edges) {
            if (e.first.x() < start.x() ||
                (e.first.x() == start.x() && e.first.y() < start.y())) {
                start = e.first;
            }
        }

        FullConvex.append(start);
        QPoint current = start;

        while (true) {
            bool foundNext = false;
            QPoint nextPoint;

            for (const auto &e : Edges) {
                if (e.first == current) {
                    nextPoint = e.second;
                    foundNext = true;
                    break;
                }
            }

            if (!foundNext || nextPoint == start)
                break;

            FullConvex.append(nextPoint);
            current = nextPoint;
        }
    }

    update();
}

void DrawingCanvas::CalculateConvexHull()
{
    UpperHull.clear();
    LowerHull.clear();
    Edges.clear();
    FullConvex.clear();
    iteration = 0;

    if (dots.isEmpty() || dots.size() < 2) {
        return;
    }
    std::sort(dots.begin(), dots.end(), [](const QPoint &a, const QPoint &b){
        return a.x() < b.x() || (a.x() == b.x() && a.y() < b.y());
    });

    UpperHull.append(dots[0]);
    UpperHull.append(dots[1]);

    for (int i = 2; i < dots.size(); i++) {
        UpperHull.append(dots[i]);

        while (UpperHull.size() > 2) {
            iteration++;
            int n = UpperHull.size();
            QPoint a = UpperHull[n - 3];
            QPoint b = UpperHull[n - 2];
            QPoint c = UpperHull[n - 1];

            double cross = (b.x() - a.x()) * (c.y() - a.y()) -
                           (b.y() - a.y()) * (c.x() - a.x());

            if (cross <= 0) {
                UpperHull.remove(n - 2);
            } else {
                break;
            }
        }
    }

    LowerHull.append(dots[dots.size() - 1]);
    LowerHull.append(dots[dots.size() - 2]);

    for (int i = dots.size() - 3; i >= 0; i--) {
        LowerHull.append(dots[i]);

        while (LowerHull.size() > 2) {
            iteration++;
            int n = LowerHull.size();
            QPoint a = LowerHull[n - 3];
            QPoint b = LowerHull[n - 2];
            QPoint c = LowerHull[n - 1];

            double cross = (b.x() - a.x()) * (c.y() - a.y()) -
                           (b.y() - a.y()) * (c.x() - a.x());

            if (cross <= 0) {
                LowerHull.remove(n - 2);
            } else {
                break;
            }
        }
    }

    for (const QPoint &p : UpperHull)
        FullConvex.append(p);

    for (int i = 1; i < LowerHull.size() - 1; ++i)
        FullConvex.append(LowerHull[i]);

    update();
}

void DrawingCanvas::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    QPen pen(Qt::blue, 5, Qt::SolidLine);
    QFont font = painter.font();
    font.setPointSize(12);
    font.setBold(true);
    painter.setFont(font);

    painter.drawText(10, 20, "Number of points: " + QString::number(dots.size()));
    painter.drawText(10, 40, "Number of Iterations: " + QString::number(iteration));
    painter.setRenderHint(QPainter::Antialiasing);

    if (!FullConvex.isEmpty()){
        pen.setColor(Qt::blue);
        painter.setPen(pen);
        for (int i = 0; i < FullConvex.size(); i++){
            painter.drawLine(FullConvex[i], FullConvex[(i+1)% FullConvex.size()]);
        }
    }

    QPen dotPen(Qt::red, 8, Qt::SolidLine, Qt::RoundCap);
    painter.setPen(dotPen);
    for (const QPoint &dot : dots) {
        painter.drawPoint(dot);
    }
}
