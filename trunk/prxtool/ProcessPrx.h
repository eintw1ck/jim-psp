#ifndef __PROCESSPRX_H__
#define __PROCESSPRX_H__

#include "ProcessElf.h"
#include "VirtualMem.h"
#include "prxtypes.h"
#include "NidMgr.h"

/* Define ProcessPrx derived from ProcessElf */
class CProcessPrx : public CProcessElf
{
	PspModule m_modInfo;
	CNidMgr   m_defNidMgr;
	CNidMgr*  m_pCurrNidMgr;
	CVirtualMem m_vMem;
	bool m_blPrxLoaded;
	/* Pointer to the allocated relocation entries, if available */
	ElfReloc  *m_pElfRelocs;
	/* Number of relocations */
	int m_iRelocCount;

	bool FillModule(ElfSection *pInfoSect);
	void FreeMemory();
	int  LoadSingleImport(PspModuleImport *pImport, u32 addr);
	bool LoadImports();
	int  LoadSingleExport(PspModuleExport *pExport, u32 addr);
	bool LoadExports();
	bool LoadRelocs();
public:
	CProcessPrx();
	virtual ~CProcessPrx();
	virtual bool LoadFromFile(const char *szFilename);
	void FixupNames();

	bool FixupPrx(FILE *fp);
	bool ElfToPrx(FILE *fp);

	PspModule* GetModuleInfo();
	ElfReloc* GetRelocs(int &iCount);
	void SetNidMgr(CNidMgr* nidMgr);
};

#endif
