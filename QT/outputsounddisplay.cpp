#include "outputsounddisplay.h"

OutputSoundDisplay::OutputSoundDisplay(QVector<SoundDisplay*>* input_vec, QWidget *parent) : SoundDisplay(parent)
{
    connect(playButton,SIGNAL(clicked()),this,SLOT(onPlayButtonClicked()));
    inputId = 0;
    buttonLayout->addWidget(playButton);
    buttonLayout->addWidget(stopButton);
    buttonLayout->addWidget(toggleEffectPanelButton);
    buttonLayout->addWidget(volumeLabel);
    buttonLayout->addWidget(volumeSlider);

    this->inputs = input_vec;

    addToOutput = false;
    addToOutputCheckBox->setVisible(false);

    filepath = QDir::currentPath() + "/audio_files/gen_output.wav";
    generate();
    changeFile(filepath);
}

void OutputSoundDisplay::generateOutputFile() {
    std::cout << "OutputSoundDisplay: Generating File\n";
    const int numSamples = outputBuf.size();

    stk::FileWvOut outputFile;
    outputFile.openFile(this->filepath.toStdString(), 1, stk::FileWrite::FILE_WAV, stk::Stk::STK_SINT16);

    for (int i = 0; i < numSamples; i++){
        outputFile.tick(outputBuf[i]/yScaling);
    }

    outputFile.closeFile();
}

#define OUTPUT_PLOT_TIME_LIMIT_S 10

void OutputSoundDisplay::generate(){
    if(!inputs){
        std::cout << "OutputSoundDisplay invalid input vector\n";
        return;
    }

    if(inputs->size() <= 0)
        return;

    std::cout << "OutputSoundDisplay: Clearing output Buffer\n";
    outputBuf.clear();
    std::cout << "OutputSoundDisplay: Updating Buffer\n";

    yScaling = 1.0;
    yMax = 1.0;
    yMin = -1.0;

    for(int i = 0; i < inputs->size(); i++) {
        SoundDisplay* input = (*inputs)[i];
        if(input != nullptr && input->isVisible() && input->addToOutput) {
            stk::FileWvIn inputFile;
            std::string fileSource = input->timeDomain->getSourceFile().toStdString();

            if(fileSource.empty()) {
                std::cout << "OutputSoundDisplay: Empty file\n";
            }
            else{
                std::cout << "OutputSoundDisplay: Trying to open file: " << input->timeDomain->getSourceFile().toStdString() << std::endl;
                try{
                    inputFile.openFile(fileSource, false, false);
                } catch (stk::StkError &error) {
                    error.printMessage();
                }

                std::cout << "OutputSoundDisplay: Opened file; size = " << inputFile.getSize()
                          << " fileRate = " << inputFile.getFileRate() << std::endl;


                int numSamples = inputFile.getSize() * (stk::Stk::sampleRate()/inputFile.getFileRate());
                for(int j = 0; j < numSamples && j < OUTPUT_PLOT_TIME_LIMIT_S*stk::Stk::sampleRate(); j++){
                    if(j >= outputBuf.size()){
                        outputBuf.push_back(input->yScaling * inputFile.tick());
                    }
                    else{
                        outputBuf[j] += input->yScaling * inputFile.tick();
                    }

                    if(outputBuf[j] > yMax) {
                        yMax = outputBuf[j];
                    }
                    if(outputBuf[j] < yMin) {
                        yMin = outputBuf[j];
                    }
                }

                //Sets the scaling to normalize the .wav file
                if(abs(yMax) > yScaling || abs(yMin) > yScaling) {
                    if(abs(yMax) > abs(yMin)) {
                        yScaling = abs(yMax);
                    }
                    else {
                         yScaling = abs(yMin);
                    }
                }

                inputFile.closeFile();
            }
        }
    }

    if(outputBuf.size() == 0) {
        std::cout << "OutputSoundDisplay: Output Buffer is empty\n";
        return;
    }

    //Stop playing audio, if playing
    this->stopFile();
    this->generateOutputFile();

}


/*
 * Called when its inputs are updated
 */
void OutputSoundDisplay::generateOutput(){
    //Clear the graph so that generateSine() is not
    //Accessing the same file
    drawWaveFromFile("");
    this->generate();

    copyFileToEffectFile();

    std::cout << "OutputSoundDisplay: Drawing Wave\n";
    drawWaveFromFile(this->selectedFile);
    std::cout << "OutputSoundDisplay: Done Drawing\n";




}
