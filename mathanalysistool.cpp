#include "mathanalysistool.h"
#include <QtCharts/QChart>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QDialog> // 确保包含QDialog头文件
#include <QPushButton> // 添加缺失的头文件
#include <QVBoxLayout>
#include <QTextEdit>

MathAnalysisTool::MathAnalysisTool(QWidget *parent) : QWidget(parent)
{
    chartView = new QChartView(this);
    barSeries = new QBarSeries();
    QChart *chart = new QChart();
    chart->addSeries(barSeries);
    chartView->setChart(chart);

    symmetryResultText = new QTextEdit(this);
    symmetryResultText->setReadOnly(true);

    QPushButton *symmetryButton = new QPushButton("分析对称性", this);
    connect(symmetryButton, &QPushButton::clicked, this, &MathAnalysisTool::analyzeSymmetry); // 此处不再报错

    QPushButton *frequencyButton = new QPushButton("分析频率", this);
    connect(frequencyButton, &QPushButton::clicked, this, &MathAnalysisTool::analyzeFrequency);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(chartView);
    layout->addWidget(symmetryResultText);
    layout->addWidget(symmetryButton);
    layout->addWidget(frequencyButton);
}

MathAnalysisTool::~MathAnalysisTool()
{
    delete chartView;
    delete barSeries;
    delete symmetryResultText;
}

void MathAnalysisTool::analyzeSymmetry()
{
    // 实现对称性快速评估
    // 简单示例，暂时不实现具体分析逻辑
    symmetryResultText->setText("对称群类型: p1");
}

void MathAnalysisTool::analyzeFrequency()
{
    // 实现频率统计
    // 简单示例，暂时不实现具体统计逻辑
    barSeries->clear();
    QBarSet *set = new QBarSet("频率");
    *set << 10 << 20 << 30;
    barSeries->append(set);
    chartView->chart()->update();
}