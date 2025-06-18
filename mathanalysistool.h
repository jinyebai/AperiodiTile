#ifndef MATHANALYSISTOOL_H
#define MATHANALYSISTOOL_H

#include <QWidget>
#include <QChartView>
#include <QBarSeries>
#include <QTextEdit>

class MathAnalysisTool : public QWidget
{
    Q_OBJECT
public:
    explicit MathAnalysisTool(QWidget *parent = nullptr);
    ~MathAnalysisTool();

private slots:
    void analyzeSymmetry();
    void analyzeFrequency();

private:
    QChartView *chartView;
    QBarSeries *barSeries;
    QTextEdit *symmetryResultText;
};

#endif // MATHANALYSISTOOL_H    