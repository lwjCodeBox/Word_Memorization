#pragma once

#include "GridCtrl_src_new/GridCtrl.h"
#include "libxl.h"

using namespace libxl;

// naming rule - _GFG_함수이름
void _GFG_InitItemBkColor(int a_rowLast, int a_colLast, CGridCtrl *ap_grid);

void _GFG_InitMakeGrid(int a_RowFirst, int a_RowLast, int a_ColFirst, int a_ColLast, CGridCtrl *ap_grid);      // 매개 변수 범위는 기준은 엑셀 기준이다.
void _GFG_SetWordFormatCell(int a_RowFirst, int a_RowLast, int a_ColFirst, int a_ColLast, CGridCtrl *ap_grid); // 매개 변수 범위는 기준은 엑셀 기준이다.
void _GFG_SetDataCheck(int a_RowFirst, int a_RowLast, int a_ColFirst, int a_ColLast, WORD a_portAddr, BYTE a_node, CGridCtrl *ap_grid);      // 매개 변수 범위는 기준은 엑셀 기준이다.
void _GFG_SetTextGrid(int a_RowFirst, int a_RowLast, int a_ColFirst, int a_ColLast, CGridCtrl *ap_grid);       // 매개 변수 범위는 그리드 컨트롤 기준이다. 


