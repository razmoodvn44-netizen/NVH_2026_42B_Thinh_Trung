#pragma once
#include <bits/stdc++.h>
#include <iomanip>
#include "SanBong.h"
#include "DatSan.h"
#include "DocFile.h"
#include "GiaoDien.h"
using namespace std;

class QuanLySanBong
{
    public:
        // Tim san theo ma san, tra ve con tro de tien sua doi (null neu khong thay)
        SanBong* TimSanTheoMa(vector<SanBong> &DS_San, const string &maSan)
        {
            for (SanBong &sb : DS_San)
            {
                if (sb.getMaSan() == maSan) return &sb;
            }
            return nullptr;
        }

        // Sinh ma dat san moi tu dong: DS001, DS002, ...
        string SinhMaDatSan(const vector<DatSan> &DS_DatSan)
        {
            int max_id = 0;
            for (const DatSan &ds : DS_DatSan)
            {
                string so = ds.getMaDatSan().substr(2); // bo "DS"
                if (!so.empty()) max_id = max(max_id, stoi(so));
            }
            int id_moi = max_id + 1;
            ostringstream oss;
            oss << "DS" << setw(3) << setfill('0') << id_moi;
            return oss.str();
        }

        // Kiem tra san co bi trung gio voi lich da dat (cung ngay, cung san) khong
        bool KiemTraTrungGio(const vector<DatSan> &DS_DatSan, const string &maSan,
                              const string &ngay, int gioBD, int gioKT)
        {
            for (const DatSan &ds : DS_DatSan)
            {
                if (ds.getTrangThai() == "Da huy") continue;
                if (ds.getMaSan() != maSan || ds.getNgayDat() != ngay) continue;

                // Trung gio neu hai khoang gio giao nhau
                if (gioBD < ds.getGioKetThuc() && gioKT > ds.getGioBatDau())
                {
                    return true;
                }
            }
            return false;
        }

        // ----- 1. DAT SAN -----
        void DatSanMoi(vector<SanBong> &DS_San, vector<DatSan> &DS_DatSan)
        {
            string maSan, ngay, tenKH, sdt;
            int gioBD, gioKT;

            SetColor(0, 15);
            cout << "Nhap ma san can thue: ";
            cin >> maSan;

            SanBong *sb = TimSanTheoMa(DS_San, maSan);
            if (sb == nullptr)
            {
                SetColor(0, 12);
                cout << "Khong tim thay san voi ma " << maSan << " !" << endl;
                SetColor(0, 7);
                return;
            }

            cout << "Nhap ngay thue (dd/mm/yyyy): ";
            cin >> ngay;
            cout << "Nhap gio bat dau (0 - 23): ";
            cin >> gioBD;
            cout << "Nhap gio ket thuc (0 - 23): ";
            cin >> gioKT;

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                SetColor(0, 12);
                cout << "Du lieu gio nhap khong hop le !" << endl;
                SetColor(0, 7);
                return;
            }

            if (gioBD < 0 || gioKT > 23 || gioBD >= gioKT)
            {
                SetColor(0, 12);
                cout << "Khoang gio khong hop le !" << endl;
                SetColor(0, 7);
                return;
            }

            if (KiemTraTrungGio(DS_DatSan, maSan, ngay, gioBD, gioKT))
            {
                SetColor(0, 12);
                cout << "San da co nguoi dat trong khoang gio nay, vui long chon gio khac !" << endl;
                SetColor(0, 7);
                return;
            }

            cout << "Nhap ten khach hang: ";
            cin.ignore();
            getline(cin, tenKH);
            cout << "Nhap so dien thoai: ";
            getline(cin, sdt);

            double tongTien = (gioKT - gioBD) * sb->getGiaThue();
            string maDatSan = SinhMaDatSan(DS_DatSan);

            DatSan ds(maDatSan, tenKH, sdt, maSan, ngay, gioBD, gioKT, tongTien, "Da dat");
            DS_DatSan.push_back(ds);
            GhiFileDatSan(DS_DatSan);
            GhiHoaDon(ds, *sb);

            SetColor(0, 10);
            cout << "\nDat san thanh cong ! Ma dat san cua ban la: " << maDatSan << endl;
            XuatHoaDon(ds, *sb);
            SetColor(0, 7);
        }

        // ----- 2. HUY SAN -----
        void HuySan(vector<DatSan> &DS_DatSan)
        {
            string maDatSan;
            SetColor(0, 15);
            cout << "Nhap ma dat san can huy: ";
            cin >> maDatSan;

            bool kt = false;
            for (DatSan &ds : DS_DatSan)
            {
                if (ds.getMaDatSan() == maDatSan)
                {
                    kt = true;
                    if (ds.getTrangThai() == "Da huy")
                    {
                        SetColor(0, 12);
                        cout << "Lich dat san nay da duoc huy truoc do !" << endl;
                    }
                    else
                    {
                        ds.setTrangThai("Da huy");
                        GhiFileDatSan(DS_DatSan);
                        SetColor(0, 10);
                        cout << "Huy lich dat san " << maDatSan << " thanh cong !" << endl;
                    }
                    break;
                }
            }

            if (!kt)
            {
                SetColor(0, 12);
                cout << "Khong tim thay lich dat san voi ma " << maDatSan << " !" << endl;
            }
            SetColor(0, 7);
        }

        // ----- 3. TRA CUU LICH TRONG THEO NGAY -----
        void TraCuuLichTrong(const vector<SanBong> &DS_San, const vector<DatSan> &DS_DatSan)
        {
            string ngay;
            SetColor(0, 15);
            cout << "Nhap ngay can tra cuu (dd/mm/yyyy): ";
            cin >> ngay;

            SetColor(0, 10);
            cout << "\n----------- LICH TRONG NGAY " << ngay << " (gio hoat dong 6h - 23h) -----------" << endl;

            for (const SanBong &sb : DS_San)
            {
                SetColor(0, 15);
                cout << "\n* San: " << sb.getTenSan() << " (" << sb.getLoaiSan() << ") - Ma: " << sb.getMaSan() << endl;

                vector<bool> daDat(24, false);
                for (const DatSan &ds : DS_DatSan)
                {
                    if (ds.getTrangThai() == "Da huy") continue;
                    if (ds.getMaSan() != sb.getMaSan() || ds.getNgayDat() != ngay) continue;
                    for (int h = ds.getGioBatDau(); h < ds.getGioKetThuc(); h++) daDat[h] = true;
                }

                cout << "  Gio trong: ";
                bool conTrong = false;
                for (int h = 6; h < 23; h++)
                {
                    if (!daDat[h])
                    {
                        cout << h << "h-" << h + 1 << "h  ";
                        conTrong = true;
                    }
                }
                if (!conTrong) cout << "Khong con gio trong";
                cout << endl;
            }
        }

        // ----- 4. TIM KIEM THEO TEN KHACH HANG -----
        void TimTheoTenKhachHang(const vector<DatSan> &DS_DatSan, const string &ten)
        {
            string tenTim = ChuyenThuong(ten);
            bool kt = false;

            SetColor(0, 10);
            cout << "\n----------- KET QUA TIM KIEM THEO TEN KHACH HANG -----------" << endl;
            InHeaderDatSan();
            for (const DatSan &ds : DS_DatSan)
            {
                if (ChuyenThuong(ds.getTenKhachHang()).find(tenTim) != string::npos)
                {
                    InDongDatSan(ds);
                    kt = true;
                }
            }
            if (!kt)
            {
                SetColor(0, 12);
                cout << "Khong tim thay lich dat san cua khach hang nay !" << endl;
            }
            SetColor(0, 7);
        }

        // ----- 4b. TIM KIEM THEO MA DAT SAN -----
        void TimTheoMaDatSan(const vector<DatSan> &DS_DatSan, const string &maDatSan)
        {
            bool kt = false;
            SetColor(0, 10);
            cout << "\n----------- KET QUA TIM KIEM THEO MA DAT SAN -----------" << endl;
            InHeaderDatSan();
            for (const DatSan &ds : DS_DatSan)
            {
                if (ds.getMaDatSan() == maDatSan)
                {
                    InDongDatSan(ds);
                    kt = true;
                    break;
                }
            }
            if (!kt)
            {
                SetColor(0, 12);
                cout << "Khong tim thay lich dat san voi ma nay !" << endl;
            }
            SetColor(0, 7);
        }

        // ----- 5. THONG KE DOANH THU THEO NGAY -----
        void ThongKeDoanhThuTheoNgay(const vector<DatSan> &DS_DatSan, const string &ngay)
        {
            double tong = 0;
            int soLuotDat = 0;
            for (const DatSan &ds : DS_DatSan)
            {
                if (ds.getNgayDat() == ngay && ds.getTrangThai() != "Da huy")
                {
                    tong += ds.getTongTien();
                    soLuotDat++;
                }
            }
            SetColor(0, 10);
            cout << "\n----------- DOANH THU NGAY " << ngay << " -----------" << endl;
            cout << "So luot dat san thanh cong: " << soLuotDat << endl;
            cout << "Tong doanh thu           : " << fixed << setprecision(0) << tong << " VND" << endl;
            SetColor(0, 7);
        }

        // ----- 5b. THONG KE DOANH THU THEO THANG (nhap dang mm/yyyy) -----
        void ThongKeDoanhThuTheoThang(const vector<DatSan> &DS_DatSan, const string &thang)
        {
            // thang dang "mm/yyyy", ngayDat dang "dd/mm/yyyy" -> so sanh 2 phan cuoi
            double tong = 0;
            int soLuotDat = 0;
            for (const DatSan &ds : DS_DatSan)
            {
                if (ds.getTrangThai() == "Da huy") continue;
                string ngay = ds.getNgayDat();
                size_t pos1 = ngay.find('/');
                string mmyyyy = (pos1 == string::npos) ? "" : ngay.substr(pos1 + 1);
                if (mmyyyy == thang)
                {
                    tong += ds.getTongTien();
                    soLuotDat++;
                }
            }
            SetColor(0, 10);
            cout << "\n----------- DOANH THU THANG " << thang << " -----------" << endl;
            cout << "So luot dat san thanh cong: " << soLuotDat << endl;
            cout << "Tong doanh thu           : " << fixed << setprecision(0) << tong << " VND" << endl;
            SetColor(0, 7);
        }

        // ----- HIEN THI DANH SACH SAN -----
        void HienThiDanhSachSan(const vector<SanBong> &DS_San)
        {
            SetColor(0, 10);
            cout << "\n--------------------- DANH SACH SAN BONG ---------------------" << endl;
            SetColor(0, 15);
            cout << "+--------+------------------+------------+---------------+" << endl;
            cout << "| " << setw(6) << "Ma" << " | " << setw(16) << "Ten san" << " | "
                 << setw(10) << "Loai san" << " | " << setw(13) << "Gia/gio(VND)" << " |" << endl;
            cout << "+--------+------------------+------------+---------------+" << endl;
            for (const SanBong &sb : DS_San)
            {
                cout << "| " << setw(6) << sb.getMaSan() << " | " << setw(16) << sb.getTenSan()
                     << " | " << setw(10) << sb.getLoaiSan() << " | " << setw(13) << sb.getGiaThue() << " |" << endl;
            }
            cout << "+--------+------------------+------------+---------------+" << endl;
        }

        // ----- XUAT HOA DON RA MAN HINH -----
        void XuatHoaDon(const DatSan &ds, const SanBong &sb)
        {
            SetColor(0, 14);
            cout << "\n================== HOA DON DAT SAN ==================" << endl;
            cout << "Ma dat san : " << ds.getMaDatSan() << endl;
            cout << "Khach hang : " << ds.getTenKhachHang() << " - SDT: " << ds.getSdt() << endl;
            cout << "San thue   : " << sb.getTenSan() << " (" << sb.getLoaiSan() << ")" << endl;
            cout << "Ngay thue  : " << ds.getNgayDat() << endl;
            cout << "Gio thue   : " << ds.getGioBatDau() << "h - " << ds.getGioKetThuc() << "h"
                 << " (" << ds.getSoGioThue() << " gio)" << endl;
            cout << "Gia/gio    : " << sb.getGiaThue() << " VND" << endl;
            cout << "Tong tien  : " << fixed << setprecision(0) << ds.getTongTien() << " VND" << endl;
            cout << "======================================================" << endl;
        }

    private:
        string ChuyenThuong(string s)
        {
            for (char &c : s) c = tolower(c);
            return s;
        }

        void InHeaderDatSan()
        {
            SetColor(0, 15);
            cout << "+----------+------------------+--------+------------+--------+----------+" << endl;
            cout << "| " << setw(8) << "Ma DS" << " | " << setw(16) << "Khach hang" << " | "
                 << setw(6) << "Ma San" << " | " << setw(10) << "Ngay" << " | " << setw(6) << "Gio"
                 << " | " << setw(8) << "Trang thai" << " |" << endl;
            cout << "+----------+------------------+--------+------------+--------+----------+" << endl;
        }

        void InDongDatSan(const DatSan &ds)
        {
            cout << "| " << setw(8) << ds.getMaDatSan() << " | " << setw(16) << ds.getTenKhachHang()
                 << " | " << setw(6) << ds.getMaSan() << " | " << setw(10) << ds.getNgayDat()
                 << " | " << setw(2) << ds.getGioBatDau() << "-" << setw(2) << ds.getGioKetThuc()
                 << " | " << setw(8) << ds.getTrangThai() << " |" << endl;
        }
};
