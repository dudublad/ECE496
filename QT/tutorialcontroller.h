#ifndef TUTORIALCONTROLLER_H
#define TUTORIALCONTROLLER_H

#include <QObject>
#include <QWidget>
#include "inputscrollview.h"
#include "tutorialpanel.h"
#include "waveoscillator.h"
#include "programenums.h"

class TutorialController : public QWidget
{
    Q_OBJECT
public:
    // Attributes
    int stepCount;

    static constexpr int TUTORIAL_TWO_START = 8;

    InputScrollView* inputScrollView;
    TutorialPanel* tutorialPanel;
    QVBoxLayout* mainTutorialLayout;

    QPushButton* tutorialOneButton;

    QPushButton* tutorialTwoButton;

    QPushButton* sandboxButton;

    QPushButton* returnToTutorialSelectionButton;

    /*
     * Utility Functions
     *
     */
    TutorialController(QWidget *parent);

    void loadTutorialPicker();

    void loadTutorial1_1();
    void loadTutorial1_2();
    void loadTutorial1_3();
    void loadTutorial1_4();
    void loadTutorial1_5();
    void loadTutorial1_6();
    void loadTutorial1_End();

    void loadTutorial2_1();
    void loadTutorial2_2();
    void loadTutorial2_3();
    void loadTutorial2_4();
    void loadTutorial2_End();
    QVector<QCheckBox> currentObjectives;
    QVector<QString> objectiveText;

public slots:
    // Responsible for receiving the signal from the start tutorial screen
    void tutorialSelection(int tutorialIndex);
    void objectiveChecked(int boxIndex,bool completed);

    /* List of indexes for signal sources =
     *static constexpr unsigned int SIGNAL_GENERATED = 1;
     *static constexpr unsigned int EFFECT_ADDED_TYPE = 2;
     *static constexpr unsigned int PLAY_BUTTON_PRESSED = 3;
     *
     */
    void checkConditions(SoundDisplay* sourceDisplay = NULL,int signalSourceType = 0);
    void moveToNextStep();
};

#endif // TUTORIALCONTROLLER_H
