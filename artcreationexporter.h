#ifndef ARTCREATIONEXPORTER_H
#define ARTCREATIONEXPORTER_H

#include <QWidget>
#include <QComboBox>
#include <QPushButton>
#include <QImage>

class ArtCreationExporter : public QWidget
{
    Q_OBJECT
public:
    explicit ArtCreationExporter(QWidget *parent = nullptr);
    ~ArtCreationExporter();

private slots:
    void selectMaterial();
    void exportImage();

private:
    QComboBox *materialComboBox;
    QPushButton *exportButton;
    QImage patternImage;
};

#endif // ARTCREATIONEXPORTER_H    