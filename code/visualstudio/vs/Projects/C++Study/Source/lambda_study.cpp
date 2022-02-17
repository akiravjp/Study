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

void LambdaStudy::TestLambdaWithCaptureCannotToFunctionPointerInterface(FuncCallback callback, void* pCallbackCookie)
{
	if (callback)
	{
		callback(pCallbackCookie);
	}
}

void LambdaStudy::TestLambdaWithCaptureCannotToFunctionPointerPrint(void* arg, int nLen)
{
	std::cout << "PrintPtr" << std::endl;
}

/*
 * @2021/04/21
 * �����Ͻ�������Ľӿ����ṩ��һ������ָ�룬����������õ���std::function�����ǵ������ʱ�����뱨��
 */
void LambdaStudy::TestLambdaWithCaptureCannotToFunctionPointer()
{

	/*FUNCTION_CALLBACK callback = [](void*)
	{
		std::cout << "call back." << std::endl;
	};*/
	FUNCTION_CALLBACK call = std::bind(&LambdaStudy::TestLambdaWithCaptureCannotToFunctionPointerPrint, this, nullptr, 5);

	// E0413	�����ڴ� "lambda []void (void *)->void" �� "FuncCallback" ���ʵ�ת������
	/*TestLambdaWithCaptureCannotToFunctionPointerInterface([&](void*) {
		call(NULL);
	}, NULL);*/

	TestLambdaWithCaptureCannotToFunctionPointerInterface([](void* pCookie) {
		FUNCTION_CALLBACK callback = *(static_cast<FUNCTION_CALLBACK*>(pCookie));
		//call(NULL);
		if (callback)
		{
			callback(NULL);
		}
	}, &call);
}