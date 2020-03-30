// dllmain.h : Declaration of module class.

class CFCVModule : public ATL::CAtlDllModuleT< CFCVModule >
{
public :
	DECLARE_LIBID(LIBID_FCVLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_FCV, "{148092D1-5A30-4BF1-8568-CFFE6C6BCEDF}")
};

extern class CFCVModule _AtlModule;
