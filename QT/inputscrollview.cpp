#include "inputscrollview.h"

InputScrollView::InputScrollView(QWidget *parent) : QWidget(parent)
{
    //Declare children
    nextInputId = START_INPUT_ID;
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
    for(int i = 0;i < inputs.size();i++)
    {
        inputSubScrollLayout->addWidget(inputs[i]);
    }
    scrollAreaInputContainer->setLayout(inputSubScrollLayout);
    scrollArea->setWidget(scrollAreaInputContainer);
    scrollArea->setWidgetResizable(true);

    addInput(InputScrollView::SoundInputType::recordedSound);
    addInput(InputScrollView::SoundInputType::sineWave);
    output->generateOutput();

    last_new_wave_time_ms = 0;
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

    SoundDisplay* insertedInput = nullptr;
    if(inputType == SoundInputType::recordedSound)
    {
        RecordedSoundDisplay* toInsert = new RecordedSoundDisplay(this,nextInputId);
        //toInsert->inputId = nextInputId;

        inputs.append(toInsert);

        //TODO: remove this print statement
        fprintf(stderr,"Added new RecordedSoundDisplay");

        insertedInput = toInsert;
    }
    else if(inputType == SoundInputType::sineWave)
    {
        if(QDateTime::currentMSecsSinceEpoch() < last_new_wave_time_ms + NEW_WAVE_LIMIT_MS)
        {
            return;
        }
        WaveDisplay* toInsert = new WaveDisplay(this,nextInputId);
        //toInsert->inputId = nextInputId;

        inputs.append(toInsert);

        //TODO: remove this print statement
        fprintf(stderr,"Added new SineWaveDisplay");

        insertedInput = toInsert;
        last_new_wave_time_ms = QDateTime::currentMSecsSinceEpoch();
    }
    else
    {
        return;
        //no-op, should never be called
    }

    if(insertedInput != nullptr){
        connect(insertedInput->timeDomain, SIGNAL(plotStarted()), this, SLOT(updateOutput()));
        connect(insertedInput->removeInputButton,SIGNAL(clicked()),this,SLOT(inputRemoved()));
    }

    updateScrollArea();
    // add new input to scrollarea
    fprintf(stderr,"Current number of Inputs: %lld",inputs.size());

    nextInputId++;
}

void InputScrollView::removeInputByIndex(int index)
{

}

void InputScrollView::removeInput(SoundDisplay* input)
{

}

void InputScrollView::inputRemoved()
{
    std::cout << "InputScrollView::inputRemoved()\n";
    updateOutput();
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

