#include "inputscrollview.h"

InputScrollView::InputScrollView(QWidget *parent) : QWidget(parent)
{
    //Declare children
    addRecordedInputButton = new QPushButton("Add Input",this);
    addSineWaveButton = new QPushButton("Add Sine Wave",this);
    scrollArea = new QScrollArea(this);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollAreaInputContainer = new QWidget(this);

    //Connections
    connect(addRecordedInputButton,&QPushButton::clicked,[this](){ addInput(InputScrollView::SoundInputType::recordedSound);});
    connect(addSineWaveButton,&QPushButton::clicked,[this](){ addInput(InputScrollView::SoundInputType::sineWave);});


    //Layout Declarations
    //TODO: do not do all parents are this?
    topLayout = new QVBoxLayout(this);
    scrollLayout = new QVBoxLayout(this);
    inputButtonLayout = new QHBoxLayout(this);
    inputSubScrollLayout = new QVBoxLayout(this);
    //Layout and Widget position setup
    inputButtonLayout->addWidget(addRecordedInputButton);
    inputButtonLayout->addWidget(addSineWaveButton);

    scrollLayout->addWidget(scrollArea);
    topLayout->addLayout(scrollLayout,4);
    topLayout->addLayout(inputButtonLayout,1);

    // Creating beginning area
    auto tempSineWaveDisplay = new SineWaveDisplay(this);
    auto tempRecordedSoundDisplay = new RecordedSoundDisplay(this);

    inputs.append(tempRecordedSoundDisplay);
    inputs.append(tempSineWaveDisplay);
    for(int i = 0;i < inputs.size();i++)
    {
        inputSubScrollLayout->addWidget(inputs[i]);
    }
    scrollAreaInputContainer->setLayout(inputSubScrollLayout);
    scrollArea->setWidget(scrollAreaInputContainer);

    updateScrollArea();
}

InputScrollView::~InputScrollView()
{
    while(inputs.size() > 0)
    {
        //TODO: this also corrupts the heap
        const auto toErase = inputs.erase(inputs.begin());
        //delete toErase;
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
        RecordedSoundDisplay* toInsert = new RecordedSoundDisplay(this);
        inputs.append(toInsert);

        //TODO: remove this print statement
        fprintf(stderr,"Added new RecordedSoundDisplay");
    }
    else if(inputType == SoundInputType::sineWave)
    {
        SineWaveDisplay* toInsert = new SineWaveDisplay(this);
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
}

void InputScrollView::removeInputByIndex(int index)
{

}

void InputScrollView::removeInput(SoundDisplay* input)
{

}

void InputScrollView::createOutputFile()
{
    //creates an output file so the output can read it
}
