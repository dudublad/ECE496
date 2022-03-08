#include "outputsounddisplay.h"

OutputSoundDisplay::OutputSoundDisplay(QWidget *parent) : SoundDisplay(parent)
{
    inputId = 0;
    buttonLayout->addWidget(playButton);
    buttonLayout->addWidget(stopButton);
    buttonLayout->addWidget(toggleEffectPanelButton);
}

/*
 * Called when its inputs are updated
 */
void OutputSoundDisplay::generateOutput()
{

}
