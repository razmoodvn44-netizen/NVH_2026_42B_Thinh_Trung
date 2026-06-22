#include <bits/stdc++.h>
#include "SanBong.h"
#include "DatSan.h"
#include "DocFile.h"
#include "QuanLySanBong.h"
#include "GiaoDien.h"
using namespace std;

// Khoi tao du lieu mau cho danh sach san neu file san chua co
void KhoiTaoDuLieuMauNeuCan(vector<SanBong> &DS_San)
{
    if (!DS_San.empty()) return;
    DS_San.push_back(SanBong("S01", "San A1", "5 nguoi", 200000));
    DS_San.push_back(SanBong("S02", "San A2", "5 nguoi", 200000));
    DS_San.push_back(SanBong("S03", "San B1", "7 nguoi", 350000));
    DS_San.push_back(SanBong("S04", "San C1", "11 nguoi", 600000));
    GhiFileSan(DS_San);
}

void MenuChinh()
{
    QuanLySanBong qlSanBong;
    vector<SanBong> DS_San = DocFileSan();
    KhoiTaoDuLieuMauNeuCan(DS_San);
    vector<DatSan> DS_DatSan = DocFileDatSan();

    bool kt = true;
    do
    {
        system("cls");
        SetColor(0, 11);
        cout << "\n\t\t +------- QUAN LY DAT SAN BONG DA -------+ " << endl;
        cout << "\t\t | 1. Xem danh sach san bong             | " << endl;
        cout << "\t\t | 2. Dat san                            | " << endl;
        cout << "\t\t | 3. Huy lich dat san                   | " << endl;
        cout << "\t\t | 4. Tra cuu lich trong theo ngay       | " << endl;
        cout << "\t\t | 5. Tim kiem theo ten khach hang        | " << endl;
        cout << "\t\t | 6. Tim kiem theo ma dat san            | " << endl;
        cout << "\t\t | 7. Thong ke doanh thu theo ngay        | " << endl;
        cout << "\t\t | 8. Thong ke doanh thu theo thang       | " << endl;
        cout << "\t\t | 9. Thoat                               | " << endl;
        cout << "\t\t +-----------------------------------------+ " << endl;

        int luaChon;
        SetColor(0, 15);
        cout << "\nMoi ban nhap lua chon: ";
        cin >> luaChon;

        if (cin.fail())
        {
            // Nguoi dung nhap khong phai so, hoac luong input da het (EOF)
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (cin.eof()) break; // het du lieu nhap -> dung chuong trinh, tranh lap vo han
            luaChon = -1;
        }

        switch (luaChon)
        {
            case 1:
            {
                system("cls");
                qlSanBong.HienThiDanhSachSan(DS_San);
                system("pause");
                break;
            }
            case 2:
            {
                system("cls");
                qlSanBong.DatSanMoi(DS_San, DS_DatSan);
                system("pause");
                break;
            }
            case 3:
            {
                system("cls");
                qlSanBong.HuySan(DS_DatSan);
                system("pause");
                break;
            }
            case 4:
            {
                system("cls");
                qlSanBong.TraCuuLichTrong(DS_San, DS_DatSan);
                system("pause");
                break;
            }
            case 5:
            {
                system("cls");
                string ten;
                SetColor(0, 15);
                cout << "Nhap ten khach hang can tim: ";
                cin.ignore();
                getline(cin, ten);
                qlSanBong.TimTheoTenKhachHang(DS_DatSan, ten);
                system("pause");
                break;
            }
            case 6:
            {
                system("cls");
                string maDatSan;
                SetColor(0, 15);
                cout << "Nhap ma dat san can tim: ";
                cin >> maDatSan;
                qlSanBong.TimTheoMaDatSan(DS_DatSan, maDatSan);
                system("pause");
                break;
            }
            case 7:
            {
                system("cls");
                string ngay;
                SetColor(0, 15);
                cout << "Nhap ngay can thong ke (dd/mm/yyyy): ";
                cin >> ngay;
                qlSanBong.ThongKeDoanhThuTheoNgay(DS_DatSan, ngay);
                system("pause");
                break;
            }
            case 8:
            {
                system("cls");
                string thang;
                SetColor(0, 15);
                cout << "Nhap thang can thong ke (mm/yyyy): ";
                cin >> thang;
                qlSanBong.ThongKeDoanhThuTheoThang(DS_DatSan, thang);
                system("pause");
                break;
            }
            case 9:
            {
                kt = false;
                SetColor(0, 12);
                cout << "\nCam on ban da su dung chuong trinh !" << endl;
                SetColor(0, 7);
                system("pause");
                break;
            }
            default:
            {
                SetColor(0, 12);
                cout << "Vui long nhap lai lua chon (1 - 9) !" << endl;
                SetColor(0, 7);
                system("pause");
                break;
            }
        }
    } while (kt);
}

int main()
{
    MenuChinh();
    return 0;
}
