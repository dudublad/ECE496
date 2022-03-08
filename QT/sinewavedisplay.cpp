#include "sinewavedisplay.h"

SineWaveDisplay::SineWaveDisplay(QWidget *parent, int id) : SoundDisplay(parent)
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
    connect(frequencySlider,SIGNAL(sliderReleased()),this,SLOT(frequencySliderStop()));
    connect(frequencyLabel,SIGNAL(valueChanged(double)),this,SLOT(onSpinBoxChanged(double)));
    connect(removeInputButton,SIGNAL(clicked()),this,SLOT(removeInputButtonPushed()));
    // Adding the frequency controls to the layout


    //frequencyLayout->addWidget(titleLabel);
    buttonLayout->addWidget(playButton,0,0,Qt::AlignCenter);
    buttonLayout->addWidget(stopButton,1,0,Qt::AlignCenter);
    buttonLayout->addWidget(toggleEffectPanelButton,2,0,Qt::AlignCenter);
    buttonLayout->addWidget(titleLabel,0,1,Qt::AlignCenter);
    buttonLayout->addWidget(frequencySlider,1,1,Qt::AlignCenter);
    buttonLayout->addWidget(frequencyLabel,2,1,Qt::AlignCenter);
    buttonLayout->addWidget(removeInputButton,3,0,Qt::AlignCenter);
    //mainLayout->addLayout(frequencyLayout);
}

void SineWaveDisplay::plotAndPlay()
{
    QString currentDirectory = QDir::currentPath();
    QString file = currentDirectory + "/audio_files/dgen_sine.wav";
    //changes frequency according to what is in the slider
    frequencyLabel->setValue(waveFrequency);
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
    frequencyLabel->setValue(value);
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

void SineWaveDisplay::onSpinBoxChanged(double value)
{
    int convertedValue = (int)value;
    fprintf(stderr,"ring ring calling \n");
    waveFrequency = convertedValue;
    frequencySlider->setValue(convertedValue);
    plotAndPlay();
}
