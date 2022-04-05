#include "effectdialog.h"


/*
 * DEPRICATED
 *
 * Please read for EffectDialog usage:
 * Create a QVector of InputInfos, specify the type you want
 * the label next to the entry box and if applicable, the choices
 * in the form of a list of strings where YOU will
 * remember the index, as the combo box only returns
 * the index of the option chosen.
 * Get entries returns the value of the comboBoxes
 * (the values which have choices first, in the order
 * they were supplied to the argument, then the
 * values of the (ints and doubles) in the order they were supplied
 * to the argument
 *
 * I.e. I asked for the input for:
 * int1, double1, int2, choices1, double2
 * the order they will be returned in the QStringList will be
 * [0]: choices1, [1]: int1, [2]: double1,[3]: int2,[4]: double2
 */
EffectDialog::EffectDialog(QWidget *parent,QVector<InputInfo> inputs) : QDialog(parent)
{
    dialogBox = new QDialog(this);
    formLayout = new QFormLayout(this);
    for (int i = 0;i < inputs.length();i++)
    {
        auto currentInputInfo = inputs[i];
        if(currentInputInfo.type == InputType::Int)
        {
            // For types where a integer is needed
            QDoubleSpinBox* intField = new QDoubleSpinBox(this);
            intField->setMaximum((int)currentInputInfo.maximum);
            intField->setMinimum((int)currentInputInfo.minimum);
            intField->setValue(1);
            intField->setDecimals(0);
            QLabel *label = new QLabel(this);
            label->setText(currentInputInfo.label);
            formLayout->addRow(label,intField);
            fields.append(intField);
            labels.append(label);
        }
        else if(currentInputInfo.type == InputType::Double)
        {
            // For types where a double is needed
            QDoubleSpinBox* doubleField = new QDoubleSpinBox(this);
            doubleField->setMaximum(currentInputInfo.maximum);
            doubleField->setMinimum(currentInputInfo.minimum);
            QLabel *label = new QLabel(this);
            label->setText(currentInputInfo.label);
            formLayout->addRow(label,doubleField);
            // TODO: see if this persists
            fields.append(doubleField);
            labels.append(label);
        }
        else if(currentInputInfo.type == InputType::Choice)
        {
            QComboBox* choiceField = new QComboBox(this);
            choiceField->addItems(currentInputInfo.choices);
            QLabel *label = new QLabel(this);
            label->setText(currentInputInfo.label);
            formLayout->addRow(label,choiceField);
            choiceFields.append(choiceField);
            labels.append(label);
        }
    }
    // end of adding fields
    dialogButtons = new QDialogButtonBox(QDialogButtonBox::Ok |
        QDialogButtonBox::Cancel,
        Qt::Horizontal,this);
    formLayout->addWidget(dialogButtons);

    connect(dialogButtons, SIGNAL(accepted()),this,SLOT(accept()));
    connect(dialogButtons,SIGNAL(rejected()),this,SLOT(reject()));

    setLayout(formLayout);
    setMinimumSize(200,200);
}

EffectDialog::EffectDialog() {
    dialogBox = new QDialog(this);
    formLayout = new QFormLayout(this);
}

EffectDialog::~EffectDialog() {
    if(dialogBox) {
        delete dialogBox;
        dialogBox = nullptr;
    }
    if(formLayout){
        delete formLayout;
        formLayout = nullptr;
    }
    if(dialogButtons){
        delete dialogButtons;
        dialogButtons = nullptr;
    }
}

QStringList EffectDialog::getEntries()
{
    QStringList entries;
    foreach(QComboBox* choiceItem,choiceFields)
    {
        entries.append(choiceItem->currentText());
        //Dump the results
    }
    foreach(QDoubleSpinBox* numberItem,fields)
    {
        entries.append(QString::fromStdString(std::to_string(numberItem->value())));
    }
    return entries;
}
