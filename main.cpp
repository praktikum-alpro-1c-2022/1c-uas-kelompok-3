#if defined _WIN64
    #define COMMAND "cls"
#elif defined __linux__
    #define COMMAND "clear"
#else 
    #define COMMAND "clear"
#endif

#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include <vector>
#include <limits>
#include <unistd.h>
#include <cmath>

using namespace std;

struct ticket{
    public:
        int jumlahTiket;
        int totalHarga;
        vector<string> codeKursi;
};

struct user{
    private:
        int id, input;
        string name;
        tm* time;
        ticket tickets;
    public:
        user(int id, string name, ticket* tickets, tm* time){
            this->id = id;
            this->name = name;
            this->tickets = *tickets;
            this->time = time;
        };
        user();
        int getId();
        string getName();
        int getTotalHarga();
        int getUangKembali();
        int getUangInput();
        vector<string> getCodeKursi();
        string getTanggalPemesanan();
        int getJumlahTiket();

};

ticket* createTicket(ticket* , int, string*);

int readInt(istream&, int*, int = -1, int = -1);

int readString(istream&, string*, int = -1, int = -1);

int countTotalHarga(tm*, int);

string int2Day(tm*);

string* readKursi();

void show2DVector(vector<vector<string>>);

string showVector(vector<string>, string);

void initChair(vector<vector<string>>*, int, int);

int binarySearch(vector<vector<string>>, vector<int>*, string);

int linearSearch(vector<vector<string>>, vector<int>*, string);

void showUser(vector<user>, long long*);

string int2ReadableFormat(string, int, string);

string int2ReadableFormat(string, long long, string);

void squarePrint(int, int);

int main(){
    vector<user> db;
    vector<vector<string>> chair;
    int m = 10, n = 10;
    initChair(&chair, m, n);
    int sisaKursi = m * n;
    int pilihan;
    do{
    do{
        cout << "    Selamat datang di bioskop K3\n" <<
                "====================================\n\n" <<
                "\tSilahkan pilih menu:\n" <<
                "\t------------------- \n" <<
                "\t1. Pembelian Tiket\n" <<
                "\t2. Cek sisa kursi\n" <<
                "\t3. Laporan penjualan tiket\n" <<
                "\t4. Keluar\n\n" <<
                "Masukan pilihan anda (1-4): ";
    
    }while(!readInt(cin, &pilihan, 1, 4));

    switch (pilihan) {
        case 1:
            {
            system(COMMAND);
            time_t now = time(0);
            tm* time = localtime(&now);
            int jml;
            do{
            jml = 0;
            cout << "\n\n         Pembelian Tiket \n" <<
                    "====================================\n\n" <<
                    "Harga Tiket:\n" <<
                    "\tSenin-Kamis\t: Rp40.000\n" <<
                    "\tJum'at\t\t: Rp45.000\n" <<
                    "\tSabtu-Minggu\t: Rp50.000\n\n" <<
                    "Masukan jumlah tiket yang akan dibeli: ";
            if(jml > sisaKursi) cout << "\nHanya tersisa " << sisaKursi << " kursi";
            }while(!readInt(cin, &jml, 1, sisaKursi));
            vector<string> codeKursi;
            int current = 0;
            cout << '\n';
            system(COMMAND);
            while(current < jml){
                squarePrint(3, (n-1)*5+2);
                cout << '\n';
                show2DVector(chair);
                string tmp;
                vector<int> index;
                cout << "\nSilahkan pilih kursi yang tersedia: ";
                if(readString(cin, &tmp, 2, 2) && linearSearch(chair, &index, tmp) && tmp != "--"){
                    codeKursi.push_back(tmp);
                    chair[index[0]][index[1]] = "--";
                    current++;
                    sisaKursi--;
                    system(COMMAND);
                }else cout << "Maaf, kursi " << tmp << " tidak tersedia!\n"; 
            }
            squarePrint(3, (n-1)*5+2);
            cout << '\n';
            show2DVector(chair);
            cout << "\nKursi " << showVector(codeKursi, ", ") << " telah dipesan!\n";

            string name;

            cout << "\nSilahkan masukan nama anda: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, name);
            system(COMMAND);

            int totalHarga = countTotalHarga(time, jml);

            ticket* t = new ticket();
            t->jumlahTiket = jml;
            t->totalHarga = totalHarga;
            t->codeKursi = codeKursi;

            user* usr = new user(db.size(), name, t, time);

            cout << "====================================\n\n" <<
                    "Tanggal Pemesanan\t: " << usr->getTanggalPemesanan() << '\n' <<
                    "Atas Nama\t\t: " << usr->getName() << '\n' <<
                    "Harga per Tiket\t\t: " << int2ReadableFormat("Rp", totalHarga / jml, ",-") << '\n' << 
                    "Harga total Tiket\t: " << int2ReadableFormat("Rp", usr->getTotalHarga(), ",-") << '\n' <<
                    "Kode Kursi yang Dipesan\t: " << showVector(usr->getCodeKursi(), ", ") << '\n' << 
                    "\n====================================\n\n";
            db.push_back(*usr);
            sleep(3);
            delete t;
            delete usr;
            break;
            }
        case 2:
            {
            system(COMMAND);
            cout << "\n\n";
            show2DVector(chair);
            vector<string> codeKursiAll;
            int counter = 0;
            for(int i = 0; i < db.size(); i++){
                for(int j = 0; j < db[i].getCodeKursi().size(); j++){
                    codeKursiAll.push_back(db[i].getCodeKursi()[j]);
                    counter++;
                }   
            }

            cout << "====================================\n\n" <<
                    "Jumlah Kursi yang Dipesan: " << counter << " [ " << showVector(codeKursiAll, ",  ") << " ]" << '\n' <<
                    "Jumlah Sisa Kursi: " << sisaKursi << '\n' <<
                    "Total kursi: " << chair.size() * chair[0].size() << '\n' << 
                    "\n====================================\n\n";
            sleep(3);
            break;
            }
        case 3:
            long long total;
            system(COMMAND);
            showUser(db, &total);
            cout << "Total Input\t\t\t: " << int2ReadableFormat("Rp", total, ",-");

            sleep(3);
            cout << "\n\n";
            
            break;
    }
    }while(pilihan != 4);
}

int user::getId(){
    return user::id;
}
string user::getName(){
    return user::name;
}
int user::getTotalHarga(){
    return user::tickets.totalHarga;
}
int user::getUangInput(){
    return user::input;
}
int user::getUangKembali(){
    return getUangInput() - getTotalHarga();
}
vector<string> user::getCodeKursi(){
    return user::tickets.codeKursi;
}
string user::getTanggalPemesanan(){
    return (int2Day(time) + ", " + to_string(time->tm_mday) + "-" + to_string(time->tm_mon+1) + "-" + to_string(time->tm_year + 1900));
}
int user::getJumlahTiket(){
    return user::tickets.jumlahTiket;
}

int readInt(istream& input, int* output, int min, int max){
    int tmp;
    if(!(input >> tmp)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nHarap masukan nilai yang valid!\n\n";
        return 0;
    }
    if(tmp < min && min != -1){
        cout << "Harap masukan nilai yang valid!\n\n";
        return 0;
    }else if(tmp > max && max != -1){
        cout << "Harap masukan nilai yang valid!\n\n";
        return 0;
    }else{ 
        *output = tmp;
        return 1;    
    }
}

int readString(istream& input, string* output, int min, int max){
    string tmp;
    input >> tmp;
    if(tmp.length() < min && min != -1 ){
        cout << "Harap masukan nilai yang valid";
        return 0;
    }else if(tmp.length() > max && max != -1){
        cout << "Harap masukan nilai yang valid";
        return 0;
    }else{
        *output = tmp;
        return 1;
    }
}

int countTotalHarga(tm* timeNow, int amountOf){
    int multiplier = 0;
    if(timeNow->tm_wday > 0 && timeNow->tm_wday < 5) multiplier = 40000;
    if(timeNow->tm_wday == 5) multiplier = 45000;
    else multiplier = 50000;

    int res = multiplier * amountOf;

    return res;
}

void show2DVector(vector<vector<string>> arr){
    for(int i = 0; i < arr.size(); i++){
        for(int j = 0; j < arr[0].size();j++){
            cout << arr[i][j] << "   ";
        }
        cout << endl;
    }
}

string showVector(vector<string> arr, string separator){
    string tmp = "";
    for(int i = 0; i < arr.size(); i++){
         tmp += arr[i];
         if(i != arr.size()-1) tmp += separator;
    }
    return tmp;
}

void initChair( vector<vector<string>>* arr, int m, int n ){
    for(int i = 0; i < m; i++){
        char c = 65 + i;
        vector<string> vtmp;
        for(int j = 0; j < n; j++){
            string tmp = "";
            tmp = tmp + c + to_string(j);
            vtmp.push_back(tmp);
        }
        arr->push_back(vtmp);
    }
}

int binarySearch(vector<string> arr, int l, int r, string x)
{
    while (l <= r) {
        int m = l + (r - l) / 2;
        if (arr[m] == x) return m;
        if(arr[m] < x) l = m + 1;
        else r = m - 1;                               
    }
    return -1;
}

int linearSearch(vector<vector<string>> arr, vector<int>* output,string target){
    for(int i = 0; i < arr.size(); i++){
        for(int j = 0; j < arr[0].size(); j++){
            if(arr[i][j] == target){
                *output = {i, j};
                return 1;
        }
    }
    }
    *output = {-1, -1};
    return 0;
}
string int2Day(tm* timeNow){
    switch (timeNow->tm_wday) {
        case 0:
            return "Minggu";
            break;
        case 1:
            return "Senin";
            break;
        case 2:
            return "Selasa";
            break;
        case 3:
            return "Rabu";
            break;
        case 4:
            return "Kamis";
            break;
        case 5:
            return "Jum'at";
            break;
        case 6:
            return "Sabtu";
            break;
        default:
            return "null";
            break;
    }
}

void showUser(vector<user> db, long long* output){
    *output = 0;
    for(int i = 0; i  < db.size(); i++){
        cout << "=========================================\n" <<
                "No.\t\t\t\t: " << db[i].getId() << '\n' <<
                "Nama\t\t\t\t: " << db[i].getName() << '\n' <<
                "Tanggal pemesanan\t\t: " << db[i].getTanggalPemesanan() << '\n' <<
                "Harga per Tiket\t\t\t: " << int2ReadableFormat("Rp", db[i].getTotalHarga() / db[i].getJumlahTiket(), ",-") << '\n' <<
                "Harga Total Tiket\t\t: " << int2ReadableFormat("Rp", db[i].getTotalHarga(), ",-") << '\n' << 
                "Kode Kursi Pesanan\t\t: " << showVector(db[i].getCodeKursi(), ", ") << '\n';
        *output += db[i].getTotalHarga();
    }
    cout << "=========================================\n";
}

string int2ReadableFormat(string prefix, int x, string suffix){
    string tmp = to_string(x);
    int multiplier = log10(x) / 3;
    if(log10(x) >= multiplier * 3){
        tmp.insert(tmp.length()-1 - (2 + (multiplier-1)*4), ".");
    }
    string res = prefix;
    res += tmp;
    res += suffix;
    return res;
}

string int2ReadableFormat(string prefix, long long x, string suffix){
    string tmp = to_string(x);
    int multiplier = log10(x) / 3;
    if(log10(x) >= multiplier * 3){
        tmp.insert(tmp.length()-1 - (2 + (multiplier-1)*4), ".");
    }
    string res = prefix;
    res += tmp;
    res += suffix;
    return res;
}

void squarePrint(int m, int n){
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            cout << "*";
        }
        cout << '\n';
    }
}
