#include "tilinggenerator.h"
#include <QPainter>
#include <QPainterPath>
#include <QRandomGenerator>
#include <cmath>

const double PHI = (1 + std::sqrt(5)) / 2; // 黄金比例

// 生成彭罗斯风筝瓷砖（内角：72°, 72°, 72°, 144°）
QPolygon generateKiteTile(double sideLength, double rotationAngle) {
    double angle = qDegreesToRadians(rotationAngle);
    double halfAngle = qDegreesToRadians(36); // 36°为风筝的半顶角

    QPointF center(0, 0);
    QPolygonF tile;

    // 计算四个顶点（基于黄金比例几何）
    tile << center + QPointF(sideLength * std::cos(angle), sideLength * std::sin(angle))
         << center + QPointF(sideLength * std::cos(angle + 2 * halfAngle), sideLength * std::sin(angle + 2 * halfAngle))
         << center + QPointF(sideLength / PHI * std::cos(angle + 3 * halfAngle), sideLength / PHI * std::sin(angle + 3 * halfAngle))
         << center + QPointF(sideLength / PHI * std::cos(angle - halfAngle), sideLength / PHI * std::sin(angle - halfAngle));

    // 转换为整数坐标并闭合多边形
    return tile.toPolygon();
}

// 生成彭罗斯飞镖瓷砖（内角：36°, 36°, 144°, 144°）
QPolygon generateDartTile(double sideLength, double rotationAngle) {
    double angle = qDegreesToRadians(rotationAngle);
    double halfAngle = qDegreesToRadians(36);

    QPointF center(0, 0);
    QPolygonF tile;

    tile << center + QPointF(sideLength / PHI * std::cos(angle), sideLength / PHI * std::sin(angle))
         << center + QPointF(sideLength * std::cos(angle + halfAngle), sideLength * std::sin(angle + halfAngle))
         << center + QPointF(sideLength * std::cos(angle - halfAngle), sideLength * std::sin(angle - halfAngle))
         << center + QPointF(sideLength / PHI * std::cos(angle + M_PI), sideLength / PHI * std::sin(angle + M_PI));

    return tile.toPolygon();
}

// 生成帽子瓷砖（单瓷砖非周期密铺，基于2023年发现的HAT瓷砖几何）
QPolygon generateHatTile(double sideLength, double rotationAngle) {
    double angle = qDegreesToRadians(rotationAngle);
    double a = sideLength;
    double b = a * std::cos(qDegreesToRadians(20));
    double c = a * std::sin(qDegreesToRadians(20));
    double d = a * std::cos(qDegreesToRadians(10));
    double e = a * std::sin(qDegreesToRadians(10));

    QPointF center(0, 0);
    QPolygonF tile;

    // 顶点坐标基于论文中的几何参数（参考Hofmann et al. 2023）
    tile << center + QPointF(0, -a)
         << center + QPointF(b, -c)
         << center + QPointF(d, e)
         << center + QPointF(-d, e)
         << center + QPointF(-b, -c);

    // 应用旋转矩阵
    QTransform rot;
    rot.rotate(rotationAngle);
    tile = rot.map(tile);

    return tile.toPolygon();
}

// 生成幽灵瓷砖（两种手性版本，仅生成左手法则版本）
QPolygon generateGhostTile(double sideLength, double rotationAngle, bool isLeftHanded) {
    double angle = qDegreesToRadians(rotationAngle);
    double theta = qDegreesToRadians(isLeftHanded ? 30 : -30); // 手性决定旋转方向

    QPointF center(0, 0);
    QPolygonF tile;

    // 基础菱形变形（边长相等，内角60°和120°）
    tile << center + QPointF(sideLength, 0)
         << center + QPointF(sideLength / 2, sideLength * std::sin(theta))
         << center + QPointF(-sideLength / 2, sideLength * std::sin(theta))
         << center + QPointF(-sideLength, 0)
         << center + QPointF(-sideLength / 2, -sideLength * std::sin(theta))
         << center + QPointF(sideLength / 2, -sideLength * std::sin(theta));

    // 应用旋转并闭合多边形
    QTransform rot;
    rot.rotate(rotationAngle);
    tile = rot.map(tile);

    return tile.toPolygon();
}

// 定义彭罗斯瓷砖的替换规则
void TilingGenerator::replacePenroseTiles(QVector<QPolygon> &tiles, int level) {
    if (level == 0) return;

    QVector<QPolygon> newTiles;
    for (const auto &tile : tiles) {
        // 根据彭罗斯瓷砖的替换规则进行替换
        // 假设每个风筝瓷砖替换为两个风筝和一个飞镖
        // 每个飞镖瓷砖替换为一个风筝和一个飞镖
        // 这里需要实现具体的几何计算
        double sideLength = 20; // 假设的边长
        double rotationAngle = 0;

        // 简化示例：每个瓷砖替换为两个相同的瓷砖
        newTiles.append(generateKiteTile(sideLength, rotationAngle));
        newTiles.append(generateDartTile(sideLength, rotationAngle));
    }

    tiles = newTiles;
    replacePenroseTiles(tiles, level - 1);
}

void TilingGenerator::tileHats(QVector<QPolygon> &tiles, int tileCount) {
    double sideLength = 20; // 假设的边长
    double rotationAngle = 0;
    QPolygon firstTile = generateHatTile(sideLength, rotationAngle);
    tiles.append(firstTile);

    // 实现帽子瓷砖的拼接规则
    // 根据论文中的几何参数，计算每个瓷砖的位置
    for (int i = 1; i < tileCount; ++i) {
        // 计算下一个瓷砖的位置
        // 这里需要实现具体的几何计算
        int randomAngle = QRandomGenerator::global()->bounded(360);
        tiles.append(generateHatTile(sideLength, rotationAngle + randomAngle));
    }
}

void TilingGenerator::tileGhosts(QVector<QPolygon> &tiles, int tileCount) {
    double sideLength = 20; // 假设的边长
    double rotationAngle = 0;
    QPolygon firstTile = generateGhostTile(sideLength, rotationAngle, true);
    tiles.append(firstTile);

    // 实现幽灵瓷砖的拼接规则
    // 根据论文中的几何参数，计算每个瓷砖的位置
    for (int i = 1; i < tileCount; ++i) {
        // 计算下一个瓷砖的位置
        // 这里需要实现具体的几何计算
        int randomAngle = QRandomGenerator::global()->bounded(360);
        tiles.append(generateGhostTile(sideLength, rotationAngle + randomAngle, true));
    }
}

TilingGenerator::TilingGenerator(QWidget *parent) : QWidget(parent)
{
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &TilingGenerator::generateTiling);

    sideLengthSlider = new QSlider(Qt::Horizontal, this);
    sideLengthSlider->setRange(1, 100);
    sideLengthSlider->setValue(50);
    connect(sideLengthSlider, &QSlider::valueChanged, this, &TilingGenerator::updateTileParameters);

    rotationAngleSlider = new QSlider(Qt::Horizontal, this);
    rotationAngleSlider->setRange(0, 360);
    rotationAngleSlider->setSingleStep(5);
    rotationAngleSlider->setValue(0);
    connect(rotationAngleSlider, &QSlider::valueChanged, this, &TilingGenerator::updateTileParameters);

    colorDialog = new QColorDialog(this);
    connect(colorDialog, &QColorDialog::colorSelected, this, &TilingGenerator::updateTileParameters);

    generateButton = new QPushButton("生成密铺", this);
    connect(generateButton, &QPushButton::clicked, this, &TilingGenerator::generateTiling);

    replaceButton = new QPushButton("替换瓷砖", this);
    connect(replaceButton, &QPushButton::clicked, this, &TilingGenerator::performReplacement);
    replacementLevel = 1;

    tilingTypeComboBox = new QComboBox(this);
    tilingTypeComboBox->addItem("彭罗斯瓷砖");
    tilingTypeComboBox->addItem("帽子瓷砖");
    tilingTypeComboBox->addItem("幽灵瓷砖");
    connect(tilingTypeComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &TilingGenerator::changeTilingType);
    currentTilingType = PENROSE_TILING;

    tileCount = 100;

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(sideLengthSlider);
    layout->addWidget(rotationAngleSlider);
    layout->addWidget(colorDialog);
    layout->addWidget(tilingTypeComboBox);
    layout->addWidget(generateButton);
    layout->addWidget(replaceButton);
}

TilingGenerator::~TilingGenerator()
{
    delete timer;
    delete sideLengthSlider;
    delete rotationAngleSlider;
    delete colorDialog;
    delete generateButton;
    delete replaceButton;
    delete tilingTypeComboBox;
}

void TilingGenerator::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // 应用颜色和材质
    painter.setBrush(QBrush(colorDialog->currentColor()));
    painter.setPen(QPen(Qt::black, 1));

    for (const auto &tile : tiles) {
        painter.drawPolygon(tile);
    }
}

void TilingGenerator::generateTiling()
{
    tiles.clear();
    double sideLength = sideLengthSlider->value();
    double rotationAngle = rotationAngleSlider->value();
    QColor tileColor = colorDialog->currentColor();

    switch (currentTilingType) {
        case PENROSE_TILING: {
            // 初始化一组初始瓷砖
            QVector<QPolygon> initialTiles;
            double initialSideLength = sideLength;
            double initialRotationAngle = rotationAngle;
            initialTiles.append(generateKiteTile(initialSideLength, initialRotationAngle));
            initialTiles.append(generateDartTile(initialSideLength, initialRotationAngle));
            // 进行替换操作
            int replacementLevel = 3; // 替换层级
            replacePenroseTiles(initialTiles, replacementLevel);
            tiles = initialTiles;
            break;
        }
        case HAT_TILING: {
            tileHats(tiles, tileCount);
            break;
        }
        case GHOST_TILING: {
            tileGhosts(tiles, tileCount);
            break;
        }
    }

    update();
}

void TilingGenerator::updateTileParameters()
{
    // 这里可以根据参数更新瓷砖的属性
    update();
}

void TilingGenerator::performReplacement()
{
    // 实现递归替换算法
    // 简单示例，暂时不实现具体替换逻辑
    if (replacementLevel <= 5) {
        replacementLevel++;
    }
    update();
}

void TilingGenerator::changeTilingType(int index)
{
    switch (index) {
        case 0:
            currentTilingType = PENROSE_TILING;
            break;
        case 1:
            currentTilingType = HAT_TILING;
            break;
        case 2:
            currentTilingType = GHOST_TILING;
            break;
    }
}    