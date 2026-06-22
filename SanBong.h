#pragma once
#include <bits/stdc++.h>
using namespace std;

class SanBong
{
    private:
        string maSan;       // Ma san, vd: S01
        string tenSan;      // Ten san, vd: San A1
        string loaiSan;     // Loai san: 5 nguoi / 7 nguoi / 11 nguoi
        double giaThue;     // Gia thue / gio (VND)

    public:
        SanBong() {}

        SanBong(string maSan, string tenSan, string loaiSan, double giaThue)
        {
            this->maSan = maSan;
            this->tenSan = tenSan;
            this->loaiSan = loaiSan;
            this->giaThue = giaThue;
        }

        // ----- Set -----
        void setMaSan(string maSan) { this->maSan = maSan; }
        void setTenSan(string tenSan) { this->tenSan = tenSan; }
        void setLoaiSan(string loaiSan) { this->loaiSan = loaiSan; }
        void setGiaThue(double giaThue) { this->giaThue = giaThue; }

        // ----- Get -----
        string getMaSan() const { return maSan; }
        string getTenSan() const { return tenSan; }
        string getLoaiSan() const { return loaiSan; }
        double getGiaThue() const { return giaThue; }
};
