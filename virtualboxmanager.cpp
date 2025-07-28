#include "virtualboxmanager.h"
#include <QDebug>
#include <QMessageBox> // Để hiển thị lỗi nếu cần
#include <QTimer> // Đã thêm include này để khắc phục lỗi "incomplete type QTimer"

// KHAI BÁO QUAN TRỌNG:
// Các dòng include và khởi tạo SDK thực tế sẽ ở đây.
// Việc này có thể bao gồm việc khởi tạo COM (CoInitializeEx),
// tạo các đối tượng VirtualBox COM (ví dụ: CoCreateInstance),
// và xử lý các giao diện (interfaces) của SDK.
// Đây là phần phức tạp nhất và yêu cầu bạn tham khảo tài liệu SDK.

VirtualBoxManager::VirtualBoxManager(QObject *parent) : QObject(parent) {
    qDebug() << "VirtualBoxManager được khởi tạo.";
    // KHỞI TẠO SDK THỰC TẾ SẼ Ở ĐÂY
    // Ví dụ:
    // HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
    // if (FAILED(hr)) {
    //     qWarning() << "Không thể khởi tạo COM:" << hr;
    // }
    // hr = CoCreateInstance(CLSID_VirtualBox, NULL, CLSCTX_LOCAL_SERVER, IID_IVirtualBox, (void**)&m_vbox);
    // if (FAILED(hr) || !m_vbox) {
    //     qWarning() << "Không thể tạo đối tượng VirtualBox:" << hr;
    // }
}

VirtualBoxManager::~VirtualBoxManager() {
    qDebug() << "VirtualBoxManager bị hủy.";
    // GIẢI PHÓNG SDK THỰC TẾ SẼ Ở ĐÂY
    // Ví dụ:
    // if (m_vbox) m_vbox->Release();
    // CoUninitialize();
}

void VirtualBoxManager::startAndroidX86VM(const QString& vmName, const QString& vdiPath) {
    emit vmOperationStarted("Khởi động VM");
    qDebug() << "Đang cố gắng khởi động VM:" << vmName << "với VDI:" << vdiPath;

    // PHẦN NÀY SẼ SỬ DỤNG VIRTUALBOX SDK THỰC TẾ.
    // Dưới đây là ví dụ sử dụng VBoxManage (công cụ dòng lệnh) để mô phỏng.
    // Sử dụng SDK C++ API sẽ hiệu quả và mạnh mẽ hơn nhiều.

    QStringList args;
    // 1. Đăng ký VM nếu chưa có (nếu bạn tạo VM mới)
    // args << "registervm" << vmName; runVBoxManageCommand(args, "Đăng ký VM");

    // 2. Tạo VM mới và gắn VDI (nếu VM chưa tồn tại)
    // args.clear(); args << "createvm" << "--name" << vmName << "--ostype" << "Other_64" << "--register"; runVBoxManageCommand(args, "Tạo VM");
    // args.clear(); args << "storagectl" << vmName << "--name" << "SATA Controller" << "--add" << "sata" << "--controller" << "IntelAHCI"; runVBoxManageCommand(args, "Thêm SATA Controller");
    // args.clear(); args << "storageattach" << vmName << "--storagectl" << "SATA Controller" << "--port" << "0" << "--device" << "0" << "--type" << "hdd" << "--medium" << vdiPath; runVBoxManageCommand(args, "Gắn VDI");

    // 3. Cấu hình mạng NAT (nếu chưa cấu hình)
    // configureNatNetwork(vmName);

    // 4. Cấu hình RAM và CPU (lấy từ SettingsDialog nếu muốn)
    // args.clear(); args << "modifyvm" << vmName << "--memory" << "2048" << "--cpus" << "2"; runVBoxManageCommand(args, "Cấu hình RAM/CPU");

    // 5. Khởi động VM headless
    args.clear();
    args << "startvm" << vmName << "--type" << "headless";
    runVBoxManageCommand(args, "Khởi động headless");

    // CẬP NHẬT TIẾN TRÌNH (ví dụ mô phỏng)
    // Trong SDK thực tế, bạn sẽ nhận được các sự kiện tiến trình từ các thao tác IProgress.
    QTimer::singleShot(1000, [this, vmName]() { // Mô phỏng tiến trình
        emit vmOperationProgress("Khởi động VM", 25);
        QTimer::singleShot(1000, [this, vmName]() {
            emit vmOperationProgress("Khởi động VM", 50);
            QTimer::singleShot(1000, [this, vmName]() {
                emit vmOperationProgress("Khởi động VM", 75);
                QTimer::singleShot(1000, [this, vmName]() {
                    emit vmOperationProgress("Khởi động VM", 100);
                    emit vmOperationFinished("Khởi động VM", true, "VM đã khởi động thành công!");
                });
            });
        });
    });

    // VỚI SDK THỰC TẾ, BẠN SẼ LÀM NHƯ SAU:
    // IVirtualBox* vbox = ...; // Lấy đối tượng VirtualBox
    // IMachine* machine = NULL;
    // HRESULT hr = vbox->FindMachine(BSTR(vmName.toStdWString().c_str()), &machine);
    // if (FAILED(hr) || !machine) { emit vmOperationFinished("Khởi động VM", false, "Không tìm thấy VM."); return; }
    // ISession* session = NULL;
    // hr = vbox->OpenSession(machine, &session, BSTR("headless"), NULL);
    // if (FAILED(hr) || !session) { emit vmOperationFinished("Khởi động VM", false, "Không thể mở session."); return; }
    // IProgress* progress = NULL;
    // hr = session->GetConsole()->PowerUp(&progress, NULL);
    // if (FAILED(hr) || !progress) { emit vmOperationFinished("Khởi động VM", false, "Không thể bật nguồn VM."); return; }
    // progress->WaitForCompletion(-1); // Chờ hoàn tất
    // long result; progress->GetResultCode(&result);
    // if (result == 0) { emit vmOperationFinished("Khởi động VM", true, "VM đã khởi động thành công!"); }
    // else { emit vmOperationFinished("Khởi động VM", false, "Lỗi khi bật nguồn VM."); }
    // progress->Release();
    // session->Release();
    // machine->Release();
}

void VirtualBoxManager::takeSnapshot(const QString& vmName, const QString& snapshotName) {
    emit vmOperationStarted("Tạo Snapshot");
    qDebug() << "Đang tạo snapshot cho VM:" << vmName << "Tên snapshot:" << snapshotName;

    QStringList args;
    args << "snapshot" << vmName << "take" << snapshotName << "--description" << "Snapshot sạch của HĐH.";
    runVBoxManageCommand(args, "Tạo Snapshot");

    // Mô phỏng tiến trình
    QTimer::singleShot(1000, [this]() {
        emit vmOperationProgress("Tạo Snapshot", 50);
        QTimer::singleShot(1000, [this]() {
            emit vmOperationProgress("Tạo Snapshot", 100);
            emit vmOperationFinished("Tạo Snapshot", true, "Snapshot đã được tạo thành công!");
        });
    });
}

void VirtualBoxManager::configureNatNetwork(const QString& vmName) {
    emit vmOperationStarted("Cấu hình mạng NAT");
    qDebug() << "Đang cấu hình mạng NAT cho VM:" << vmName;

    QStringList args;
    // Cấu hình Adapter 1 thành NAT
    args << "modifyvm" << vmName << "--nic1" << "nat";
    runVBoxManageCommand(args, "Cấu hình mạng NAT");

    // Mô phỏng tiến trình
    QTimer::singleShot(500, [this]() {
        emit vmOperationProgress("Cấu hình mạng NAT", 100);
        emit vmOperationFinished("Cấu hình mạng NAT", true, "Mạng NAT đã được cấu hình thành công!");
    });
}

void VirtualBoxManager::runVBoxManageCommand(const QStringList& args, const QString& operationName) {
    QProcess *process = new QProcess(this);
    process->setProgram("VBoxManage"); // Đảm bảo VBoxManage có trong PATH

    // Kết nối tín hiệu finished() để xử lý kết quả
    connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            this, [this, process, operationName](int exitCode, QProcess::ExitStatus exitStatus) {
        QString stdOutput = process->readAllStandardOutput();
        QString stdError = process->readAllStandardError();
        handleVBoxManageOutput(operationName, exitCode, exitStatus, stdOutput, stdError);
        process->deleteLater(); // Xóa đối tượng QProcess sau khi hoàn tất
    });

    process->setArguments(args);
    process->start();

    if (!process->waitForStarted()) {
        emit vmOperationFinished(operationName, false, "Không thể khởi động tiến trình VBoxManage. Đảm bảo VirtualBox được cài đặt và VBoxManage có trong PATH.");
        process->deleteLater();
    }
}

void VirtualBoxManager::handleVBoxManageOutput(const QString& operationName, int exitCode, QProcess::ExitStatus exitStatus, const QString& stdOutput, const QString& stdError) {
    if (exitStatus == QProcess::NormalExit && exitCode == 0) {
        qDebug() << "VBoxManage Output (Thành công):" << stdOutput;
        // Các tín hiệu vmOperationProgress và vmOperationFinished sẽ được gọi từ các hàm gọi runVBoxManageCommand
    } else {
        qWarning() << "VBoxManage Output (Lỗi):" << stdOutput;
        qWarning() << "VBoxManage Error (Lỗi):" << stdError;
        emit vmOperationFinished(operationName, false, stdError.isEmpty() ? stdOutput : stdError);
    }
}