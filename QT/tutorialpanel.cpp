#include "tutorialpanel.h"

TutorialPanel::TutorialPanel(QWidget *parent, int tutorialNumber) : QWidget(parent)
{
    objectivesLayout = new QVBoxLayout(this);
    submitObjectivesButton = new QPushButton("Submit Objectives",this);
    instructionsText = new QLabel("",this);
    instructionsText->setWordWrap(true);
}

TutorialPanel::~TutorialPanel()
{

}

//
void TutorialPanel::updatePanel(QStringList objectives,QString instructions)
{
    std::cout << "\n updating panel count is: " << objectivesLayout->count() << std::endl;
//    while(objectivesLayout->count() > 0)
//    {
//        QLayoutItem* child = objectivesLayout->takeAt(0);

//        objectivesLayout->removeItem(child);
//    }

    //Disposes of existing checkboxes
    for(int i = 0;i < checkboxes.size();i++)
    {
        checkboxes[i]->setVisible(false);
        //TODO: Crashes on exit if this is left on
        delete checkboxes[i];
    }
    checkboxes.clear();


    objectivesLayout->removeWidget(submitObjectivesButton);
    //connections are not handled here, they are handled in the tutorialController
    instructionsText->setText(instructions);
    objectivesLayout->addWidget(instructionsText);
    for( const auto& objective : objectives)
    {
        QCheckBox* newCheckBox = new QCheckBox(objective,this);
        newCheckBox->setAttribute(Qt::WA_TransparentForMouseEvents);
        newCheckBox->setFocusPolicy(Qt::NoFocus);
        checkboxes.append(newCheckBox);
        objectivesLayout->addWidget(newCheckBox);
    }

    objectivesLayout->addWidget(submitObjectivesButton,Qt::AlignCenter);
    std::cout << "done updating panel" << std::endl;
}

bool TutorialPanel::getObjectivesStatus()
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

/**
 * in .h
  signals:
    void valueChanged(int newValue)

   where u want to emit (some .cpp)
   emit valueChanged(value);
  */
