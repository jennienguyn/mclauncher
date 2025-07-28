#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog {
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = nullptr);
    ~SettingsDialog();

    int getRamValue() const;
    int getCpuValue() const;

private slots:
    void on_ramSlider_valueChanged(int value);
    void on_ramSpinBox_valueChanged(int value);
    void on_cpuSlider_valueChanged(int value);
    void on_cpuSpinBox_valueChanged(int value);

private:
    Ui::SettingsDialog *ui;
};

#endif // SETTINGSDIALOG_H