/*������һ���ಥ�����������ӡ��ಥ�������ĳ�����ƺܼ򵥣�����һ�����ݰ��׽��֣�ѡ���ಥ��IP��ַ�Ͷ˿ڣ�ֱ����˶ಥ��ַ�������ݾͿ����ˡ�
�ಥ�������ĳ�����ƣ�����Ҫ����������ಥ�飬����ֱ����ĳ���ಥ�鷢�����ݡ�
*/
/*
*broadcast_server.c - �ಥ�������
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
#define MCAST_DATA    "Linux c multicast data" /*�ಥ���͵�����*/
#define MCAST_INTERVAL    5 /*���ͼ��ʱ��*/
int main(int argc, char*argv)
{
	int s;
	struct sockaddr_in    my_mcast_addr;
	s = socket(AF_INET,    SOCK_DGRAM, 0); /*�����׽���*/
	if (s == -1)
	{
		perror("socket()");
		return -1;
	}
	memset(&my_mcast_addr, 0, sizeof(my_mcast_addr));/*��ʼ��IP�ಥ��ַΪ0*/
	my_mcast_addr.sin_family = AF_INET;/*����Э��������ΪAF*/
	my_mcast_addr.sin_addr.s_addr = inet_addr(MCAST_ADDR);/*���öಥIP��ַ*/
	my_mcast_addr.sin_port = htons(MCAST_PORT);/*���öಥ�˿�*/
	
	/*��ಥ��ַ��������*/
	/*����һ������*/
	int n = sendto(s, /*�׽���������*/
				MCAST_DATA, /*����*/
				sizeof(MCAST_DATA), /*����*/
				0,(struct sockaddr*)&my_mcast_addr, sizeof(my_mcast_addr)) ;
	if( n < 0)
	{
		perror("sendto()");
		return -2;
	}
	/*
	//������ಥIP��ַ"224.0.0.88"��8888�˿ڷ�������"BROADCAST TEST DATA"��ÿ����һ�μ��5s��
	while(1) {
		int n = sendto(s, //�׽���������
				MCAST_DATA, //����
				sizeof(MCAST_DATA), //����
				0,(struct sockaddr*)&my_mcast_addr, sizeof(my_mcast_addr)) ;
		if( n < 0)
		{
			perror("sendto()");
			return -2;
		}
		sleep(MCAST_INTERVAL);    //�ȴ�һ��ʱ��
	}
	*/
	return 0;
}