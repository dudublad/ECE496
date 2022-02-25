#ifndef INPUTSCROLLVIEW_H
#define INPUTSCROLLVIEW_H

#include <QWidget>
#include <QScrollArea>
#include "sounddisplay.h"
#include "sinewavedisplay.h"
#include "recordedsounddisplay.h"

class InputScrollView : public QWidget
{
    Q_OBJECT
public:
    // Functions
    InputScrollView(QWidget *parent);
    ~InputScrollView();
    void removeInput(SoundDisplay* input);
    void removeInputByIndex(int index);
    void createOutputFile();
    void updateScrollArea();

    // Subwidgets
    QPushButton* addRecordedInputButton;
    QPushButton* addSineWaveButton;
    QScrollArea* scrollArea;

    //Layouts
    QVBoxLayout* topLayout; // Top Level Layout for this class
    QVBoxLayout* scrollLayout; // Holds the scrollable area
    QHBoxLayout* inputButtonLayout; // Holds the buttons to add inputs

    /*
     * The layout for the scroll area input container
     * When adding new inputs, the inputs should be added to this layout
     */
    QVBoxLayout* inputSubScrollLayout;
    /*
     * Holds the actual Scrollable inputs since scroll area
     * only holds one widget which can be scrolled
     */
    QWidget* scrollAreaInputContainer;

    //constants
    enum SoundInputType {recordedSound,sineWave};

public slots:
    void addInput(SoundInputType inputType);
private:
    QVector<SoundDisplay*> inputs;
    //private members
};

#endif // INPUTSCROLLVIEW_H
