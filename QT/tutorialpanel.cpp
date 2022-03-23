#include "tutorialpanel.h"

TutorialPanel::TutorialPanel(QWidget *parent, int tutorialNumber) : QWidget(parent)
{
    objectivesLayout = new QVBoxLayout(this);
    submitObjectivesButton = new QPushButton("Submit Objectives",this);

}

TutorialPanel::~TutorialPanel()
{

}

//
void TutorialPanel::updatePanel(QStringList objectives)
{
    //Disposes of checkboxes
    for(int i = 0;i < checkboxes.size();i++)
    {
        free(checkboxes[i]);
    }
    checkboxes.clear();


    objectivesLayout->removeWidget(submitObjectivesButton);
    //connections are not handled here, they are handled in the tutorialController
    for( const auto& objective : objectives)
    {
        QCheckBox* newCheckBox = new QCheckBox(objective,this);
        newCheckBox->setAttribute(Qt::WA_TransparentForMouseEvents);
        newCheckBox->setFocusPolicy(Qt::NoFocus);
        checkboxes.append(newCheckBox);
        objectivesLayout->addWidget(newCheckBox);
    }

    objectivesLayout->addWidget(submitObjectivesButton);
}

bool TutorialPanel::getObjectiveStatus()
{
    int numCheckBoxes = checkboxes.size();
    bool isChecked = true;
    for(int i = 0;i<numCheckBoxes;i++)
    {
        isChecked = checkboxes[i]->isChecked();
        if(isChecked == false)
        {
            break;
        }
    }

    return isChecked;
}
