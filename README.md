
# Flappy Bird Clone (C++ & SDL2)

Dự án là một phiên bản clone của tựa game **Flappy Bird**, được lập trình bằng **C++** và sử dụng thư viện **SDL2**.

---

## Cấu trúc thư mục

```
.
├── assets/                 # Thư mục chứa hình ảnh, âm thanh
├── bin/Debug               # Output build
├── obj/Debug               # Object files
├── src/                    # Mã nguồn chính chia thành nhiều module:
│   ├── Animation/          # Xử lý hoạt ảnh
│   ├── Camera/             # Điều khiển camera
│   ├── Characters/         # Định nghĩa nhân vật
│   ├── Collision/          # Va chạm
│   ├── Core/               # Core game logic
│   ├── Graphics/           # Hiển thị hình ảnh
│   ├── Input/              # Nhận input từ bàn phím hoặc chuột
│   ├── Map/                # Xử lý bản đồ, địa hình
│   ├── Object/             # Object cơ bản của game
│   ├── Physics/            # Vật lý game: trọng lực, va chạm
│   ├── SoundManager/       # Quản lý âm thanh
│   ├── State/              # Quản lý các state của game
│   ├── Vendor/TinyXML/     # Thư viện XML
│   └── Widgets/            # Các thành phần UI
├── main.cpp                # Hàm main khởi chạy game
├── Flappy_Bird.cbp         # Dự án Code::Blocks
├── *.dll                   # Thư viện SDL2 runtime
```

---

## Hướng dẫn build

### Yêu cầu:

- C++ compiler (g++/clang/MSVC)
- SDL2
- SDL2_image
- SDL2_ttf
- SDL2_mixer

### Build với Code::Blocks:
1. Mở file `Flappy_Bird.cbp` bằng Code::Blocks IDE.
2. Build và Run (F9).

### Build thủ công bằng terminal (g++ ví dụ):
```bash
g++ -std=c++17 -I./src -I./src/Vendor/TinyXML \
    src/**/*.cpp main.cpp -o FlappyBird \
    -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
```

---

## Gameplay

- **Nhấn Space** để giúp chú chim bay lên.
- Tránh các ống cống, nếu va vào sẽ game over.
- Ghi điểm mỗi khi bay qua một ống thành công.
- **Mục tiêu**: đạt được số điểm cao nhất có thể!

---

## Giấy phép

Dự án học tập - **phi thương mại**. Tự do chỉnh sửa và sử dụng cho mục đích học tập và cá nhân.

---

## Ghi chú thêm

- Có thể cần cấu hình lại đường dẫn asset nếu chạy trên hệ điều hành khác.
- Nếu gặp lỗi thiếu `.dll` thì đảm bảo các file như `SDL2.dll`, `SDL2_image.dll`, `SDL2_mixer.dll`, `SDL2_ttf.dll` nằm cùng thư mục với file thực thi.

---

## Thư viện bên thứ ba

- **Vendor/TinyXML/**: chứa mã nguồn của thư viện [**TinyXML**](https://sourceforge.net/projects/tinyxml/)
  
  > Nguồn gốc: Tải từ [https://sourceforge.net/projects/tinyxml/](https://sourceforge.net/projects/tinyxml/)
