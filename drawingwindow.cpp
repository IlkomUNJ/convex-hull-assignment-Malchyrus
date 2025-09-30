#include "drawingwindow.h"
#include "drawingcanvas.h"
#include <QVBoxLayout>
#include <QMessageBox>

DrawingWindow::DrawingWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Computer Graphic Simulation");
    resize(900, 600);

    QWidget *mainContainer = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(mainContainer);

    canvas = new DrawingCanvas(this);

    QPushButton *pushButtonDraw = new QPushButton("Run Simulation ConvexHull", this);
    QPushButton *pushButtonClear = new QPushButton("Clear Canvas", this);
    QPushButton *pushButtonSlowConvex = new QPushButton("Run Simulation SlowConvex", this);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(pushButtonDraw);
    buttonLayout->addWidget(pushButtonClear);
    buttonLayout->addWidget(pushButtonSlowConvex);

    mainLayout->addWidget(canvas);
    mainLayout->addLayout(buttonLayout);

    setCentralWidget(mainContainer);

    connect(pushButtonDraw, &QPushButton::clicked, canvas, &DrawingCanvas::CalculateConvexHull);
    connect(pushButtonClear, &QPushButton::clicked, canvas, &DrawingCanvas::ClearCanvas);
    connect(pushButtonSlowConvex, &QPushButton::clicked, canvas, &DrawingCanvas::SlowConvex);
}
