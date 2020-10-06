#include "pch.h"

#include "DefineOfDev_J.h"

//size 크기의 data배열안에서 d를 찾기
//값이없으면 -1반환
//값이 있으면 data배열의 index 반환
int binarySearch(WORD *data, int size, WORD d)
{
	int s = 0; //시작
	int e = size - 1; //끝
	int m;

	while (s <= e) {
		m = (s + e) / 2;
		if (data[m] == d)
			return m;
		else if (data[m] > d)
			e = m - 1;
		else
			s = m + 1;
	}
	return -1;
}
//--------------------------------------------------------------------------------------------

bool IsBitCheck16(WORD a_Target, WORD a_BitPos)
{
	if ((a_Target >> a_BitPos) & 0x01) return true;
	else return false;
}
//--------------------------------------------------------------------------------------------

CString GetTextFormExcel(int a_Row, int a_Col, libxl::Sheet *ap_Excel){
	// [그리드 2, 1] -> [엑셀 포멧 5, 2]
	return ap_Excel->readStr(a_Row + 3, a_Col + 1, NULL);
}
//--------------------------------------------------------------------------------------------

void TrainButtonPos(int a_StartPos, int a_RowCount, int a_ColCount)
{

	//int startHeight, endHeight;

	a_StartPos = 20;
	int startWidth, endWidht;

	for (int cnt = 0; cnt < a_RowCount; cnt++) {
		startWidth = a_StartPos + cnt * 120; // x좌표 시작점, 10만큼 떨어진 곳에 그림.
		endWidht = startWidth + 100/*110*/;


		//for (int j = 0; j < a_ColCount; j++) {
			//startHeight = 35 + j * 40; // 10만큼 떨어진 곳에 그림.
			//endHeight = startHeight + 35;
		//}
	}
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

UINT WorkerThread(LPVOID lParam)   //Thread를호출한클래스의주소값을받는다
{
	//CThreadDlg *dlg = (CThreadDlg *)lParam; //호출한클래스의포인터객체생성
	int per = 0;

	for (int i = 0; i < 1000; i++) { //0부터999까지1000번의루프를실행하며
		Sleep(500);
		//dlg->m_progressWT.SetPos(i);       //프로그레스바를수정
		
		if (i % 10 == 0) {
			per++;
			TRACE(L"[lParam >> %x] %d%%\n", lParam, per);
			//dlg->m_strWT.Format(_T("%d%%"), per);       //퍼센트출력			
		}
	}

	return 0;
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+