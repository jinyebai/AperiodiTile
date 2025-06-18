#include "artcreationexporter.h"
#include <QFileDialog>
#include <QVBoxLayout>

ArtCreationExporter::ArtCreationExporter(QWidget *parent) : QWidget(parent)
{
    materialComboBox = new QComboBox(this);
    materialComboBox->addItem("哑光");
    materialComboBox->addItem("金属");
    materialComboBox->addItem("玻璃");
    connect(materialComboBox, &QComboBox::currentTextChanged, this, &ArtCreationExporter::selectMaterial);

    exportButton = new QPushButton("导出图片", this);
    connect(exportButton, &QPushButton::clicked, this, &ArtCreationExporter::exportImage);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(materialComboBox);
    layout->addWidget(exportButton);
}

ArtCreationExporter::~ArtCreationExporter()
{
    delete materialComboBox;
    delete exportButton;
}

void ArtCreationExporter::selectMaterial()
{
    // 实现材质选择逻辑
    // 简单示例，暂时不实现具体逻辑
}

void ArtCreationExporter::exportImage()
{
    QString filePath = QFileDialog::getSaveFileName(this, "保存图片", "", "PNG Files (*.png)");
    if (!filePath.isEmpty()) {
        // 简单示例，生成一个空白图片
        patternImage = QImage(800, 600, QImage::Format_RGB32);
        patternImage.fill(Qt::white);
        patternImage.save(filePath);
    }
}    
