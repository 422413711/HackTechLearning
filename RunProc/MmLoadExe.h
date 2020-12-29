#ifndef _MM_LOAD_EXE_H_
#define _MM_LOAD_EXE_H_


#include <Windows.h>


void ShowErrorExe(char *lpszText);


// �ж��Ƿ����ض�λ�����
BOOL IsExistRelocationTable(LPVOID lpBaseAddress);


// ģ��PE�����������ڴ�EXE�ļ���������
// lpData: �ڴ�EXE�ļ����ݵĻ�ַ
// dwSize: �ڴ�EXE�ļ����ڴ��С
// ����ֵ: �ڴ�EXE���ص����̵ļ��ػ�ַ
LPVOID MmRunExe(LPVOID lpData, DWORD dwSize);


// ����PE�ṹ,��ȡPE�ļ����ص��ڴ��ľ����С
// lpData: �ڴ�DLL�ļ����ݵĻ�ַ
// ����ֵ: ����PE�ļ��ṹ��IMAGE_NT_HEADERS.OptionalHeader.SizeOfImageֵ�Ĵ�С
DWORD GetSizeOfImageExe(LPVOID lpData);


// ���ڴ�DLL���ݰ�SectionAlignment��С����ӳ�䵽�����ڴ���
// lpData: �ڴ�DLL�ļ����ݵĻ�ַ
// lpBaseAddress: �ڴ�DLL���ݰ�SectionAlignment��С����ӳ�䵽�����ڴ��е��ڴ��ַ
// ����ֵ: �ɹ�����TRUE�����򷵻�FALSE
BOOL MmMapFileExe(LPVOID lpData, LPVOID lpBaseAddress);


// ����SectionAlignment
// dwSize: ��ʾδ����ǰ�ڴ�Ĵ�С
// dwAlignment: �����Сֵ
// ����ֵ: �����ڴ����֮���ֵ
DWORD AlignExe(DWORD dwSize, DWORD dwAlignment);


// �޸�PE�ļ��ض�λ����Ϣ
// lpBaseAddress: �ڴ�DLL���ݰ�SectionAlignment��С����ӳ�䵽�����ڴ��е��ڴ��ַ
// ����ֵ: �ɹ�����TRUE�����򷵻�FALSE
BOOL DoRelocationTableExe(LPVOID lpBaseAddress);


// ��дPE�ļ��������Ϣ
// lpBaseAddress: �ڴ�DLL���ݰ�SectionAlignment��С����ӳ�䵽�����ڴ��е��ڴ��ַ
// ����ֵ: �ɹ�����TRUE�����򷵻�FALSE
BOOL DoImportTableExe(LPVOID lpBaseAddress);


// �޸�PE�ļ����ػ�ַIMAGE_NT_HEADERS.OptionalHeader.ImageBase
// lpBaseAddress: �ڴ�DLL���ݰ�SectionAlignment��С����ӳ�䵽�����ڴ��е��ڴ��ַ
// ����ֵ: �ɹ�����TRUE�����򷵻�FALSE
BOOL SetImageBaseExe(LPVOID lpBaseAddress);


// ��ת��PE����ڵ㴦ִ��, ������ַ��ΪPE�ļ�����ڵ�IMAGE_NT_HEADERS.OptionalHeader.AddressOfEntryPoint
// lpBaseAddress: �ڴ�PE���ݰ�SectionAlignment��С����ӳ�䵽�����ڴ��е��ڴ��ַ
// ����ֵ: �ɹ�����TRUE�����򷵻�FALSE
BOOL CallExeEntry(LPVOID lpBaseAddress);


#endif