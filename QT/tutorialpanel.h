#ifndef TUTORIALPANEL_H
#define TUTORIALPANEL_H

#include <QObject>
#include <QWidget>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QPushButton>

/*
 * This is the panel anchored to the top of the screen
 * that displays the current progress of this tutorial step
 */

/*
 * checkBox->setAttribute(Qt::WA_TransparentForMouseEvents, readOnly);
   checkBox->setFocusPolicy(readOnly ? Qt::NoFocus : Qt::StrongFocus);
 * TODO: for later
 * You leave the checkbox as "enabled" and "checkable".
 * This just makes it so the control
 * ignores mouse events and can not have focus
 *
 */
class TutorialPanel : public QWidget
{
    Q_OBJECT
public:
    TutorialPanel(QWidget *parent, int tutorialNumber);
    ~TutorialPanel();

    //Updates the text contained in the tutorial Panel
    void updatePanel(QStringList objectives);

    // Returns true if all objectives have been completed, false otherwise
    bool getObjectiveStatus();
    QVector<QCheckBox*> checkboxes;
    QPushButton* submitObjectivesButton;
    QVBoxLayout* objectivesLayout;
};

#endif // TUTORIALPANEL_H
