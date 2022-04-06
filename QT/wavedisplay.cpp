#include "wavedisplay.h"

WaveDisplay::WaveDisplay(QWidget *parent, int id) : SoundDisplay(parent)
{

    int MAX_FREQ = 20000;
    int MIN_FREQ = 20;
    // initializing data attributes
    waveFrequency = 20;
    amplitude = 1.00;
    inputId = id;
    // Creating subwidgets
    frequencySlider = new QSlider(Qt::Vertical,this);

    frequencyLabel = new QSpinBox(this);
    titleLabel = new QLabel(this);
    removeInputButton = new QPushButton("Remove Input",this);
    generateButton = new QPushButton("Generate Wave",this);
    amplitudeLabel = new QLabel(this);
    amplitudeSlider = new QSlider(Qt::Horizontal,this);
    //frequencyLayout = new QVBoxLayout(this);
    // setting up frequency slider
    frequencySlider->setValue(waveFrequency);
    frequencySlider->setMinimum(MIN_FREQ);
    frequencySlider->setMaximum(MAX_FREQ);
    frequencySlider->setSingleStep(100);
    //Label inits
    frequencyLabel->setValue(waveFrequency);
    frequencyLabel->setMinimum(MIN_FREQ);
    frequencyLabel->setMaximum(MAX_FREQ);
    frequencyLabel->setSuffix(" Hz");

    amplitudeSlider->setMinimum(1);
    amplitudeSlider->setMaximum(100);
    amplitudeSlider->setSingleStep(1);
    amplitudeSlider->setValue(amplitude*100);
    amplitudeLabel->setText(QString::fromStdString("Wave Amplitude: 1.00"));
    amplitudeLabel->setAlignment(Qt::AlignCenter);
    //frequencyLabel->setValue(QString::number(waveFrequency) + "Hz");
    titleLabel->setText("Set Wave Frequency");
    titleLabel->setAlignment(Qt::AlignCenter);

    // connecting signals
    connect(frequencySlider,SIGNAL(valueChanged(int)),this,SLOT(frequencySliderChange(int)));
    connect(playButton,SIGNAL(clicked()),this,SLOT(onPlayButtonClicked()));
    connect(frequencyLabel,SIGNAL(valueChanged(int)),this,SLOT(onSpinBoxChanged(int)));
    connect(removeInputButton,SIGNAL(clicked()),this,SLOT(removeInputButtonPushed()));
    connect(generateButton,SIGNAL(clicked()),this,SLOT(generateButtonPushed()));
    connect(amplitudeSlider,SIGNAL(sliderReleased()),this,SLOT(amplitudeSliderStop()));
    connect(amplitudeSlider,SIGNAL(valueChanged(int)),this,SLOT(amplitudeSliderChange(int)));
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
    buttonLayout->addWidget(amplitudeLabel,5,0,Qt::AlignCenter);
    buttonLayout->addWidget(amplitudeSlider,5,1,Qt::AlignCenter);
    buttonLayout->addWidget(generateButton,6,0,Qt::AlignCenter);

    //Setup Sine wave
    QString file = QDir::currentPath() + "/audio_files/gen_sine.wav";
    wave.setFilePath(file);
    //changes frequency according to what is in the slider
    wave.setFrequency(waveFrequency);
    plotWave();

    last_generate_time_ms = QDateTime::currentMSecsSinceEpoch();
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
    if(frequencyLabel->value() != value) {
        frequencyLabel->setValue(value);
    }
}

void WaveDisplay::waveTypeIndexChanged(int index)
{
    wave.setWaveType((WaveType) index);
}

void WaveDisplay::onPlayButtonClicked()
{
    //plotWave();
    if(! this->soundFile.isPlaying())
    {
        playSound();
    }
}

void WaveDisplay::onSpinBoxChanged(int value)
{
    waveFrequency = value;
    frequencySlider->setValue(value);
}

/*
 * Limited by GENERATE_LIMIT_S
 */
void WaveDisplay::generateButtonPushed()
{
    if(QDateTime::currentMSecsSinceEpoch() >= last_generate_time_ms + GENERATE_LIMIT_MS)
    {
        wave.setFrequency(waveFrequency);
        plotWave();
        emit waveGenerated(waveFrequency);
        last_generate_time_ms = QDateTime::currentMSecsSinceEpoch();
    }
}

void WaveDisplay::amplitudeSliderStop()
{
    wave.setAmplitude(amplitude);
}

void WaveDisplay::amplitudeSliderChange(int value)
{
    double convAmp = ((double)value)/100.0;
    amplitude = convAmp;
    std::string convAmpString = std::to_string(convAmp).substr(0, std::to_string(convAmp).find(".") + 2 + 1);
    amplitudeLabel->setText(QString::fromStdString("Wave Amplitude: " + convAmpString));
    amplitude = convAmp;
}

