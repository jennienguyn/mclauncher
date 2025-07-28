<<<<<<< HEAD
# mclauncher
=======
# Minecraft Bedrock Launcher

![Giao diện ứng dụng](https://placehold.co/600x400/aabbcc/ffffff?text=Giao+diện+ứng+dụng)

Ứng dụng desktop viết bằng **C++ và Qt**, giúp quản lý và khởi chạy **Minecraft Bedrock Edition** trên máy ảo Android x86 (VirtualBox) một cách dễ dàng và tiện lợi.

---

## Tính năng chính

* **Quản lý Máy ảo (VM):** Khởi chạy, dừng và quản lý máy ảo Android x86.
* **Giao diện điều khiển động:** Hiển thị trạng thái máy ảo, tiến trình, và các nút điều khiển rõ ràng.
* **Cấu hình tài nguyên:** Cho phép chỉnh sửa RAM, CPU cấp phát cho máy ảo qua hộp thoại cài đặt.
* **Theo dõi tiến trình:** Thanh tiến trình thể hiện trạng thái khởi động của máy ảo.
* **Xem nhật ký:** Giao diện xem log chi tiết giúp phát hiện và sửa lỗi.
* **Tính năng APK:** Nút để chạy các chức năng cài đặt, quản lý APK (ví dụ "Navión APK" và "Downlusher").
* **Đa nền tảng:** Sử dụng Qt để có thể chạy trên nhiều hệ điều hành.

---

## Yêu cầu hệ thống

* **VirtualBox** đã được cài đặt.
* Ảnh máy ảo Android x86 (.vdi) đã được cấu hình sẵn cho Minecraft Bedrock.
* **Qt 6.9.1** (khuyên dùng MinGW 64-bit cho Windows).
* **Trình biên dịch MinGW-w64** (thường đi kèm Qt MinGW).
* **Git** để clone mã nguồn.
* **Visual Studio Code** (cài thêm extension C/C++ và Qt Tools).

---

## Hướng dẫn cài đặt và chạy

1. **Clone dự án:**

   ```bash
   git clone https://github.com/jennienguyn/mclauncher.git
   cd mclauncher
   ```

2. **Mở dự án trong VS Code.**

3. **Cấu hình các tệp `.vscode/c_cpp_properties.json` và `.vscode/tasks.json` cho đúng với đường dẫn Qt và MinGW của bạn.**

4. **Xây dựng dự án:**

   * Xóa các thư mục `debug/`, `release/` và tệp `.qmake.stash` nếu có (để tránh lỗi build).
   * Mở Command Palette (Ctrl+Shift+P), chọn `Tasks: Run Task`, rồi chọn `Run qmake`.
   * Tiếp tục `Tasks: Run Build Task` (Ctrl+Shift+B), chọn `Build Qt Project`.

5. **Chạy ứng dụng:** Tìm file thực thi trong thư mục `debug/` hoặc `release/` (ví dụ `mclauncher.exe`).

---

## Cách sử dụng

* Mở ứng dụng, vào **File > Settings** để cấu hình RAM và CPU cho máy ảo.
* Nhấn nút **Khởi động VM** để chạy máy ảo Android x86.
* Theo dõi trạng thái và tiến trình khởi động qua giao diện chính.
* Sử dụng các nút như **Navión APK** và **Downlusher** để cài đặt hoặc quản lý APK.
* Nhấn **Xem Log** để xem nhật ký ứng dụng khi cần xử lý sự cố.

---

## Đóng góp

Rất hoan nghênh các bạn đóng góp code, sửa lỗi hoặc thêm tính năng:

* Fork repo.
* Tạo branch mới: `git checkout -b feature/ten-tinh-nang-cua-ban`
* Commit thay đổi.
* Push lên branch.
* Tạo Pull Request.

---

## Giấy phép

Dự án được cấp phép theo [MIT License](./LICENSE).

---

## Liên hệ

GitHub: [@jennienguyn](https://github.com/jennienguyn)
>>>>>>> 7bd58b0 (v1.0)
