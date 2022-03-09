#include "sounddisplay.h"

SoundDisplay::SoundDisplay(QWidget *parent)
    : QWidget(parent)
{
    //constructor
    cursor = 0.0;
    volume = 50;
    selectedFile = "";
    //create everything?
    stopButton = new QPushButton("Stop",this);
    playButton = new QPushButton("Play",this);
    toggleEffectPanelButton = new QPushButton("Toggle Effects Panel",this);
    timeDomain = new TimeDomain(this);
    frequencyDisplay = new FrequencyDomainDisplay(this);
    effectPanel = new EffectPanel(this);
    idLabel = new QLabel(this);
    volumeSlider = new QSlider(Qt::Horizontal,this);
    volumeLabel = new QLabel(this);

    // Volume Slider config
    volumeSlider->setMaximum(100);
    volumeSlider->setMinimum(0);
    volumeSlider->setTickInterval(1);
    volumeSlider->setValue(volume);

    volumeLabel->setText(QString::fromStdString("Volume: " + std::to_string(volume)));
    //connect(button,&QPushButton::clicked,insert);

    // Connecting to slots
    connect(playButton,SIGNAL(clicked()),this,SLOT(onPlayButtonClicked()));
    connect(stopButton,SIGNAL(clicked()),this,SLOT(stopFile()));
    connect(toggleEffectPanelButton,SIGNAL(clicked()),this, SLOT(toggleEffectPanel()));
    connect(volumeSlider,SIGNAL(valueChanged(int)),this,SLOT(volumeChanged(int)));
    connect(timeDomain->decoder,&QAudioDecoder::finished,[this](){frequencyDisplay->setCoefficients(fft(timeDomain->samples));});
    //connect(addSineWaveButton,&QPushButton::clicked,[this](){ addInput(InputScrollView::SoundInputType::sineWave);});


    /*
     * Layout adding and declarations
     */
    mainLayout = new QHBoxLayout(this);
    //ATTENTION: this could be error prone
    domainLayout = new QHBoxLayout(this);
    buttonLayout = new QGridLayout(this);
    //effectLayout = new QGridLayout(this);
    mainLayout->addLayout(buttonLayout,1);
    mainLayout->addLayout(domainLayout,4);
    // To change sizes of timeDomain or freq Domain,
    // change the numbers, they're ratios within the layout
    //domainLayout->addWidget(buttonHolder,1);
    domainLayout->addWidget(timeDomain,4);
    domainLayout->addWidget(frequencyDisplay,2);
    domainLayout->addWidget(effectPanel,2);
    //mainLayout->addLayout(effectLayout);
    //this->setStyleSheet("border: 1px solid blue");
    setLayout(mainLayout);
}

SoundDisplay::~SoundDisplay()
{
    delete stopButton;
    delete playButton;
    delete timeDomain;
    delete frequencyDisplay;
    delete effectPanel;
    delete mainLayout;
    //delete domainLayout;
    //delete buttonLayout;
}

void SoundDisplay::changeFile(QString path)
{
    selectedFile = path;
    this->soundFile.openFile(path);
}


void SoundDisplay::onPlayButtonClicked()
{

    // Get current cursor position when it exists
    // If this following section is not loading the sound file
    // Ensure that you have the right working directory set under
    // Projects->Run->Working Directory
    drawWaveFromFile(selectedFile);
    if (this->soundFile.dac.isStreamRunning()){
       this->soundFile.setStreamTime(0);
    }
    this->soundFile.startStream();
    //std::cout << "Play Button Finished" << std::endl;
}

void SoundDisplay::stopFile()
{
    // stops the file and the cursor
    this->soundFile.pauseStream();
}

void SoundDisplay::drawWaveFromFile(QString file)
{
    timeDomain->setSource(file);
}

void SoundDisplay::toggleEffectPanel()
{
    if (effectPanel->isVisible() == false)
    {
        effectPanel->setVisible(true);
    }
    else
    {
        effectPanel->setVisible(false);
    }
}

void SoundDisplay::removeInputButtonPushed()
{
    this->setVisible(false);
    // emit signal to inputScrollView to remove
}

void SoundDisplay::volumeChanged(int changedVolume)
{
    volume = changedVolume;
    volumeLabel->setText(QString::fromStdString("Volume: " + std::to_string(volume)));
    double scaledVolume = (double)(volume)/100;
    this->soundFile.changeVolume(scaledVolume);
    // Call other function which actually changes volume
    //change the volume
}


