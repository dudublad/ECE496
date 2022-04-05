#ifndef EFFECTDIALOG_H
#define EFFECTDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <map>
#include <tuple>
#include <QComboBox>
#include "programenums.h"

class EffectDialog : public QDialog
{
    Q_OBJECT
public:

    // Include the enums for choices in this file
    //DEPRICATED
    EffectDialog(QWidget *parent,QVector<InputInfo> inputs);

    //Create an empty dialog
    EffectDialog();
    ~EffectDialog();

    /*
     * Functions
     */
    //gets the values from the dialog after done
    QStringList getEntries();

    QFormLayout* formLayout = nullptr;

    //SubWidgets
    QDialog* dialogBox = nullptr;
public slots:

protected:
    QList<QDoubleSpinBox*> fields;
    QList<QComboBox*> choiceFields;
    QList<QLabel*> labels;
    QDialogButtonBox* dialogButtons = nullptr;
};

#endif // EFFECTDIALOG_H
