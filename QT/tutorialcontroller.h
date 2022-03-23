#ifndef TUTORIALCONTROLLER_H
#define TUTORIALCONTROLLER_H

#include <QObject>
#include <QWidget>
#include "inputscrollview.h"
#include "tutorialpanel.h"

class TutorialController : public QWidget
{
    Q_OBJECT
public:
    // Attributes
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
    QVector<QCheckBox> currentObjectives;
    QVector<QString> objectiveText;

public slots:
    void objectiveComplete(int boxIndex);
};

#endif // TUTORIALCONTROLLER_H
