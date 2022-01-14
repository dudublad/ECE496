#include "recordedsounddisplay.h"

// Uses parent constructor

RecordedSoundDisplay::RecordedSoundDisplay(QWidget *parent) : SoundDisplay(parent)
{
    // init
    chooseFileButton = new QPushButton("Choose a new File",this);
    connect(chooseFileButton,SIGNAL(clicked()),this,SLOT(chooseFile()));
    buttonLayout->addWidget(chooseFileButton);


}
void RecordedSoundDisplay::chooseFile()
{
    //opens up a dialog to choose a file from PC
    QString fileName = QFileDialog::getOpenFileName(nullptr,"Select one or more files to open","","Sounds (*.wav)");
    std::cout << "returned file name = " << fileName.toStdString() << std::endl;
    if(!fileName.isNull() && fileName.endsWith(".wav"))
    {
        selectedFile = fileName;
    }
    else
    {
        selectedFile = "";
    }
    std::cout << "returned file name = " << selectedFile.toStdString() << std::endl;
    changeFile(selectedFile);

}
