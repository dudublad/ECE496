#include "outputsounddisplay.h"

OutputSoundDisplay::OutputSoundDisplay(QWidget *parent) : SoundDisplay(parent)
{
    buttonLayout->addWidget(playButton);
    buttonLayout->addWidget(stopButton);
}

/*
 * Called when its inputs are updated
 */
void OutputSoundDisplay::generateOutput()
{

}
