#include <iostream>
#include <iomanip>
using namespace std;

void JST(string kasus){
    system("cls");
    float berat[3];
    float rumus[4] = {0, 0, 0, 0};
    float miu = 0.1;
    int input[4][3] = {{1,0,0},{1,0,1},{1,1,0},{1,1,1}};
    int hasil[4] = {0,0,0,0};
    int target[4];
    int iterasi;
    int status[4] = {0, 0, 0, 0};

    if (kasus=="OR"){
        target[0]=0; target[1]=1; target[2]=1; target[3]=1;
    } else if(kasus=="AND"){
        target[0]=0; target[1]=0; target[2]=0; target[3]=1;        
    } else if(kasus=="ANDNOT"){
        target[0]=0; target[1]=0; target[2]=1; target[3]=0;        
    }
    
    cout << "============================= Studi Kasus " << kasus << endl;
    cout << endl;
    cout << "Masukkan Nilai Berat (x1) = "; cin >> berat[0];
    cout << "Masukkan Nilai Berat (x2) = "; cin >> berat[1];
    cout << "Masukkan Nilai Berat (x3) = "; cin >> berat[2];
    cout << "Masukkan Jumlah Iterasi   = "; cin >> iterasi;

    int iter=1, tambahIterasi, selesai=0, berhenti;
    while(selesai==0){
        for(iter; iter <= iterasi; iter++){
            int berhenti=0;
                cout << "|===================================================================================================| Iterasi ke- " << iter << endl;
                cout << "| Target|\t Hasil \t|\t Rumus \t|     Status    |\t w1 \t|\t w2 \t|\t w3 |\n";
                cout << "|---------------------------------------------------------------------------------------------------|" << endl;
                //Menghitung Rumus
                for(int i=0; i<4; i++){
                    rumus[i] = 0;
                    for(int j=0; j<3; j++){
                        rumus[i] += (input[i][j] * berat[j]);
                    }

                    //Menghitung Hasil
                    if(rumus[i] < -1e-3) {
                        hasil[i] = 0;
                    }else{
                        hasil[i] = 1;
                    }

                    //Menghitung Error
                    status[i]=target[i]-hasil[i];
                    
                    //Menghitung Bobot
                    if(status[i]!=0){
                        for (int j=0; j<3; j++){
                            berat[j] = berat[j] + miu * status[i] * input[i][j];
                            }
                        cout << fixed << setprecision(1);
                        cout << "| " << target[i] << "\t|\t" << hasil[i] << "\t|\t"  << rumus[i] << "\t|\t" << status[i] << "\t|\t" << berat[0] << "\t|\t" << berat[1] << "\t|\t" << berat[2] << " |" <<endl;
                    }else{
                        cout << fixed << setprecision(1);
                        cout << "| " << target[i] << "\t|\t" << hasil[i] << "\t|\t"  << rumus[i] << "\t|\t" << status[i] << "\t|\t" << berat[0] << "\t|\t" << berat[1] << "\t|\t" << berat[2] << " |" <<endl;
                        berhenti++;
                    }

                    //End State (Error=0 ditemukan)
                    if(berhenti==4){
                        iter=iterasi+1;
                        selesai=1;
                    }
                }   
                cout << "|---------------------------------------------------------------------------------------------------|" << endl;
                cout<<endl;
        }    
        if(selesai==0){
            //Menambah Iterasi
            cout<<"Tambah iterasi (0 untuk berhenti)    : "; cin>>tambahIterasi;
            if(tambahIterasi==0){
                selesai=1;
            }else{
                iterasi+=tambahIterasi;
            }
        }
    }
    cout << "        |===================================================================================|"<< endl;
    cout << "        |                           TARGET DITEMUKAN - PROGRAM SELESAI                      |"<< endl;
    cout << "        |-----------------------------------------------------------------------------------|"<< endl;
}
int main(){
    string kasus;
    int ulang = 1;
    while (ulang == 1) {
        cout << "===================================================\n";
        cout << "       FINAL PROJECT - Jaringan Sistem Syaraf      \n";
        cout << "=========== oleh Septianto - 22081010178 ==========\n";
        cout << endl;
        cout << "Pilih Studi Kasus: \n";
        cout << "1. OR\n";
        cout << "2. AND\n";
        cout << "3. AND NOT\n";
        
        int pilihan;
        cout << "Pilihanmu: "; cin >> pilihan;

        if (pilihan == 1) {
            kasus = "OR";
            JST(kasus);   
        } else if (pilihan == 2) {
            kasus = "AND";
            JST(kasus);   
        } else if (pilihan == 3) {
            kasus = "ANDNOT";
            JST(kasus);   
        }
        
        cout << "Tekan 1 untuk kembali, Tekan 0 untuk keluar: "; cin >> ulang;
    }
    return 0;
}
