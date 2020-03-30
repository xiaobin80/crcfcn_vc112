/**
 * \file
 *
 * \brief The external method definition matches the IDL.
 *
 */

#pragma once
#include "resource.h"       // main symbols



#include "FCV_i.h"
#include "_IUCRC32Events_CP.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;


// CUCRC32

class ATL_NO_VTABLE CUCRC32 :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CUCRC32, &CLSID_UCRC32>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CUCRC32>,
	public CProxy_IUCRC32Events<CUCRC32>,
	public IDispatchImpl<IUCRC32, &IID_IUCRC32, &LIBID_FCVLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CUCRC32()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_UCRC32)


BEGIN_COM_MAP(CUCRC32)
	COM_INTERFACE_ENTRY(IUCRC32)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CUCRC32)
	CONNECTION_POINT_ENTRY(__uuidof(_IUCRC32Events))
END_CONNECTION_POINT_MAP()
// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);


	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:



	STDMETHOD(CalCRC32)(BSTR filePath, ULONG* presult);
	STDMETHOD(ReadFCN)(BSTR loadFile, ULONG* presult);
	STDMETHOD(SaveFCN)(BSTR saveFile, BSTR CheckFilePath, LONG* pstate);
};

OBJECT_ENTRY_AUTO(__uuidof(UCRC32), CUCRC32)
