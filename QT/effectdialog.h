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
    EffectDialog(QWidget *parent,QVector<InputInfo> inputs);

    /*
     * Functions
     */
    //gets the values from the dialog after done
    QStringList getEntries();

    QFormLayout* formLayout;

    //SubWidgets
    QDialog* dialogBox;
public slots:

private:
    QList<QDoubleSpinBox*> fields;
    QList<QComboBox*> choiceFields;
    QList<QLabel*> labels;
    QDialogButtonBox* dialogButtons;
};

#endif // EFFECTDIALOG_H
