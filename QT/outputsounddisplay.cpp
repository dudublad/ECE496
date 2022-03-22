#include "outputsounddisplay.h"

OutputSoundDisplay::OutputSoundDisplay(QWidget *parent) : SoundDisplay(parent)
{
    inputId = 0;
    buttonLayout->addWidget(playButton);
    buttonLayout->addWidget(stopButton);
    buttonLayout->addWidget(toggleEffectPanelButton);
    buttonLayout->addWidget(volumeLabel);
    buttonLayout->addWidget(volumeSlider);
}

/*
 * Called when its inputs are updated
 */
void OutputSoundDisplay::generateOutput()
{

}
