#ifndef net_io_event_h
#define net_io_event_h

#include "net_def.h"
#include "net_connection.h"
#include "net_log.h"

typedef struct net_io_event_ net_io_event_t; 

enum io_event_type
{
	select,
	epoll,
};

//����io_event_type_������Ӧ��ioģ�͵ķ�ʽ����selectָ������ʵ�ַ�ʽ����select 
//��epool�����epool��ֻ����linux��ʹ�ã�
net_io_event_t* nio_event_create(enum io_event_type io_event_type_, net_log_t* net_log_ ,net_connection_t* conn_array);

//����io�߳̽����¼�����
void nio_event_dispatch(net_io_event_t*self);

//�����Ӳ��ɹ�������-1
int  nio_event_add_fd(net_io_event_t*self,net_connection_t* conn_ptr);

int  nio_event_remove_fd(net_io_event_t*self,net_connection_t* conn_ptr);

//����net_io_event_t���ر�ioģ����������io�߳�
void nio_event_destory(net_io_event_t*self);

#endif