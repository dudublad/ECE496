#include "wavedisplay.h"
#include <QSizePolicy>

WaveDisplay::WaveDisplay(QWidget *parent, int id) : SoundDisplay(parent)
{
    soundType = WAVE_SOUND_TYPE;
    int MAX_FREQ = 20000;
    int MIN_FREQ = 20;
    // initializing data attributes
    waveFrequency = 20;
    amplitude = 1.00;
    inputId = id;
    waveType = Wave_Sin;
    // Creating subwidgets
    frequencySlider = new QSlider(Qt::Horizontal,this);

    frequencySpinBox = new QSpinBox(this);
    frequencyLabel = new QLabel(this);
    removeInputButton = new QPushButton("Remove Input",this);
    generateButton = new QPushButton("Generate Wave",this);
    amplitudeLabel = new QLabel(this);
    amplitudeSlider = new QSlider(Qt::Horizontal,this);
    amplitudeSpinBox = new QDoubleSpinBox (this);
    //frequencyLayout = new QVBoxLayout(this);
    // setting up frequency slider
    frequencySlider->setValue(waveFrequency);
    frequencySlider->setMinimum(MIN_FREQ);
    frequencySlider->setMaximum(MAX_FREQ);
    frequencySlider->setSingleStep(100);
    //Label inits
    frequencySpinBox->setValue(waveFrequency);
    frequencySpinBox->setMinimum(MIN_FREQ);
    frequencySpinBox->setMaximum(MAX_FREQ);
    frequencySpinBox->setSuffix(" Hz");

    amplitudeSpinBox->setMinimum(0);
    amplitudeSpinBox->setMaximum(2);
    amplitudeSpinBox->setSingleStep(0.1);
    amplitudeSpinBox->setValue(amplitude);
    amplitudeSlider->setMinimum(0);
    amplitudeSlider->setMaximum(100);
    amplitudeSlider->setSingleStep(1);
    amplitudeSlider->setValue(amplitude*100);
    amplitudeLabel->setText(QString::fromStdString("Amplitude"));
    amplitudeLabel->setAlignment(Qt::AlignCenter);
    //frequencyLabel->setValue(QString::number(waveFrequency) + "Hz");
    frequencyLabel->setText("Frequency");
    frequencyLabel->setAlignment(Qt::AlignCenter);

    // connecting signals
    connect(frequencySlider,SIGNAL(valueChanged(int)),this,SLOT(frequencySliderChange(int)));
    connect(playButton,SIGNAL(clicked()),this,SLOT(onPlayButtonClicked()));
    connect(frequencySpinBox,SIGNAL(valueChanged(int)),this,SLOT(onSpinBoxChanged(int)));
    connect(removeInputButton,SIGNAL(clicked()),this,SLOT(removeInputButtonPushed()));
    connect(generateButton,SIGNAL(clicked()),this,SLOT(generateButtonPushed()));
    connect(amplitudeSlider,SIGNAL(valueChanged(int)),this,SLOT(amplitudeSliderChange(int)));
    connect(amplitudeSpinBox,SIGNAL(valueChanged(double)),this,SLOT(amplitudeSpinBoxChange(double)));
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

    //Setup the button layouy
    buttonLayout->addWidget(playButton,0,0,Qt::AlignCenter);
    buttonLayout->addWidget(waveTypeSelector,0,1,Qt::AlignCenter);
    buttonLayout->addWidget(stopButton,1,0,Qt::AlignCenter);
    buttonLayout->addWidget(toggleEffectPanelButton,1,1,Qt::AlignCenter);
    buttonLayout->addWidget(removeInputButton,2,0,Qt::AlignCenter);
    buttonLayout->addWidget(generateButton,2,1,Qt::AlignCenter);
    buttonLayout->addWidget(frequencyLabel,3,0, 1, 2, Qt::AlignCenter);
    buttonLayout->addWidget(frequencySlider,4,1,Qt::AlignCenter);
    buttonLayout->addWidget(frequencySpinBox,4,0,Qt::AlignCenter);
    buttonLayout->addWidget(amplitudeLabel,5,0, 1, 2, Qt::AlignCenter);
    buttonLayout->addWidget(amplitudeSpinBox,6,0,Qt::AlignCenter);
    buttonLayout->addWidget(amplitudeSlider,6,1,Qt::AlignCenter);
    buttonLayout->addWidget(volumeLabel,7,0,Qt::AlignCenter);
    buttonLayout->addWidget(volumeSlider,7,1,Qt::AlignCenter);


    //Setup Sine wave
    QString file = QDir::currentPath() + "/audio_files/gen_sine.wav";

    // set the file path name with its id
    wave.setFilePath(file);
    //changes frequency according to what is in the slider
    wave.setFrequency(waveFrequency);

    last_generate_time_ms = QDateTime::currentMSecsSinceEpoch();
    wave.generateSine();

    // set parent path to file as this current file
    this->changeFile(wave.getFilePath());
}

void WaveDisplay::frequencySliderChange(int value)
{
    //changes frequency according to what is in the slider
    if(frequencySpinBox->value() != value) {
        frequencySpinBox->setValue(value);
    }
}

void WaveDisplay::waveTypeIndexChanged(int index)
{
    wave.setWaveType((WaveType) index);
    waveType = (WaveType)index;
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
    wave.setFrequency(waveFrequency);
    wave.setAmplitude(amplitude);
    if(QDateTime::currentMSecsSinceEpoch() >= last_generate_time_ms + GENERATE_LIMIT_MS) {
        std::cout << "generating in file: " << wave.getFilePath().toStdString() << std::endl;
        drawWaveFromFile("");
        wave.generateSine();
        copyFileToEffectFile();
        drawWaveFromFile(this->selectedFile);
        emit waveGenerated(this);
        last_generate_time_ms = QDateTime::currentMSecsSinceEpoch();
    }
}

void WaveDisplay::amplitudeSliderChange(int value)
{
    double convAmp = ((double)value)/100.0;
    amplitude = convAmp;
    if(amplitudeSpinBox->value() != convAmp) {
        amplitudeSpinBox->setValue(convAmp);
    }
}

void WaveDisplay::amplitudeSpinBoxChange(double value)
{
    amplitudeSlider->setValue(round(100 * value));
}

