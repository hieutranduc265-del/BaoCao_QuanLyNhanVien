#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;

// Cấu trúc dữ liệu nhân viên [cite: 19]
struct NhanVien {
    string id;
    string hoTen;
    double luongCoBan;
    double heSo;
};

// --- CÁC HÀM CHỨC NĂNG (TOP-DOWN DESIGN) [cite: 64, 66] ---

+ void nhapNhanVien(vector<NhanVien> &ds) {
    NhanVien nv;
    cout << "Nhap ID nhan vien: "; cin >> nv.id;
    cout << "Nhap Ho ten: "; cin.ignore(); getline(cin, nv.hoTen);
    
    // Xác thực dữ liệu (Validation) [cite: 36, 74]
    do {
        cout << "Nhap Luong co ban (phai >= 0): "; 
        if (!(cin >> nv.luongCoBan)) {
            cin.clear();
            cin.ignore(1000, '\n');
            nv.luongCoBan = -1;
        }
    } while (nv.luongCoBan < 0);
    
    cout << "Nhap He so luong: "; cin >> nv.heSo;
    ds.push_back(nv);
    cout << "=> Them thanh cong!" << endl;
}

+ void hienThiDanhSach(vector<NhanVien> &ds) {
    if (ds.empty()) {
        cout << "Danh sach trong!" << endl;
        return;
    }
    // Định dạng bảng đẹp mắt [cite: 38, 39, 74]
    cout << "\n" << left << setw(10) << "ID" << setw(25) << "Ho Ten" << setw(15) << "Tong Luong" << endl;
    cout << "------------------------------------------------------------" << endl;
    for (int i = 0; i < ds.size(); i++) {
        double tong = ds[i].luongCoBan * ds[i].heSo;
        cout << left << setw(10) << ds[i].id << setw(25) << ds[i].hoTen << setw(15) << (long long)tong << endl;
    }
}

+ void timKiemNangCao(vector<NhanVien> &ds) {
    string keyword;
    cout << "Nhap ten nhan vien can tim (khop mot phan): ";
    cin.ignore();
    getline(cin, keyword);
    bool thay = false;
    cout << "\nKet qua tim kiem cho '" << keyword << "':" << endl;
    for (int i = 0; i < ds.size(); i++) {
        // Tìm kiếm chuỗi con (Partial Match) 
        if (ds[i].hoTen.find(keyword) != string::npos) {
            double tong = ds[i].luongCoBan * ds[i].heSo;
            cout << "- " << ds[i].hoTen << " [ID: " << ds[i].id << "] | Luong: " << (long long)tong << endl;
            thay = true;
        }
    }
    if (!thay) cout << "Khong tim thay nhan vien nao!" << endl;
}

+ void thongKeNangCao(vector<NhanVien> &ds) {
    if (ds.empty()) return;
    double tongQuy = 0;
    int countCao = 0;
    for (int i = 0; i < ds.size(); i++) {
        double luong = ds[i].luongCoBan * ds[i].heSo;
        tongQuy += luong;
        if (luong > 15000000) countCao++; // Ví dụ lọc nhân viên lương cao > 15tr 
    }
    cout << "\n--- THONG KE ---" << endl;
    cout << "+ Tong so nhan vien: " << ds.size() << endl;
    cout << "+ Tong ngan sach chi tra: " << (long long)tongQuy << endl;
    cout << "+ So nhan vien luong cao (>15tr): " << countCao << endl;
}

+ void luuFile(vector<NhanVien> &ds) {
    ofstream f("nhanvien.txt"); // Xử lý tệp TXT [cite: 34, 46, 77]
    for (int i = 0; i < ds.size(); i++) {
        f << ds[i].id << "|" << ds[i].hoTen << "|" << ds[i].luongCoBan << "|" << ds[i].heSo << endl;
    }
    f.close();
    cout << "=> Da luu du lieu!" << endl;
}

+ void docFile(vector<NhanVien> &ds) {
    ifstream f("nhanvien.txt");
    if (!f.is_open()) return;
    ds.clear();
    string id, ten, lcb, hs;
    while (getline(f, id, '|')) {
        getline(f, ten, '|');
        getline(f, lcb, '|');
        getline(f, hs);
        ds.push_back({id, ten, stod(lcb), stod(hs)});
    }
    f.close();
}

// --- CHƯƠNG TRÌNH CHÍNH [cite: 28, 30, 31, 74] ---

int main() {
    vector<NhanVien> danhSach;
    docFile(danhSach); 
    int chon;

    while (true) {
        cout << "\n===== MENU QUAN LY NHAN VIEN =====" << endl;
        cout << "1. Them nhan vien" << endl;
        cout << "2. Hien thi danh sach" << endl;
        cout << "3. Tim kiem (Theo ten)" << endl;
        cout << "4. Thong ke nang cao" << endl;
        cout << "5. Luu file" << endl;
        cout << "0. Thoat" << endl;
        cout << "Chon chuc nang: ";
        
        if (!(cin >> chon)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Loi! Vui long nhap so." << endl;
            continue;
        }

        if (chon == 0) break;

        switch (chon) {
            case 1: nhapNhanVien(danhSach); break;
            case 2: hienThiDanhSach(danhSach); break;
            case 3: timKiemNangCao(danhSach); break;
            case 4: thongKeNangCao(danhSach); break;
            case 5: luuFile(danhSach); break;
            default: cout << "Lua chon khong hop le!" << endl;
        }
    }
    return 0;
}
