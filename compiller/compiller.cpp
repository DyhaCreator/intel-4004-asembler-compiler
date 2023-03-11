#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

void parser(vector<short> bytes, string out) {
    ofstream fout;
    fout.open(out);
    for (int i = 0; i < bytes.size(); i++) {
        if (bytes[i] >= 0x10) { 
            cout << hex << bytes[i] << " ";
        }
        else {
            cout << 0 << hex << bytes[i] << " ";
        }
        fout << char(bytes[i]);
    }
}

int addresing(vector<string> code, string addres) {
    int numAddres = 0;
    for (int i = 0; i < code.size();) {
        cout << "-" << code[i] << endl;
        if (code[i][code[i].size()-1] == ',') {
            if (code[i] == addres + ',') {
                return numAddres;
            }
            else {
                numAddres--;
            }
        }
        if (code[i] == "src" ||
            code[i] == "fin" ||
            code[i] == "jin" ||
            code[i] == "inc" ||
            code[i] == "add" ||
            code[i] == "sub" ||
            code[i] == "ld"  ||
            code[i] == "xch" ||
            code[i] == "bbl" ||
            code[i] == "ldm" ||
            code[i] == "jcn" ||
            code[i] == "fim" ||
            code[i] == "jsz") {
            i += 2;
        }
        else {
            i++;
        }
        numAddres++;
    }
    return -1;
}
int registerCode(string reg) {
    short byte;
    if (reg == "r0")byte = 0x0;
    else if (reg == "r1")byte = 0x1;
    else if (reg == "r2")byte = 0x2;
    else if (reg == "r3")byte = 0x3;
    else if (reg == "r4")byte = 0x4;
    else if (reg == "r5")byte = 0x5;
    else if (reg == "r6")byte = 0x6;
    else if (reg == "r7")byte = 0x7;
    else if (reg == "r8")byte = 0x8;
    else if (reg == "r9")byte = 0x9;
    else if (reg == "r10")byte = 0xA;
    else if (reg == "r11")byte = 0xB;
    else if (reg == "r12")byte = 0xC;
    else if (reg == "r13")byte = 0xD;
    else if (reg == "r14")byte = 0xE;
    else if (reg == "r15")byte = 0xF;

    return byte;
}

void lexer(vector<string> code, string out) {
    vector<short> bytes;
    for (int i = 0; i < code.size();) {
        cout << code[i] << endl;
        //тут идут самые простые
        if (code[i] == "nop") {
            bytes.push_back(0x00);
        }
        else if (code[i] == "wrm") {
            bytes.push_back(0xE0);
        }
        else if (code[i] == "wmp") {
            bytes.push_back(0xE1);
        }
        else if (code[i] == "wrr") {
            bytes.push_back(0xE2);
        }
        else if (code[i] == "wr0") {
            bytes.push_back(0xE4);
        }
        else if (code[i] == "wr1") {
            bytes.push_back(0xE5);
        }
        else if (code[i] == "wr2") {
            bytes.push_back(0xE6);
        }
        else if (code[i] == "wr3") {
            bytes.push_back(0xE7);
        }
        else if (code[i] == "sbm") {
            bytes.push_back(0xE8);
        }
        else if (code[i] == "rdm") {
            bytes.push_back(0xE9);
        }
        else if (code[i] == "rdr") {
            bytes.push_back(0xEA);
        }
        else if (code[i] == "adm") {
            bytes.push_back(0xEB);
        }
        else if (code[i] == "rd0") {
            bytes.push_back(0xEC);
        }
        else if (code[i] == "rd1") {
            bytes.push_back(0xED);
        }
        else if (code[i] == "rd2") {
            bytes.push_back(0xEE);
        }
        else if (code[i] == "rd3") {
            bytes.push_back(0xEF);
        }
        else if (code[i] == "clb") {
            bytes.push_back(0xF0);
        }
        else if (code[i] == "clc") {
            bytes.push_back(0xF1);
        }
        else if (code[i] == "iac") {
            bytes.push_back(0xF2);
        }
        else if (code[i] == "cmc") {
            bytes.push_back(0xF3);
        }
        else if (code[i] == "cma") {
            bytes.push_back(0xF4);
        }
        else if (code[i] == "ral") {
            bytes.push_back(0xF5);
        }
        else if (code[i] == "rar") {
            bytes.push_back(0xF6);
        }
        else if (code[i] == "tcc") {
            bytes.push_back(0xF7);
        }
        else if (code[i] == "dac") {
            bytes.push_back(0xF8);
        }
        else if (code[i] == "tcs") {
            bytes.push_back(0xF9);
        }
        else if (code[i] == "stc") {
            bytes.push_back(0xFA);
        }
        else if (code[i] == "daa") {
            bytes.push_back(0xFB);
        }
        else if (code[i] == "kbp") {
            bytes.push_back(0xFC);
        }
        else if (code[i] == "dcl") {
            bytes.push_back(0xFD);
        }
        //тут уже идут сложные
        //сначала те которые занимают 1 байт
        else if (code[i] == "src") {
            short byte;
            if (code[i+1] == "0p")byte = 0x1;
            else if (code[i+1] == "1p")byte = 0x3;
            else if (code[i + 1] == "2p")byte = 0x5;
            else if (code[i + 1] == "3p")byte = 0x7;
            else if (code[i + 1] == "4p")byte = 0x9;
            else if (code[i + 1] == "5p")byte = 0xB;
            else if (code[i + 1] == "6p")byte = 0xD;
            else if (code[i + 1] == "7p")byte = 0xF;
            
            bytes.push_back(0x20 + byte);
            i++;
        }
        else if (code[i] == "fin") {
            short byte;
            if (code[i + 1] == "0p")byte = 0x0;
            else if (code[i + 1] == "1p")byte = 0x2;
            else if (code[i + 1] == "2p")byte = 0x4;
            else if (code[i + 1] == "3p")byte = 0x6;
            else if (code[i + 1] == "4p")byte = 0x8;
            else if (code[i + 1] == "5p")byte = 0xA;
            else if (code[i + 1] == "6p")byte = 0xC;
            else if (code[i + 1] == "7p")byte = 0xE;

            bytes.push_back(0x30 + byte);
            i++;
        }
        else if (code[i] == "jin") {
            short byte;
            if (code[i + 1] == "0p")byte = 0x1;
            else if (code[i + 1] == "1p")byte = 0x3;
            else if (code[i + 1] == "2p")byte = 0x5;
            else if (code[i + 1] == "3p")byte = 0x7;
            else if (code[i + 1] == "4p")byte = 0x9;
            else if (code[i + 1] == "5p")byte = 0xB;
            else if (code[i + 1] == "6p")byte = 0xD;
            else if (code[i + 1] == "7p")byte = 0xF;

            bytes.push_back(0x30 + byte);
            i++;
        }
        else if (code[i] == "inc") {
            short byte = registerCode(code[i + 1]);

            bytes.push_back(0x60 + byte);
            i++;
        }
        else if (code[i] == "add") {
            short byte = registerCode(code[i + 1]);

            bytes.push_back(0x80 + byte);
            i++;
        }
        else if (code[i] == "sub") {
            short byte = registerCode(code[i + 1]);

            bytes.push_back(0x90 + byte);
            i++;
        }
        else if (code[i] == "ld") {
            short byte = registerCode(code[i + 1]);

            bytes.push_back(0xA0 + byte);
            i++;
        }
        else if (code[i] == "xch") {
            short byte = registerCode(code[i + 1]);

            bytes.push_back(0xB0 + byte);
            i++;
        }
        else if (code[i] == "bbl") {
            short byte;

            if (code[i + 1][0] == '$') {
                string str;
                str = code[i + 1].substr(1);
                byte = stoul(str, nullptr, 16);
            }
            else if (code[i + 1][0] == '%') {
                string str;
                str = code[i + 1].substr(1);
                byte = stoul(str, nullptr, 2);
            }
            else {
                byte = stoi(code[i + 1]);
            }

            bytes.push_back(0xC0 + byte);
            i++;
        }
        else if (code[i] == "ldm") {
            int num = 0;
            if (code[i + 1][0] == '$') {
                string str;
                str = code[i + 1].substr(1);
                num = stoul(str, nullptr, 16);
            }
            else if (code[i + 1][0] == '%') {
                string str;
                str = code[i + 1].substr(1);
                num = stoul(str, nullptr, 2);
            }
            else {
                num = stoi(code[i + 1]);
            }
            bytes.push_back(0xD0 + num);
            i++;
        }
        //тут те которые занимают 2 байта
        else if (code[i] == "jcn") {
            short byte;
            short addres;
            //определяем конфигурацию запроса
            if (code[i + 1] == "c0") {
                byte = 0xA;
            }
            else if (code[i + 1] == "c1") {
                byte = 0x2;
            }
            else if (code[i + 1] == "az") {
                byte = 0x4;
            }
            else if (code[i + 1] == "an") {
                byte = 0xC;
            }
            else if (code[i + 1][0] == '%') {
                string str;
                str = code[i + 1].substr(1);
                byte = stoul(str, nullptr, 2);
            }
            else if (code[i + 1][0] == '$') {
                string str;
                str = code[i + 1].substr(1);
                byte = stoul(str, nullptr, 16);
            }
            //определяем адрес перехода
            addres = addresing(code,code[i+2]);
            i += 2;
            bytes.push_back(0x10 + byte);
            bytes.push_back(addres);
        }
        else if (code[i] == "fim") {
            short byte;
            int data;
            if (code[i + 1] == "0p")byte = 0x0;
            else if (code[i + 1] == "1p")byte = 0x2;
            else if (code[i + 1] == "2p")byte = 0x4;
            else if (code[i + 1] == "3p")byte = 0x6;
            else if (code[i + 1] == "4p")byte = 0x8;
            else if (code[i + 1] == "5p")byte = 0xA;
            else if (code[i + 1] == "6p")byte = 0xC;
            else if (code[i + 1] == "7p")byte = 0xE;

            if (code[i + 2][0] == '$') {
                string str;
                str = code[i + 2].substr(1);
                data = stoul(str, nullptr, 16);
            }
            else if (code[i + 2][0] == '%') {
                string str;
                str = code[i + 2].substr(1);
                data = stoul(str, nullptr, 2);
            }
            else {
                data = stoi(code[i + 2]);
            }

            bytes.push_back(0x20 + byte);
            bytes.push_back(data);
            i+=2;
        }
        else if (code[i] == "jun") {
            short byte;

            byte = addresing(code, code[i + 1]);

            bytes.push_back(0x40);
            bytes.push_back(byte);
            i++;
        }
        else if (code[i] == "jms") {
            short addres;

            addres = addresing(code, code[i + 1]);

            bytes.push_back(0x50);
            bytes.push_back(addres);
            i++;
        }
        else if (code[i] == "jsz") {
            short byte;
            short addres;

            byte = registerCode(code[i + 1]);
            addres = addresing(code, code[i + 2]);

            bytes.push_back(0x70 + byte);
            bytes.push_back(addres);
            i += 2;
        }
        i++;
    }
    parser(bytes,out);
}

int main()
{
    string comand,inputFile,outputFile;
    string line;
    ifstream fin;
    ofstream fout;
    cout << line;
    cout << "start compiler\n";
    //запрашиваем данные о файлах у пользователя
    cin >> comand >> inputFile >> outputFile;
    cout << "\n" << comand << "\n" << inputFile << "\n" << outputFile << "\n\n";
    if (comand == "obj") {
        fin.open(inputFile);
        fout.open(outputFile);
        //проверяем открылся ли файл
        if (fin.is_open() && fout.is_open()) {
            //создаем массив токенов разделенных пробелами и энтерами
            vector<string> arr;
            string str;
            while (fin >> str) {
                arr.push_back(str);
            }
            lexer(arr,outputFile);
        }
        else {
            //это на случай если пользователь ошибся с названием файла
            cout << "file not found";
            return 1;
        }
    }
    return 0;
}