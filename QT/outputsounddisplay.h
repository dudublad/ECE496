#ifndef OUTPUTSOUNDDISPLAY_H
#define OUTPUTSOUNDDISPLAY_H

#include "sounddisplay.h"

class OutputSoundDisplay : public SoundDisplay
{
    Q_OBJECT
public:
    OutputSoundDisplay(QWidget *parent);


public slots:
    void generateOutput();
};

#endif // OUTPUTSOUNDDISPLAY_H
