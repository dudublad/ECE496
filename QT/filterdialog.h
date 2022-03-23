#ifndef FILTERDIALOG_H
#define FILTERDIALOG_H

#include <QObject>
#include <QWidget>
#include "effectdialog.h"
#include "audiofilter.h"

class FilterDialog : public EffectDialog
{
    Q_OBJECT
public:
    FilterDialog();
    ~FilterDialog();

    QLabel * filter_label;
    QComboBox* filter_select;

    QLabel * window_label;
    QComboBox* window_select;

    QLabel * cutoff_1_label;
    QLabel * cutoff_2_label;
    QDoubleSpinBox* set_cutoff_1;
    QDoubleSpinBox* set_cutoff_2;

    FilterType filterType = FilterType::LPF;
    WindowType windowType = WindowType::rect;
    double cutoff_low;
    double cutoff_high;



public slots:
    void filterTypeChanged(int type);
    void windowTypeChanged(int type);
    void cutoff_low_changed(double cutoff);
    void cutoff_high_changed(double cutoff);
private:
    audioFilter filter;
};

#endif // FILTERDIALOG_H
