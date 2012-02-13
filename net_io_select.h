#ifndef net_io_select_h
#define net_io_select_h

#include "net_def.h"
#include "net_connection.h"
#include "net_log.h"

typedef struct net_io_select_ net_io_select_t;


net_io_select_t* nio_select_create( net_log_t* net_log_ ,net_connection_t* conn_array);

//����io�߳̽����¼�����
void nio_select_dispatch(void*self);

int  nio_select_add_fd(void*self,net_connection_t* conn_ptr);

int  nio_select_remove_fd(void*self,net_connection_t* conn_ptr);

//����net_io_event_t���ر�ioģ����������io�߳�
void nio_select_destory(void*self);


#endif