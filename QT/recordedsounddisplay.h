#ifndef RECORDEDSOUNDDISPLAY_H
#define RECORDEDSOUNDDISPLAY_H

#include "sounddisplay.h"
#include <QFileDialog>
class RecordedSoundDisplay : public SoundDisplay
{
    Q_OBJECT
public:
    RecordedSoundDisplay(QWidget *parent, int id);

    /*
     * Subwidgets custom to RecordedSound
     */
    QPushButton* chooseFileButton;
public slots:
    void chooseFile();
};

#endif // RECORDEDSOUNDDISPLAY_H
