#include<iostream>
#include<string>
#include<fstream>

using namespace std;
struct Hasta {
	char ID[5]{};
	string ad{};
	string soyad{};
	int yas{};
	string sehir{};
	string sonas�tarih{}; //GG.AA.YYYY
	int dozNo{};  //0, 1, 2
	char tur{};  //X, Y
	Hasta() {};
};
void sisteme_kay�t(struct Hasta* ptr, int* psayac) {
	struct Hasta hasta;
	while (1) { //ID->HHRR formda almak i�in while loop
		cout << "ID giriniz:(HHRR form H:harf, R:rakam):";
		cin >> hasta.ID;
		//cin.getline(hasta.ID, 4);
		if (isalpha(hasta.ID[0]) != 0 && isalpha(hasta.ID[1]) != 0 && isdigit(hasta.ID[2]) != 0 && isdigit(hasta.ID[3]) != 0) {
			break; //ilk iki har ve son iki rakam ise dur
		}
		else {
			cout << "Hatali formda ID girdiniz!" << endl;
			cout << "Tekrar ";
		}
	}
	cout << "Ad:"; //verileri kullan�c�dan alma
	cin >> hasta.ad;
	cout << "Soyad:";
	cin >> hasta.soyad;
	cout << "Yas(Age):";
	cin >> hasta.yas;
	cout << "Sehir:";
	cin >> hasta.sehir;
	//default degerler:
	hasta.sonas�tarih = "01.06.2020";
	hasta.dozNo = 0;
	hasta.tur = '\0';

	fstream myFile;
	myFile.open("database.txt", ios::app); //append - ekle 
	myFile << *(psayac)+1 << "- ";
	myFile << hasta.ID << " ";
	myFile << hasta.ad << " ";
	myFile << hasta.soyad << " ";
	myFile << hasta.yas << " ";
	myFile << hasta.sehir << " ";
	myFile << hasta.sonas�tarih << " ";
	myFile << hasta.dozNo << " ";
	myFile << hasta.tur << endl;
	myFile.close();
	cout << "Kaydolma Basarili!" << endl;

	*(ptr + *psayac) = hasta;
	*psayac = *psayac + 1;
}
void kayitgoruntule(struct Hasta* ptr, int* psayac) { //kay�t g�r
	char tempID[5];
	int flag = 0;
	while (1) { //Dogru ID girildi�ini saptamak icin while loop
		cout << "Kayit gormek istediginiz hastanin ID'sini giriniz:";
		cin >> tempID;
		for (int i = 0; i < *psayac; i++) {
			if (string(ptr[i].ID) == string(tempID)) {
				cout << ptr[i].ID << " ";
				cout << ptr[i].ad << " ";
				cout << ptr[i].soyad << " ";
				cout << ptr[i].yas << " ";
				cout << ptr[i].sehir << " ";
				cout << ptr[i].sonas�tarih << " ";
				cout << ptr[i].dozNo << " ";
				cout << "-" << ptr[i].tur << "-" << endl;
				flag++;
				break;
			}
		}
		if (flag == 0) {
			cout << "Gecersiz/kayitli olmayan ID girdiniz tekrar deneyin" << endl;
		}
		else {
			break;
		}
	}
}
void kayitdegistir(struct Hasta* ptr, int* psayac) { //kay�t g�ncelle
	char tempID[5];
	int flag = 0;
	int number;
	while (1) { //Dogru ID girildi�ini saptamak icin while loop
		cout << "Kayit gormek istediginiz hastanin ID'sini giriniz:";
		cin >> tempID;
		for (int i = 0; i < *psayac; i++) {
			if (string(ptr[i].ID) == string(tempID)) {
				//buraya  cin ile de�i�ikler al�can
				cout << "1-Ad   " << "2-soyad   " << "3-yas   " << "4-Sehir" << endl;
				cout << "Guncellemek istediginiz numara girin:";
				cin >> number;
				if (number == 1) {
					cout << "Yeni ad degeri: ";
					cin >> ptr[i].ad;
				}
				else if (number == 2) {
					cout << "Yeni soyad degeri: ";
					cin >> ptr[i].soyad;
				}
				else if (number == 3) {
					cout << "Yeni yas degeri: ";
					cin >> ptr[i].yas;
				}
				else if (number == 4) {
					cout << "Yeni sehir degeri: ";
					cin >> ptr[i].sehir;
				}
				else {
					cout << "Gecersiz sayi degeri girdiniz!" << endl;
				}
				flag++;
				break;
			}
		}//end for loop
		if (flag == 0) {
			cout << "Gecersiz/kayitli olmayan ID girdiniz tekrar deneyin" << endl;
		}
		else {
			break;
		}
	}//end while loop
}
void asikayit(struct Hasta* ptr, int* psayac) {
	//yeni a�� kay�t
	char tempID[5];
	string todaydate;
	int flag = 0; //Girilen ID kayit kontrol bayrag�
	while (1) { //Dogru ID girildi�ini saptamak icin while loop
		cout << "Asi kayit istediginiz hastanin ID'sini giriniz:";
		cin >> tempID;
		for (int i = 0; i < *psayac; i++) {
			if (string(ptr[i].ID) == string(tempID)) {
				if (ptr[i].yas >= 18) { //Yas kontrol noktasi
					if (ptr[i].dozNo < 2) { //Doz no kontrol noktasi
						cout << "GG.AA.YYYY formda bugugun tarihini giriniz:";
						cin >> todaydate;
						// Comparing last two numbers of years 
						if ((int(todaydate[8]) * 10 + int(todaydate[9])) > (int(ptr[i].sonas�tarih[8]) * 10 + int(ptr[i].sonas�tarih[9]))) { //A�� verildi
							char tempname;
							while (1) {
								cout << "Asi seciniz(X or Y):";
								cin >> tempname;
								if ((ptr[i].tur) == '\0' || ptr[i].tur == tempname) {
									ptr[i].tur = tempname;
									cout << "Girdiginiz tarihte Asi kayit olusturdunuz." << endl;
									ptr[i].sonas�tarih = todaydate; //tarih kayit
									ptr[i].dozNo = ptr[i].dozNo + 1; //Doz no +1
									flag++;
									break;
								}
								else {
									cout << "Bu asi uygun degil. Lutfen baska seciniz. ";
								}
							}
							break;
						}
						else if ((int(todaydate[8]) * 10 + int(todaydate[9])) == (int(ptr[i].sonas�tarih[8]) * 10 + int(ptr[i].sonas�tarih[9]))) { //Ay 
							if ((int(todaydate[3]) * 10 + int(todaydate[4])) - (int(ptr[i].sonas�tarih[3]) * 10 + int(ptr[i].sonas�tarih[4])) == 1) { //Gun bak
								//1 ay 30 gun dusunursek
								if ((int(todaydate[1]) * 10 + int(todaydate[0])) + (30 - (int(ptr[i].sonas�tarih[1]) * 10 + int(ptr[i].sonas�tarih[0]))) >= 30) {
									//Aylar ardisik ise g�n fark� 30 olmal�
									char tempname;
									while (1) {
										cout << "Asi seciniz(X or Y):";
										cin >> tempname;
										if (ptr[i].tur == NULL || ptr[i].tur == tempname) {
											ptr[i].tur == tempname;
											cout << "Girdiginiz tarihte Asi kayit olusturdunuz." << endl;
											ptr[i].sonas�tarih = todaydate; //tarih kayit
											ptr[i].dozNo = ptr[i].dozNo + 1; //Doz no +1
											flag++;
											break;
										}
										else {
											cout << "Bu asi uygun degil. Lutfen baska seciniz. ";
										}
									}
									break;
								}
								else { //g�n farki ile Asi verilmedi
									cout << "Yeni asi verilemedi.Talep reddedildi." << endl;
									flag++;
									break;
								}
							}
							else if ((int(todaydate[3]) * 10 + int(todaydate[4])) - (int(ptr[i].sonas�tarih[3]) * 10 + int(ptr[i].sonas�tarih[4])) >= 2) { //ver
								char tempname;
								while (1) {
									cout << "Asi seciniz(X or Y):";
									cin >> tempname;
									if (ptr[i].tur == '\0' || ptr[i].tur == tempname) {
										ptr[i].tur == tempname;
										cout << "Girdiginiz tarihte Asi kayit olusturdunuz." << endl;
										ptr[i].sonas�tarih = todaydate; //tarih kayit
										ptr[i].dozNo = ptr[i].dozNo + 1; //Doz no +1
										flag++;
										break;
									}
									else {
										cout << "Bu asi uygun degil. Lutfen baska seciniz. ";
									}
								}
								break;
							}
							else { //Tarihte ay tutmad��� icin verilmedi
								cout << "Yeni asi verilemedi. Son asidan 1 ay ge�melidir. Talep reddedildi." << endl;
								flag++;
								break;
							}

						}
						else { //Tarihte yil nedeniyle verilemedi 
							cout << "Yeni asi verilemedi.Talep reddedildi." << endl;
							flag++;
							break;
						}
					}
					else if (ptr[i].dozNo == 2) { //Doz no nedeniyle verilemedi
						cout << "En fazla 2 doz olunabilir. Talep reddedildi." << endl;
						flag++;
						break;
					}
				}
				else { //yas nedeniyle verilemedi
					cout << "18 yasini doldurmaniz gerekmektedir!.Talep reddedildi." << endl;
					flag++;
					break;
				}
				//flag++;
				//break;
			}
		}
		if (flag == 0) {
			cout << "Gecersiz/kayitli olmayan ID girdiniz tekrar deneyin" << endl;
		}
		else {
			break;
		}
	}
}
int main() {
	//S�STEMDEN: hasta kay�t -- kay�d�n� g�r�nt�lemek --- kayd�n� g�ncelemek-- yeni a�� kayd� yapt�rmak 
	int sayac = 0; //txt ten veri al�rken ona at her zaman s�f�rlanmas�n 
	int* psayac = &sayac; //struct dizisinin kac struct tuttu�unu gosterir
	struct Hasta* ptr = new Hasta[1]; //Her yeni kay�tta size DMA ile arttirilacak


	int choice = 0;
	while (1) {
		cout << "Hangisini yapmak istersiniz:\n" << "1-Sisteme kayit  " << "2-Kayit goruntule ";
		cout << "3-Kayit Guncelle  " << "4-Yeni asi kayit  " << "5-Sistemden cikis " << endl;
		cin >> choice;
		if (choice == 1) {
			sisteme_kay�t(ptr, psayac);
			//Sruct array size artt�rma
			int size = *psayac + 1;
			struct Hasta* ptryeni;
			ptryeni = new Hasta[size]; //size arttirilmis DMA
			for (int i = 0; i < *psayac; i++) {
				ptryeni[i] = ptr[i]; //eski struct array yeniye gonder
			}
			delete[]ptr; //eski struct array bosalt
			ptr = ptryeni;
			ptryeni = NULL;
		}
		else if (choice == 2) {
			kayitgoruntule(ptr, psayac);
		}
		else if (choice == 3) {
			kayitdegistir(ptr, psayac);
		}
		else if (choice == 4) {
			asikayit(ptr, psayac);
		}
		else if (choice == 5) {
			//file yazma i�lemleri
			break;
		}
		else {
			cout << "Gecersiz secim.";
		}
		cout << endl;
	}
	delete[]ptr;
	ptr = NULL;
}