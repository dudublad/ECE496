#include "audiosine.h"

int audioSine::id = 0;

audioSine::audioSine() : currentId(++id)
{
}

void audioSine::setFrequency(float freq){
    this->sineWave.setFrequency(freq);
}

void audioSine::setDuration(float len){
    this->durationSecs = len;
}

void audioSine::setFilePath(QString filePath){
    QStringList dotSplit = filePath.split(QLatin1Char('.'));
    this->filePath = "";
    for (int i = 0; i < dotSplit.length() - 1; i++){
        this->filePath = this->filePath + dotSplit[i];
    }
    this->filePath = this->filePath + "_" + QString::number(this->currentId) + "." + dotSplit[dotSplit.length() - 1];
}

QString audioSine::getFilePath(){
    return this->filePath;
}

void audioSine::generateSine(){
    const int numSamples = this->durationSecs * stk::Stk::sampleRate();

    this->output.openFile(this->filePath.toStdString(), 1, stk::FileWrite::FILE_WAV, stk::Stk::STK_SINT16);

    this->sineWave.reset();

    for (int i = 0; i < numSamples; i++){
        output.tick(this->sineWave.tick());
    }

    this->output.closeFile();
}
