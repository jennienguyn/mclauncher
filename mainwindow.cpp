#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settingsdialog.h"
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Minecraft Bedrock Launcher");

    settingsDialog = new SettingsDialog(this);

    progressTimer = new QTimer(this);
    connect(progressTimer, &QTimer::timeout, this, &MainWindow::updateProgressBar);
    currentProgress = 0;
    ui->progressBar->setValue(0);

    // Khởi tạo VirtualBoxManager
    vmManager = new VirtualBoxManager(this);
    // Kết nối các tín hiệu từ vmManager để cập nhật UI
    connect(vmManager, &VirtualBoxManager::vmOperationStarted, this, &MainWindow::onVmOperationStarted);
    connect(vmManager, &VirtualBoxManager::vmOperationProgress, this, &MainWindow::onVmOperationProgress);
    connect(vmManager, &VirtualBoxManager::onVmOperationFinished, this, &MainWindow::onVmOperationFinished);


    if (ui->vmControlsGroup) {
        ui->vmControlsGroup->setVisible(false);
    }
    ui->vmStatusLabel->setText("Trạng thái VM: Đang chờ khởi động...");

    connect(ui->launchButton, &QPushButton::clicked, this, &MainWindow::on_launchButton_clicked);
    if (ui->actionSettings) {
        connect(ui->actionSettings, &QAction::triggered, this, &MainWindow::on_actionSettings_triggered);
    }
    connect(ui->viewLogButton, &QPushButton::clicked, this, &MainWindow::on_viewLogButton_clicked);

    if (ui->actionAbout) {
        connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::on_actionAbout_triggered);
    }
}

MainWindow::~MainWindow() {
    delete ui;
    delete vmManager; // Giải phóng vmManager
}

void MainWindow::on_launchButton_clicked() {
    qDebug() << "Nút Launch đã được nhấp!";
    ui->vmStatusLabel->setText("Trạng thái VM: Đang khởi động...");
    currentProgress = 0;
    ui->progressBar->setValue(0);
    updateVmControlsVisibility(false);
    vmManager->startAndroidX86VM("AndroidX86VM", "C:/path/to/your/android_x86.vdi");
}

void MainWindow::on_actionSettings_triggered() {
    qDebug() << "Hành động Settings trong Menu Bar đã được kích hoạt!";
    settingsDialog->exec();
}

void MainWindow::on_viewLogButton_clicked() {
    qDebug() << "Nút Xem Log đã được nhấp!";
    QMessageBox::information(this, "Log ứng dụng", "Đây là nơi hiển thị log của ứng dụng.");
}

void MainWindow::updateProgressBar() {

}

void MainWindow::updateVmControlsVisibility(bool ready) {
    if (ui->vmControlsGroup) {
        ui->vmControlsGroup->setVisible(ready);
    }
}

void MainWindow::on_actionAbout_triggered() {
    qDebug() << "Hành động About đã được kích hoạt!";
    QMessageBox::about(this, "Giới thiệu Minecraft Bedrock Launcher",
                       "<h2>Minecraft Bedrock Launcher v1.0</h2>"
                       "<p>Ứng dụng này giúp bạn quản lý và khởi chạy máy ảo cho Minecraft Bedrock.</p>"
                       "<p>Phát triển bởi: jennienguyn</p>"
                       "<p>Phiên bản Qt: 6.9.1</p>"
                       "<p>Năm: 2025</p>");
}

// Triển khai các khe cắm mới từ VirtualBoxManager
void MainWindow::onVmOperationStarted(const QString& operation) {
    ui->vmStatusLabel->setText(QString("Trạng thái VM: %1...").arg(operation));
    ui->progressBar->setValue(0);
    updateVmControlsVisibility(false);
    qDebug() << "Thao tác VM bắt đầu:" << operation;
}

void MainWindow::onVmOperationProgress(const QString& operation, int progress) {
    ui->progressBar->setValue(progress);
    ui->vmStatusLabel->setText(QString("Trạng thái VM: %1 (%2%%)...").arg(operation).arg(progress));
    qDebug() << "Tiến trình VM:" << operation << progress << "%";
}

void MainWindow::onVmOperationFinished(const QString& operation, bool success, const QString& message) {
    ui->progressBar->setValue(success ? 100 : 0);
    if (success) {
        ui->vmStatusLabel->setText(QString("Trạng thái VM: %1 hoàn tất!").arg(operation));
        updateVmControlsVisibility(true);
        qDebug() << "Thao tác VM hoàn tất thành công:" << operation;
    } else {
        ui->vmStatusLabel->setText(QString("Trạng thái VM: %1 thất bại! Lỗi: %2").arg(operation).arg(message));
        updateVmControlsVisibility(false);
        qDebug() << "Thao tác VM thất bại:" << operation << "Lỗi:" << message;
        QMessageBox::critical(this, "Lỗi VM", QString("Thao tác VM '%1' thất bại:\n%2").arg(operation).arg(message));
    }
}