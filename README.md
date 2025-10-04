This is a tool that helps you manage your class members.
Đây là một công cụ giúp bạn có thể quản lý các thành viên trong lớp 

📌 Yêu cầu hệ thống (System Requirements)

Hệ điều hành: Windows 7/8/10/11

Trình biên dịch: g++ (MinGW) / MSVC / Code::Blocks / Dev-C++

C++11 trở lên

🚀 Cách chạy chương trình
1️⃣ Chạy bằng CMD + MinGW

Cài đặt MinGW
.

Trong quá trình cài, tick chọn g++.

Thêm C:\MinGW\bin vào Environment Variables → PATH.

Mở CMD trong thư mục chứa file app.cpp.

Compile chương trình:

g++ app.cpp -o app.exe


Chạy chương trình:

app.exe

2️⃣ Chạy trực tiếp file .exe

Sau khi compile, trong thư mục sẽ có file app.exe.

Chỉ cần double-click vào app.exe là chạy ứng dụng như phần mềm bình thường.

Nếu cửa sổ tự tắt ngay, hãy thêm dòng sau vào cuối main:

system("pause");

3️⃣ Chạy bằng Batch file (.bat)

Tạo 1 file run.bat trong cùng thư mục với nội dung:

@echo off
g++ app.cpp -o app.exe
app.exe
pause


Sau đó chỉ cần double-click run.bat → chương trình sẽ tự compile và chạy.

4️⃣ Chạy bằng IDE

Nếu dùng Code::Blocks / Dev-C++ / Visual Studio Code:

Mở app.cpp trong IDE.

Nhấn Run (F9 hoặc Ctrl+F5) để chạy chương trình.

📝 Tính năng

✅ Thêm sinh viên (ID, Họ tên, Lớp, GPA ≤ 4)

✅ Hiển thị danh sách sinh viên

✅ Xóa sinh viên

✅ Chỉnh sửa/bổ sung thông tin sinh viên

✅ Xuất dữ liệu ra file student.xlsx