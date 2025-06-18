#include <QApplication>
#include <QMainWindow>
#include <QGridLayout>
#include "tilinggenerator.h"
#include "customtiledetector.h"
#include "mathanalysistool.h"
#include "artcreationexporter.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QMainWindow mainWindow;
    mainWindow.setWindowTitle("非周期密铺");

    QWidget centralWidget;
    QGridLayout *layout = new QGridLayout(&centralWidget);

    TilingGenerator *tilingGenerator = new TilingGenerator(); // 修改：创建独立窗口
    tilingGenerator->show(); // 新增：显示独立窗口

    CustomTileDetector *customTileDetector = new CustomTileDetector(&centralWidget);
    MathAnalysisTool *mathAnalysisTool = new MathAnalysisTool(&centralWidget);
    ArtCreationExporter *artCreationExporter = new ArtCreationExporter(&centralWidget);

    layout->addWidget(customTileDetector, 0, 0);
    layout->addWidget(mathAnalysisTool, 1, 0);
    layout->addWidget(artCreationExporter, 1, 1);

    mainWindow.setCentralWidget(&centralWidget);
    mainWindow.resize(1200, 800);
    mainWindow.show();

    return app.exec();
}