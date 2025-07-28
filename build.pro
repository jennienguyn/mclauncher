QT       += widgets

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    settingsdialog.cpp \
    virtualboxmanager.cpp

HEADERS += \
    include/mainwindow.h \
    include/settingsdialog.h \
    include/virtualboxmanager.h

FORMS += \
    mainwindow.ui \
    settingsdialog.ui

# QUAN TRỌNG: Thêm thư mục build vào INCLUDEPATH để tìm ui_*.h
# ${OUT_PWD} là biến của qmake trỏ đến thư mục build hiện tại (ví dụ: debug/ hoặc release/)
INCLUDEPATH += ${OUT_PWD}

# QUAN TRỌNG: Cấu hình liên kết với VirtualBox SDK (COM)
# Đối với MinGW, việc liên kết với các thư viện COM của Windows có thể phức tạp hơn.
# Nếu bạn cần các chức năng COM cấp thấp, bạn có thể cần tìm các thư viện tương thích MinGW
# hoặc sử dụng các wrapper.
# Hiện tại, chúng ta đang sử dụng VBoxManage (công cụ dòng lệnh) nên các thư viện này không cần thiết.
# ĐÃ XÓA: LIBS += -lole32 -loleaut32 -luuid

# Đường dẫn đến các tệp tiêu đề được tạo từ IDL của VirtualBox SDK
INCLUDEPATH += "${workspaceFolder}/include"

# Không cần QMAKE_CXXFLAGS và QMAKE_LFLAGS dành riêng cho MSVC nữa.