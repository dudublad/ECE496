#include "effectpanel.h"

EffectPanel::EffectPanel(QWidget *parent) : QWidget(parent)
{
    //Initializing Buttons
    filterButton = new QPushButton("Add Filter",this);
    noiseButton = new QPushButton("Add Noise",this);

    // Initializing Layout
    effectButtonLayout = new QGridLayout(this);
    this->setVisible(false);

    connect(filterButton,SIGNAL(clicked()),this,SLOT(filterButtonPressed()));
    connect(noiseButton,SIGNAL(clicked()),this,SLOT(noiseButtonPressed()));

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
    //Pop up a QInputDialog for the filter Button Menu
}

void EffectPanel::noiseButtonPressed()
{

}
