#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QMessageBox>
#include "virtualboxmanager.h"

namespace Ui {
class MainWindow;
}

class SettingsDialog;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_launchButton_clicked();
    void on_actionSettings_triggered();
    void on_viewLogButton_clicked();
    void updateProgressBar();
    void on_actionAbout_triggered();

    void onVmOperationStarted(const QString& operation);
    void onVmOperationProgress(const QString& operation, int progress);
    void onVmOperationFinished(const QString& operation, bool success, const QString& message);

private:
    Ui::MainWindow *ui;
    SettingsDialog *settingsDialog;
    QTimer *progressTimer;
    int currentProgress;
    VirtualBoxManager *vmManager;

    void updateVmControlsVisibility(bool ready);
};

#endif