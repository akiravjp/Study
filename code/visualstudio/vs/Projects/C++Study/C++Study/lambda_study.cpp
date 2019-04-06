#include "lamada_study.h"

void TestLambda() {
	int j = 12;
	auto by_val_lambda = [=] { return j + 1;};
	auto by_ref_lambda = [&] { return j + 1;};
	cout << "by_val_lambda: " << by_val_lambda() << endl;
	cout << "by_ref_lambda: " << by_ref_lambda() << endl;
	j++;
	cout << "by_val_lambda: " << by_val_lambda() << endl;
	cout << "by_ref_lambda: " << by_ref_lambda() << endl;
}


void LambdaStudy::TestValueAndReferenceCapture()
{
	int j = 12;
	auto by_val_lambda = [=] { return j + 1;};
	auto by_ref_lambda = [&] { return j + 1;};
	cout << "by_val_lambda: " << by_val_lambda() << endl;
	cout << "by_ref_lambda: " << by_ref_lambda() << endl;
	j++;
	cout << "by_val_lambda: " << by_val_lambda() << endl;
	cout << "by_ref_lambda: " << by_ref_lambda() << endl;
}

/*
* ��ʹ�ǲ�������ʽ���ݽ�ȥ��j��Ҳ�Ǵ������һ�̱���˳�����j++��û��Ӱ������ֵ���ݵ��ã����ɻ���ԭ����ֵ
*/
void LambdaStudy::TestValueAndReferenceCapture(int j)
{
	auto by_val_lambda = [=] { return j + 1;};
	auto by_ref_lambda = [&] { return j + 1;};
	cout << "by_val_lambda: " << by_val_lambda() << endl;
	cout << "by_ref_lambda: " << by_ref_lambda() << endl;
	j++;
	cout << "by_val_lambda: " << by_val_lambda() << endl;
	cout << "by_ref_lambda: " << by_ref_lambda() << endl;
}