#include "outputsounddisplay.h"

OutputSoundDisplay::OutputSoundDisplay(QVector<SoundDisplay*>* input_vec, QWidget *parent) : SoundDisplay(parent)
{
    inputId = 0;
    buttonLayout->addWidget(playButton);
    buttonLayout->addWidget(stopButton);
    buttonLayout->addWidget(toggleEffectPanelButton);
    buttonLayout->addWidget(volumeLabel);
    buttonLayout->addWidget(volumeSlider);

    this->inputs = input_vec;

    filepath = QDir::currentPath() + "/audio_files/gen_output.wav";
}

void OutputSoundDisplay::generateOutputFile() {
    const int numSamples = outputBuf.size();

    stk::FileWvOut outputFile;
    outputFile.openFile(this->filepath.toStdString(), 1, stk::FileWrite::FILE_WAV, stk::Stk::STK_SINT16);

    for (int i = 0; i < numSamples; i++){
        outputFile.tick(outputBuf[i]/yScaling);
    }

    outputFile.closeFile();
}

/*
 * Called when its inputs are updated
 */
void OutputSoundDisplay::generateOutput()
{
    if(!inputs){
        std::cout << "OutputSoundDisplay invalid input vector\n";
        return;
    }

    //Clear the graph so that generateSine() is not
    //Accessing the same file
    drawWaveFromFile("");
    if(inputs->size() == 0)
        return;

    std::cout << "OutputSoundDisplay: Clearing output Buffer\n";
    outputBuf.clear();
    std::cout << "OutputSoundDisplay: Updating Buffer\n";

    yScaling = 1.0;
    yMax = 1.0;
    yMin = -1.0;

    for(int i = 0; i < inputs->size(); i++) {
        SoundDisplay* input = (*inputs)[i];
        if(input != nullptr && input->isVisible()) {
            stk::FileWvIn inputFile;
            std::string fileSource = input->timeDomain->getSourceFile().toStdString();

            if(fileSource.empty()) {
                std::cout << "OutputSoundDisplay: Empty file\n";
            }
            else{
                std::cout << "OutputSoundDisplay: Trying to open file: " << input->timeDomain->getSourceFile().toStdString() << std::endl;
                try{
                    inputFile.openFile(fileSource);
                } catch (stk::StkError &error) {
                    error.printMessage();
                }

                int numSamples = inputFile.getSize();
                for(int j = 0; j < numSamples; j++){
                    if(j >= outputBuf.size()){
                        outputBuf.push_back(inputFile.tick());
                    }
                    else{
                        outputBuf[j] += inputFile.tick();
                    }

                    if(abs(outputBuf[j]) > yScaling){
                        yScaling = abs(outputBuf[j]);
                    }
                    if(outputBuf[j] > yMax) {
                        yMax = outputBuf[j];
                    }
                    if(outputBuf[j] < yMin) {
                        yMin = outputBuf[j];
                    }
                }

                if(abs(yMax) > yScaling || abs(yMin > yScaling)) {
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

    std::cout << "OutputSoundDisplay: Generating File\n";
    generateOutputFile();

    std::cout << "OutputSoundDisplay: Drawing Wave\n";
    drawWaveFromFile(filepath);
    std::cout << "OutputSoundDisplay: Done Drawing\n";
}
