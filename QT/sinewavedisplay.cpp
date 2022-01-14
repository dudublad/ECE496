#include "sinewavedisplay.h"

SineWaveDisplay::SineWaveDisplay(QWidget *parent) : SoundDisplay(parent)
{
    // initializing data attributes
    waveFrequency = 20;

    // Creating subwidgets
    frequencySlider = new QSlider(this);

    // TODO: make this into a spinbox
    frequencyLabel = new QLabel(this);
    titleLabel = new QLabel(this);
    frequencyLayout = new QGridLayout(this);
    // setting up frequency slider
    frequencySlider->setValue(waveFrequency);
    frequencySlider->setMinimum(20);
    frequencySlider->setMaximum(20000);
    frequencySlider->setSingleStep(100);
    // connecting signals
    connect(frequencySlider,SIGNAL(valueChanged(int)),this,SLOT(frequencySliderStop(int)));
    // Adding the frequency controls to the layout

    mainLayout->addLayout(frequencyLayout);
    frequencyLayout->addWidget(frequencyLabel,0,0);
    frequencyLayout->addWidget(frequencySlider,1,0);
    frequencyLayout->addWidget(frequencyLabel,1,1);
    frequencyLayout->addWidget(playButton,1,2);
}

void SineWaveDisplay::frequencySliderStop(int value)
{
    //changes frequency according to what is in the slider
    frequencyLabel->setText(QString::number(value) + "Hz");
    waveFrequency = value;
    //std::cout << "current value: " << value << std::endl;
    //Clear the graph so that generateSineWave() is not
    //Accessing the same file
    //TODO: Better method for this
//    drawWaveFromFile("");

//    generateSineWav(file);
//    drawWaveFromFile(file);
//    playSine();

}

void SineWaveDisplay::setFrequency(int freq)
{
    //nothing for now
    waveFrequency = freq;
}
