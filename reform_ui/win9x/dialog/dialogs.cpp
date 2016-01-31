/**
 * @file	dialogs.cpp
 * @brief	ダイアログ ヘルパーの動作の定義を行います
 *
 * @author	$Author: yui $
 * @date	$Date: 2011/03/07 09:54:11 $
 */

#include "compiler.h"
#include "resource.h"
#include "strres.h"
#include "bmpdata.h"
#include "dosio.h"
#include "misc\tstring.h"
#include "commng.h"
#include "dialogs.h"
#include "np2.h"
#if defined(MT32SOUND_DLL)
#include "..\ext\mt32snd.h"
#endif

#if !defined(__GNUC__)
#pragma comment(lib, "winmm.lib")
#endif	// !defined(__GNUC__)

// ---- file select

static BOOL openFileParam(LPOPENFILENAME lpOFN, PCFSPARAM pcParam,
							LPTSTR pszPath, UINT uSize,
							BOOL (WINAPI * fnAPI)(LPOPENFILENAME lpofn))
{
	if ((lpOFN == NULL) || (pcParam == NULL) ||
		(pszPath == NULL) || (uSize == 0) || (fnAPI == NULL))
	{
		return FALSE;
	}

	std::tstring rTitle(LoadTString(pcParam->lpszTitle));
	std::tstring rFilter(LoadTString(pcParam->lpszFilter));
	std::tstring rDefExt(LoadTString(pcParam->lpszDefExt));

	for (std::tstring::iterator it = rFilter.begin(); it != rFilter.end(); ++it)
	{
#if !defined(_UNICODE)
		if (IsDBCSLeadByte(static_cast<BYTE>(*it)))
		{
			++it;
			if (it == rFilter.end())
			{
				break;
			}
			continue;
		}
#endif	// !defined(_UNICODE)
		if (*it == '|')
		{
			*it = '\0';
		}
	}

	lpOFN->lpstrTitle = rTitle.c_str();
	lpOFN->lpstrFilter = rFilter.c_str();
	lpOFN->lpstrDefExt = rDefExt.c_str();
	lpOFN->nFilterIndex = pcParam->nFilterIndex;
	lpOFN->lpstrFile = pszPath;
	lpOFN->nMaxFile = uSize;

	return (*fnAPI)(lpOFN);
}

BOOL dlgs_openfile(HWND hWnd, PCFSPARAM pcParam, LPTSTR pszPath, UINT uSize, int *pnRO)
{
	OPENFILENAME	ofn;
	BOOL			bResult;

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hWnd;
	ofn.Flags = OFN_FILEMUSTEXIST;

	if (pnRO == NULL)
	{
		ofn.Flags |= OFN_HIDEREADONLY;
	}

	bResult = openFileParam(&ofn, pcParam, pszPath, uSize, GetOpenFileName);

	if ((bResult) && (pnRO != NULL))
	{
		*pnRO = ofn.Flags & OFN_READONLY;
	}

	return bResult;
}


// ---- mimpi def file

static const FSPARAM fpMIMPI =
{
	MAKEINTRESOURCE(IDS_MIMPITITLE),
	MAKEINTRESOURCE(IDS_MIMPIEXT),
	MAKEINTRESOURCE(IDS_MIMPIFILTER),
	1
};

void dlgs_browsemimpidef(HWND hWnd, UINT16 res) {

	HWND	subwnd;
	TCHAR	path[MAX_PATH];
	LPCTSTR	p;

	subwnd = GetDlgItem(hWnd, res);
	GetWindowText(subwnd, path, NELEMENTS(path));
	if (dlgs_openfile(hWnd, &fpMIMPI, path, NELEMENTS(path), NULL)) {
		p = path;
	}
	else {
		p = str_null;
	}
	SetWindowText(subwnd, p);
}


// ---- list

void dlgs_setliststr(HWND hWnd, UINT16 res, const TCHAR **item, UINT items) {

	HWND	wnd;
	UINT	i;

	wnd = GetDlgItem(hWnd, res);
	for (i=0; i<items; i++) {
		SendMessage(wnd, CB_INSERTSTRING, (WPARAM)i, (LPARAM)item[i]);
	}
}

void dlgs_setlistuint32(HWND hWnd, UINT16 res, const UINT32 *item, UINT items) {
	HWND	wnd;
	UINT	i;
	TCHAR	str[16];

	wnd = GetDlgItem(hWnd, res);
	for (i=0; i<items; i++) {
		wsprintf(str, str_u, item[i]);
		SendMessage(wnd, CB_INSERTSTRING, (WPARAM)i, (LPARAM)str);
	}
}

void dlgs_setcbitem(HWND hWnd, UINT uID, PCCBPARAM pcItem, UINT uItems)
{
	HWND	hItem;
	UINT	i;
	int		nIndex;

	hItem = GetDlgItem(hWnd, uID);
	for (i=0; i<uItems; i++)
	{
		std::tstring rString(LoadTString(pcItem[i].lpcszString));
		nIndex = (int)SendMessage(hItem, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(rString.c_str()));
		if (nIndex >= 0)
		{
			SendMessage(hItem, CB_SETITEMDATA,
								(WPARAM)nIndex, (LPARAM)pcItem[i].nItemData);
		}
	}
}

void dlgs_setcbnumber(HWND hWnd, UINT uID, PCCBNPARAM pcItem, UINT uItems)
{
	HWND	hItem;
	UINT	i;
	TCHAR	szValue[16];
	int		nIndex;

	hItem = GetDlgItem(hWnd, uID);
	for (i=0; i<uItems; i++)
	{
		wsprintf(szValue, str_u, pcItem[i].uValue);
		nIndex = (int)SendMessage(hItem, CB_ADDSTRING, 0, (LPARAM)szValue);
		if (nIndex >= 0)
		{
			SendMessage(hItem, CB_SETITEMDATA,
								(WPARAM)nIndex, (LPARAM)pcItem[i].nItemData);
		}
	}
}

void dlgs_setcbcur(HWND hWnd, UINT uID, int nItemData)
{
	HWND	hItem;
	int		nItems;
	int		i;

	hItem = GetDlgItem(hWnd, uID);
	nItems = (int)SendMessage(hItem, CB_GETCOUNT, 0, 0);
	for (i=0; i<nItems; i++)
	{
		if (SendMessage(hItem, CB_GETITEMDATA, (WPARAM)i, 0) == nItemData)
		{
			SendMessage(hItem, CB_SETCURSEL, (WPARAM)i, 0);
			break;
		}
	}
}

int dlgs_getcbcur(HWND hWnd, UINT uID, int nDefault)
{
	HWND	hItem;
	int		nPos;

	hItem = GetDlgItem(hWnd, uID);
	nPos = (int)SendMessage(hItem, CB_GETCURSEL, 0, 0);
	if (nPos >= 0)
	{
		return (int)SendMessage(hItem, CB_GETITEMDATA, (WPARAM)nPos, 0);
	}
	return nDefault;
}


// ---- MIDIデバイスのリスト

static void insertnc(HWND hWnd, int nPos)
{
	std::tstring rNC(LoadTString(IDS_NONCONNECT));
	SendMessage(hWnd, CB_INSERTSTRING, (WPARAM)nPos, reinterpret_cast<LPARAM>(rNC.c_str()));
}

void dlgs_setlistmidiout(HWND hWnd, UINT16 res, LPCTSTR defname) {

	HWND		wnd;
	UINT		defcur;
	UINT		devs;
	UINT		num;
	UINT		i;
	MIDIOUTCAPS	moc;

	wnd = GetDlgItem(hWnd, res);
	defcur = 0;
	devs = midiOutGetNumDevs();
	insertnc(wnd, 0);
	SendMessage(wnd, CB_INSERTSTRING, (WPARAM)1, (LPARAM)cmmidi_midimapper);
	if (!milstr_cmp(defname, cmmidi_midimapper)) {
		defcur = 1;
	}
	num = 2;
#if defined(VERMOUTH_LIB)
	SendMessage(wnd, CB_INSERTSTRING, (WPARAM)num, (LPARAM)cmmidi_vermouth);
	if (!milstr_cmp(defname, cmmidi_vermouth)) {
		defcur = num;
	}
	num++;
#endif
#if defined(MT32SOUND_DLL)
	if (MT32Sound::GetInstance()->IsEnabled())
	{
		SendMessage(wnd, CB_INSERTSTRING, (WPARAM)num,
													(LPARAM)cmmidi_mt32sound);
		if (!milstr_cmp(defname, cmmidi_mt32sound)) {
			defcur = num;
		}
		num++;
	}
#endif
	for (i=0; i<devs; i++) {
		if (midiOutGetDevCaps(i, &moc, sizeof(moc)) == MMSYSERR_NOERROR) {
			SendMessage(wnd, CB_INSERTSTRING,
											(WPARAM)num, (LPARAM)moc.szPname);
			if ((!defcur) && (!milstr_cmp(defname, moc.szPname))) {
				defcur = num;
			}
			num++;
		}
	}
	SendMessage(wnd, CB_SETCURSEL, (WPARAM)defcur, (LPARAM)0);
}

void dlgs_setlistmidiin(HWND hWnd, UINT16 res, LPCTSTR defname) {

	HWND		wnd;
	UINT		defcur;
	UINT		num;
	UINT		i;
	MIDIINCAPS	mic;

	wnd = GetDlgItem(hWnd, res);
	defcur = 0;
	num = midiInGetNumDevs();
	insertnc(wnd, 0);
	for (i=0; i<num; i++) {
		if (midiInGetDevCaps(i, &mic, sizeof(mic)) == MMSYSERR_NOERROR) {
			SendMessage(wnd, CB_INSERTSTRING,
									(WPARAM)(i+1), (LPARAM)mic.szPname);
			if ((!defcur) && (!milstr_cmp(defname, mic.szPname))) {
				defcur = (i+1);
			}
		}
	}
	SendMessage(wnd, CB_SETCURSEL, (WPARAM)defcur, (LPARAM)0);
}
