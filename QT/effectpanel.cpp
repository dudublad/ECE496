#include "effectpanel.h"

EffectPanel::EffectPanel(QWidget *parent) : QWidget(parent)
{
    //Initializing Buttons
    filterButton = new QPushButton(this);
    noiseButton = new QPushButton(this);

    // Initializing Layout
    effectButtonLayout = new QGridLayout(this);
    this->setVisible(false);

    // Adding stuff to Layout
    effectButtonLayout->addWidget(filterButton);
    effectButtonLayout->addWidget(noiseButton);
}

EffectPanel::~EffectPanel()
{
    //stuff
}

void EffectPanel::filterButtonPressed()
{
    //Pop up the filter Button Menu
}
