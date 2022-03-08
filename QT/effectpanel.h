#ifndef EFFECTPANEL_H
#define EFFECTPANEL_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
class EffectPanel : public QWidget
{
    Q_OBJECT
public:
    // Functions
    EffectPanel(QWidget *parent);
    ~EffectPanel();


    // Subwidgets
    QPushButton* filterButton;

    QPushButton* noiseButton;



    // Layouts
    QGridLayout* effectButtonLayout;

    // Variables

public slots:
    void filterButtonPressed();
    void noiseButtonPressed();
};

#endif // EFFECTPANEL_H
