#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <limits>

using namespace std;

struct NhanVien {
    string id;
    string hoTen;
    double luongCoBan;
    double heSo;
};

// Ham dem so ky tu hien thi thuc te (Fix loi lech cot do Unicode)
int visualLength(string s) {
    int len = 0;
    for (int i = 0; i < s.length(); i++) {
        if ((s[i] & 0xc0) != 0x80) len++;
    }
    return len;
}

// Ham in mot o du lieu co ke vach | va can le chinh xac
void printCell(string content, int width) {
    int vLen = visualLength(content);
    int padding = width - vLen;
    cout << "| " << content << string(padding > 0 ? padding : 0, ' ');
}

void nhapNhanVien(vector<NhanVien> &ds) {
    NhanVien nv;
    cout << "Nhap ID: "; cin >> nv.id;
    cout << "Nhap Ho ten: "; cin.ignore(); getline(cin, nv.hoTen);
    do {
        cout << "Nhap Luong co ban (>=0): "; 
        if (!(cin >> nv.luongCoBan)) {
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
            nv.luongCoBan = -1;
        }
    } while (nv.luongCoBan < 0);
    cout << "Nhap He so (Dung dau CHAM '.'): "; 
    while (!(cin >> nv.heSo)) {
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Nhap lai He so (VD: 3.33): ";
    }
    ds.push_back(nv);
    cout << "=> Them thanh cong!" << endl;
}

void hienThiDanhSach(vector<NhanVien> &ds) {
    if (ds.empty()) {
        cout << "Danh sach trong!" << endl;
        return;
    }
    
    // Dinh nghia do rong cac cot
    int wID = 10, wTen = 25, wLCB = 15, wHS = 10, wTong = 15;
    string border = "+" + string(wID+1, '-') + "+" + string(wTen+1, '-') + "+" + string(wLCB+1, '-') + "+" + string(wHS+1, '-') + "+" + string(wTong+1, '-') + "+";

    cout << "\n" << border << endl;
    printCell("ID", wID); printCell("Ho Ten", wTen); printCell("Luong CB", wLCB); printCell("He so", wHS); printCell("Tong Luong", wTong);
    cout << " |" << endl << border << endl;

    for (int i = 0; i < ds.size(); i++) {
        double tong = ds[i].luongCoBan * ds[i].heSo;
        
        // Chuyen so sang chuoi de can le cho chuan
        string sLCB = to_string((long long)ds[i].luongCoBan);
        
        // Dinh dang He so lay 2 chu so thap phan
        char hsChar[20]; sprintf(hsChar, "%.2f", ds[i].heSo);
        string sHS(hsChar);
        
        string sTong = to_string((long long)tong);

        printCell(ds[i].id, wID);
        printCell(ds[i].hoTen, wTen);
        printCell(sLCB, wLCB);
        printCell(sHS, wHS);
        printCell(sTong, wTong);
        cout << " |" << endl;
    }
    cout << border << endl;
}

void timKiemNangCao(vector<NhanVien> &ds) {
    string keyword;
    cout << "Nhap ten can tim: "; cin.ignore(); getline(cin, keyword);
    bool thay = false;
    for (auto &nv : ds) {
        if (nv.hoTen.find(keyword) != string::npos) {
            cout << "Tim thay: " << nv.hoTen << " [ID: " << nv.id << "]" << endl;
            thay = true;
        }
    }
    if (!thay) cout << "Khong tim thay!" << endl;
}

void thongKeNangCao(vector<NhanVien> &ds) {
    if (ds.empty()) return;
    double tong = 0;
    for (auto &nv : ds) tong += (nv.luongCoBan * nv.heSo);
    cout << "\n--- THONG KE ---" << endl;
    cout << "+ Tong nhan vien: " << ds.size() << endl;
    cout << "+ Tong luong: " << (long long)tong << endl;
}

void luuFile(vector<NhanVien> &ds) {
    ofstream f("nhanvien.txt");
    for (auto &nv : ds) {
        f << nv.id << "|" << nv.hoTen << "|" << nv.luongCoBan << "|" << nv.heSo << endl;
    }
    f.close();
    cout << "=> Da luu file!" << endl;
}

void docFile(vector<NhanVien> &ds) {
    ifstream f("nhanvien.txt");
    if (!f.is_open()) return;
    ds.clear();
    string id, ten, lcb, hs;
    while (getline(f, id, '|')) {
        getline(f, ten, '|'); getline(f, lcb, '|'); getline(f, hs);
        try { ds.push_back({id, ten, stod(lcb), stod(hs)}); } catch (...) { continue; }
    }
    f.close();
}

int main() {
    vector<NhanVien> danhSach;
    docFile(danhSach);
    int chon;
    while (true) {
        cout << "\n1. Them | 2. Hien thi | 3. Tim kiem | 4. Thong ke | 5. Luu | 0. Thoat" << endl;
        cout << "Chon: ";
        if (!(cin >> chon)) {
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        if (chon == 0) break;
        switch (chon) {
            case 1: nhapNhanVien(danhSach); break;
            case 2: hienThiDanhSach(danhSach); break;
            case 3: timKiemNangCao(danhSach); break;
            case 4: thongKeNangCao(danhSach); break;
            case 5: luuFile(danhSach); break;
        }
    }
    return 0;
}
