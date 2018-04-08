#ifndef XBUFFER_H
#define XBUFFER_H
#include <stdio.h>
#include <string.h>
#include "ZPort.h"

#define MINIMIZE_BLOCK 32						//��С���СΪ32�ֽ�

//��������ͳ�Ƶ���
class ZPerf {
public:
	unsigned long packet_number;				//����/���յ����ݰ�����
	unsigned long remain_number;				//��ǰ��Ȼ�ڻ���������Ŀ

	int max_interval;							//��֮������ʱ����
	int min_interval;							//��֮�����Сʱ����
	unsigned long tick_count;					//��ʼ��ʱ��

	short max_size;								//��������С
	short min_size;								//������С��С
	INT64 total_size;					//�ܴ�С
	unsigned long remain_size; 
	ZPerf();
	void start();
	void stop();
	void perfPacket(int size);
	void useBuffer(int size);
	void freeBuffer(int size);
};

class ZBuffer {
public:
	char *send_buffer;							//ʵ��ʹ�õķ��ͻ�����
	char *receive_buffer;						//ʵ��ʹ�õĽ��ջ�����
	long max_send;								//���ͻ������Ĵ�С
	long max_receive;							//���ջ������Ĵ�С

	char *receive_ptr;							//��ǰ�������ݵ�ָ��
	long receive_size;							//�������ݵĴ�С

	char *send_ptr;								//��ǰ�������ݵ�ָ��
	long send_size;								//�������ݵĴ�С
	char *packet_ptr;							//��ǰ���ݰ��Ŀ�ʼָ��
	unsigned short packet_size;					//��ǰ���ݰ��Ĵ�С

	ZPerf* pRecvPerf;
	ZPerf* pSendPerf;

public:
	ZBuffer(long the_max_send, long the_max_receive) {
		pRecvPerf = NULL;
		pSendPerf = NULL;
		send_buffer = new char[the_max_send];
		if(send_buffer) max_send = the_max_send;
		else max_send = 0;
		receive_buffer = new char[the_max_receive];
		if(receive_buffer) max_receive = the_max_receive;
		else max_receive = 0;
		//recv_buffer = 0;
		//recv_buffer_size = 0;
//		pack_buffer = 0;
//		pack_buffer_size = 0;
		if (pRecvPerf)
			pRecvPerf->useBuffer(the_max_receive);
		if (pSendPerf)
			pSendPerf->useBuffer(the_max_send);
		clear();
	}
	virtual ~ZBuffer() {
		if(send_buffer) delete[] send_buffer;
		if(receive_buffer) delete[] receive_buffer;
		if (pRecvPerf)
		{
			pRecvPerf->freeBuffer(max_receive);
		}
		if (pSendPerf)
		{
			pSendPerf->freeBuffer(max_send);
		}
	}

//�����Ƕ����ṩ�Ľӿ�
	void stopPerf() {
		pRecvPerf = NULL;
		pSendPerf = NULL;
	}

	void startPerf(ZPerf* pRP, ZPerf* pSP) {
		pRecvPerf = pRP;
		pSendPerf = pSP;
	}

//��ȡ���õĽ������ݵĻ�����
	char *getReceiveBuffer(int &size) {
		if(receive_size + MINIMIZE_BLOCK > max_receive) {
//������󻺳������ر�����
			return NULL;
		}
		if (receive_size < 0)
		{
			printf("receive size Negative ?!!!!\n");
			receive_size = 0;
			receive_ptr = receive_buffer;
			return NULL;
		}
		if(receive_ptr + receive_size + MINIMIZE_BLOCK > receive_buffer + max_receive) {		//β�����ݲ�����
			memmove(receive_buffer, receive_ptr, receive_size);
			receive_ptr = receive_buffer;
		}
		size = max_receive - (receive_ptr - receive_buffer) - receive_size;
		return receive_ptr + receive_size;
	}
	void receiveData(int size) {
		receive_size += size;
		if (pRecvPerf)
		{
			pRecvPerf->perfPacket(size);
			pRecvPerf->packet_number++;
		}
	}
	const char *getPacket(int &size) {
		if(receive_size < sizeof(unsigned short)) return NULL;
		size = *(unsigned short *)receive_ptr;
		if (size < sizeof(unsigned short))
		{
			printf("Unexpected recv buffer reset (size = %d)\n", size);
			receive_ptr = receive_buffer;
			receive_size = 0;
			return NULL;
		}

		if(receive_size >= size) {
			const char *result = (const char *)receive_ptr + sizeof(unsigned short);
			receive_ptr += size;
			receive_size -= size;
			size -= sizeof(unsigned short);
			return result;
		}
		return NULL;
	}

	void clear() {
		receive_ptr = receive_buffer;
		receive_size = 0;

		packet_ptr = send_ptr = send_buffer;
		*(unsigned short *)send_ptr = 0;
		send_size = 0;
		packet_size = 0;
	}

//�������ݵĽӿڷֳ�����������һ���ǻ�ȡ��ǰ���͵Ļ������ͳ��ȣ�����һ���Ǵӻ��������ָ����С������
	char *getSendData(int &size) {
		size = packet_ptr - send_ptr;
		if(size) {
			return send_ptr;
		}
		else {
			return NULL;
		}
	}
	void sendData(int size) {
		if (size > 0) {
			send_ptr += size;
			send_size -= size;
			if (send_size <= 0) {
				send_ptr = packet_ptr = send_buffer;
				*(unsigned short *)send_ptr = 0;
			}
			if (pSendPerf)
				pSendPerf->perfPacket(size);
			if (pSendPerf)
				pSendPerf->packet_number++;
		}
	}

	bool packData(const char *data, int size) {
		if (size <= 0 ||
			send_size + size + MINIMIZE_BLOCK >= max_send) {						
			//�����������ر�����
			return false;
		}

		if(!packet_size) {
			*(unsigned short *)packet_ptr = 0;
			packet_size += sizeof(unsigned short);
			send_size += sizeof(unsigned short);
		}

		if (send_size < 0)
		{
			printf("send size Negative ?!!!!\n");
			send_ptr = send_buffer;
			send_size = 0;
			packet_ptr = send_ptr;
			packet_size = 0;
			return false;
		}

		if(packet_ptr + packet_size + size + MINIMIZE_BLOCK >= send_buffer + max_send) {		//β���Ŀռ䲻����
			memmove(send_buffer, send_ptr, send_size);
			packet_ptr -= (send_ptr - send_buffer);
			send_ptr = send_buffer;
		}
		memcpy(packet_ptr + packet_size, data, size);
		packet_size += size;
		send_size += size;
		return true;
	}
	char *completePacket(int &datalength) {
		if(!packet_size) {
			return NULL;
		}

		datalength = packet_size - sizeof(unsigned short);
		return packet_ptr + sizeof(unsigned short);
	}
	void sendPacket() {							//���һ�����ݰ�
		if (!packet_size)
			return;
		*(unsigned short *)packet_ptr = packet_size;
		packet_ptr += packet_size;
		packet_size = 0;
	}
};

#endif
