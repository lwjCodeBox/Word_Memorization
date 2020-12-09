#pragma once

#include "GridCtrl_src_new/GridCtrl.h"
#include "libxl.h"
#include "_CExcelLib.h"
using namespace libxl;

// _Grid Function Group
namespace _GFG { 
	// naming rule - _GFG_�Լ��̸�
	void _GFG_InitItemBkColor(int a_rowLast, int a_colLast, CGridCtrl *ap_grid); // (O)
	void _GFG_InitMakeGrid(unsigned short a_fcode, WORD a_portAddr, WORD a_node, CGridCtrl *ap_grid); // ��Ʈ �������� ������ �������� üũ.
	
	void _GFG_SetMergeData(int a_GridRow, int a_GridColumn, WORD a_SetData, WORD a_portAddr, BYTE a_node, CGridCtrl *ap_grid);
	WORD _GFG_GetMergeCheck(int a_GridRow, int a_GridColumn, WORD a_portAddr);

	// ���߿� �����Ұ���.
	void _GFG_GetBitDataFormSMTest(int a_RowFirst, int a_RowLast, int a_ColFirst, int a_ColLast, WORD a_portAddr, BYTE a_node, CGridCtrl *ap_grid);
}


