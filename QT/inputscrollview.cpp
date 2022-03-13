#include "inputscrollview.h"

InputScrollView::InputScrollView(QWidget *parent) : QWidget(parent)
{
    //Declare children
    nextInputId = 1;
    addRecordedInputButton = new QPushButton("Add Input",this);
    addSineWaveButton = new QPushButton("Add Wave",this);
    scrollArea = new QScrollArea(this);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollAreaInputContainer = new QWidget(this);
    output = new OutputSoundDisplay(&this->inputs, this);
    //Connections
    connect(addRecordedInputButton,&QPushButton::clicked,[this](){ addInput(InputScrollView::SoundInputType::recordedSound);});
    connect(addSineWaveButton,&QPushButton::clicked,[this](){ addInput(InputScrollView::SoundInputType::sineWave);});


    //Layout Declarations
    //TODO: do not do all parents are this?
    topLayout = new QVBoxLayout(this);
    scrollLayout = new QVBoxLayout(this);
    inputButtonLayout = new QHBoxLayout(this);
    inputSubScrollLayout = new QVBoxLayout(scrollAreaInputContainer);
    outputLayout = new QHBoxLayout(this);
    //Layout and Widget position setup
    inputButtonLayout->addWidget(addRecordedInputButton);
    inputButtonLayout->addWidget(addSineWaveButton);
    outputLayout->addWidget(output);

    scrollLayout->addWidget(scrollArea);
    topLayout->addLayout(scrollLayout,5);
    topLayout->addLayout(inputButtonLayout,1);
    topLayout->addLayout(outputLayout,2);
    setLayout(topLayout);
    // Creating beginning area
    auto tempSineWaveDisplay = new WaveDisplay(this,nextInputId);
    connect(tempSineWaveDisplay->timeDomain, SIGNAL(plotStarted()), this, SLOT(updateOutput()));
    nextInputId++;
    auto tempRecordedSoundDisplay = new RecordedSoundDisplay(this,nextInputId);
    connect(tempRecordedSoundDisplay->timeDomain, SIGNAL(plotStarted()), this, SLOT(updateOutput()));
    nextInputId++;
    inputs.append(tempRecordedSoundDisplay);
    inputs.append(tempSineWaveDisplay);
    for(int i = 0;i < inputs.size();i++)
    {
        inputSubScrollLayout->addWidget(inputs[i]);
    }
    scrollAreaInputContainer->setLayout(inputSubScrollLayout);
    scrollArea->setWidget(scrollAreaInputContainer);
    scrollArea->setWidgetResizable(true);
    updateScrollArea();

    output->generateOutput();
}

InputScrollView::~InputScrollView()
{
    for(int i = 0; i < inputs.size(); i++) {
        delete inputs[i];
        inputs[i] = nullptr;
    }
    delete inputButtonLayout;
    delete scrollLayout;
    delete topLayout;
    delete scrollArea;
    delete addRecordedInputButton;
    delete addSineWaveButton;
}

void InputScrollView::updateScrollArea()
{
    //Loop adds missing inputs
    for(int i = 0;i < inputs.size();i++)
    {
        int index = inputSubScrollLayout->indexOf(inputs[i]);
        if(!(index  >= 0))
        {
            inputSubScrollLayout->addWidget(inputs[i]);
        }
    }

    // This loop deletes inputs that are no longer valid
    for(int i = 0;i < inputSubScrollLayout->count();i++)
    {
        //TODO: change this check to check for visibility
        // as that is what we use
        auto *widget = inputSubScrollLayout->itemAt(i)->widget();
        auto widgetExists = inputs.contains(widget);
        if(widgetExists == false)
        {
            inputSubScrollLayout->removeWidget(widget);
        }
    }
}

void InputScrollView::addInput(SoundInputType inputType)
{
    fprintf(stderr,"adding input");
    //create input and add it at the end
    if(inputType == SoundInputType::recordedSound)
    {
        RecordedSoundDisplay* toInsert = new RecordedSoundDisplay(this,nextInputId);
        //toInsert->inputId = nextInputId;

        connect(toInsert->timeDomain, SIGNAL(plotStarted()), this, SLOT(updateOutput()));

        nextInputId++;
        inputs.append(toInsert);

        //TODO: remove this print statement
        fprintf(stderr,"Added new RecordedSoundDisplay");
    }
    else if(inputType == SoundInputType::sineWave)
    {
        WaveDisplay* toInsert = new WaveDisplay(this,nextInputId);
        //toInsert->inputId = nextInputId;

        connect(toInsert->timeDomain, SIGNAL(plotStarted()), this, SLOT(updateOutput()));
//        connect(toInsert->timeDomain->decoder, SIGNAL(QAudioDecoder::finished()), this, SLOT(updateOutput()));
//        connect(toInsert->timeDomain->decoder,&QAudioDecoder::finished,[this](){updateOutput();});
        nextInputId++;
        inputs.append(toInsert);

        //TODO: remove this print statement
        fprintf(stderr,"Added new SineWaveDisplay");
    }
    else
    {
        return;
        //no-op, should never be called
    }

    updateScrollArea();
    // add new input to scrollarea
    fprintf(stderr,"Current number of Inputs: %lld",inputs.size());
}

void InputScrollView::removeInputByIndex(int index)
{

}

void InputScrollView::removeInput(SoundDisplay* input)
{

}

void InputScrollView::updateOutput()
{
    std::cout << "InputScrollView::updateOutput()\n";
    // up dates the output sound display
    this->output->generateOutput();
}

void InputScrollView::createOutputFile()
{
    //creates an output file so the output can read it
}

