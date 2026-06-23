#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
using namespace std;

struct SanBong {
    int maSan;
    string tenSan;
    string loaiSan;
    long long giaMoiGio;
};

struct DatSan {
    int maDat;
    int maSan;
    string tenKhach;
    string ngay;        // dang: dd/mm/yyyy
    int gioBatDau;
    int gioKetThuc;
    bool daHuy;
    bool daThanhToan;
};

vector<SanBong> dsSan = {
    {1, "San A", "5 nguoi", 200000},
    {2, "San B", "7 nguoi", 300000},
    {3, "San C", "11 nguoi", 500000}
};

vector<DatSan> dsDat;
int maDatTuDong = 1;

void boQuaEnter() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

SanBong* timSan(int maSan) {
    for (auto &s : dsSan)
        if (s.maSan == maSan) return &s;
    return nullptr;
}

long long tinhTien(const DatSan &d) {
    SanBong *s = timSan(d.maSan);
    if (s == nullptr) return 0;
    return (d.gioKetThuc - d.gioBatDau) * s->giaMoiGio;
}

bool biTrungLich(int maSan, string ngay, int bd, int kt) {
    for (auto d : dsDat) {
        if (!d.daHuy && d.maSan == maSan && d.ngay == ngay) {
            if (max(bd, d.gioBatDau) < min(kt, d.gioKetThuc))
                return true;
        }
    }
    return false;
}

void hienThiSan() {
    cout << "\n--- DANH SACH SAN ---\n";
    for (auto s : dsSan) {
        cout << "Ma san: " << s.maSan
             << " | Ten: " << s.tenSan
             << " | Loai: " << s.loaiSan
             << " | Gia: " << s.giaMoiGio << " VND/gio\n";
    }
}

void kiemTraLichTrong() {
    int maSan, bd, kt;
    string ngay;

    cout << "\nNhap ma san: "; 
    cin >> maSan;
    cout << "Nhap ngay dd/mm/yyyy: ";
    cin >> ngay;
    cout << "Nhap gio bat dau: ";
    cin >> bd;
    cout << "Nhap gio ket thuc: ";
    cin >> kt;

    if (timSan(maSan) == nullptr || bd >= kt) {
        cout << "Thong tin khong hop le!\n";
        return;
    }

    if (biTrungLich(maSan, ngay, bd, kt))
        cout << "San da co nguoi dat trong khung gio nay.\n";
    else
        cout << "San con trong, co the dat.\n";
}

void datSan() {
    DatSan d;

    hienThiSan();

    cout << "\nNhap ma san muon dat: ";
    cin >> d.maSan;

    if (timSan(d.maSan) == nullptr) {
        cout << "Ma san khong ton tai!\n";
        return;
    }

    boQuaEnter();
    cout << "Nhap ten khach hang: ";
    getline(cin, d.tenKhach);

    cout << "Nhap ngay dd/mm/yyyy: ";
    cin >> d.ngay;
    cout << "Nhap gio bat dau: ";
    cin >> d.gioBatDau;
    cout << "Nhap gio ket thuc: ";
    cin >> d.gioKetThuc;

    if (d.gioBatDau >= d.gioKetThuc) {
        cout << "Gio dat khong hop le!\n";
        return;
    }

    if (biTrungLich(d.maSan, d.ngay, d.gioBatDau, d.gioKetThuc)) {
        cout << "Dat san that bai! San da co nguoi dat.\n";
        return;
    }

    d.maDat = maDatTuDong++;
    d.daHuy = false;
    d.daThanhToan = false;
    dsDat.push_back(d);

    cout << "Dat san thanh cong! Ma dat san la: " << d.maDat << endl;
}

void inPhieuDat(const DatSan &d) {
    SanBong *s = timSan(d.maSan);

    cout << "\nMa dat: " << d.maDat;
    cout << "\nKhach hang: " << d.tenKhach;
    cout << "\nSan: " << s->tenSan << " - " << s->loaiSan;
    cout << "\nNgay: " << d.ngay;
    cout << "\nGio: " << d.gioBatDau << "h - " << d.gioKetThuc << "h";
    cout << "\nTong tien: " << tinhTien(d) << " VND";
    cout << "\nTrang thai: ";

    if (d.daHuy) cout << "Da huy";
    else if (d.daThanhToan) cout << "Da thanh toan";
    else cout << "Chua thanh toan";

    cout << "\n";
}

void hienThiDatSan() {
    if (dsDat.empty()) {
        cout << "\nChua co lich dat san.\n";
        return;
    }

    cout << "\n--- DANH SACH DAT SAN ---\n";
    for (auto d : dsDat) {
        inPhieuDat(d);
    }
}

void huySan() {
    int maSan;
    string tenKhach;
    string ngay;
    int gioBatDau, gioKetThuc;
    bool timThay = false;

    cout << "\n===== HUY SAN =====\n";

    cout << "Nhap ma san muon huy: ";
    cin >> maSan;

    if (timSan(maSan) == NULL) {
        cout << "Ma san khong ton tai!\n";
        return;
    }

    boQuaEnter();

    cout << "Nhap ten khach hang: ";
    getline(cin, tenKhach);

    cout << "Nhap ngay dd/mm/yyyy: ";
    cin >> ngay;

    cout << "Nhap gio bat dau: ";
    cin >> gioBatDau;

    cout << "Nhap gio ket thuc: ";
    cin >> gioKetThuc;

    if (gioBatDau >= gioKetThuc) {
        cout << "Gio huy san khong hop le!\n";
        return;
    }

    for (int i = 0; i < dsDat.size(); i++) {
        if (dsDat[i].maSan == maSan &&
            dsDat[i].tenKhach == tenKhach &&
            dsDat[i].ngay == ngay &&
            dsDat[i].gioBatDau == gioBatDau &&
            dsDat[i].gioKetThuc == gioKetThuc) {

            timThay = true;

            if (dsDat[i].daHuy == true) {
                cout << "Lich dat san nay da duoc huy truoc do.\n";
                return;
            }

            if (dsDat[i].daThanhToan == true) {
                cout << "Lich nay da thanh toan, khong the huy.\n";
                return;
            }

            dsDat[i].daHuy = true;

            cout << "\nHuy san thanh cong!\n";
            cout << "Thong tin lich da huy:\n";
            inPhieuDat(dsDat[i]);

            return;
        }
    }

    if (timThay == false) {
        cout << "Khong tim thay lich dat san phu hop de huy.\n";
    }
}
//void huySan() {
 //   int maDat;
   // cout << "\nNhap ma dat san can huy: ";
    //cin >> maDat;

    //for (auto &d : dsDat) {
      //  if (d.maDat == maDat) {
        //    if (d.daHuy) {
          //      cout << "Lich nay da bi huy truoc do.\n";
            //} else {
              //  d.daHuy = true;
                //cout << "Huy san thanh cong.\n";
            //}
            //return;
        //}
    //}

  //  cout << "Khong tim thay ma dat san.\n";
//}

void thanhToan() {
    int maDat;
    cout << "\nNhap ma dat san can thanh toan: ";
    cin >> maDat;

    for (auto &d : dsDat) {
        if (d.maDat == maDat) {
            if (d.daHuy) {
                cout << "Khong the thanh toan lich da huy.\n";
                return;
            }

            d.daThanhToan = true;

            cout << "\n========== HOA DON ==========\n";
            inPhieuDat(d);
            cout << "=============================\n";
            return;
        }
    }

    cout << "Khong tim thay ma dat san.\n";
}

void timKiem() {
    string tuKhoa;
    boQuaEnter();

    cout << "\nNhap ten khach hang hoac ma dat san: ";
    getline(cin, tuKhoa);

    bool timThay = false;

    for (auto d : dsDat) {
        if (d.tenKhach.find(tuKhoa) != string::npos ||
            to_string(d.maDat) == tuKhoa) {
            inPhieuDat(d);
            timThay = true;
        }
    }

    if (!timThay)
        cout << "Khong tim thay thong tin phu hop.\n";
}

void thongKeDoanhThu() {
    int chon;
    string mocThoiGian;
    long long tong = 0;
    int soHoaDon = 0;

    cout << "\n1. Thong ke theo ngay";
    cout << "\n2. Thong ke theo thang";
    cout << "\nChon: ";
    cin >> chon;

    if (chon == 1) {
        cout << "Nhap ngay dd/mm/yyyy: ";
        cin >> mocThoiGian;
    } else if (chon == 2) {
        cout << "Nhap thang mm/yyyy: ";
        cin >> mocThoiGian;
    } else {
        cout << "Lua chon khong hop le!\n";
        return;
    }

    for (auto d : dsDat) {
        if (d.daHuy || !d.daThanhToan) continue;

        bool hopLe = false;

        if (chon == 1 && d.ngay == mocThoiGian)
            hopLe = true;

        if (chon == 2 && d.ngay.size() >= 10 && d.ngay.substr(3) == mocThoiGian)
            hopLe = true;

        if (hopLe) {
            tong += tinhTien(d);
            soHoaDon++;
        }
    }

    cout << "\nSo hoa don da thanh toan: " << soHoaDon;
    cout << "\nTong doanh thu: " << tong << " VND\n";
}

int main() {
    int chon;

    do {
        cout << "\n========== QUAN LY SAN BONG ==========\n";
        cout << "1. Xem danh sach san\n";
        cout << "2. Kiem tra lich trong\n";
        cout << "3. Dat san\n";
        cout << "4. Huy san\n";
        cout << "5. Thanh toan va in hoa don\n";
        cout << "6. Tim kiem thong tin dat san\n";
        cout << "7. Thong ke doanh thu\n";
        cout << "8. Xem tat ca lich dat san\n";
        cout << "0. Thoat\n";
        cout << "Chon chuc nang: ";
        cin >> chon;

        switch (chon) {
            case 1: hienThiSan(); break;
            case 2: kiemTraLichTrong(); break;
            case 3: datSan(); break;
            case 4: huySan(); break;
            case 5: thanhToan(); break;
            case 6: timKiem(); break;
            case 7: thongKeDoanhThu(); break;
            case 8: hienThiDatSan(); break;
            case 0: cout << "Thoat chuong trinh.\n"; break;
            default: cout << "Lua chon khong hop le!\n";
        }

    } while (chon != 0);

    return 0;
}
