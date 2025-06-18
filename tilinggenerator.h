#ifndef TILINGGENERATOR_H
#define TILINGGENERATOR_H

#include <QWidget>
#include <QVector>
#include <QPolygon>
#include <QTimer>
#include <QSlider>
#include <QColorDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QComboBox>
#include <QMainWindow> // 新增：包含QMainWindow头文件

enum TilingType {
    PENROSE_TILING,
    HAT_TILING,
    GHOST_TILING
};

class TilingGenerator : public QMainWindow // 修改：继承自QMainWindow而不是QWidget
{
    Q_OBJECT
public:
    explicit TilingGenerator(QWidget *parent = nullptr);
    ~TilingGenerator();

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void generateTiling();
    void updateTileParameters();
    void performReplacement();
    void changeTilingType(int index);

private:
    QVector<QPolygon> tiles;
    QTimer *timer;
    QSlider *sideLengthSlider;
    QSlider *rotationAngleSlider;
    QColorDialog *colorDialog;
    QPushButton *generateButton;
    QPushButton *replaceButton;
    QComboBox *tilingTypeComboBox;
    int replacementLevel;
    TilingType currentTilingType;
    int tileCount;

    // 新增私有函数声明
    void replacePenroseTiles(QVector<QPolygon> &tiles, int level);
    void tileHats(QVector<QPolygon> &tiles, int tileCount);
    void tileGhosts(QVector<QPolygon> &tiles, int tileCount);
};

#endif // TILINGGENERATOR_H