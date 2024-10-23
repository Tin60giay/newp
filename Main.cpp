#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>

using namespace std;

#define MAX_LOP 100

//Khai bao

struct CauHoiThi // DSLK Don
{
	int Id; 
	string Noidung;
	string A;
	string B;
	string C;
	string D;
	char Dapan;
	CauHoiThi* next;

};

struct DSMonHoc  // Cay nhi phan tim kiem can bang
{
	string Mamh; //gioi han 15 ky tu
	string Tenmh;
	int Chieucao; // Moi them
	CauHoiThi* Cauhoithi = NULL;
	DSMonHoc* left = NULL;
	DSMonHoc* right = NULL;

};

struct DiemThi //DSLK Don //Them bai thi(Id+dapan sinh vien chon)
{
	string Mamh;
	double Diem; //Lam tron 1 so sau dau cham
	DiemThi* next;
};

struct SinhVien	 //DSLK Don
{
	string Masv; // gioi han 15 ky tu
	string Ho;
	string Ten;
	string Phai;
	string Password;
	DiemThi* Diemthi  = NULL;
	SinhVien* next = NULL;
};

struct Lop // Khai bao ngoai yeu cau
{
	string Malop; // gioi han 15 ky tu;
	string Tenlop;
	SinhVien* Sinhvien = NULL;
};

struct DSLop //Mang con tro
{
	Lop* lop[MAX_LOP]; // Mang con tro toi Lop
	int so_luong_lop = 0; //so luong lop hien co
};

//Ham khoi tao

int TaoIdNgauNhien()
{
	return rand() % 10000;
}

CauHoiThi* taoNodeCauHoiThi(string noidung, string a, string b, string c, string d, char dapan)
{
	CauHoiThi* node = new CauHoiThi();
	node->Id = TaoIdNgauNhien(); // chua tinh truong hop id trung nhau
	node->Noidung = noidung;
	node->A = a;
	node->B = b;
	node->C = c;
	node->D = d;
	node->Dapan = dapan;
	node->next = NULL;

	return node;
}

DiemThi* taoNodeDiemThi(string mamh, double diem)
{
	DiemThi* node = new DiemThi();
	node->Mamh = mamh;
	node->Diem = diem;
	node->next = NULL;

	return node;
}

SinhVien* taoNodeSinhVien(string masv, string ho, string ten, string phai, string password)
{
	SinhVien* node = new SinhVien();
	node->Masv = masv;
	node->Ho = ho;
	node->Ten = ten;
	node->Phai = phai;
	node->Password = password;
	node->Diemthi = NULL;
	node->next = NULL;

	return node;
}

DSMonHoc* taoNodeDSMonHoc(string mamh, string tenmh)
{
	DSMonHoc* node = new DSMonHoc();
	node->Mamh = mamh;
	node->Tenmh = tenmh;
	node->Chieucao = 1;
	node->Cauhoithi = NULL;
	node->left = NULL;
	node->right = NULL;

	return node;
}



//Ham nhap 

void NhapSinhVien(SinhVien *&head)
{
	string masv, ho, ten, phai, password;
	cout << "Nhap ma sinh vien: ";
	cin >> masv;
	if (masv.size() > 15)
	{
		cout << "Ma sinh vien qua dai!" << endl;
		return;
	}
	cout << "Nhap ho sinh vien: ";
	cin.ignore();
	getline(cin, ho);
	cout << "Nhap ten sinh vien: ";
	getline(cin, ten);
	cout << "Nhap gioi tinh sinh vien: ";
	cin >> phai;
	cout << "Nhap mat khau: ";
	cin >> password;
	SinhVien* newSinhVien = taoNodeSinhVien(masv, ho, ten, phai, password);
	if (head == NULL)
	{
		head = newSinhVien;
	}
	else
	{
		SinhVien* tmp = head;
		while (tmp->next != NULL)
		{
			tmp = tmp->next;
		}
		tmp->next = newSinhVien;
	}
}

void NhapLop(DSLop& dslop)
{
	if (dslop.so_luong_lop >= MAX_LOP) 
	{
		cout << "Khong the them lop moi. Da dat gioi han." << endl;
		return;
	}
	Lop* lop = new Lop();
	cout << "Nhap ma lop: ";
	cin >> lop->Malop;
	cout << "Nhap ten lop: ";
	cin.ignore();
	getline(cin, lop->Tenlop);
	//char kiemtra;
	//cout << "Ban co muon nhap tiep sinh vien khong? Y/N"<<" ";
	//cin >> kiemtra;
	//if (kiemtra == 'Y')
	//{
	//	NhapSinhVien(lop->Dssinhvien);
	//}
	//else
	//{
	//	cout << "OK!" << endl;
	//}
	dslop.lop[dslop.so_luong_lop] = lop;
	//dslop.lop[dslop.so_luong_lop]->Dssinhvien = NULL;
	dslop.so_luong_lop++;


}

int KiemTraLop(DSLop dslop, string check)
{
	if (dslop.so_luong_lop == 0)
	{
		return -1;
	}
	else
	{
		for (int i = 0; i < dslop.so_luong_lop; i++)
		{
			if (check == dslop.lop[i]->Malop)
			{
				return i;
			}
		}
	}
	return -1;
}

void NhapSinhVienCuaLop(DSLop dslop,string check)
{
	if (KiemTraLop(dslop, check) >-1)
	{
		int them = KiemTraLop(dslop, check);
		NhapSinhVien(dslop.lop[them]->Sinhvien);
	}
}





//Ham dang nhap
int KiemTraDangNhap(DSLop dslop, string masv, string password)
{
	if (masv == "GV" && password == "GV")
	{
		cout << "Dang nhap thanh cong! Ban co toan quyen." << endl;
		return 1;
	}
	DSLop current = dslop;
	for (int i = 0; i < dslop.so_luong_lop; i++)
	{
		SinhVien* tmp = dslop.lop[i]->Sinhvien;
		while (tmp!= NULL)
		{
			if (masv == tmp->Masv)
			{
				if (password == tmp->Password)
				{
					cout << "Dang nhap thanh cong" << endl;
					return 2;
				}
				else
				{
					cout << "Sai mat khau" << endl;
					return 0;
				}
			}
			tmp = tmp->next;

		}

	}
	cout << "Dang Nhap That Bai!" << endl;
	return 0;
}

int DangNhap(DSLop dslop)
{
	string masv;
	string password = "";
	char ch;
	cout << "Nhap tai khoan: ";
	cin >> masv;
	cout << "Nhap mat khau: ";
	while ((ch = _getch()) != '\r')
	{
		if (ch == '\b')
		{
			if (!password.empty())
			{
				cout << "\b \b";
				password.pop_back();
			}
		}
		else
		{
			cout << '*';
			password += ch;
		}
	}
	cout << endl;
	int check = KiemTraDangNhap(dslop, masv, password);
	return check;
}




// Ham xu ly file

void DocDuLieu(DSLop& dslop, const string& filename) 
{
	ifstream file(filename);
	if (!file.is_open()) 
	{
		cout << "Mo file loi roi" << endl;
		return;
	}

	string header, line;
	getline(file, header);
	while (getline(file, line)) 
	{
		stringstream str(line);
		string malop, tenlop, masv, ho, ten, phai, password;

		if (getline(str, malop, ';') && getline(str, tenlop, ';')) 
		{
			int lopIndex = KiemTraLop(dslop, malop);
			Lop* lop;

			if (lopIndex == -1) 
			{
				lop = new Lop();
				lop->Malop = malop;
				lop->Tenlop = tenlop;
				lop->Sinhvien = nullptr;

				dslop.lop[dslop.so_luong_lop] = lop;
				dslop.so_luong_lop++;
			}
			else 
			{
				lop = dslop.lop[lopIndex];
			}

			while (getline(str, masv, ';') && getline(str, ho, ';') && getline(str, ten, ';') && getline(str, phai, ';') && getline(str, password, ';')) 
			{
				SinhVien* sv = taoNodeSinhVien(masv, ho, ten, phai, password);
				if (lop->Sinhvien == nullptr) 
				{
					lop->Sinhvien = sv;
				}
				else 
				{
					SinhVien* temp = lop->Sinhvien;
					while (temp->next != nullptr) 
					{
						temp = temp->next;
					}
					temp->next = sv;
				}
			}
		}
	}
	file.close();
}

void GhiDuLieu(DSLop& dslop, const string& filename)
{
	ofstream file(filename);
	if (!file.is_open())
	{
		cout << "Khong the mo file de ghi" << endl;
		return;
	}
	else
	{
		file << "Ma Lop;Ten Lop;Ma Sinh Vien;Ho;Ten;Phai;Mat Khau"<<endl;
		for (int i = 0; i < dslop.so_luong_lop; i++)
		{
			Lop* lop = dslop.lop[i];
			if (lop != NULL)
			{
				SinhVien* sv = lop->Sinhvien;
				while (sv!= NULL)
				{
					file << lop->Malop << ";" << lop->Tenlop << ";" << sv->Masv << ";" << sv->Ho << ";" << sv->Ten << ";" << sv->Phai << ";" << sv->Password << endl;
					sv = sv->next;
				}
				

			}

		}
	}
	file.close();
	cout << "Luu du lieu thanh cong" << endl;
}

//Ham nhap mon hoc
int LayChieuCao(DSMonHoc* root)
{
	if (root == NULL)
	{
		return 0;
	}
	return root->Chieucao;
}

DSMonHoc* XoayTrai(DSMonHoc* root)
{
	DSMonHoc* x = root->right;
	root->right = x->left;
	x->left = root;
	
	root->Chieucao = 1 + max(LayChieuCao(root->left), LayChieuCao(root->right));
	x->Chieucao = 1 + max(LayChieuCao(x->left), LayChieuCao(x->right));

	return x;
}

DSMonHoc* XoayPhai(DSMonHoc* root)
{
	DSMonHoc* y = root->left;
	root->left = y->right;
	y->right = root;

	root->Chieucao = 1 + max(LayChieuCao(root->left), LayChieuCao(root->right));
	y->Chieucao = 1 + max(LayChieuCao(y->left), LayChieuCao(y->right));

	return y;
}

DSMonHoc* ThemMonHoc(DSMonHoc* root, string mamh, string tenmh)
{
	if (root == NULL)
	{
		return root = taoNodeDSMonHoc(mamh, tenmh);
	}
	if (mamh>root->Mamh)
	{
		root->right = ThemMonHoc(root->right, mamh, tenmh);
	}
	else if (mamh < root->Mamh)
	{
		root->left = ThemMonHoc(root->left, mamh, tenmh);
	}
	else
	{
		return root;
	}

	root->Chieucao = 1 + max(LayChieuCao(root->left), LayChieuCao(root->right));
	int chieucaohientai = LayChieuCao(root->left) - LayChieuCao(root->right);

	if (chieucaohientai > 1 && mamh < root->left->Mamh)
	{
		return XoayPhai(root);
	}
	if (chieucaohientai<-1 && mamh>root->right->Mamh)
	{
		return XoayTrai(root);
	}
	if (chieucaohientai > 1 && mamh > root->left->Mamh)
	{
		root->left = XoayTrai(root->left);
		return XoayPhai(root);
	}
	if (chieucaohientai < -1 && mamh < root->right->Mamh)
	{
		root->right = XoayPhai(root->right);
		return XoayTrai(root);
	}
	return root;
}

//Ham Xoa Mon Hoc

int KiemTraChieuCao(DSMonHoc* dsmonhoc)
{
	if (dsmonhoc == NULL)
	{
		return 0;
	}

	return LayChieuCao(dsmonhoc->left) - LayChieuCao(dsmonhoc->right);
}

DSMonHoc* TimMonHocThe(DSMonHoc* monhoc)
{
	DSMonHoc* tmp = monhoc;
	while (tmp->right != NULL)
	{
		tmp = tmp->right;
	}
	return tmp;
}

DSMonHoc* XoaMonHoc(DSMonHoc* monhoc, string mamh)
{
	if (monhoc == NULL)
	{
		return monhoc;
	}
	if (mamh > monhoc->Mamh)
	{
		monhoc->right = XoaMonHoc(monhoc->right, mamh);
	}
	else if (mamh < monhoc->Mamh)
	{
		monhoc->left = XoaMonHoc(monhoc->left, mamh);
	}
	else
	{

		if (monhoc->left == NULL)
		{
			DSMonHoc* tmp = monhoc->right;
			delete monhoc;
			return tmp;
		}
		else if (monhoc->right == NULL)
		{
			DSMonHoc* tmp = monhoc->left;
			delete monhoc;
			return tmp;
		}
		DSMonHoc* tmp = TimMonHocThe(monhoc->left);
		monhoc->Mamh = tmp->Mamh;
		monhoc->Tenmh = tmp->Tenmh;
		monhoc->left = XoaMonHoc(monhoc->left, tmp->Mamh);

	}

	if (monhoc == NULL)
		return monhoc;

	monhoc->Chieucao = 1 + max(LayChieuCao(monhoc->left), LayChieuCao(monhoc->right));
	int chieucaohientai = KiemTraChieuCao(monhoc);
	if (chieucaohientai > 1 && KiemTraChieuCao(monhoc->left)>=0)
	{
		return XoayPhai(monhoc);
	}
	if (chieucaohientai < -1 && KiemTraChieuCao(monhoc->right) <= 0)
	{
		return XoayTrai(monhoc);
	}
	if (chieucaohientai > 1 && KiemTraChieuCao(monhoc->left) < 0)
	{
		monhoc->left = XoayTrai(monhoc->left);
		return XoayPhai(monhoc);
	}
	if (chieucaohientai < -1 && KiemTraChieuCao(monhoc->right)>0)
	{
		monhoc->right = XoayPhai(monhoc->right);
		return XoayTrai(monhoc);
	}
	
	return monhoc;
}

DSMonHoc* TimMonHoc(DSMonHoc* monhoc, string mamh) 
{
	if (monhoc == NULL) return NULL;
	if (mamh > monhoc->Mamh) return TimMonHoc(monhoc->right, mamh);
	if (mamh < monhoc->Mamh) return TimMonHoc(monhoc->left, mamh);
	return monhoc;
}


//Ham hieu chinh

DSMonHoc* HieuChinhMon(DSMonHoc* monhoc, string mamh) 
{
	if (monhoc == NULL) 
	{
		return monhoc;
	}
	if (mamh > monhoc->Mamh) 
	{
		return HieuChinhMon(monhoc->right, mamh);
	}
	else if (mamh < monhoc->Mamh) 
	{
		return HieuChinhMon(monhoc->left, mamh);
	}
	else 
	{
		cout << "Nhap ma mon hoc moi: ";
		cin.ignore();
		getline(cin, monhoc->Mamh);
		cout << "Nhap ten mon hoc moi: ";
		getline(cin, monhoc->Tenmh);
	}
	return monhoc;
}


void NhapMonHoc(DSMonHoc*& dsmonhoc)
{
	string mamh, tenmh;
	cout << "Nhap ma mon hoc: ";
	cin.ignore();
	getline(cin, mamh);
	cout << "Nhap ten mon hoc: ";
	getline(cin, tenmh);
	dsmonhoc = ThemMonHoc(dsmonhoc, mamh, tenmh);
}

//Ham thiet ke cau hoi thi

void NhapCauHoiThi(CauHoiThi*& cauhoithi)
{
	string nd, a, b, c, d;
	char dapan;
	cout << "Nhap noi dung cau hoi thi: ";
	cin.ignore();
	getline(cin, nd);
	cout << "Nhap dan an A: ";
	/*cin.ignore();*/
	getline(cin, a);
	cout << "Nhap dap an B: ";
	/*cin.ignore();*/
	getline(cin, b);
	cout << "Nhap dap an C: ";
	/*cin.ignore();*/
	getline(cin, c);
	cout << "Nhap dap an D: ";
	/*cin.ignore();*/
	getline(cin, d);
	cout << "Nhap dan an dung: ";
	cin >> dapan;

	CauHoiThi *newCauHoiThi = taoNodeCauHoiThi(nd, a, b, c, d, dapan);
	newCauHoiThi->next = cauhoithi;
	cauhoithi = newCauHoiThi;
	
}

void XoaCauHoi(CauHoiThi*& cauhoithi, int id)
{

	if (cauhoithi == NULL)
	{
		std::cout << "Cau hoi thi rong" << endl;
		return;
	}

	if (cauhoithi->Id == id)
	{
		CauHoiThi* tmp = cauhoithi;
		cauhoithi = cauhoithi->next;
		delete tmp;
		return;
	}
	CauHoiThi* prev = cauhoithi;
	CauHoiThi* current = cauhoithi->next;
	while (current!= NULL && current->Id != id)
	{
		prev = current;
		current = current->next;
	}
	if (current != NULL)
	{
		prev->next = current ->next;
		delete current;
	}
	else
	{
		return;
	}
	

}

bool KiemTraCauHoi(CauHoiThi* cauhoithi, int id)
{

	if (cauhoithi == NULL)
	{
		std::cout << "Cau hoi thi rong" << endl;
		return false;
	}

	if (cauhoithi->Id == id)
	{
		return true;
	}
	CauHoiThi* prev = cauhoithi;
	CauHoiThi* current = cauhoithi->next;
	while (current != NULL && current->Id != id)
	{
		prev = current;
		current = current->next;
	}
	if (current != NULL)
	{
		prev->next = current->next;
		return true;
	}
	else
	{
		std::cout << "Khong tim thay id cau hoi" << endl;
		return false;
	}
}

////////////////////////////
int SoLuongCauHoi(CauHoiThi* cauhoithi)
{
	int dem = 0;
	while (cauhoithi!=NULL)
	{
		dem++;
		cauhoithi = cauhoithi->next;
	}
	return dem;
}

int LayIdCauHoi(CauHoiThi* cauhoithi)
{
	int id = cauhoithi->Id;
	return id;
}

int LayNgauNhienId(int* A, int soluong, int soluongcauhoi, int* ketqua)
{
	if (soluong < soluongcauhoi)
	{
		cout << "Khong du cau hoi" << endl;
		return 0;
	}
	bool* dachon = new bool[soluongcauhoi];
	for (int i = 0; i < soluongcauhoi; i++)
	{
		dachon[i] = false;
	}
	srand(time(NULL));

	int i = 0;
	while (i < soluongcauhoi)
	{
		int idngaunhien = rand() % soluongcauhoi;
		if (!dachon[idngaunhien])
		{
			ketqua[i++] = A[idngaunhien];
			dachon[idngaunhien] = true;
		}
	}

	delete[] dachon;
	return 1;
}

void InCauHoiThi(CauHoiThi* cauhoithi)
{
	while (cauhoithi != NULL)
	{
		cout << cauhoithi->Id << " " << cauhoithi->Noidung.c_str() << endl;
		cout << "A. " << cauhoithi->A.c_str() << endl;
		cout << "B. " << cauhoithi->B.c_str() << endl;
		cout << "C. " << cauhoithi->C.c_str() << endl;
		cout << "D. " << cauhoithi->D.c_str() << endl;
		cout << cauhoithi->Dapan << endl;
		cauhoithi = cauhoithi->next;
	}
}

//Ham doc du lieu cau hoi

CauHoiThi* DocCauHoiThi2(CauHoiThi* cauhoithi, const string& filename)
{
	ifstream filecauhoi(filename);
	if (!filecauhoi.is_open())
	{
		cout << "Khong the mo file cau hoi cho mon hoc: " << endl;
		return NULL;
	}
	string id, noidung, a, b, c, d, dapan;
	while (getline(filecauhoi, id) && getline(filecauhoi, noidung) && getline(filecauhoi, a) && getline(filecauhoi, b) && getline(filecauhoi, c) && getline(filecauhoi, d) && getline(filecauhoi, dapan))
	{
		CauHoiThi* cauhoi = NULL;
		cauhoi = new CauHoiThi();
		cauhoi->Id = stoi(id);
		cauhoi->Noidung = noidung;
		cauhoi->A = a;
		cauhoi->B = b;
		cauhoi->C = c;
		cauhoi->D = d;
		cauhoi->Dapan = dapan[0];
		cauhoi->next = cauhoithi;
		cauhoithi = cauhoi;

		
		
	}
	filecauhoi.close();
	return cauhoithi;
}

void DocCauHoiThi(DSMonHoc*& dsmonhoc) 
{
	ifstream file("DanhSachMonHoc.txt");
	if (!file.is_open()) {
		cout << "Khong the mo duoc file" << endl;
		return;
	}

	string mamh, tenmh, filename;
	while (getline(file, mamh))
	{
		if (getline(file, tenmh) && getline(file, filename))
		{
			DSMonHoc* monhoc = NULL;
			if (TimMonHoc(dsmonhoc, mamh) == NULL)
			{
				monhoc = new DSMonHoc();
				monhoc->Mamh = mamh;
				dsmonhoc = ThemMonHoc(dsmonhoc, mamh, tenmh);
				monhoc = TimMonHoc(dsmonhoc, mamh);
				monhoc->Cauhoithi = DocCauHoiThi2(monhoc->Cauhoithi, filename);
				
			}
			else
			{
				monhoc = TimMonHoc(dsmonhoc, mamh);
			}
			
			
		}
	}

	file.close();
	cout << "Da doc cau hoi thi tu cac file thanh cong!" << endl;
}

void GhiCauHoiThi(CauHoiThi* cauhoithi, const string& filename) 
{
	ofstream file(filename);
	if (!file.is_open()) {
		cout << "Khong the mo duoc file de ghi" << endl;
		return;
	}

	while (cauhoithi != NULL) 
	{
		file << cauhoithi->Id << endl;
		file << cauhoithi->Noidung << endl;
		file << cauhoithi->A << endl;
		file << cauhoithi->B << endl;
		file << cauhoithi->C << endl;
		file << cauhoithi->D << endl;
		file << cauhoithi->Dapan << endl;
		cauhoithi = cauhoithi->next;
	}

	file.close();
	cout << "Da ghi cau hoi thi vao file thanh cong!" << endl;
}



//Ham hien thi

void InDanhSachLop(DSLop dslop)
{
	if (dslop.so_luong_lop == 0)
	{
		cout << "Hien chua co lop" << endl;
		return;
	}
	for (int i = 0; i < dslop.so_luong_lop; i++)
	{
		Lop* temp = dslop.lop[i];
		if (temp != NULL)
		{
			cout << temp->Malop << " " << temp->Tenlop << " ";
			SinhVien* tmp = temp->Sinhvien;
			while (tmp != NULL)
			{
				cout << tmp->Masv << " ";
				tmp = tmp->next;
			}
			cout << endl;
		}
	}
}

void InDanhSachLop2(DSLop dslop)
{
	if (dslop.so_luong_lop == 0)
	{
		cout << "Hien chua co lop" << endl;
		return;
	}
	for (int i = 0; i < dslop.so_luong_lop; i++)
	{
		Lop* temp = dslop.lop[i];
		if (temp != NULL)
		{
			cout << temp->Malop << " " << temp->Tenlop << " "<<endl;
			SinhVien* tmp = temp->Sinhvien;
			printf("+---------------+--------------------+----------+------+---------------+\n");
			printf("| %-13s | %-18s | %-8s | %-3s | %-13s |\n", "Ma SV", "Ho", "Ten", "Phai", "Mat Khau");
			printf("+---------------+--------------------+----------+------+---------------+\n");
			while (tmp != NULL)
			{
				printf("| %-13s | %-18s | %-8s | %-4s | %-13s |\n", tmp->Masv.c_str(), tmp->Ho.c_str(), tmp->Ten.c_str(), tmp->Phai.c_str(), tmp->Password.c_str());
				tmp = tmp->next;
			}
			printf("+---------------+--------------------+----------+------+---------------+\n");
		}
	}
}

void InDanhSachMonHoc(DSMonHoc* dsmonhoc) 
{
	if (dsmonhoc == nullptr)
	{
		return;
	}
	InDanhSachMonHoc(dsmonhoc->left);
	cout << dsmonhoc->Mamh << " " << dsmonhoc->Tenmh << endl;
	InDanhSachMonHoc(dsmonhoc->right);
}


void InDanhSachCauHoiThi(DSMonHoc* dsmonhoc) {
	if (dsmonhoc == NULL) return;

	cout << "Danh sach cau hoi thi cua mon hoc " << dsmonhoc->Mamh << ": " << endl;
	CauHoiThi* cauhoi = dsmonhoc->Cauhoithi;
	while (cauhoi != NULL) 
	{
		cout << "ID: " << cauhoi->Id << endl;
		cout << "Noi dung: " << cauhoi->Noidung << endl;
		cout << "A: " << cauhoi->A << endl;
		cout << "B: " << cauhoi->B << endl;
		cout << "C: " << cauhoi->C << endl;
		cout << "D: " << cauhoi->D << endl;
		cout << "Dap an: " << cauhoi->Dapan << endl;
		cout << endl;
		cauhoi = cauhoi->next;
	}

	InDanhSachCauHoiThi(dsmonhoc->left);
	InDanhSachCauHoiThi(dsmonhoc->right);
}


//Giai phong bo nho
void giaiPhongDiemThi(DiemThi*& head) 
{
	while (head != NULL) 
	{
		DiemThi* temp = head;
		head = head->next;
		delete temp;
	}
}

void giaiPhongSinhVien(SinhVien*& head) 
{
	while (head != NULL) 
	{
		SinhVien* temp = head;
		giaiPhongDiemThi(temp->Diemthi);
		head = head->next;
		delete temp;
	}
}

void giaiPhongCauHoiThi(CauHoiThi*& head) 
{
	while (head != NULL) 
	{
		CauHoiThi* temp = head;
		head = head->next;
		delete temp;
	}
}

void giaiPhongMonHoc(DSMonHoc* root) 
{
	if (root == nullptr) return;
	giaiPhongCauHoiThi(root->Cauhoithi);
	giaiPhongMonHoc(root->left);
	giaiPhongMonHoc(root->right);
	delete root;
}




int main()
{
	DSLop dslop;
	DocDuLieu(dslop, "SinhVien.csv");
	DSMonHoc* dsmonhoc = NULL;
	CauHoiThi* cauhoithi = NULL;
	DocCauHoiThi(dsmonhoc);
	int check = DangNhap(dslop);
	if (check == 1)
	{	
		int luachon;
		std::cout << "1. Them Lop"<<endl;
		std::cout << "2. In Danh Sach Lop" << endl;
		std::cout << "3. Nhap Sinh Vien Cua Lop" << endl;
		std::cout << "4. Them Mon Hoc" << endl;
		std::cout << "5. Hien Thi Mon Hoc" << endl;
		std::cout << "6. Xoa Mon Hoc" << endl;
		std::cout << "7. Hieu Chinh Mon Hoc" << endl;
		std::cout << "8. Nhap Cau Hoi Thi" << endl;
		std::cout << "9. In Cau Hoi Thi" << endl;
		std::cout << "10. In tat ca cau hoi thi" << endl;
		std::cout << "11. Xoa Cau Hoi" << endl;
		std::cout << "0. Thoat" << endl;
		while (1)
		{
			cout << "Nhap su lua chon cua ban: ";
			cin >> luachon;
			if (luachon == 0)
			{
				break;
			}
			switch (luachon)
			{
			case 1:
				NhapLop(dslop);
				break;
			case 2:
				InDanhSachLop2(dslop);
				break;
			case 3:
			{
				string check;
				cout << "Nhap lop can them: ";
				cin >> check;
				if (KiemTraLop(dslop, check) >= 0)
				{
					NhapSinhVienCuaLop(dslop, check);
					cout << "Ban co chac chan muon nhap sinh vien vao lop?Y/N: ";
					char choice;
					cin >> choice;
					if (choice == 'Y')
					{
						GhiDuLieu(dslop, "SinhVien.csv");
					}
				}
				break;
			}
			case 4:
				NhapMonHoc(dsmonhoc);
				break;
			case 5:
				InDanhSachMonHoc(dsmonhoc);
				break;
			case 6:
			{
				string mamh;
				cout << "Nhap ma mon hoc can xoa: ";
				cin >> mamh;
				dsmonhoc = XoaMonHoc(dsmonhoc, mamh);
				break;
			}
			case 7:
			{
				string mamh;
				cout << "Nhap ma mon hoc can sua: ";
				cin >> mamh;
				dsmonhoc = HieuChinhMon(dsmonhoc, mamh);
				break;
			}
			case 8:
			{
				string mamh;
				cout << "Nhap ma mon hoc can them: ";
				cin >> mamh;
				DSMonHoc* monhoc = TimMonHoc(dsmonhoc, mamh);
				if (monhoc == NULL)
				{
					cout << "Khong tim thay mon hoc" << endl;
					break;
				}
				else
				{
					NhapCauHoiThi(monhoc->Cauhoithi);
					char check;
					cout << "Ban co muon ghi cau hoi thi khong? Y/N: ";
					cin >> check;
					if (check == 'Y')
					{
						string filename = monhoc->Mamh + "_CauHoiThi.txt";
						cout << filename << endl;
						GhiCauHoiThi(monhoc->Cauhoithi, filename);
					}

					
				}

				break;
			}
			case 9: 
			{
				string mamh;
				cout << "Nhap ma mon hoc can xem: ";
				cin >> mamh;

				DSMonHoc* monhoc = TimMonHoc(dsmonhoc, mamh);
				if (monhoc == NULL) {
					cout << "Khong tim thay mon hoc" << endl;
					break;
				}
				else {
					if (monhoc->Cauhoithi == NULL)
					{
						cout << "khong co cau hoi" << endl;
					}
					else
					{
						cout << "Danh sach cau hoi thi cua mon hoc " << monhoc->Tenmh << " (" << monhoc->Mamh << "):" << endl;
						InCauHoiThi(monhoc->Cauhoithi); // In câu hỏi thi của môn học tìm được
					}

				}
				cout << SoLuongCauHoi(monhoc->Cauhoithi);
				break;
			}
			case 10:
				InDanhSachCauHoiThi(dsmonhoc);
				break;
			case 11:
			{
				int id;
				string mamh;
				cout << "Nhap ma mon hoc can xoa: ";
				cin >> mamh;
				DSMonHoc* monhoc = TimMonHoc(dsmonhoc, mamh);
				if (monhoc == NULL)
				{
					cout << "khong ton tai mon hoc" << endl;
					continue;
				}
				cout << "Nhap id cau hoi can xoa: ";
				cin >> id;
				if (KiemTraCauHoi(monhoc->Cauhoithi, id) == false)
				{
					cout << "Khong co id nay" << endl;
					continue;
				}
				XoaCauHoi(monhoc->Cauhoithi, id);
				cout << "Ban co chac chan mon xoa?Y/N: ";
				char check;
				cin >> check;
				if (check == 'Y')
				{
					string filename = monhoc->Mamh + "_CauHoiThi.txt";
					cout << filename << endl;
					GhiCauHoiThi(monhoc->Cauhoithi, filename);
				}
				break;
			}
				
			}
		}
	}
	else if (check == 2)
	{
		InDanhSachMonHoc(dsmonhoc);
		string mamh;
		std::cout << "Nhap ma mon hoc can thi: ";
		cin >> mamh;
		DSMonHoc* monhoc = TimMonHoc(dsmonhoc, mamh);
		if (monhoc != NULL)
		{
			int soluong = SoLuongCauHoi(monhoc->Cauhoithi);
			int *A = new int[soluong];
			CauHoiThi* tmp = monhoc->Cauhoithi;
			for (int i = 0; i < soluong; ++i)
			{
				if (tmp == NULL)
				{
					cout << "Loi" << endl;
					break;
				}
				A[i] = tmp->Id;
				tmp = tmp->next;
			}

			cout << "Nhap so luong cau hoi muon thi: ";
			int soluongcauhoi;
			cin >> soluongcauhoi;
			int* ketqua = new int[soluongcauhoi];
			if (LayNgauNhienId(A, soluong, soluongcauhoi, ketqua))
			{
				cout << "ID NGAU NHIEN: ";
				for (int i = 0; i < soluongcauhoi; i++)
				{
					cout<<ketqua[i]<<" ";
				}
			}

			delete[] ketqua;
			delete[] A;
			
		}
		else
			cout << "Sai ma mon hoc" << endl;
	}
	

	for (int i = 0; i < dslop.so_luong_lop; ++i) 
	{
		giaiPhongSinhVien(dslop.lop[i]->Sinhvien);
		delete dslop.lop[i];
	}
	
	giaiPhongMonHoc(dsmonhoc);
	/*giaiPhongCauHoiThi(dsmonhoc->Cauhoithi);*/
	/*giaiPhongDSSinhVien(head);*/
	return 0;
}