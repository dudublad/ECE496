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
    //connect(playButton,SIGNAL(clicked()),this,SLOT(onPlayButtonClicked()));
    connect(stopButton,SIGNAL(clicked()),this,SLOT(stopFile()));
    connect(toggleEffectPanelButton,SIGNAL(clicked()),this, SLOT(toggleEffectPanel()));
    connect(volumeSlider,SIGNAL(valueChanged(int)),this,SLOT(volumeChanged(int)));
    connect(timeDomain->decoder,&QAudioDecoder::finished,[this](){frequencyDisplay->setCoefficients(fft(timeDomain->samples));});
    //connect(addSineWaveButton,&QPushButton::clicked,[this](){ addInput(InputScrollView::SoundInputType::sineWave);});
    //connect(effectPanel->effectD)

    connect(this->effectPanel, SIGNAL(sendFilter(audioFilter)), this, SLOT(generateEffect(audioFilter)));

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
    this->fileName = path;
    setEffectFile(path);
    copyFileToEffectFile();

    // always modify the effect file
    this->openFile();
}

void SoundDisplay::copyFileToEffectFile(){
    this->soundFile.closeFile();
    stk::FileWvOut output;
    stk::FileWvIn input;
    std::cout << this->fileName.toStdString() << std::endl;
    input.openFile(this->fileName.toStdString());

    output.openFile(this->selectedFile.toStdString(), 1, stk::FileWrite::FILE_WAV, stk::Stk::STK_SINT16);

    while(!input.isFinished()){
        output.tick(input.tick());
    }

    output.closeFile();
    input.closeFile();
}

void SoundDisplay::openFile(){
    this->soundFile.openFile(this->selectedFile);
    this->drawWaveFromFile(this->selectedFile);
}

void SoundDisplay::setEffectFile(QString path){

    // get current path and slap on audiofile for our directory to modify the signal
    QString currentPath = QDir::currentPath() + "/audio_files/";
    QStringList slashSplit = path.split(QLatin1Char('/'));

    // append on the file name of the path which is the last one of the slash
    currentPath = currentPath + slashSplit[slashSplit.length() - 1];

    // obtain the current path and split with a dot to append _effects
    QStringList dotSplit = currentPath.split(QLatin1Char('.'));
    this->selectedFile = "";

    for (int i = 0; i < dotSplit.length() - 1; i++){
        this->selectedFile = this->selectedFile + dotSplit[i];
    }
    this->selectedFile = this->selectedFile + "_effects." + dotSplit[dotSplit.length() - 1];
}

void SoundDisplay::onPlayButtonClicked()
{

    // Get current cursor position when it exists
    // If this following section is not loading the sound file
    // Ensure that you have the right working directory set under
    // Projects->Run->Working Directory
    drawWaveFromFile(selectedFile);
    this->soundFile.setStreamTime(0);
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
    timeDomain->yScaling = yScaling;
    timeDomain->yMax = yMax;
    timeDomain->yMin = yMin;
    timeDomain->setSource(file);
}

void SoundDisplay::toggleEffectPanel()
{
    effectPanel->setVisible(!effectPanel->isVisible());
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
    float scaledVolume = volume/100.0;
    this->soundFile.changeVolume(scaledVolume);
    // Call other function which actually changes volume
    //change the volume
}

void SoundDisplay::generateEffect(audioFilter filter){
    filter.openFile(this->selectedFile);
    filter.generateFile();
    drawWaveFromFile(this->selectedFile);
}
