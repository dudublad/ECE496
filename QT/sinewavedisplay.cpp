#include "sinewavedisplay.h"

SineWaveDisplay::SineWaveDisplay(QWidget *parent) : SoundDisplay(parent)
{

    //DO NOT MESS WITH THE LAYOUTS, THEY ARE VERY SENSITIVE AND PRONE TO BREAKING

    // initializing data attributes
    waveFrequency = 20;

    // Creating subwidgets
    frequencySlider = new QSlider(Qt::Horizontal,this);

    // TODO: make this into a spinbox
    frequencyLabel = new QLabel(this);
    titleLabel = new QLabel(this);
    frequencyLayout = new QVBoxLayout(this);
    // setting up frequency slider
    frequencySlider->setValue(waveFrequency);
    frequencySlider->setMinimum(20);
    frequencySlider->setMaximum(20000);
    frequencySlider->setSingleStep(100);

    //Label inits
    frequencyLabel->setText(QString::number(waveFrequency) + "Hz");
    titleLabel->setText("Set Wave Frequency");
    titleLabel->setAlignment(Qt::AlignCenter);
    // connecting signals
    connect(frequencySlider,SIGNAL(valueChanged(int)),this,SLOT(frequencySliderStop(int)));
    // Adding the frequency controls to the layout


    frequencyLayout->addWidget(titleLabel);

    frequencyControlLayout = new QHBoxLayout(this);
    frequencyControlLayout->addWidget(stopButton);
    frequencyControlLayout->addWidget(frequencySlider);
    frequencyControlLayout->addWidget(frequencyLabel);
    frequencyControlLayout->addWidget(playButton);
    frequencyLayout->addLayout(frequencyControlLayout);
    mainLayout->addLayout(frequencyLayout);
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