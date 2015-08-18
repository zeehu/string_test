/***************************************************************************
 * 
 * Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file filter_nonChn.cpp
 * @author gongcaixia(com@baidu.com)
 * @date 2015/05/15 09:43:56
 * @brief 
 *  
 **/

#include<iostream>
#include<fstream>
#include<string>

using namespace std;
bool is_chn(string str)
{
    unsigned index;
    for(index=0;index<str.length();index++)
    {
        unsigned char lo=str[index];
        if(lo<=127) return false;
        unsigned char hi=str[++index];
        if(hi==0x7F) return false;
        else
        {

            if(lo>=0x81 && lo<=0xA0 && hi>=0x40 && hi<=0xFE) continue;
            if(lo>=0xB0 && lo<=0xF7 && hi>=0x40 && hi<=0xFE) continue;
            if(lo>=0xAA && lo<=0xAF && hi>=0x40 && hi<=0xA0) continue;
            if(lo>=0xF8 && lo<=0xFE && hi>=0x40 && hi<=0xA0) continue;
			if(lo==0xA3 && ((hi>=0xB0 && hi<=0xB9) || (hi>=0xC1 && hi<=0xDA) || (hi>=0xE1 && hi<=0xFA)) continue;
            return false;
        }
    }
    return true;
}

int main(int argc, char *argv[])
{
    if(argc<4){
        cout<<"usage: "<<argv[0]<<" ifile ofile_chn ofile_non_chn\n";
        return 0;
    }

    string ifile=argv[1];
    string ofile1=argv[2];
    string ofile2=argv[3];

    ifstream in(ifile.c_str());
    if(!in){
        cerr<<"can not open "<<ifile<<" for reading\n";
        return -1;
    }

    ofstream out1(ofile1.c_str());
    if(!out1){
        cerr<<"can not open "<<ofile1<<" for writing\n";
        return -1;
    }

    ofstream out2(ofile2.c_str());
    if(!out2){
        cerr<<"can not open "<<ofile2<<" for writing\n";
        return -1;
    }

    string line="";
    while(getline(in,line)){
        if(line=="") continue;
        
        bool is_chn_str=true;
        for(int i=0; i<line.length();i++){
            char c=line[i];
            if(c<0){
                string str=line.substr(i,2);
                if(!is_chn(str)){
                    is_chn_str=false;
                    break;
                }
                i++;
            }else if(c!=' ' && c!='.'){
                is_chn_str=false;
                break;
            }
        }

        if(is_chn_str) 
            out1<<line<<endl;
        else 
            out2<<line<<endl;
    }

    in.close();
    out1.close();
    out2.close();
}

















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */

