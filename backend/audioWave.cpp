#include "audioWave.h"

int audioWave::id = 0;

audioWave::audioWave() : currentId(++id)
{
}

void audioWave::setFrequency(float freq){
    this->gen_wave.setFrequency(freq);
}

void audioWave::setDuration(float len){
    gen_wave.setDuration(len);
}

void audioWave::setWaveType(WaveType type) {
    gen_wave.setType(type);
}

void audioWave::setFilePath(QString filePath){
    QStringList dotSplit = filePath.split(QLatin1Char('.'));
    this->filePath = "";
    for (int i = 0; i < dotSplit.length() - 1; i++){
        this->filePath = this->filePath + dotSplit[i];
    }
    this->filePath = this->filePath + "_" + QString::number(this->currentId) + "." + dotSplit[dotSplit.length() - 1];
}

QString audioWave::getFilePath(){
    return this->filePath;
}

void audioWave::generateSine(){
    const int numSamples = this->gen_wave.getDuration() * stk::Stk::sampleRate();

    this->output.openFile(this->filePath.toStdString(), 1, stk::FileWrite::FILE_WAV, stk::Stk::STK_SINT16);

//    this->sineWave.reset();
    this->gen_wave.generate();


    for (int i = 0; i < numSamples; i++){
        output.tick(gen_wave.values[i]);
    }

    this->output.closeFile();
}
