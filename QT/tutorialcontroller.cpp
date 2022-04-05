#include "tutorialcontroller.h"

TutorialController::TutorialController(QWidget *parent) : QWidget(parent)
{
    stepCount = 0;
    mainTutorialLayout = new QVBoxLayout(this);
    inputScrollView = new InputScrollView(this);
    tutorialPanel = new TutorialPanel(this,1);

    mainTutorialLayout->addWidget(tutorialPanel,1);
    mainTutorialLayout->addWidget(inputScrollView,6);
    this->setLayout(mainTutorialLayout);

    loadTutorial1_1();
    // set up to emit signal when all boxes are ticked
}

void TutorialController::checkConditions()
{
    auto inputs = inputScrollView->inputs;
    if(stepCount == 1){
      /* Tutorial 1_1 Objectives
       *
       *
       */
      for(int i = 0;i <inputs.size();i++)
      {

      }
    }
    else if(stepCount == 2){
        /* Tutorial 1_2 Objectives
         *
         *
         */
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
    stepCount++;
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
    connect(inputScrollView->addSineWaveButton,&QPushButton::clicked,[this](){objectiveComplete(0);});

}


void TutorialController::loadTutorial1_2()
{
    stepCount++;
}

void TutorialController::loadTutorial1_3()
{
    stepCount++;
}

void TutorialController::loadTutorial1_4()
{
    stepCount++;
}

void TutorialController::loadTutorial1_5()
{
    stepCount++;
}

void TutorialController::loadTutorial1_6()
{
    stepCount++;
}

void TutorialController::objectiveComplete(int boxIndex)
{
    tutorialPanel->checkboxes[boxIndex]->setCheckState(Qt::Checked);
    bool objectivesComplete = this->tutorialPanel->getObjectiveStatus();
    std::cout << "Objectives  complete: " << objectivesComplete << std::endl;
}
