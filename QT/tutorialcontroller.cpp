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
                        && wavePointer->amplitude == 100)
                {
                  objectives[0] = true;
                }
                if(wavePointer->waveFrequency == 300 && wavePointer->wave.gen_wave.getType() == WaveType::Wave_Sin \
                       && wavePointer->amplitude == 33)
                {
                  objectives[1] = true;
                }
                if(wavePointer->waveFrequency == 500 && wavePointer->wave.gen_wave.getType() == WaveType::Wave_Sin \
                        && wavePointer->amplitude == 20)
                {
                  objectives[2] = true;
                }
                if(wavePointer->waveFrequency == 700 && wavePointer->wave.gen_wave.getType() == WaveType::Wave_Sin \
                        && wavePointer->amplitude == 14)
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
    for(int i =0;i<objectives.size();i++)
    {
        objectiveChecked(i,objectives[i]);
    }
}

// Loads the very opening part of the first tutorial
void TutorialController::loadTutorial1_1()
{
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
    QStringList objectives = { "Step 3"};
    QString instructions = "";
    tutorialPanel->updatePanel(objectives,instructions);
}

void TutorialController::loadTutorial1_4()
{
    QStringList objectives = { "Step 4"};
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
