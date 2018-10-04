#include<iostream>
#include<cstdlib>
#include<string>
#include<fstream>

using namespace std;

void AccessPointConnect(void){
    system("ssh pi@akashiaspoint.local");
    system("AkashiRoboB");
}

void sendFile(string filename){
    string scp("sshpass -p 'a' scp ");
    string adr(" pi@tapioka.local:/home/pi/Image_recognition_akashi2018");
    string putcommand = scp + filename + adr;
    const char* cstr = putcommand.c_str();
    system(cstr);
}

int readFile(string readfilename){
    ifstream servefile(readfilename);
    string tabledata;

    if (servefile.fail()) {
        cerr << "Failed to open file." << endl;
        return -1;
    }
    int a[5];
    int i = 0;
    while (getline(servefile,tabledata)) {
        ++i;
        //cout << tabledata << endl;
	const char* num = tabledata.c_str();
        a[i] = atoi(num);
        cout << i << ":" <<a[i] << endl;
    }
    return 0;
}


