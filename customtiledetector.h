#ifndef CUSTOMTILEDETECTOR_H
#define CUSTOMTILEDETECTOR_H

#include <QWidget>
#include <QGraphicsView>
#include <QSvgRenderer>
#include <QImage>

class CustomTileDetector : public QWidget
{
    Q_OBJECT
public:
    explicit CustomTileDetector(QWidget *parent = nullptr);
    ~CustomTileDetector();

private slots:
    void importSvgTile();
    void analyzeTilingPotential();

private:
    QGraphicsView *graphicsView;
    QSvgRenderer *svgRenderer;
    QImage heatmap;
};

#endif // CUSTOMTILEDETECTOR_H    