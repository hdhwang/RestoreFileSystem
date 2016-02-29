#include <afx.h>
#include <afxwin.h>
#include <string.h>

using namespace std;

#ifndef Restore_file_system_NTFS_H
#define Restore_file_system_NTFS_H

typedef struct Partion_entry{
	char booting_flag;
	char start_CHS[3];
	char type;
	char end_CHS[3];
	char start_LBA[4];
	char sec_size[4];
};

class Restore_file_system_NTFS{
public:
	Restore_file_system_NTFS();
	virtual~Restore_file_system_NTFS();
	void Start_analysis(CString filename, int type);

private:
	void Set_file_system(CString filename);
	char* IntToHexString(int _value);
	unsigned long GetFileSize (CString filename);
	unsigned long Start_LBA_Addr(CString filename, unsigned long filesize);
	Partion_entry Set_partion_entry(CString filename);

	void Unset_file_system(CString filename);
};


#endif