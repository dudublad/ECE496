#include "tutorialcontroller.h"

TutorialController::TutorialController(QWidget *parent) : QWidget(parent)
{
    stepCount = 0;
    mainTutorialLayout = new QVBoxLayout(this);
    inputScrollView = new InputScrollView(this);
    tutorialPanel = new TutorialPanel(this,1);
    tutorialOneButton = new QPushButton("Tutorial One",this);
    tutorialTwoButton = new QPushButton("Tutorial Two",this);
    sandboxButton = new QPushButton("SandBox",this);

    connect(sandboxButton,&QPushButton::clicked,[this](){ tutorialSelection(0);});
    connect(tutorialOneButton,&QPushButton::clicked,[this](){ tutorialSelection(1);});
    connect(tutorialTwoButton,&QPushButton::clicked,[this](){ tutorialSelection(2);});

    connect(inputScrollView,&InputScrollView::checkTutorialSignal,this,&TutorialController::checkConditions);
    connect(inputScrollView,&InputScrollView::filterAddedSignal,this,&TutorialController::checkConditions);
    connect(inputScrollView,&InputScrollView::playPressedSignal,this,&TutorialController::checkConditions);
    connect(tutorialPanel->submitObjectivesButton,SIGNAL(clicked()),this,SLOT(moveToNextStep()));
    mainTutorialLayout->addWidget(tutorialPanel,1);
    mainTutorialLayout->addWidget(inputScrollView,6);
    this->setLayout(mainTutorialLayout);

    this->tutorialPanel->objectivesLayout->addWidget(tutorialOneButton);
    this->tutorialPanel->objectivesLayout->addWidget(tutorialTwoButton);
    this->tutorialPanel->objectivesLayout->addWidget(sandboxButton);
    this->tutorialPanel->submitObjectivesButton->setVisible(false);
    //loadTutorial1_1();
    // set up to emit signal when all boxes are ticked
}

void TutorialController::tutorialSelection(int tutorialIndex)
{
    this->tutorialPanel->objectivesLayout->removeWidget(tutorialOneButton);
    this->tutorialPanel->objectivesLayout->removeWidget(tutorialTwoButton);
    this->tutorialPanel->objectivesLayout->removeWidget(sandboxButton);
    sandboxButton->setVisible(false);
    tutorialOneButton->setVisible(false);
    tutorialTwoButton->setVisible(false);
//    delete sandboxButton;
//    delete tutorialOneButton;
//    delete tutorialTwoButton;

   switch(tutorialIndex) {

   case 0:
        // Unload the tutorial section this is sandbox mode
       //Straight up no op probably
       break;
   case 1:
        this->tutorialPanel->submitObjectivesButton->setVisible(true);
        loadTutorial1_1();
        // Load Tutorial 1
        break;
   case 2:
       this->tutorialPanel->submitObjectivesButton->setVisible(true);
       loadTutorial2_1();
       //
       break;
   default:
       //No op
       break;

   }
}

void TutorialController::moveToNextStep()
{
   bool stepCompleted = true;
   for(QCheckBox* checkBox : tutorialPanel->checkboxes)
   {
        if(checkBox->isChecked() == false)
        {
            stepCompleted = false;
            break;
        }
   }
   if(stepCompleted)
   {
       stepCount++;
       switch(stepCount) {

        case 1:
           loadTutorial1_1();
           break;
        case 2:
          loadTutorial1_2();
          break;
        case 3:
          loadTutorial1_3();
          break;
        case 4:
          loadTutorial1_4();
          break;
        case 5:
          loadTutorial1_5();
          break;
        case 6:
           loadEndTutorial1();
        case TUTORIAL_TWO_START:
           loadTutorial2_1();
        default:
          break;
       }
   }
}

void TutorialController::checkConditions(SoundDisplay* sourceDisplay,int signalSourceType)
{
    // If sourceDisplay is not null then the source is from a filter
    if(sourceDisplay != NULL && signalSourceType != 0)
    {
        std::cout << "signal received" << std::endl;
    }
    std::cout << "checking conditions" << std::endl;
    auto inputs = inputScrollView->inputs;
    QVector<bool> objectives = {};
    if(stepCount == 1){
      /* Tutorial 1_1 Objectives
       * // Create square wave 100Hz
       *
       */
        objectives.clear();
        objectives = {false};
        for(SoundDisplay* input : inputs)
        {
            if(input->soundType == input->WAVE_SOUND_TYPE)
            {
              WaveDisplay* wavePointer = (WaveDisplay*)(input);
              if(wavePointer->waveFrequency == 100 && wavePointer->wave.gen_wave.getType() == WaveType::Wave_Square)
              {
                objectives[0] = true;
              }
            }
        }
    }
    else if(stepCount == 2){
        /* Tutorial 1_2 Objectives
         * 0: "Create Sine wave Frequency: 100Hz, Amplitude: 1"
         * 1: "Create Sine wave Frequency: 300Hz, Amplitude: 0.33"
         * 2: "Create Sine wave Frequency: 500Hz, Amplitude: 0.20"
         * 3: "Create Sine wave Frequency: 700Hz, Amplitude: 0.14"
         */
        objectives.clear();
        objectives = {false,false,false,false};
        for(SoundDisplay* input : inputs)
        {
            if(input->soundType == input->WAVE_SOUND_TYPE)
            {
                WaveDisplay* wavePointer = (WaveDisplay*)(input);
                if(wavePointer->waveFrequency == 100 && wavePointer->wave.gen_wave.getType() == WaveType::Wave_Sin \
                        && round(wavePointer->amplitude*100) == 100)
                {
                  objectives[0] = true;
                }
                if(wavePointer->waveFrequency == 300 && wavePointer->wave.gen_wave.getType() == WaveType::Wave_Sin \
                       && round(wavePointer->amplitude*100) == 33)
                {
                  objectives[1] = true;
                }
                if(wavePointer->waveFrequency == 500 && wavePointer->wave.gen_wave.getType() == WaveType::Wave_Sin \
                        && round(wavePointer->amplitude*100) == 20)
                {
                  objectives[2] = true;
                }
                if(wavePointer->waveFrequency == 700 && wavePointer->wave.gen_wave.getType() == WaveType::Wave_Sin \
                        && round(wavePointer->amplitude*100) == 14)
                {
                  objectives[3] = true;
                }
            }
        }
    }
    else if(stepCount == 3){
        /* Tutorial 1_3 Objectives
         *
         *
         */
    }
    else if(stepCount == 4){
        /* Tutorial 1_4 Objectives
         *
         *
         */
    }
    else if(stepCount ==5){
        /* Tutorial 1_5 Objectives
         *
         *
         */
    }
    else if(stepCount == 6){
        /* Tutorial 1_6 Objectives
         *
         *
         */
    }
    else if(stepCount == TUTORIAL_TWO_START)
    {
        /* Tutorial 2_1 Objectives
         *
         */
    }
    else if(stepCount == TUTORIAL_TWO_START + 1)
    {
        /* Tutorial 2_2 Objectives
         *
         */
    }
    else if(stepCount == TUTORIAL_TWO_START + 2)
    {
        /* Tutorial 2_3 Objectives
         *
         */

    }
    else if(stepCount == TUTORIAL_TWO_START + 3)
    {
        /* Tutorial 2_4 Objectives
         *
         */

    }

    //checks objectives
    for(int i =0;i<objectives.size();i++)
    {
        objectiveChecked(i,objectives[i]);
    }
}

// Loads the very opening part of the first tutorial
void TutorialController::loadTutorial1_1()
{
    stepCount = 1;
    QStringList objectives = { "Make a Square Wave, Frequency: 100Hz"};
    QString instructions = "Welcome to the first tutorial: Superposition, Frequency and Time!\n \
Lets start off by getting familiar with the display, Create a new input or use the existing ones to \
create a square wave with a frequency of 100Hz";
    //changes the objective texts
    tutorialPanel->updatePanel(objectives,instructions);
    /*
     * Note the checkboxes will be added in the same order
     * they were supplied
     *
     */
    //connects the relevant signals to the buttons
    //connect(timeDomain->decoder,&QAudioDecoder::finished,[this](){frequencyDisplay->setCoefficients(fft(timeDomain->samples));});
    //connect(inputScrollView->addSineWaveButton,&QPushButton::clicked,[this](){objectiveComplete(0);});

}


void TutorialController::loadTutorial1_2()
{
    QStringList objectives = { "Create Sine wave Frequency: 100Hz, Amplitude: 1",
                             "Create Sine wave Frequency: 300Hz, Amplitude: 0.33",
                             "Create Sine wave Frequency: 500Hz, Amplitude: 0.20",
                             "Create Sine wave Frequency: 700Hz, Amplitude: 0.14"};
    QString instructions = "Create Sine Waves: \n\
Create 4 new inputs. All of these inputs will be sin waves with 0 phase offset.\
The first should have a frequency of 100Hz and an amplitude of 1. \
Observe the frequency domain, and note that the fourier transform of a sin wave is a spike, \
or delta at the frequency 100Hz.\nNow make a separate sin wave with a frequency of 300Hz and an amplitude of ⅓.\
Do this again for 500Hz with amplitude of ⅕, and 700Hz with amplitude of 1/7. \
Note each time that the frequency domain is a spike at the respective frequency values\
\nOnce you’ve made your signals, add each sin wave together one by one, observing the time domain output each time. \
You should see that as more signals are added, the wave starts to look more and more like a square wave\
\nAlso note that the frequency domain of the sum of sins is the same as the sum of the frequency domain plots for each sin.\
This is because the fourier transform is a linear operation";
    tutorialPanel->updatePanel(objectives,instructions);
}

void TutorialController::loadTutorial1_3()
{
    QStringList objectives = {};
    QString instructions = "Compare the frequency domain for the square wave and the superposition of sin waves. \
Note that they are similar, with spikes at 100Hz, 300Hz, 500Hz, and 700Hz for both signals,\
and more smaller spikes at higher frequencies for the square wave";
    tutorialPanel->updatePanel(objectives,instructions);
}

void TutorialController::loadTutorial1_4()
{
    QStringList objectives = {"Step 4"};
    QString instructions = "";
    tutorialPanel->updatePanel(objectives,instructions);
}

void TutorialController::loadTutorial1_5()
{

}

void TutorialController::loadTutorial1_6()
{

}

void TutorialController::loadEndTutorial1()
{

}

void TutorialController::loadTutorial2_1()
{
    stepCount = TUTORIAL_TWO_START;
    // First step of tutorial 2
}

void TutorialController::loadTutorial2_2()
{
    // First step of tutorial 2
}

void TutorialController::loadTutorial2_3()
{
    // First step of tutorial 2
}

void TutorialController::loadTutorial2_4()
{
    // First step of tutorial 2
}

void TutorialController::objectiveChecked(int boxIndex,bool completed)
{
    if(completed)
    {
        tutorialPanel->checkboxes[boxIndex]->setCheckState(Qt::Checked);
    }
    else{
        tutorialPanel->checkboxes[boxIndex]->setCheckState(Qt::Unchecked);
    }
    //bool objectivesComplete = this->tutorialPanel->getObjectiveStatus();
    //std::cout << "Objectives  complete: " << objectivesComplete << std::endl;
}
