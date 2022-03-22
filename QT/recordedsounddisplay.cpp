#include "recordedsounddisplay.h"

// Uses parent constructor

RecordedSoundDisplay::RecordedSoundDisplay(QWidget *parent, int id) : SoundDisplay(parent)
{
    // init
    inputId = id;
    idLabel = new QLabel(this);
    idLabel->setText(QString::fromStdString("ID: " + std::to_string(inputId)));
    chooseFileButton = new QPushButton("Choose a new File",this);
    removeInputButton = new QPushButton("Remove Input",this);
    connect(chooseFileButton,SIGNAL(clicked()),this,SLOT(chooseFile()));
    connect(removeInputButton,SIGNAL(clicked()),this,SLOT(removeInputButtonPushed()));
    connect(playButton,SIGNAL(clicked()),this,SLOT(onPlayButtonClicked()));
    buttonLayout->addWidget(playButton,0,0,Qt::AlignCenter);
    buttonLayout->addWidget(stopButton,1,0,Qt::AlignCenter);
    buttonLayout->addWidget(chooseFileButton,0,1,Qt::AlignCenter);
    buttonLayout->addWidget(toggleEffectPanelButton,1,1,Qt::AlignCenter);
    buttonLayout->addWidget(idLabel,2,0,Qt::AlignCenter);
    buttonLayout->addWidget(removeInputButton,2,1,Qt::AlignCenter);
    buttonLayout->addWidget(volumeLabel,3,0,Qt::AlignCenter);
    buttonLayout->addWidget(volumeSlider,3,1,Qt::AlignCenter);

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
