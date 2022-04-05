#ifndef TUTORIALCONTROLLER_H
#define TUTORIALCONTROLLER_H

#include <QObject>
#include <QWidget>
#include "inputscrollview.h"
#include "tutorialpanel.h"
#include "waveoscillator.h"

class TutorialController : public QWidget
{
    Q_OBJECT
public:
    // Attributes
    int stepCount;
    InputScrollView* inputScrollView;
    TutorialPanel* tutorialPanel;
    QVBoxLayout* mainTutorialLayout;

    /*
     * Utility Functions
     *
     */
    TutorialController(QWidget *parent);

    void loadTutorial1_1();
    void loadTutorial1_2();
    void loadTutorial1_3();
    void loadTutorial1_4();
    void loadTutorial1_5();
    void loadTutorial1_6();
    QVector<QCheckBox> currentObjectives;
    QVector<QString> objectiveText;

public slots:
    void objectiveChecked(int boxIndex,bool completed);
    void checkConditions();
};

#endif // TUTORIALCONTROLLER_H
