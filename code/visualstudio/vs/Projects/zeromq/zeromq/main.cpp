#include "zmq.h"
#include "zmq_utils.h"
#include <string.h>
#include <stdio.h>

int main(void)
{
	void* context = zmq_ctx_new();

	// Socket to talk to server
	printf("Connecting to hello world server��\n");
	void* requester = zmq_socket(context, ZMQ_REQ);
	zmq_connect(requester, "tcp://localhost:5555");

	int request_nbr;
	for (request_nbr = 0; request_nbr != 10; request_nbr++) {
		zmq_msg_t request;
		zmq_msg_init_size(&request, 5);
		memcpy(zmq_msg_data(&request), "Hello", 5);
		printf("Sending Hello %d��\n", request_nbr);
		zmq_msg_send(&request, requester, 0);
		zmq_msg_close(&request);

		zmq_msg_t reply;
		zmq_msg_init(&reply);
		zmq_msg_recv(&reply, requester, 0);
		printf("Received World %d\n", request_nbr);
		zmq_msg_close(&reply);
	}
	zmq_close(requester);
	return 0;
}

//
// Hello World ����� C++���԰�
// ��һ��REP�׽�����tcp://*:5555
// �ӿͻ��˽���Hello����Ӧ��World
//
//#include "zmq.h"
//#include "zmq_utils.h"
//#include <iostream>
//#include <unistd.h>
//
//int main() {
//    // ׼�������ĺ��׽���
//    zmq::context_t context(1);
//    zmq::socket_t socket(context, ZMQ_REP);
//    socket.bind("tcp://*:5555");
//
//    while (true) {
//        zmq::message_t request;
//
//        // �ȴ��ͻ�������
//        socket.recv(&request);
//        std::cout << "�յ� Hello" << std::endl;
//
//        // ��һЩ������
//        sleep(1);
//
//        // Ӧ��World
//        zmq::message_t reply(5);
//        memcpy((void*)reply.data(), "World", 5);
//        socket.send(reply);
//    }
//    return 0;
//}