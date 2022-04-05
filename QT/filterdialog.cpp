#include "filterdialog.h"

FilterDialog::FilterDialog()
{
    filter_label = new QLabel(this);
    filter_label->setText("Filter Type");
    filter_select = new QComboBox(this);
    filter_select->insertItem(FilterType::LPF, "Low-Pass Filter");
    filter_select->insertItem(FilterType::HPF, "High-Pass Filter");
    filter_select->insertItem(FilterType::BPF, "Band-Pass Filter");
    filter_select->insertItem(FilterType::BSF, "Band-Stop Filter");
    formLayout->addRow(filter_label, filter_select);

    window_label = new QLabel(this);
    window_label->setText("Window Type");
    window_select = new QComboBox(this);
    window_select->insertItem(WindowType::rect, "Rectangular");
    window_select->insertItem(WindowType::hann, "Hann");
    window_select->insertItem(WindowType::hamm, "Hamm");
    window_select->insertItem(WindowType::bart, "Bart");
    window_select->insertItem(WindowType::black, "Black");
    formLayout->addRow(window_label, window_select);

    cutoff_1_label = new QLabel(this);
    cutoff_1_label->setText("Cutoff Frequency (Low)");
    set_cutoff_1 = new QDoubleSpinBox(this);
    set_cutoff_1->setMinimum(0);
    set_cutoff_1->setMaximum(22000);
    formLayout->addRow(cutoff_1_label, set_cutoff_1);

    cutoff_2_label = new QLabel(this);
    cutoff_2_label->setText("Cutoff Frequency (High)");
    set_cutoff_2 = new QDoubleSpinBox(this);
    set_cutoff_2->setMinimum(0);
    set_cutoff_2->setMaximum(22000);
    formLayout->addRow(cutoff_2_label, set_cutoff_2);

    connect(filter_select,SIGNAL(currentIndexChanged(int)),this,SLOT(filterTypeChanged(int)));
    connect(window_select,SIGNAL(currentIndexChanged(int)),this,SLOT(windowTypeChanged(int)));
    connect(set_cutoff_1,SIGNAL(valueChanged(double)),this,SLOT(cutoff_low_changed(double)));
    connect(set_cutoff_2,SIGNAL(valueChanged(double)),this,SLOT(cutoff_high_changed(double)));

    dialogButtons = new QDialogButtonBox(QDialogButtonBox::Ok |
        QDialogButtonBox::Cancel,
        Qt::Horizontal,this);
    formLayout->addWidget(dialogButtons);

    connect(dialogButtons, SIGNAL(accepted()),this,SLOT(accept()));
    connect(dialogButtons,SIGNAL(rejected()),this,SLOT(reject()));

    //Set Initial Values
    //TODO: Save these values outside class and pass to constructor?
    filter_select->setCurrentIndex(FilterType::LPF);
    filterTypeChanged(FilterType::LPF);
    window_select->setCurrentIndex(WindowType::rect);
    windowTypeChanged(WindowType::rect);
    set_cutoff_1->setValue(0);
    cutoff_low_changed(0);
    set_cutoff_2->setValue(22000);

    setLayout(formLayout);
    setMinimumSize(200,200);
}

FilterDialog::~FilterDialog()
{
    delete filter_label;
    delete filter_select;
    delete window_label;
    delete window_select;
    delete cutoff_1_label;
    delete set_cutoff_1;
    delete cutoff_2_label;
    delete set_cutoff_2;
    delete dialogButtons;

    filter_label = nullptr;
    filter_select = nullptr;
    window_label = nullptr;
    window_select = nullptr;
    cutoff_1_label = nullptr;
    set_cutoff_1 = nullptr;
    cutoff_2_label = nullptr;
    set_cutoff_2 = nullptr;
    dialogButtons = nullptr;
}

void FilterDialog::filterTypeChanged(int type)
{
    filterType = (FilterType) type;
    std::cout << "Filter Type Changed to: " << type << std::endl;

    bool cutoff_high_visible = (filterType == HPF || filterType == BPF || filterType == BSF);
    bool cutoff_low_visible = (filterType == LPF || filterType == BPF || filterType == BSF);
    cutoff_1_label->setVisible(cutoff_low_visible);
    set_cutoff_1->setVisible(cutoff_low_visible);
    cutoff_2_label->setVisible(cutoff_high_visible);
    set_cutoff_2->setVisible(cutoff_high_visible);

    //TODO: Implemnt backend changes
}

void FilterDialog::windowTypeChanged(int type)
{
    windowType = (WindowType) type;
    std::cout << "Window Type Changed to: " << type << std::endl;
    //TODO: Implemnt backend changes
}

void FilterDialog::cutoff_low_changed(double cutoff)
{
    cutoff_low = cutoff;
    set_cutoff_2->setMinimum(cutoff);

    std::cout << "Low Cutoff Changed to: " << cutoff << std::endl;
    //TODO: Implemnt backend changes
}

void FilterDialog::cutoff_high_changed(double cutoff)
{
    cutoff_high = cutoff;
    set_cutoff_1->setMaximum(cutoff);

    std::cout << "High Cutoff Changed to: " << cutoff << std::endl;
    //TODO: Implemnt backend changes
}
