#include "tutorialcontroller.h"

TutorialController::TutorialController(QWidget *parent) : QWidget(parent)
{
    mainTutorialLayout = new QVBoxLayout(this);
    inputScrollView = new InputScrollView(this);
    tutorialPanel = new TutorialPanel(this,1);

    mainTutorialLayout->addWidget(tutorialPanel,1);
    mainTutorialLayout->addWidget(inputScrollView,6);
    this->setLayout(mainTutorialLayout);

    loadTutorial1_1();
    // set up to emit signal when all boxes are ticked
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
    connect(inputScrollView->addSineWaveButton,&QPushButton::clicked,[this](){objectiveComplete(0);});

}

void TutorialController::loadTutorial1_2()
{

}

void TutorialController::objectiveComplete(int boxIndex)
{
    tutorialPanel->checkboxes[boxIndex]->setCheckState(Qt::Checked);
    bool objectivesComplete = this->tutorialPanel->getObjectiveStatus();
    std::cout << "Objectives  complete: " << objectivesComplete << std::endl;
}
