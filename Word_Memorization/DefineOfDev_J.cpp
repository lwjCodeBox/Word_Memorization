#include "pch.h"

#include "DefineOfDev_J.h"

//size ũ���� data�迭�ȿ��� d�� ã��
//���̾����� -1��ȯ
//���� ������ data�迭�� index ��ȯ
int binarySearch(WORD *data, int size, WORD d)
{
	int s = 0; //����
	int e = size - 1; //��
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
	// [�׸��� 2, 1] -> [���� ���� 5, 2]
	return ap_Excel->readStr(a_Row + 3, a_Col + 1, NULL);
}
//--------------------------------------------------------------------------------------------

void TrainButtonPos(int a_StartPos, int a_RowCount, int a_ColCount)
{

	//int startHeight, endHeight;

	a_StartPos = 20;
	int startWidth, endWidht;

	for (int cnt = 0; cnt < a_RowCount; cnt++) {
		startWidth = a_StartPos + cnt * 120; // x��ǥ ������, 10��ŭ ������ ���� �׸�.
		endWidht = startWidth + 100/*110*/;


		//for (int j = 0; j < a_ColCount; j++) {
			//startHeight = 35 + j * 40; // 10��ŭ ������ ���� �׸�.
			//endHeight = startHeight + 35;
		//}
	}
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

UINT WorkerThread(LPVOID lParam)   //Thread��ȣ����Ŭ�������ּҰ����޴´�
{
	//CThreadDlg *dlg = (CThreadDlg *)lParam; //ȣ����Ŭ�����������Ͱ�ü����
	int per = 0;

	for (int i = 0; i < 1000; i++) { //0����999����1000���Ƿ����������ϸ�
		Sleep(500);
		//dlg->m_progressWT.SetPos(i);       //���α׷����ٸ�����
		
		if (i % 10 == 0) {
			per++;
			TRACE(L"[lParam >> %x] %d%%\n", lParam, per);
			//dlg->m_strWT.Format(_T("%d%%"), per);       //�ۼ�Ʈ���			
		}
	}

	return 0;
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+