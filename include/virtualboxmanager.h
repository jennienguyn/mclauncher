#ifndef VIRTUALBOXMANAGER_H
#define VIRTUALBOXMANAGER_H

#include <QObject>
#include <QString>
#include <QProcess> // Để chạy các lệnh VBoxManage

// KHAI BÁO QUAN TRỌNG:
// Để sử dụng VirtualBox SDK C++ API, bạn sẽ cần các tệp tiêu đề được tạo từ các tệp IDL của VirtualBox.
// Ví dụ: IVirtualBox.h, IMachine.h, ISession.h, v.v.
// Việc này thường đòi hỏi quá trình "IDL compilation" (ví dụ: bằng midl.exe trên Windows)
// và thiết lập build phức tạp để liên kết với các thư viện COM/SDK của VirtualBox.
// Các dòng include dưới đây chỉ là ví dụ và sẽ không hoạt động nếu bạn chưa thiết lập SDK đúng cách.
// #include <VBox/COM/VirtualBox.h>
// #include <VBox/COM/VirtualBox_c.h>
// #include <VBox/COM/VirtualBox_i.h>
// #include <VBox/COM/VirtualBox_idl.h> // Đây là tệp IDL, cần được biên dịch

class VirtualBoxManager : public QObject {
    Q_OBJECT

public:
    explicit VirtualBoxManager(QObject *parent = nullptr);
    ~VirtualBoxManager();

    // Hàm để khởi động VM
    void startAndroidX86VM(const QString& vmName, const QString& vdiPath);

    // Hàm để tạo snapshot (ví dụ: "CleanOS")
    void takeSnapshot(const QString& vmName, const QString& snapshotName);

    // Hàm để cấu hình mạng NAT (ví dụ: cho một VM hiện có)
    void configureNatNetwork(const QString& vmName);

signals:
    // Tín hiệu để thông báo trạng thái hoạt động của VM
    void vmOperationStarted(const QString& operation);
    void vmOperationProgress(const QString& operation, int progress);
    void vmOperationFinished(const QString& operation, bool success, const QString& message);

private:
    // Các hàm trợ giúp để chạy lệnh VBoxManage
    void runVBoxManageCommand(const QStringList& args, const QString& operationName);
    void handleVBoxManageOutput(const QString& operationName, int exitCode, QProcess::ExitStatus exitStatus, const QString& stdOutput, const QString& stdError);

    // Bạn sẽ cần các biến thành viên để giữ các đối tượng SDK VirtualBox
    // Ví dụ: IVirtualBox* m_vbox;
    //        IMachine* m_machine;
    //        ISession* m_session;
};

#endif 
