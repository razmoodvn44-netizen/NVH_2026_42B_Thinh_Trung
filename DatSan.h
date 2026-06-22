#pragma once
#include <bits/stdc++.h>
using namespace std;

class DatSan
{
    private:
        string maDatSan;      // Ma dat san, vd: DS001
        string tenKhachHang;  // Ten khach hang
        string sdt;           // So dien thoai khach hang
        string maSan;         // Ma san duoc dat (lien ket toi SanBong)
        string ngayDat;       // Ngay dat san, dang dd/mm/yyyy
        int gioBatDau;        // Gio bat dau thue (0 - 23)
        int gioKetThuc;       // Gio ket thuc thue (0 - 23)
        double tongTien;      // Tong tien = so gio thue * gia thue san
        string trangThai;     // "Da dat" hoac "Da huy"

    public:
        DatSan() {}

        DatSan(string maDatSan, string tenKhachHang, string sdt, string maSan,
               string ngayDat, int gioBatDau, int gioKetThuc, double tongTien,
               string trangThai)
        {
            this->maDatSan = maDatSan;
            this->tenKhachHang = tenKhachHang;
            this->sdt = sdt;
            this->maSan = maSan;
            this->ngayDat = ngayDat;
            this->gioBatDau = gioBatDau;
            this->gioKetThuc = gioKetThuc;
            this->tongTien = tongTien;
            this->trangThai = trangThai;
        }

        // ----- Set -----
        void setMaDatSan(string maDatSan) { this->maDatSan = maDatSan; }
        void setTenKhachHang(string tenKhachHang) { this->tenKhachHang = tenKhachHang; }
        void setSdt(string sdt) { this->sdt = sdt; }
        void setMaSan(string maSan) { this->maSan = maSan; }
        void setNgayDat(string ngayDat) { this->ngayDat = ngayDat; }
        void setGioBatDau(int gioBatDau) { this->gioBatDau = gioBatDau; }
        void setGioKetThuc(int gioKetThuc) { this->gioKetThuc = gioKetThuc; }
        void setTongTien(double tongTien) { this->tongTien = tongTien; }
        void setTrangThai(string trangThai) { this->trangThai = trangThai; }

        // ----- Get -----
        string getMaDatSan() const { return maDatSan; }
        string getTenKhachHang() const { return tenKhachHang; }
        string getSdt() const { return sdt; }
        string getMaSan() const { return maSan; }
        string getNgayDat() const { return ngayDat; }
        int getGioBatDau() const { return gioBatDau; }
        int getGioKetThuc() const { return gioKetThuc; }
        double getTongTien() const { return tongTien; }
        string getTrangThai() const { return trangThai; }

        int getSoGioThue() const { return gioKetThuc - gioBatDau; }
};
