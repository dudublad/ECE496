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
    timeDomain = new TimeDomain(this);
    frequencyDisplay = new FrequencyDomainDisplay(this);
    //connect(button,&QPushButton::clicked,insert);
    connect(playButton,SIGNAL(clicked()),this,SLOT(onPlayButtonClicked()));
    connect(stopButton,SIGNAL(clicked()),this,SLOT(stopFile()));
    /*
     * Layout adding and declarations
     */
    mainLayout = new QVBoxLayout(this);
    //ATTENTION: this could be error prone
    domainLayout = new QHBoxLayout(this);
    buttonLayout = new QHBoxLayout(this);
    mainLayout->addLayout(domainLayout);

    // To change sizes of timeDOmain or freq Domain,
    // change the numbers, they're ratios within the layout
    domainLayout->addWidget(timeDomain,2);
    domainLayout->addWidget(frequencyDisplay,1);
    mainLayout->addLayout(buttonLayout);
}

SoundDisplay::~SoundDisplay()
{
    //destructor, if we cant get the freeing to work
    // just straight up start leaking memory
}

void SoundDisplay::changeFile(QString path)
{
    selectedFile = path;
}


void SoundDisplay::onPlayButtonClicked()
{

    // Get current cursor position when it exists
    // If this following section is not loading the sound file
    // Ensure that you have the right working directory set under
    // Projects->Run->Working Directory
    drawWaveFromFile(selectedFile);
    //playFile(file);
    //std::cout << "Play Button Finished" << std::endl;
}

void SoundDisplay::playFile()
{
    //IMPLEMENT ME
    std::cout << "haha lol" << std::endl;
}

void SoundDisplay::stopFile()
{
    // stops the file and the cursor
}

void SoundDisplay::drawWaveFromFile(QString file)
{
    timeDomain->setSource(file);
}


