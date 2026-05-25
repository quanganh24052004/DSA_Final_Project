# Hướng dẫn Cài đặt và Chạy Dự án Final_Project_DSA

Dự án này là một ứng dụng quản lý sinh viên chạy trên giao diện dòng lệnh (CLI), được viết bằng **C++** và sử dụng **CMake** để quản lý biên dịch.

## Yêu cầu Hệ thống (Prerequisites)
- Trình biên dịch C++ hỗ trợ chuẩn **C++11** trở lên.
- **CMake** (phiên bản 3.10 trở lên).

---

## 🍎 Hướng dẫn chạy trên macOS (hoặc Linux)

### Cách 1: Sử dụng Terminal (Khuyên dùng)

1. **Mở Terminal** và di chuyển vào thư mục gốc của dự án:
   ```bash
   cd /đường/dẫn/đến/thư/mục/Final_Project_DSA
   ```

2. **Xóa bộ nhớ đệm CMake cũ (nếu có)** 
   Nếu bạn gặp lỗi `CMakeCache.txt is different than the directory...` khi di chuyển hoặc đổi tên thư mục dự án, hãy xóa các file sinh ra trước đó:
   ```bash
   rm -rf build CMakeCache.txt CMakeFiles
   ```

3. **Tạo thư mục build và di chuyển vào đó**:
   ```bash
   mkdir -p build
   cd build
   ```

4. **Sinh cấu hình build bằng CMake**:
   ```bash
   cmake ..
   ```

5. **Biên dịch dự án**:
   ```bash
   make
   ```

6. **Chạy chương trình**:
   Sau khi biên dịch thành công, chạy file thực thi:
   ```bash
   ./Final_Project_DSA
   ```

### Cách 2: Sử dụng Xcode
Nếu bạn đã cài đặt Xcode, bạn có thể nhấp đúp vào tệp `Final_Project_DSA.xcodeproj` để mở dự án bằng Xcode, sau đó nhấn biểu tượng **Run (▶)** (hoặc tổ hợp phím `Cmd + R`) để chạy.

---

## 🪟 Hướng dẫn chạy trên Windows

Trên Windows, bạn có hai cách phổ biến để biên dịch dự án CMake: sử dụng **Visual Studio** hoặc sử dụng **MinGW (GCC)**.

### Cách 1: Sử dụng Visual Studio (Khuyên dùng nếu đã cài đặt)
*Yêu cầu: Đã cài đặt Visual Studio với tính năng "Desktop development with C++".*

1. **Sử dụng Visual Studio IDE**:
   - Mở Visual Studio.
   - Chọn **"Open a local folder"** và chọn thư mục gốc của dự án `Final_Project_DSA`.
   - Visual Studio sẽ tự động nhận diện file `CMakeLists.txt` và cấu hình dự án.
   - Sau khi cấu hình xong, bạn chọn mục tiêu (target) là `Final_Project_DSA` trên thanh công cụ và nhấn nút **Run (▶)** có biểu tượng nút Play màu xanh lá cây.

2. **Sử dụng Developer Command Prompt**:
   - Mở **x64 Native Tools Command Prompt for VS**.
   - Di chuyển đến thư mục dự án:
     ```cmd
     cd đường\dẫn\đến\Final_Project_DSA
     ```
   - Tạo thư mục build và cấu hình:
     ```cmd
     mkdir build
     cd build
     cmake ..
     ```
   - Biên dịch dự án:
     ```cmd
     cmake --build . --config Release
     ```
   - Chạy chương trình:
     ```cmd
     Release\Final_Project_DSA.exe
     ```

### Cách 2: Sử dụng MinGW (GCC) & CMake trên Command Prompt/PowerShell
*Yêu cầu: Đã cài đặt MinGW-w64 (có `g++` và `mingw32-make`) và CMake, đồng thời đã thêm chúng vào biến môi trường PATH.*

1. Mở **Command Prompt** hoặc **PowerShell** và di chuyển vào thư mục dự án:
   ```cmd
   cd đường\dẫn\đến\Final_Project_DSA
   ```

2. Tạo thư mục build:
   ```cmd
   mkdir build
   cd build
   ```

3. Cấu hình CMake để sử dụng MinGW Makefiles:
   ```cmd
   cmake -G "MinGW Makefiles" ..
   ```

4. Biên dịch dự án:
   ```cmd
   mingw32-make
   ```

5. Chạy chương trình:
   ```cmd
   Final_Project_DSA.exe
   ```

---

## 💡 Lưu ý chung
- **Lỗi Cache**: Nếu bạn copy thư mục dự án từ máy tính này sang máy tính khác hoặc đổi tên thư mục, CMake sẽ báo lỗi về Cache. Cách khắc phục là xóa thư mục `build` (và file `CMakeCache.txt` ngoài thư mục gốc nếu có) rồi chạy lại lệnh `cmake ..` hoặc cấu hình lại từ đầu.
- **Dữ liệu mẫu**: Chương trình sẽ tự động copy file `students.csv` vào thư mục build để bạn có thể tải dữ liệu một cách dễ dàng khi chạy chương trình (Bấm phím `1` -> Enter).
