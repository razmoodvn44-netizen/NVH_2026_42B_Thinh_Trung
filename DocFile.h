#pragma once
#include <bits/stdc++.h>
#include "SanBong.h"
#include "DatSan.h"
using namespace std;

const string FILE_SAN = "DanhSachSan.txt";
const string FILE_DATSAN = "DanhSachDatSan.txt";
const string FILE_HOADON = "HoaDon.txt";

// ---------- DOC / GHI DANH SACH SAN BONG ----------
vector<SanBong> DocFileSan()
{
    vector<SanBong> DS_San;
    ifstream f(FILE_SAN);
    if (!f.is_open()) return DS_San;

    string maSan, tenSan, loaiSan;
    double giaThue;
    while (f >> maSan)
    {
        f.ignore();
        getline(f, tenSan, '|');
        getline(f, loaiSan, '|');
        f >> giaThue;
        DS_San.push_back(SanBong(maSan, tenSan, loaiSan, giaThue));
    }
    f.close();
    return DS_San;
}

void GhiFileSan(const vector<SanBong> &DS_San)
{
    ofstream f(FILE_SAN);
    for (const SanBong &sb : DS_San)
    {
        f << sb.getMaSan() << " " << sb.getTenSan() << "|" << sb.getLoaiSan()
          << "|" << sb.getGiaThue() << endl;
    }
    f.close();
}

// ---------- DOC / GHI DANH SACH DAT SAN ----------
vector<DatSan> DocFileDatSan()
{
    vector<DatSan> DS_DatSan;
    ifstream f(FILE_DATSAN);
    if (!f.is_open()) return DS_DatSan;

    string maDatSan, tenKH, sdt, maSan, ngayDat, trangThai;
    int gioBD, gioKT;
    double tongTien;

    while (f >> maDatSan)
    {
        f.ignore();
        getline(f, tenKH, '|');
        getline(f, sdt, '|');
        getline(f, maSan, '|');
        getline(f, ngayDat, '|');
        f >> gioBD >> gioKT >> tongTien;
        f.ignore();
        getline(f, trangThai);

        DS_DatSan.push_back(DatSan(maDatSan, tenKH, sdt, maSan, ngayDat,
                                    gioBD, gioKT, tongTien, trangThai));
    }
    f.close();
    return DS_DatSan;
}

void GhiFileDatSan(const vector<DatSan> &DS_DatSan)
{
    ofstream f(FILE_DATSAN);
    for (const DatSan &ds : DS_DatSan)
    {
        f << ds.getMaDatSan() << " " << ds.getTenKhachHang() << "|" << ds.getSdt()
          << "|" << ds.getMaSan() << "|" << ds.getNgayDat() << "|"
          << ds.getGioBatDau() << " " << ds.getGioKetThuc() << " "
          << ds.getTongTien() << " " << ds.getTrangThai() << endl;
    }
    f.close();
}

// ---------- GHI LOG HOA DON ----------
void GhiHoaDon(const DatSan &ds, const SanBong &sb)
{
    ofstream f(FILE_HOADON, ios::app);
    f << "===================================================" << endl;
    f << "Ma dat san : " << ds.getMaDatSan() << endl;
    f << "Khach hang : " << ds.getTenKhachHang() << " - SDT: " << ds.getSdt() << endl;
    f << "San thue   : " << sb.getTenSan() << " (" << sb.getLoaiSan() << ")" << endl;
    f << "Ngay thue  : " << ds.getNgayDat() << endl;
    f << "Gio thue   : " << ds.getGioBatDau() << "h - " << ds.getGioKetThuc() << "h"
      << " (" << ds.getSoGioThue() << " gio)" << endl;
    f << "Gia/gio    : " << sb.getGiaThue() << " VND" << endl;
    f << "Tong tien  : " << ds.getTongTien() << " VND" << endl;
    f << "===================================================" << endl << endl;
    f.close();
}
