#ifndef EFFECTDIALOG_H
#define EFFECTDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QFormLayout>
#include <QDialogButtonBox>

class EffectDialog : public QDialog
{
    Q_OBJECT
public:
    EffectDialog(QWidget *parent);
    ~EffectDialog();

    QStringList getEntries();

public slots:

private:
    QList<QLineEdit*> fields;

};

#endif // EFFECTDIALOG_H
