#pragma once

#include<iostream>
#include<cstdlib>
#include<string>
#include<fstream>

using namespace std;

namespace FRW{

    void write(string filename,int tabledata[3]){
        ofstream txt(filename);
        int i = 0;
        while(i < 3){
            txt << tabledata[i] << "\n";
            ++i;
        }
        txt.close();
    }


    void send(string filename){
        string scp("sshpass -p 'a' scp ");
        string adr(" pi@tapioka.local:/home/pi/Image_recognition_akashi2018");
        string putcommand = scp + filename + adr;
        const char* cstr = putcommand.c_str();
        system(cstr);
    }

    int readRed(string readfilename,int sendPlace[3]){
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
            //cout << i << ":" <<TablePlace[i] << endl;
            i = i+1;
        }
        servefile.close();
        return 0;
    }

    int readBlue(string readfilename,int sendPlace[3]){
        ifstream servefile(readfilename);
        string tabledata;
        int a = 0;
        int b = 0;

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
            //cout << i << ":" <<TablePlace[i] << endl;
            i = i+1;
        }
        a = sendPlace[0];
        b = sendPlace[2];

        sendPlace[0] = b;
        sendPlace[2] = a;
        servefile.close();
        return 0;
    }


}

