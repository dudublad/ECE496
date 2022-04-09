#ifndef EFFECTPANEL_H
#define EFFECTPANEL_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include "effectdialog.h"
#include "programenums.h"
#include <iostream>
#include "filterdialog.h"
#include "audiofilter.h"

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

signals:
    void sendFilter(audioFilter filter);


};

#endif // EFFECTPANEL_H
