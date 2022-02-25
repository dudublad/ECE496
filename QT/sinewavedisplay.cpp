#include "sinewavedisplay.h"

SineWaveDisplay::SineWaveDisplay(QWidget *parent) : SoundDisplay(parent)
{

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
    connect(frequencySlider,SIGNAL(valueChanged(int)),this,SLOT(frequencySliderChange(int)));
    connect(frequencySlider,SIGNAL(sliderReleased()),this,SLOT(frequencySliderStop()));
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

void SineWaveDisplay::plotAndPlay()
{
    QString currentDirectory = QDir::currentPath();
    QString file = currentDirectory + "/audio_files/dgen_sine.wav";
    //changes frequency according to what is in the slider
    frequencyLabel->setText(QString::number(waveFrequency) + "Hz");
    sinWave.setFrequency(waveFrequency);
    //std::cout << "current value: " << value << std::endl;
    //Clear the graph so that generateSineWave() is not
    //Accessing the same file

    sinWave.setFilePath(file);
    sinWave.setFrequency(waveFrequency);
    sinWave.generateSine();

    drawWaveFromFile(file);
    sinWave.openFile(sinWave.getFilePath());
    sinWave.startStream();
}

void SineWaveDisplay::frequencySliderChange(int value)
{
    //changes frequency according to what is in the slider
    frequencyLabel->setText(QString::number(value) + "Hz");
    waveFrequency = value;
}

void SineWaveDisplay::frequencySliderStop()
{
    plotAndPlay();
}

void SineWaveDisplay::onPlayButtonClicked()
{
    plotAndPlay();
}

void SineWaveDisplay::setFrequency(int freq)
{
    waveFrequency = freq;
}
