#include "StdAfx.h"
#include "Restore_file_system_NTFS.h"
#include <iostream>
#include <fstream>

Restore_file_system_NTFS::Restore_file_system_NTFS(){
}

Restore_file_system_NTFS::~Restore_file_system_NTFS(){
}

char* Restore_file_system_NTFS::IntToHexString(int _value){
	char _hexString[4];
	_hexString[0] = (_value >> 24) & 0xFF;
	_hexString[1] = (_value >> 16) & 0xFF;
	_hexString[2] = (_value >> 8) & 0xFF;
	_hexString[3] = _value & 0xFF;
	return _hexString;
}

void Restore_file_system_NTFS::Start_analysis(CString filename, int type){
	if(type==1){
		Set_file_system(filename);
	}
	else if(type==0){
		Unset_file_system(filename);
	}
}

void Restore_file_system_NTFS::Set_file_system(CString filename){
	Partion_entry rs1 = Set_partion_entry(filename);
	ofstream file1;
	file1.open(filename.GetBuffer(),ios::out||ios::binary);
	file1.seekp(446L,ios::cur);

	file1 << rs1.booting_flag;
	
	for(int i=2; i>=0; i--){
		file1 << rs1.start_CHS[i];
	}
	file1 << rs1.type;
	for(int i=2; i>=0; i--){
		file1 << rs1.end_CHS[i];
	}
	for(int i=3; i>=0; i--){
		file1 << rs1.start_LBA[i];
	}
	for(int i=3; i>=0; i--){
		file1 << rs1.sec_size[i];
	}
	file1.close();
}

unsigned long Restore_file_system_NTFS::GetFileSize (CString filename){
  // 파일의 크기를 저장할 변수 선언
 unsigned long size = 0;

  // 파일을 읽기모드, 이진모드로 연다
  // 파일열기의 성공여부를 확인
 ifstream f(filename.GetBuffer(), ios_base::in | ios_base::binary); 
 if(f.is_open() == 0){
      cout << "열기실패" << endl;
 }
  // 마무리로 파일 닫기
 f.seekg(0, ios_base::end);
 size  = f.tellg();
 f.close();
 
 return size;
}


unsigned long Restore_file_system_NTFS::Start_LBA_Addr(CString filename, unsigned long filesize){
  // 파일을 읽기모드, 이진모드로 연다
  // 파일열기의 성공여부를 확인
 int MAX_BUFSIZE=40960;
 int buf_count = 0;
 char* temp_buf = new char[MAX_BUFSIZE+1];
 ifstream f(filename.GetBuffer(), ios_base::in | ios_base::binary); 
 if(f.is_open() == 0){
      cout << "열기실패" << endl;
 }
 unsigned long addr=0;
 char ntfs_sig[7] = {0xEB, 0x52, 0x90, 0x4E, 0x54, 0x46, 0x53};
 char tmp2[7];
 int result;
 BOOL func_end=FALSE;
 while(!f.eof()){
	ZeroMemory(temp_buf,MAX_BUFSIZE+1);
	f.read(temp_buf,MAX_BUFSIZE);
	int start;
	if(buf_count==0) start = 32256;
	else start = 0;
	for(int i = start; i < MAX_BUFSIZE-6 ; i++){
		for(int j = 0 ; j < 7 ; j++){
			tmp2[j] = temp_buf[i+j];
		}
		result = strncmp(tmp2,ntfs_sig,7);
		if(result == 0){
			addr = (i+buf_count)/512;
			func_end =TRUE;
			break;
		}
	}
	if(func_end==TRUE) break;
	else{
		f.seekg(-6L,ios::cur);
		buf_count+=MAX_BUFSIZE;
	}
 }
 
 temp_buf=NULL;
 delete[] temp_buf;
 f.close();
 return addr;
}


Partion_entry Restore_file_system_NTFS::Set_partion_entry(CString filename){
	Partion_entry sp;
	//파일 크기 읽어옴
	unsigned long filesize = GetFileSize(filename);
	
	//부팅 플래그
	sp.booting_flag = 0x80;
	
	//파티션 시작 CHS
	sp.start_CHS[0] = 0x00;
	sp.start_CHS[1] = 0x01;
	sp.start_CHS[2] = 0x01;

	//파티션 타입
	sp.type = 0x07;

	//파티션 끝 CHS
	sp.end_CHS[0] = 0x80;
	sp.end_CHS[1] = 0x19;
	sp.end_CHS[2] = 0x1B;
	
	//파티션 시작 LBA
	int LBA_addr = Start_LBA_Addr(filename,filesize);;

	//10진수 정수 값을 16진수 문자열 값으로 변환
	char* tmp_LBA;
	tmp_LBA = IntToHexString(LBA_addr);
	for(int i = 0 ; i < 4 ; i++){
		sp.start_LBA[i] = tmp_LBA[i];
	}

	//섹터 크기
	//파티션 크기 계산
	int sec_size = (filesize/512) - 63;
	//10진수 정수 값을 16진수 문자열 값으로 변환
	char* tmp_size;
	tmp_size = IntToHexString(sec_size);
	for(int i = 0 ; i < 4 ; i++){
		sp.sec_size[i] = tmp_size[i];
	}

	return sp;
}

void Restore_file_system_NTFS::Unset_file_system(CString filename){
	ofstream file1;
	file1.open(filename.GetBuffer(),ios::out||ios::binary);
	file1.seekp(446L,ios::cur);
	for(int i=0; i < 64; i++){
		file1 << '\0';
	}
	file1.close();
}