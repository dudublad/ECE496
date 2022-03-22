#ifndef TUTORIALPANEL_H
#define TUTORIALPANEL_H

#include <QObject>
#include <QWidget>
#include <QCheckBox>
#include <QVBoxLayout>

/*
 * This is the panel anchored to the top of the screen
 * that displays the current progress of this tutorial step
 */
class TutorialPanel : public QWidget
{
    Q_OBJECT
public:
    TutorialPanel(QWidget *parent, int tutorialNumber);
    ~TutorialPanel();
    void updatePanel();
    QVector<QCheckBox> checkboxes;
    QVBoxLayout* objectivesLayout;
};

#endif // TUTORIALPANEL_H
