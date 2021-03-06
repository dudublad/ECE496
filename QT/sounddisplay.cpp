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

    addToOutput = true;
    addToOutputCheckBox = new QCheckBox("Add to Output", this);
    addToOutputCheckBox->setChecked(true);

    // Connecting to slots
    connect(stopButton,SIGNAL(clicked()),this,SLOT(stopFile()));
    connect(toggleEffectPanelButton,SIGNAL(clicked()),this, SLOT(toggleEffectPanel()));
    connect(volumeSlider,SIGNAL(valueChanged(int)),this,SLOT(volumeChanged(int)));
    connect(timeDomain->decoder,&QAudioDecoder::finished,[this](){frequencyDisplay->setCoefficients(fft(timeDomain->samples));});
    connect(this->effectPanel, SIGNAL(sendFilter(audioFilter)), this, SLOT(generateEffect(audioFilter)));
    connect(addToOutputCheckBox,SIGNAL(stateChanged(int)),this,SLOT(addToOutputStateChanged(int)));

    /*
     * Layout adding and declarations
     */
    mainLayout = new QHBoxLayout(this);
    //ATTENTION: this could be error prone
    domainLayout = new QHBoxLayout(this);
    buttonLayout = new QGridLayout(this);
    //effectLayout = new QGridLayout(this);
    mainLayout->addWidget(addToOutputCheckBox);
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
    //delete mainLayout;
    delete addToOutputCheckBox;
    //delete domainLayout;
    //delete buttonLayout;
}

void SoundDisplay::changeFile(QString path)
{
    this->fileName = path;
    std::cout << "CHANGING file to " << path.toStdString() << std::endl;
    setEffectFile(path);
    copyFileToEffectFile();

    // always modify the effect file
    this->openFile();
}

void SoundDisplay::copyFileToEffectFile(){
    stk::FileWvOut output;
    stk::FileWvIn input;
    std::cout << this->fileName.toStdString() << std::endl;
    input.openFile(this->fileName.toStdString(), false, false);
    if (input.getSize() != 0){
        output.openFile(this->selectedFile.toStdString(), 1, stk::FileWrite::FILE_WAV, stk::Stk::STK_SINT16);

        while(!input.isFinished()){
        output.tick(input.tick());
        }

        output.closeFile();
    }
    input.closeFile();
}

void SoundDisplay::openFile(){
    std::cout << "OPENING: " << this->selectedFile.toStdString() << std::endl;
    this->soundFile.openFile(this->selectedFile);
    this->drawWaveFromFile("");
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

    this->soundFile.openFile(this->selectedFile);
    this->soundFile.changeVolume(volume/100.0);
    this->soundFile.setStreamTime(0);
    this->soundFile.startStream();
    //std::cout << "Play Button Finished" << std::endl;
    emit playButtonPressed(this);
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
    emit inputRemoved(this);
    // emit signal to inputScrollView to remove
}

void SoundDisplay::volumeChanged(int changedVolume)
{
    volume = changedVolume;
    this->soundFile.changeVolume(volume/100.0);
    volumeLabel->setText(QString::fromStdString("Volume: " + std::to_string(volume)));
    // Call other function which actually changes volume
    //change the volume
}

void SoundDisplay::addToOutputStateChanged(int state)
{
    addToOutput = (state != 0);
    std::cout << "addToOutputStateChanged()" << std::endl;
    emit superpositionStateChanged();
    std::cout << "emitted superpositionStateChanged(()" << std::endl;
}

void SoundDisplay::generateEffect(audioFilter filter){
    drawWaveFromFile("");
    audioFilterData = filter;
    filter.generateFilter(this->selectedFile, this->fileName, yScaling);
    this->yMax = yScaling;
    this->yMin = -yScaling;
    drawWaveFromFile(this->selectedFile);
    std::cout << "effect generated" << std::endl;
    emit filterAdded(this);
}
