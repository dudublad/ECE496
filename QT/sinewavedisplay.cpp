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

    waveTypeSelector = new QComboBox(this);
    waveTypeSelector->insertItem(Wave_Sin, "Sine Wave");
    waveTypeSelector->insertItem(Wave_Square, "Square Wave");
    waveTypeSelector->insertItem(Wave_SawTooth, "Sawtooth Wave");
    connect(waveTypeSelector,SIGNAL(currentIndexChanged(int)),this,SLOT(waveTypeIndexChanged(int)));
    frequencyControlLayout->addWidget(waveTypeSelector);


    //Setup Sine wave
    QString file = QDir::currentPath() + "/audio_files/gen_sine.wav";
    wave.setFilePath(file);
    //changes frequency according to what is in the slider
    wave.setFrequency(waveFrequency);
    plotWave();
}

void SineWaveDisplay::plotWave()
{
    //Clear the graph so that generateSine() is not
    //Accessing the same file
    drawWaveFromFile("");
    wave.generateSine();

    QString file = wave.getFilePath();
    drawWaveFromFile(file);
}

void SineWaveDisplay::playSound()
{
    QString file = wave.getFilePath();
    wave.openFile(file);
    wave.startStream();
}

void SineWaveDisplay::frequencySliderChange(int value)
{
    //changes frequency according to what is in the slider
    frequencyLabel->setText(QString::number(value) + "Hz");
    waveFrequency = value;
}

void SineWaveDisplay::frequencySliderStop()
{
    //changes frequency according to what is in the slider
    wave.setFrequency(waveFrequency);

    plotWave();

    if(wave.isPlaying())
    {
        playSound();
    }
}

void SineWaveDisplay::waveTypeIndexChanged(int index)
{
    wave.setWaveType((WaveType) index);

    plotWave();

    if(wave.isPlaying())
    {
        playSound();
    }
}

void SineWaveDisplay::onPlayButtonClicked()
{
    playSound();
}
