#pragma once

#include<iostream>
#include<cstdlib>
#include<string>
#include<fstream>

using namespace std;

namespace TD{
    void Connect(void){
        system("ssh pi@akashiaspoint.local");
        system("AkashiRoboB");
    }

    void send(string filename){
        string scp("sshpass -p 'a' scp ");
        string adr(" pi@tapioka.local:/home/pi/Image_recognition_akashi2018");
        string putcommand = scp + filename + adr;
        const char* cstr = putcommand.c_str();
        system(cstr);
    }

    int read(string readfilename,int sendPlace[3]){
        ifstream servefile(readfilename);
        string tabledata;

        if (servefile.fail()) {
            cerr << "Failed to open file." << endl;
            return -1;
        }

        int i = 0;
        int TablePlace[3];
        while (getline(servefile,tabledata)) {
            //cout << tabledata << endl;
            const char* num = tabledata.c_str();
            TablePlace[i] = atoi(num);
            sendPlace[i] = TablePlace[i];
            cout << i << ":" <<TablePlace[i] << endl;//TablePlaceは関数外からも使用可能
            i = i+1;
        }
        return 0;
    }


}

