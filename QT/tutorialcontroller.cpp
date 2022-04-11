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
    returnToTutorialSelectionButton = new QPushButton("Return to Tutorial Selection Screen");


    connect(sandboxButton,&QPushButton::clicked,[this](){ tutorialSelection(0);});
    connect(tutorialOneButton,&QPushButton::clicked,[this](){ tutorialSelection(1);});
    connect(tutorialTwoButton,&QPushButton::clicked,[this](){ tutorialSelection(2);});
    connect(returnToTutorialSelectionButton,&QPushButton::clicked,[this](){loadTutorialPicker();});

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
    this->tutorialPanel->objectivesLayout->addWidget(returnToTutorialSelectionButton);
    this->returnToTutorialSelectionButton->setVisible(false);
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
    this->returnToTutorialSelectionButton->setVisible(false);
//    delete sandboxButton;
//    delete tutorialOneButton;
//    delete tutorialTwoButton;

   switch(tutorialIndex) {

   case 0:
       this->tutorialPanel->setVisible(false);
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
           loadTutorial1_6();
           break;
        case 7:
           loadTutorial1_End();
           break;
        case TUTORIAL_TWO_START:
           loadTutorial2_1();
           break;
        case TUTORIAL_TWO_START+1:
           loadTutorial2_2();
           break;
        case TUTORIAL_TWO_START+2:
          loadTutorial2_3();
          break;
        case TUTORIAL_TWO_START+3:
          loadTutorial2_4();
          break;
        case TUTORIAL_TWO_START+4:
          loadTutorial2_End();
          break;
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
        //objectives = {true,true,true,true};
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
         * None
         *
         */
    }
    else if(stepCount == 4){
        /* Tutorial 1_4 Objectives
         * Apply a lowpass filter with cutoff = 800Hz to your square wave
         *
         */
        objectives.clear();
        objectives = {false};
        if(signalSourceType == EFFECT_ADDED_TYPE && sourceDisplay != NULL)
        {
            if(sourceDisplay->soundType == sourceDisplay->WAVE_SOUND_TYPE)
            {
                 WaveDisplay* wavePointer = (WaveDisplay*)(sourceDisplay);
                 if(wavePointer->wave.gen_wave.getType() == WaveType::Wave_Square)
                 {
                    if(wavePointer->audioFilterData.filterType == FilterType::LPF && round(wavePointer->audioFilterData.freqCutoff1)== 800)
                    {
                        objectives[0] = true;
                    }
                 }
            }
        }
    }
    else if(stepCount ==5){
        /* Tutorial 1_5 Objectives
         * None
         *
         */
    }
    else if(stepCount == 6){
        /* Tutorial 1_6 Objectives
         * First wave added
         * Second wave added
         */
        objectives.clear();
        objectives = {false,false};
        QVector<bool> prelimObjectives = {false,false,false,false};
        for(SoundDisplay* input : inputs)
        {
            if(input->soundType == input->WAVE_SOUND_TYPE)
            {
                WaveDisplay* wavePointer = (WaveDisplay*)(input);
                if(wavePointer->waveFrequency == 100 && wavePointer->wave.gen_wave.getType() == WaveType::Wave_Sin \
                        && round(wavePointer->amplitude*100) == 100)
                {
                  prelimObjectives[0] = true;
                }
                if(wavePointer->waveFrequency == 300 && wavePointer->wave.gen_wave.getType() == WaveType::Wave_Sin \
                       && round(wavePointer->amplitude*100) == 33)
                {
                  prelimObjectives[1] = true;
                }
                if(wavePointer->waveFrequency == 500 && wavePointer->wave.gen_wave.getType() == WaveType::Wave_Sin \
                        && round(wavePointer->amplitude*100) == 20)
                {
                  prelimObjectives[2] = true;
                }
                if(wavePointer->waveFrequency == 700 && wavePointer->wave.gen_wave.getType() == WaveType::Wave_Sin \
                        && round(wavePointer->amplitude*100) == 14)
                {
                  prelimObjectives[3] = true;
                }
            }
        }
        if ( (std::equal(prelimObjectives.begin() + 1, prelimObjectives.end(), prelimObjectives.begin())) && prelimObjectives[0] == true)
        {
            // if all prelimObjectives are true
            for(SoundDisplay* input : inputs)
            {
                if(input->soundType == input->WAVE_SOUND_TYPE)
                {
                    WaveDisplay* wavePointer = (WaveDisplay*)(input);
                    if(wavePointer->waveFrequency == 900 && round(wavePointer->amplitude*100) == 11)
                    {
                        objectives[0] = true;
                    }
                    if(wavePointer->waveFrequency == 1100 && round(wavePointer->amplitude*100) == 9)
                    {
                        objectives[1] = true;
                    }
                }
            }
        }
    }
    else if(stepCount == 7){
        // End nothing happens
    }
    else if(stepCount == TUTORIAL_TWO_START)
    {
        /* Tutorial 2_1 Objectives
         * Create 300Hz sin wave
         * Add noise
         * Listen to the inputs individually
         */
        objectives.clear();
        objectives = {false,false,false};
        for(SoundDisplay* input : inputs)
        {
            if(input->soundType == input->WAVE_SOUND_TYPE)
            {
                WaveDisplay* wavePointer = (WaveDisplay*)(input);
                if(wavePointer->wave.gen_wave.getType() == WaveType::Wave_Sin && wavePointer->waveFrequency == 300)
                {
                    objectives[0] = true;
                }
                if(wavePointer->wave.gen_wave.getType() == WaveType::Wave_Noise)
                {
                   objectives[1] = true;
                }
            }
        }
        if(signalSourceType == PLAY_BUTTON_PRESSED && sourceDisplay != NULL)
            if(sourceDisplay->soundType == sourceDisplay->WAVE_SOUND_TYPE)
            {
                WaveDisplay* wavePointer = (WaveDisplay*)(sourceDisplay);
                if(wavePointer->wave.gen_wave.getType() == WaveType::Wave_Sin && wavePointer->waveFrequency == 300)
                {
                    objectives[2] = true;
                }
                else if(wavePointer->wave.gen_wave.getType() == WaveType::Wave_Noise)
                {
                    objectives[2] = true;
                }
            }
    }
    else if(stepCount == (TUTORIAL_TWO_START + 1))
    {
        /* Tutorial 2_2 Objectives
         * Listen to the sum of the inputs at the output on the bottom
         */
        objectives.clear();
        objectives = {false};
        //std::cout << "stuff SST: " << signalSourceType  << "SD: "<< (sourceDisplay != NULL) << "Type:" << sourceDisplay->soundType << std::endl;
        if(signalSourceType == PLAY_BUTTON_PRESSED && sourceDisplay != NULL && sourceDisplay->soundType == sourceDisplay->OUTPUT_SOUND_TYPE)
        {
            objectives[0] = true;
        }
    }
    else if(stepCount == (TUTORIAL_TWO_START + 2))
    {
        /* Tutorial 2_3 Objectives
         * Add lowpass filter with cutoff = 300Hz to output
         */
        objectives.clear();
        objectives = {false};
        //std::cout << "stuff SSD: " << signalSourceType  << "SD: "<< (sourceDisplay != NULL) << "Type:" << sourceDisplay->soundType << std::endl;
        if(signalSourceType == EFFECT_ADDED_TYPE && sourceDisplay != NULL && sourceDisplay->soundType == sourceDisplay->OUTPUT_SOUND_TYPE)
        {
                if(sourceDisplay->audioFilterData.filterType == FilterType::LPF && round(sourceDisplay->audioFilterData.freqCutoff1)== 300)
                {
                    objectives[0] = true;
                }
        }

    }
    else if(stepCount == (TUTORIAL_TWO_START + 3))
    {
        /* Tutorial 2_4 Objectives
         * Listen to the filtered output signal
         */
        objectives.clear();
        objectives = {false};
        if(signalSourceType == PLAY_BUTTON_PRESSED && sourceDisplay != NULL && sourceDisplay->soundType == sourceDisplay->OUTPUT_SOUND_TYPE)
        {
            objectives[0] = true;
        }
    }
    std::cout << "objectives checked, step count = " << stepCount << std::endl;
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
    QStringList objectives = { "Create 100Hz square wave"};
    QString instructions = "Welcome to the first tutorial: Superposition, Frequency and Time!\n \
Lets start off by getting familiar with the display, Create a new input.\n \
Set the type to square wave, and set the frequency to 100Hz. \
Click the “Generate Wave” button to create the wave.";
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
    QStringList objectives = { "Create Sine wave: Frequency: 100Hz, Amplitude: 1",
                             "Create Sine wave: Frequency: 300Hz, Amplitude: 0.33",
                             "Create Sine wave: Frequency: 500Hz, Amplitude: 0.20",
                             "Create Sine wave: Frequency: 700Hz, Amplitude: 0.14"};
    QString instructions = "Create 4 new sin waves. Observe the frequency domain,\
and note that the fourier transform of a sin wave is a spike, \
or delta at the respective frequency.";
    tutorialPanel->updatePanel(objectives,instructions);
}

void TutorialController::loadTutorial1_3()
{
    QStringList objectives = {};
    QString instructions = "Compare the frequency domain for the square wave and the superposition of sin waves. \
Note that they are similar, with spikes at 100Hz, 300Hz, 500Hz, and 700Hz for both signals,\
and more smaller spikes at higher frequencies for the square wave. Press Next Step When ready";
    tutorialPanel->submitObjectivesButton->setText("Next Step");
    tutorialPanel->updatePanel(objectives,instructions);
}

void TutorialController::loadTutorial1_4()
{
    tutorialPanel->submitObjectivesButton->setText("Submit Objectives");
    QStringList objectives = {"Apply a lowpass filter with cutoff = 800Hz to your square wave of 100Hz"};
    QString instructions = "Now you will add a low pass filter to the square wave. \
This will pass frequencies below the cutoff frequency, and stop frequencies above the cutoff. \
On your square wave, click the “Toggle Effects Panel” button and select “Add Filter”. \
Create your filter by choosing Low Pass Filter, and setting the cutoff frequency to 800Hz.\
One you apply the filter, note how in the frequency domain, \
all of the spikes above 700Hz are now gone.";
    tutorialPanel->updatePanel(objectives,instructions);
}

void TutorialController::loadTutorial1_5()
{
    QStringList objectives = {};
    QString instructions = " Compare your filtered square wave to your sum of sin waves in both the time and frequency domain.\
They should look the same.\
This is because the fourier series of a square wave is the infinite sum of odd harmonics of the fundamental frequency (100Hz in our case),\
whose magnitudes are inversely proportional to the harmonic number.\
For example, 300Hz is k = 3 times 100Hz, and the 300Hz component has an amplitude of ⅓.\
Theoretically, you could keep adding sinusoids like this for k = 5, 7, 9, 11, 13… infinitely to create a square wave.";
    tutorialPanel->submitObjectivesButton->setText("Next Step");
    tutorialPanel->updatePanel(objectives,instructions);
}

void TutorialController::loadTutorial1_6()
{
    QStringList objectives = {"Create Sine wave: Frequency: 900Hz, Amplitude: 0.11","Create Sine wave: Frequency: 1100Hz, Amplitude: 0.09"};
    QString instructions = "Add two more waves to your sum of sins in order to make it better approximate (look more like) a square wave.\
Make sure you keep the inputs from the previous steps (Sine wave: Frequency: 100Hz, Amplitude: 1,\
Sine wave: Frequency: 300Hz, Amplitude: 0.33, Sine wave: Frequency: 500Hz, Amplitude: 0.20, and \
Sine wave: Frequency: 700Hz, Amplitude: 0.14)";
    tutorialPanel->submitObjectivesButton->setText("Submit Objectives");
    tutorialPanel->updatePanel(objectives,instructions);
}

void TutorialController::loadTutorial1_End()
{
    QString instructions = "You've completed Tutorial 1! Click the buttons on the screen to either go into\
sandbox mode where you can play with the waves at will, or move on to Tutorial 2";
            QStringList objectives = {};
    tutorialPanel->submitObjectivesButton->setText("Return to Tutorial Selection");
    tutorialPanel->updatePanel(objectives,instructions);
    this->tutorialPanel->submitObjectivesButton->setVisible(false);
    this->returnToTutorialSelectionButton->setVisible(true);
}

void TutorialController::loadTutorial2_1()
{
    stepCount = TUTORIAL_TWO_START;
    QString instructions = "Create a sin wave input at 300Hz and add a noise input.\
 Click “Generate Wave” once you’ve set the desired values. Then listen to each input individually.";
            QStringList objectives = {"Create 300Hz sin wave","Add noise","Listen to the inputs"};
    tutorialPanel->updatePanel(objectives,instructions);
    // First step of tutorial 2
}

void TutorialController::loadTutorial2_2()
{
    // First step of tutorial 2
    QString instructions = "Where the two signals are summed together, \
click the “Play” button to listen to the sum of the inputs";
    QStringList objectives = {"Listen to the sum of the inputs"};
    tutorialPanel->updatePanel(objectives,instructions);
}

void TutorialController::loadTutorial2_3()
{
    // First step of tutorial 2
    QString instructions = "Next, add a low pass filter with cutoff frequency = 300Hz.\
Click the “Toggle Effects Panel” button and select “Add Filter”,\
then select low pass filter and change the cutoff frequency to 300Hz";
    QStringList objectives = {"Add lowpass filter with cutoff = 300Hz to the output"};
    tutorialPanel->updatePanel(objectives,instructions);
}

void TutorialController::loadTutorial2_4()
{
    // First step of tutorial 2
    QString instructions = "Click the “Play” button again to hear how the signal is changed by the filter.\
Notice that the noise is now much quieter compared to the signal.\
This is because the lowpass filter filtered out the frequency components of the noise which were about 300Hz,\
meaning there is much less overall noise in the signal.\
Observe the frequency domain of the noise signal input, \
and see that much of the energy of the noise is contained within components greater than 300Hz.";
    QStringList objectives = {"Listen to the filtered signal"};
    tutorialPanel->updatePanel(objectives,instructions);
}

void TutorialController::loadTutorial2_End()
{
    QString instructions = "You've completed Tutorial 2! Click the buttons on the screen to either go into\
sandbox mode where you can play with the waves at will, or go back to tutorial 1";
            QStringList objectives = {};
    tutorialPanel->updatePanel(objectives,instructions);
    this->tutorialPanel->submitObjectivesButton->setVisible(false);
    this->returnToTutorialSelectionButton->setVisible(true);
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

void TutorialController::loadTutorialPicker()
{
    QString instructions = "Select a Tutorial";
    QStringList objectives = {};
    tutorialPanel->updatePanel(objectives,instructions);
    this->tutorialPanel->objectivesLayout->addWidget(tutorialOneButton);
    this->tutorialPanel->objectivesLayout->addWidget(tutorialTwoButton);
    this->tutorialPanel->objectivesLayout->addWidget(sandboxButton);
    sandboxButton->setVisible(true);
    tutorialOneButton->setVisible(true);
    tutorialTwoButton->setVisible(true);
    this->returnToTutorialSelectionButton->setVisible(false);
}
