import tkinter as tk
from tkinter import messagebox
import time
import threading

# --- CẤU HÌNH HỆ THỐNG ---
WIDTH = 3
HEIGHT = 4
drawn_path = [] # Mảng lưu lộ trình (C-style array)
buttons = {}    # Lưu trữ các ô để đổi màu

class RobotApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Robot 12 Cells Demo - C Style")
        self.is_running = False
        
        # Tiêu đề
        tk.Label(root, text="VẼ ĐƯỜNG ĐI (1-12)", font=('Arial', 14, 'bold')).pack(pady=10)
        
        # Khung chứa ma trận
        self.grid_frame = tk.Frame(root)
        self.grid_frame.pack(pady=10, padx=20)
        
        self.create_grid()
        
        # Nút điều khiển
        btn_frame = tk.Frame(root)
        btn_frame.pack(pady=20)
        
        tk.Button(btn_frame, text="CHẠY ROBOT", font=('Arial', 10, 'bold'), 
                  bg="#4CAF50", fg="white", command=self.start_thread).pack(side=tk.LEFT, padx=5)
        
        tk.Button(btn_frame, text="XÓA HẾT", font=('Arial', 10, 'bold'), 
                  bg="#f44336", fg="white", command=self.reset_path).pack(side=tk.LEFT, padx=5)
        
        # Hiển thị mảng tọa độ bên dưới
        self.status_label = tk.Label(root, text="Mảng: []", font=('Courier', 10), fg="blue")
        self.status_label.pack(pady=5)

    def create_grid(self):
        """Tạo lưới 12 ô theo sơ đồ 10 11 12 ... 1 2 3"""
        for r in range(HEIGHT):
            for c in range(WIDTH):
                # Tính số ô dựa theo yêu cầu của bạn
                cell_num = (HEIGHT - 1 - r) * WIDTH + (c + 1)
                
                btn = tk.Button(self.grid_frame, text=f"{cell_num}", width=8, height=4,
                                font=('Arial', 10, 'bold'), bg="white",
                                command=lambda n=cell_num: self.toggle_cell(n))
                btn.grid(row=r, column=c, padx=2, pady=2)
                buttons[cell_num] = btn

    def toggle_cell(self, n):
        if self.is_running: return
        
        if n in drawn_path:
            drawn_path.remove(n)
            buttons[n].config(bg="white", fg="black", text=f"{n}")
        else:
            drawn_path.append(n)
            step = len(drawn_path)
            buttons[n].config(bg="#2196F3", fg="white", text=f"{n}\n(BƯỚC {step})")
        
        self.status_label.config(text=f"Mảng: {drawn_path}")

    def start_thread(self):
        if not drawn_path:
            messagebox.showwarning("Chú ý", "Vui lòng vẽ đường đi trước!")
            return
        if self.is_running: return
        
        # Chạy robot trong một luồng riêng để không bị treo giao diện
        threading.Thread(target=self.run_robot, daemon=True).start()

    def run_robot(self):
        self.is_running = True
        
        # Giải thuật ma trận: Duyệt qua mảng lộ trình
        for i, cell in enumerate(drawn_path):
            # Hiệu ứng Robot đang ở ô hiện tại (Màu đỏ)
            original_color = buttons[cell].cget("bg")
            buttons[cell].config(bg="#FF5722")
            
            time.sleep(0.7) # Tốc độ robot
            
            # Sau khi đi qua thì trả lại màu xanh của lộ trình
            buttons[cell].config(bg="#2196F3")
            
        messagebox.showinfo("Xong", "Robot đã đi hết 12 ô chỉ định!")
        self.is_running = False

    def reset_path(self):
        drawn_path.clear()
        self.is_running = False
        for n in buttons:
            buttons[n].config(bg="white", fg="black", text=f"{n}")
        self.status_label.config(text="Mảng: []")

# --- CHẠY CHƯƠNG TRÌNH ---
if __name__ == "__main__":
    root = tk.Tk()
    app = RobotApp(root)
    root.mainloop()