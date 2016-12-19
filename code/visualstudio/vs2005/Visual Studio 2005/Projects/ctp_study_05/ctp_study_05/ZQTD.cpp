// ZQTD.cpp: implementation of the CZQTD class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZQTD.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CZQTD::CZQTD()
{

}

CZQTD::~CZQTD()
{

}

void CZQTD::Init()
{

	// ����һ��CThostFtdcTraderApiʵ��
	m_pTdApi = CThostFtdcTraderApi::CreateFtdcTraderApi(".\\flow\\td");

	// ע��һ�¼������ʵ��
	m_pTdApi->RegisterSpi(this);
	
	// ����˽����
	//        TERT_RESTART:�ӱ������տ�ʼ�ش�
	//        TERT_RESUME:���ϴ��յ�������
	//        TERT_QUICK:ֻ���͵�¼��˽����������
	m_pTdApi->SubscribePrivateTopic(THOST_TERT_RESTART);
	
	// ���Ĺ�����
	//        TERT_RESTART:�ӱ������տ�ʼ�ش�
	//        TERT_RESUME:���ϴ��յ�������
	//        TERT_QUICK:ֻ���͵�¼�󹫹���������
	m_pTdApi->SubscribePublicTopic(THOST_TERT_RESTART);

	// ���ý����й�ϵͳ����ĵ�ַ������ע������ַ����
	m_pTdApi->RegisterFront("tcp://172.16.126.104:29407");

	// ʹ�ͻ��˿�ʼ���̨����������
	m_pTdApi->Init();
}

void CZQTD::OnFrontConnected()
{
	CThostFtdcReqUserLoginField reqUserLogin;
	memset(&reqUserLogin,0,sizeof(reqUserLogin));
	strcpy(reqUserLogin.BrokerID,"2011");
	strcpy(reqUserLogin.UserID,"698048");
	strcpy(reqUserLogin.Password,"1");
	// ������½����
	m_pTdApi->ReqUserLogin(&reqUserLogin, 1);

}
void CZQTD::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
//��ѯ��Լ��������-��δ�ṩ//////////////////////////////////////////////////////////////////////////////////////////////
	CThostFtdcQryInstrumentCommissionRateField QryInstrumentCommissionRate;
	memset(&QryInstrumentCommissionRate,0,sizeof(QryInstrumentCommissionRate));
	strcpy(QryInstrumentCommissionRate.BrokerID,"2011");
	strcpy(QryInstrumentCommissionRate.InvestorID,"698048");
//	strcpy(QryInstrumentCommissionRate.ExchangeID,"SSE");
	//strcpy(QryInstrumentCommissionRate.InstrumentID,"601857");
	m_pTdApi->ReqQryInstrumentCommissionRate(&QryInstrumentCommissionRate,1);

//��ѯ�ɶ��˺�//////////////////////////////////////////////////////////////////////////////////////////////
	CThostFtdcQryTradingCodeField QryTradingCode;
	memset(&QryTradingCode,0,sizeof(QryTradingCode));
	strcpy(QryTradingCode.BrokerID,"2011");
	strcpy(QryTradingCode.InvestorID,"698048");

	m_pTdApi->ReqQryTradingCode(&QryTradingCode, 1);
//��ѯ����//////////////////////////////////////////////////////////////////////////////////////////////
	CThostFtdcQryOrderField QryOrder;
	memset(&QryOrder,0,sizeof(QryOrder));
	strcpy(QryOrder.BrokerID,"2011");
	strcpy(QryOrder.InvestorID,"698048");

	m_pTdApi->ReqQryOrder(&QryOrder, 1);

//////////////////////////////////////////
	CThostFtdcQryInstrumentField qryStruct;
	memset(&qryStruct,0,sizeof(qryStruct));
	//m_pTdApi->ReqQryInstrument(&qryStruct,1);

//����//////////////////////////////////////////////////////////////////////////////////////////////
	CThostFtdcInputOrderField pInputOrder;
	
	memset(&pInputOrder,0,sizeof(pInputOrder));
	CThostFtdcInputOrderField * pIptOrdFld=&pInputOrder;

	strcpy(pIptOrdFld->BrokerID,"2011");
	strcpy(pIptOrdFld->InvestorID,"698048");
	strcpy(pIptOrdFld->InstrumentID,"601857");
	//strcpy(pIptOrdFld->ExchangeID,"SSE");
	pIptOrdFld->OrderPriceType=THOST_FTDC_OPT_AnyPrice;//TZQThostFtdcOrderPriceTypeType	
	pIptOrdFld->Direction=THOST_FTDC_D_Buy;
	pIptOrdFld->VolumeTotalOriginal=100;
	pIptOrdFld->TimeCondition = THOST_FTDC_TC_GFD;///������Ч
	pIptOrdFld->VolumeCondition=THOST_FTDC_VC_AV;
	pIptOrdFld->ContingentCondition = THOST_FTDC_CC_Immediately;
	pIptOrdFld->ForceCloseReason = THOST_FTDC_FCC_NotForceClose;
	//strcpy(pIptOrdFld->LimitPrice,"9.12");
//////////////////////////////////////////////////////////////////////////////////////////////////////
	//strcpy(pIptOrdFld->UserID,"698048");// �û�����
	//strcpy(pIptOrdFld->OrderRef,"1"); ///��������
	//pIptOrdFld->CombOffsetFlag[0]=THOST_FTDC_OF_Open;
	//pIptOrdFld->CombHedgeFlag[0]=THOST_FTDC_HF_Speculation;
	//strcpy(pIptOrdFld->GTDDate,"20120202");
	//pIptOrdFld->MinVolume=0;
	//pIptOrdFld->IsAutoSuspend = 0;
	//pIptOrdFld->UserForceClose = 0;
	//pIptOrdFld->RequestID=1;

	m_pTdApi->ReqOrderInsert(pIptOrdFld, 1);
}
void CZQTD::OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if(pInstrument!=NULL)
		printf("Instrument:%s;Name:%s!\n",pInstrument->InstrumentID,pInstrument->InstrumentName);
}
void CZQTD::OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
 {
	return;
}
void CZQTD::OnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
 {
	return;
}
void CZQTD::OnRspQryTradingCode(CThostFtdcTradingCodeField *pTradingCode, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	return;
}
void CZQTD::OnRspQryInstrumentCommissionRate(CThostFtdcInstrumentCommissionRateField *pInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	return;
}

//ErrRSP&Rtn/////////////////////////////////////////////////////////////////////
void CZQTD::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	return;
}
void CZQTD::OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo)
{
	return;
}
void CZQTD::OnErrRtnOrderAction(CThostFtdcOrderActionField *pOrderAction, CThostFtdcRspInfoField *pRspInfo)
{
	return;
}
//Rtn/////////////////////////////////////////////////////////////////////

void CZQTD::OnRtnOrder(CThostFtdcOrderField *pOrder)
{
	return;
}
void CZQTD::OnRtnTrade(CThostFtdcTradeField *pTrade)
{
	//if(pTrade!=NULL)
		
	//	printf("Instrument:%s;Price:%s;dbPrice:%n!\n",pTrade->InstrumentID,pTrade->Price,getPrice(pTrade->Price));
	return;
}
void CZQTD::OnRtnInstrumentStatus(CThostFtdcInstrumentStatusField *pInstrumentStatus)
{
	return;
}
/////////////////////////////////////////////////////////////////////////////////////
/*
double CZQTD::getPrice(TThostFtdcStockPriceType price)
{
	return sizeof(price) / sizeof(price[0]);
}
*/