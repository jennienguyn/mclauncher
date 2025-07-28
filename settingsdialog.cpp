#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent)
    : QDialog(parent),
      ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

    setWindowTitle("Cài đặt");

    connect(ui->ramSlider, &QSlider::valueChanged, ui->ramSpinBox, &QSpinBox::setValue);
    connect(ui->ramSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), ui->ramSlider, &QSlider::setValue);

    connect(ui->cpuSlider, &QSlider::valueChanged, ui->cpuSpinBox, &QSpinBox::setValue);
    connect(ui->cpuSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), ui->cpuSlider, &QSpinBox::setValue);

    ui->ramSlider->setValue(4);
    ui->cpuSlider->setValue(2);
}

SettingsDialog::~SettingsDialog() {
    delete ui;
}

int SettingsDialog::getRamValue() const {
    return ui->ramSpinBox->value();
}

int SettingsDialog::getCpuValue() const {
    return ui->cpuSpinBox->value();
}