#include "wavedisplay.h"

WaveDisplay::WaveDisplay(QWidget *parent, int id) : SoundDisplay(parent)
{

    int MAX_FREQ = 20000;
    int MIN_FREQ = 20;
    // initializing data attributes
    waveFrequency = 20;
    inputId = id;
    // Creating subwidgets
    frequencySlider = new QSlider(Qt::Vertical,this);

    frequencyLabel = new QDoubleSpinBox(this);
    titleLabel = new QLabel(this);
    removeInputButton = new QPushButton("Remove Input",this);
    //frequencyLayout = new QVBoxLayout(this);
    // setting up frequency slider
    frequencySlider->setValue(waveFrequency);
    frequencySlider->setMinimum(MIN_FREQ);
    frequencySlider->setMaximum(MAX_FREQ);
    frequencySlider->setSingleStep(100);
    //Label inits
    frequencyLabel->setValue(waveFrequency);
    frequencyLabel->setDecimals(0);
    frequencyLabel->setMinimum(MIN_FREQ);
    frequencyLabel->setMaximum(MAX_FREQ);
    frequencyLabel->setSuffix(" Hz");
    //frequencyLabel->setValue(QString::number(waveFrequency) + "Hz");
    titleLabel->setText("Set Wave Frequency");
    titleLabel->setAlignment(Qt::AlignCenter);
    // connecting signals
    connect(frequencySlider,SIGNAL(valueChanged(int)),this,SLOT(frequencySliderChange(int)));
    connect(playButton,SIGNAL(clicked()),this,SLOT(onPlayButtonClicked()));
    connect(frequencySlider,SIGNAL(sliderReleased()),this,SLOT(frequencySliderStop()));
    connect(frequencyLabel,SIGNAL(valueChanged(double)),this,SLOT(onSpinBoxChanged(double)));
    connect(removeInputButton,SIGNAL(clicked()),this,SLOT(removeInputButtonPushed()));
    // Adding the frequency controls to the layout


    // frequencyLayout->addWidget(titleLabel);

    // frequencyControlLayout = new QHBoxLayout(this);
    // frequencyControlLayout->addWidget(stopButton);
    // frequencyControlLayout->addWidget(frequencySlider);
    // frequencyControlLayout->addWidget(frequencyLabel);
    // frequencyControlLayout->addWidget(playButton);
    // frequencyLayout->addLayout(frequencyControlLayout);
    // mainLayout->addLayout(frequencyLayout);
//    buttonLayout->addWidget(playButton,0,0,Qt::AlignCenter);
//    buttonLayout->addWidget(stopButton,1,0,Qt::AlignCenter);
//    buttonLayout->addWidget(toggleEffectPanelButton,2,0,Qt::AlignCenter);
//    buttonLayout->addWidget(titleLabel,0,1,Qt::AlignCenter);
//    buttonLayout->addWidget(frequencySlider,1,1,Qt::AlignCenter);
//    buttonLayout->addWidget(frequencyLabel,2,1,Qt::AlignCenter);
//    buttonLayout->addWidget(removeInputButton,3,0,Qt::AlignCenter);
//    buttonLayout->addWidget(volumeLabel,)

    waveTypeSelector = new QComboBox(this);
    waveTypeSelector->insertItem(Wave_Sin, "Sine Wave");
    waveTypeSelector->insertItem(Wave_Square, "Square Wave");
    waveTypeSelector->insertItem(Wave_SawTooth, "Sawtooth Wave");
    connect(waveTypeSelector,SIGNAL(currentIndexChanged(int)),this,SLOT(waveTypeIndexChanged(int)));
    buttonLayout->addWidget(playButton,0,0,Qt::AlignCenter);
    buttonLayout->addWidget(stopButton,1,0,Qt::AlignCenter);
    buttonLayout->addWidget(toggleEffectPanelButton,2,0,Qt::AlignCenter);
    buttonLayout->addWidget(titleLabel,0,1,Qt::AlignCenter);
    buttonLayout->addWidget(frequencySlider,1,1,Qt::AlignCenter);
    buttonLayout->addWidget(frequencyLabel,2,1,Qt::AlignCenter);
    buttonLayout->addWidget(removeInputButton,3,0,Qt::AlignCenter);
    buttonLayout->addWidget(waveTypeSelector,3,1,Qt::AlignCenter);
    buttonLayout->addWidget(volumeLabel,4,0,Qt::AlignCenter);
    buttonLayout->addWidget(volumeSlider,4,1,Qt::AlignCenter);


    //Setup Sine wave
    QString file = QDir::currentPath() + "/audio_files/gen_sine.wav";
    wave.setFilePath(file);
    //changes frequency according to what is in the slider
    wave.setFrequency(waveFrequency);
    plotWave();
}

void WaveDisplay::plotWave()
{
    //Clear the graph so that generateSine() is not
    //Accessing the same file
    drawWaveFromFile("");
    wave.generateSine();

    QString file = wave.getFilePath();
    drawWaveFromFile(file);
}

void WaveDisplay::playSound()
{
    QString file = wave.getFilePath();
    this->soundFile.openFile(file);
    this->soundFile.startStream();
}

void WaveDisplay::frequencySliderChange(int value)
{
    //changes frequency according to what is in the slider
    frequencyLabel->setValue(value);
    waveFrequency = value;
}

void WaveDisplay::frequencySliderStop()
{
    //changes frequency according to what is in the slider
    wave.setFrequency(waveFrequency);

    plotWave();

    if(this->soundFile.isPlaying())
    {
        playSound();
    }
}

void WaveDisplay::waveTypeIndexChanged(int index)
{
    wave.setWaveType((WaveType) index);

    plotWave();

    if(this->soundFile.isPlaying())
    {
        playSound();
    }
}

void WaveDisplay::onPlayButtonClicked()
{
    playSound();
}

void WaveDisplay::onSpinBoxChanged(double value)
{
//    int convertedValue = (int)value;
//    fprintf(stderr,"ring ring calling \n");
//    waveFrequency = convertedValue;
//    frequencySlider->setValue(convertedValue);
//    plotWave();
}
