/**
 * \file
 *
 * \brief The COM(DLL) is adapted from DELPHI is FCN!
 *
 * <table>
 * <tr><th>Version</th><th>Author</th><th>Date</th><th>Memo</th>
 * <tr><td>1.1</td><td>Guibin.Li</td><td>2009.09.20</td><td>VS6.0</td>
 * <tr><td>1.1.1</td><td>Guibin.Li</td><td>2020.03.30</td><td>VS10</td>
 * </table>
 *
 * \page License
 *
 *   Copyright (c) 2013-2020 Tdtc Corporation. All rights reserved.
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 *
 */

#include "stdafx.h"
#include "UCRC32.h"
#include <comdef.h>
#include "time.h"
#include <stdlib.h>

#include "Udefine.h"


/// \brief CRC32 table(integer array)
unsigned int crc32table[256];

/**
 * \brief Generate CRC table array
 * \param void
 * \return int array
 */
void generateCRC32Array()
{
	DWORD i11;
	DWORD j22;
	DWORD crc;
	for(i11=0; i11<256; i11++){
		crc = i11;
		for(j22=0; j22<8; j22++){  /// standard for(j22 = 8; j22 > 0; j22--)
			if(crc&1 == 1){ /// if(crc&1)
				crc = (crc>>1)^0xEDB88320;
			}
			else {
				crc = crc>>1; /// crc >>=1;
			}
		}

		 crc32table[i11] = crc;
	}
}

/**
 * \brief Calculate the CRC32 value
 * \param BSTR filePath
 * \return DWORD value
 */
DWORD calculateCRC32Number(BSTR filePath)
{
	generateCRC32Array();
	FILE* file;
	_bstr_t tempBstr;
	tempBstr = filePath;
	char* tempChar = tempBstr;
	file = fopen(tempChar, "rb");
	unsigned char buffer[8192];

	int len = sizeof(buffer);
	fread(buffer, len, 1, file);

	DWORD crc32 = 0xffffffff;
	
	for(int i1 = 1; i1<len; i1++){
		crc32 = ((crc32>>8)&0xffffff) ^ crc32table[(crc32 ^ DWORD(buffer[i1])) & 0xff];
	}
	fclose(file);

	return crc32;
}

/**
 * \brief Get the time of this machine
 * \param void
 * \return String date
 */
char* getLocalMachineTime()
{
	struct tm* myTime;
	time_t long_time;
	time(&long_time);
	myTime = localtime(&long_time);

	char* result = new char[10];

	int iYear = myTime->tm_year;
	iYear += 1900;

	char chYear[4];
	char* myYear = new char[4];
	myYear = _itoa(iYear, chYear, 10);

	strcpy(result, myYear);
	strcat(result, "-");

	int iMonth = myTime->tm_mon;
	iMonth += 1;

	char chMonth[2];
	char* myMonth = new char[2];
	if(iMonth < 10) {
		strcpy(myMonth, "0");
		_itoa(iMonth, chMonth, 10);
		strcat(myMonth, chMonth);
	} else {
		myMonth = _itoa(iMonth, chMonth, 10);
	}
	strcat(result, myMonth);
	strcat(result, "-");

	int iDay = myTime->tm_mday;

	char chDay[2];
	char* myDay = new char[2];
	if(iDay < 10) {
		strcpy(myDay, "0");
		_itoa(iDay, chDay, 10);
		strcat(myDay, chDay);
	} else {
		myDay = _itoa(iDay, chDay, 10);
	}

	strcat(result, myDay);

	return result;
}

STDMETHODIMP CUCRC32::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* const arr[] = 
	{
		&IID_IUCRC32
	};

	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}


STDMETHODIMP CUCRC32::CalCRC32(BSTR filePath, ULONG* presult)
{
	*presult = calculateCRC32Number(filePath);

	return S_OK;
}


STDMETHODIMP CUCRC32::ReadFCN(BSTR loadFile, ULONG* presult)
{
    FILE* file;
	_bstr_t tempBstr;
	tempBstr = loadFile;
	char* tempChar = tempBstr;
	/// tempChar = _com_util::ConvertBSTRToString(tempBstr);
	///
	PTFileHead = &FileHead;
	
	memset(&FileHead, 0, sizeof(struct TFileHead));
	file = fopen(tempChar, "rb");
	rewind(file);
	/// fseek(file, sizeof(FileHead), -1);
	fread(PTFileHead, sizeof(struct TFileHead), 1, file);
	*presult = PTFileHead->CRC32;
	
	fclose(file);

	return S_OK;
}


STDMETHODIMP CUCRC32::SaveFCN(BSTR saveFile, BSTR CheckFilePath, LONG* pstate)
{
    FILE* file;
	_bstr_t tempBSTR = saveFile;
	char* tempChar = tempBSTR;
	int i229 = remove(tempChar);
	/// use date
	if((file = fopen(tempChar, "rb")) == NULL){
		file = fopen(tempChar, "wb+");
		DWORD crcValue = calculateCRC32Number(CheckFilePath);
		/// 
		PTFileHead = &FileHead;
		/// Version
		PTFileHead->Version[0] = '2';
		PTFileHead->Version[1] = '.';
		PTFileHead->Version[2] = '1';
		PTFileHead->Version[3] = '.';
		PTFileHead->Version[4] = '1';
		PTFileHead->Version[5] = '.';
		PTFileHead->Version[6] = '2';
		/// author
		PTFileHead->author[0] = 'x';
		PTFileHead->author[1] = 'i';
		PTFileHead->author[2] = 'a';
		PTFileHead->author[3] = 'o';
		PTFileHead->author[4] = 'b';
		PTFileHead->author[5] = 'i';
		PTFileHead->author[6] = 'n';
		/// crc32
		PTFileHead->CRC32 = crcValue;
		/// UpdateDate
		char dateChar[10];
		strcpy(dateChar ,getLocalMachineTime());
		for(int i=0; i<10; i++){
			PTFileHead->UpdateDate[i] = dateChar[i];
		}
		/// PTFileHead->UpdateDate = getLocalMachineTime();

		/// write
		fwrite(PTFileHead, sizeof(FileHead), 1, file);
		
		pstate = (long*)0;
	} else {
	    pstate = (long*)-1;
	}
	fclose(file);

	return S_OK;
}
