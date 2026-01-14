#include <stdio.h>

/* * --- ĐỊNH NGHĨA CẤU HÌNH HỆ THỐNG ---
 * Sơ đồ ô bạn chỉ định:
 * 10 11 12  <- Hàng 0
 * 7  8  9   <- Hàng 1
 * 4  5  6   <- Hàng 2
 * 1  2  3   <- Hàng 3 (Gốc)
 */

#define SO_COT 3
#define SO_HANG 4
#define MAX_O 12

// Cấu trúc để lưu tọa độ thực tế trên ma trận
typedef struct {
    int hang;
    int cot;
} ToaDo;

/**
 * PHẦN 1: GIẢI THUẬT GIẢI MA TRẬN
 * Hàm này biến con số 1-12 thành vị trí Hàng và Cột cụ thể.
 */
ToaDo lay_vi_tri(int id_o) {
    ToaDo pos;
    
    // Thuật toán:
    // (id_o - 1) / SO_COT: Tính xem ô đó nằm ở nhóm hàng nào (từ dưới lên)
    // (SO_HANG - 1) - ... : Đảo ngược lại để hàng 0 nằm ở trên cùng
    pos.hang = (SO_HANG - 1) - ((id_o - 1) / SO_COT);
    
    // (id_o - 1) % SO_COT: Tính vị trí cột (0, 1, hoặc 2)
    pos.cot = (id_o - 1) % SO_COT;
    
    return pos;
}

/**
 * PHẦN 2: GIẢI THUẬT ĐIỀU HƯỚNG ROBOT
 * So sánh ô hiện tại và ô tiếp theo để ra lệnh cho Motor.
 */
void phat_lenh_dieu_khien(int o_hien_tai, int o_tiep_theo) {
    ToaDo p1 = lay_vi_tri(o_hien_tai);
    ToaDo p2 = lay_vi_tri(o_tiep_theo);

    printf(" -> Lenh: ");
    if (p2.hang < p1.hang) {
        printf("DI LEN (UP)\n");
    } else if (p2.hang > p1.hang) {
        printf("DI XUONG (DOWN)\n");
    } else if (p2.cot > p1.cot) {
        printf("RE PHAI (RIGHT)\n");
    } else if (p2.cot < p1.cot) {
        printf("RE TRAI (LEFT)\n");
    } else {
        printf("DUNG TAI CHO\n");
    }
}

/**
 * PHẦN 3: CHƯƠNG TRÌNH CHÍNH
 */
int main() {
    // Đây là mảng lộ trình bạn "vẽ" ra (Robot sẽ chạy theo đúng thứ tự này)
    // Ví dụ: Đi từ 1 đến 12 theo hình zigzag
    int lo_trinh[] = {1, 2, 3, 6, 5, 4, 7, 8, 9, 12, 11, 10};
    
    // Tính số lượng ô trong lộ trình
    int tong_buoc = sizeof(lo_trinh) / sizeof(lo_trinh[0]);

    printf("=== HE THONG DIEU KHIEN ROBOT 12 O ===\n\n");

    for (int i = 0; i < tong_buoc; i++) {
        int o_nay = lo_trinh[i];
        ToaDo td = lay_vi_tri(o_nay);

        // In ra trạng thái hiện tại
        printf("[BUOC %02d]: Dang tai o %2d (Toa do mang: [%d][%d])", 
                i + 1, o_nay, td.hang, td.cot);

        // Nếu chưa phải ô cuối cùng thì tính toán hướng đi tiếp theo
        if (i < tong_buoc - 1) {
            phat_lenh_dieu_khien(o_nay, lo_trinh[i + 1]);
        } else {
            printf(" -> DA DEN DICH!\n");
        }
    }

    printf("\n====================================\n");
    return 0;
}