#pragma once

#include "GridCtrl_src_new/GridCtrl.h"
#include "libxl.h"
#include "_CExcelLib.h"
using namespace libxl;

// _Grid Function Group
namespace _GFG { 
	// naming rule - _GFG_함수이름
	void _GFG_InitItemBkColor(int a_rowLast, int a_colLast, CGridCtrl *ap_grid); // (O)
	void _GFG_InitMakeGrid(unsigned short a_fcode, WORD a_portAddr, WORD a_node, CGridCtrl *ap_grid); // 비트 형식인지 병합한 형식인지 체크.
	
	void _GFG_SetMergeData(int a_GridRow, int a_GridColumn, WORD a_SetData, WORD a_portAddr, BYTE a_node, CGridCtrl *ap_grid);
	WORD _GFG_GetMergeCheck(int a_GridRow, int a_GridColumn, WORD a_portAddr);

	// 나중에 삭제할거임.
	void _GFG_GetBitDataFormSMTest(int a_RowFirst, int a_RowLast, int a_ColFirst, int a_ColLast, WORD a_portAddr, BYTE a_node, CGridCtrl *ap_grid);
}


