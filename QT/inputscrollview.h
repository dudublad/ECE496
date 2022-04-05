#ifndef INPUTSCROLLVIEW_H
#define INPUTSCROLLVIEW_H

#include <QWidget>
#include <QScrollArea>
#include <QPushButton>
#include "sounddisplay.h"
#include "wavedisplay.h"
#include "recordedsounddisplay.h"
#include "outputsounddisplay.h"

class InputScrollView : public QWidget
{
    Q_OBJECT
public:
    // Functions
    InputScrollView(QWidget *parent);
    ~InputScrollView();

    void createOutputFile();
    void updateScrollArea();

    // Subwidgets
    QPushButton* addRecordedInputButton;
    QPushButton* addSineWaveButton;
    QScrollArea* scrollArea;
    OutputSoundDisplay* output;

    //Layouts
    QVBoxLayout* topLayout; // Top Level Layout for this class
    QVBoxLayout* scrollLayout; // Holds the scrollable area
    QHBoxLayout* inputButtonLayout; // Holds the buttons to add inputs
    QHBoxLayout* outputLayout;
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
    enum SoundInputType {recordedSound,sineWave, squareWave, sawtoothWave};

    // ID value current count
    int nextInputId;

    QVector<SoundDisplay*> inputs;

public slots:
    void addInput(InputScrollView::SoundInputType inputType);
    void updateOutput();
    void removeInput(SoundDisplay* input);
    void removeInputByIndex(int index);
    void inputRemoved();
};

#endif // INPUTSCROLLVIEW_H
