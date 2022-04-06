#include "tutorialcontroller.h"

TutorialController::TutorialController(QWidget *parent) : QWidget(parent)
{
    stepCount = 1;
    mainTutorialLayout = new QVBoxLayout(this);
    inputScrollView = new InputScrollView(this);
    tutorialPanel = new TutorialPanel(this,1);
    connect(inputScrollView,SIGNAL(checkTutorialSignal()),this,SLOT(checkConditions()));
    connect(tutorialPanel->submitObjectivesButton,SIGNAL(clicked()),this,SLOT(moveToNextStep()));
    mainTutorialLayout->addWidget(tutorialPanel,1);
    mainTutorialLayout->addWidget(inputScrollView,6);
    this->setLayout(mainTutorialLayout);

    loadTutorial1_1();
    // set up to emit signal when all boxes are ticked
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
        default:
          loadEndTutorial1();
       }
   }
}

void TutorialController::checkConditions()
{
    std::cout << "checking conditions" << std::endl;
    auto inputs = inputScrollView->inputs;
    if(stepCount == 1){
      /* Tutorial 1_1 Objectives
       * // Create square wave 100Hz
       *
       */
        bool objective1 = false;
        for(SoundDisplay* input : inputs)
        {
            if(input->soundType == input->WAVE_SOUND_TYPE)
            {
              WaveDisplay* wavePointer = (WaveDisplay*)(input);
              if(wavePointer->waveFrequency == 100 && wavePointer->wave.gen_wave.getType() == WaveType::Wave_Square)
              {
                objective1 = true;
              }
            }
        }
       objectiveChecked(0,objective1);
    }
    else if(stepCount == 2){
        /* Tutorial 1_2 Objectives
         *
         *
         */
        for(SoundDisplay* inputs : inputs)
        {

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
}

// Loads the very opening part of the first tutorial
void TutorialController::loadTutorial1_1()
{
    QStringList objectives = { "Add A Sine Wave"};
    //changes the objective texts
    tutorialPanel->updatePanel(objectives);
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
    QStringList objectives = { "Add A Sine Wave"};
    tutorialPanel->updatePanel(objectives);
}

void TutorialController::loadTutorial1_3()
{
    QStringList objectives = { "Step 2"};
    tutorialPanel->updatePanel(objectives);
}

void TutorialController::loadTutorial1_4()
{
    QStringList objectives = { "Step 3"};
    tutorialPanel->updatePanel(objectives);
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
