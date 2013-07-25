/*�ಥ���IP��ַΪ224.0.0.88���˿�Ϊ8888�����ͻ��˽��յ��ಥ�����ݺ󽫴�ӡ ������
�ͻ���ֻ���ڼ���ಥ�����ܽ��ܶಥ������ݣ���˶ಥ�ͻ����ڽ��նಥ�������֮ǰ��Ҫ�ȼ���ಥ�飬��������Ϻ�Ҫ�˳��ಥ�顣
*/
/*
*broadcast_client.c - �ಥ�Ŀͻ���
*/
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <errno.h>
#include <strings.h>

#define MCAST_PORT    8888
#define MCAST_ADDR    "224.0.0.88" /*һ���ֲ����Ӷಥ��ַ��·����������ת��*/
#define MCAST_INTERVAL    5 /*���ͼ��ʱ��*/
#define BUFF_SIZE 256 /*���ջ�������С*/
int main(int argc, char*argv[])
{
	int s; /*�׽����ļ�������*/
	struct sockaddr_in    local_addr; /*���ص�ַ*/
	int err = -1;
	s = socket(AF_INET,    SOCK_DGRAM, 0); /*�����׽���*/
	if (s == -1)
	{
	perror("socket()");
	return -1;
	}
	/*��ʼ����ַ*/
	memset(&local_addr,    0, sizeof(local_addr));
	local_addr.sin_family =    AF_INET;
	local_addr.sin_addr.s_addr    = htonl(INADDR_ANY);
	local_addr.sin_port =    htons(MCAST_PORT);
	/*��socket*/
	err = bind(s,(struct    sockaddr*)&local_addr, sizeof(local_addr))    ;
	if(err < 0)
	{
	perror("bind()");
	return -2;
	}
	/*���ûػ����*/
	int loop = 1;
	err =    setsockopt(s,IPPROTO_IP, IP_MULTICAST_LOOP,&loop, sizeof(loop));
	if(err < 0)
	{
	perror("setsockopt():IP_MULTICAST_LOOP");
	return -3;
	}
	struct ip_mreq mreq; /*����㲥��*/
	mreq.imr_multiaddr.s_addr    = inet_addr(MCAST_ADDR); /*�㲥��ַ*/
	mreq.imr_interface.s_addr    = htonl(INADDR_ANY); /*����ӿ�ΪĬ��*/
	/*����������㲥��*/
	err = setsockopt(s,    IPPROTO_IP, IP_ADD_MEMBERSHIP,&mreq, sizeof
		(mreq));
	if (err < 0)
	{
	perror("setsockopt():IP_ADD_MEMBERSHIP");
	return -4;
	}

	int addr_len = 0;
	char buff[BUFF_SIZE];
	int n = 0;
	// ������Ϣһ��
	addr_len =    sizeof(local_addr);
	memset(buff, 0,    BUFF_SIZE); //��ս��ջ�����
	//��������
	n = recvfrom(s, buff,    BUFF_SIZE, 0,(struct sockaddr*)&local_addr,&addr_len);
	if( n== -1)
	{
		perror("recvfrom()");
	}
	//��ӡ��Ϣ
	printf("Received message from server:%s\n", buff);
	
	/*
	//ѭ�����չ㲥�����Ϣ��5�κ��˳�
	int times = 0;
	for(times =    0;times<5;times++)
	{
		addr_len =    sizeof(local_addr);
		memset(buff, 0,    BUFF_SIZE); //��ս��ջ�����
		//��������
		n = recvfrom(s, buff,    BUFF_SIZE, 0,(struct sockaddr*)&local_addr,&addr_len);
		if( n== -1)
		{
			perror("recvfrom()");
		}
		//��ӡ��Ϣ
		printf("Recv %dst    message from server:%s\n", times, buff);
		sleep(MCAST_INTERVAL);
	}
	*/
	/*�˳��㲥��*/
	err = setsockopt(s,    IPPROTO_IP, IP_DROP_MEMBERSHIP,&mreq, sizeof(mreq));
	close(s);
	return 0;
}