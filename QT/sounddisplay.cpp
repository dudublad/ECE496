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
    //effectPanel = new EffectPanel(this);

    //connect(button,&QPushButton::clicked,insert);
    connect(playButton,SIGNAL(clicked()),this,SLOT(onPlayButtonClicked()));
    connect(stopButton,SIGNAL(clicked()),this,SLOT(stopFile()));
    connect(toggleEffectPanelButton,SIGNAL(clicked()),this, SLOT(toggleEffectPanel()));
    /*
     * Layout adding and declarations
     */
    mainLayout = new QVBoxLayout(this);
    //ATTENTION: this could be error prone
    domainLayout = new QHBoxLayout(this);
    buttonLayout = new QHBoxLayout(this);
    effectLayout = new QGridLayout(this);
    mainLayout->addLayout(domainLayout);
    // To change sizes of timeDomain or freq Domain,
    // change the numbers, they're ratios within the layout
    domainLayout->addWidget(timeDomain,2);
    domainLayout->addWidget(frequencyDisplay,1);
    mainLayout->addLayout(buttonLayout);
    //mainLayout->addLayout(effectLayout);

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
    this->soundFile.closeStream();
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


