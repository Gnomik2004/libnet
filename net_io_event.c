#include "net_io_event.h"

typedef void (*cb_create)(net_log_t* net_log_);
typedef void (*cb_dispatch)(void* instance);
typedef int  (*cb_add_fd)(void*instance,net_connection_t* conn_ptr) ;
typedef int  (*cb_remove_fd)(void*instance,net_connection_t* conn_ptr);
typedef void (*cd_destory)(void*instance);

struct net_io_event_
{
	void* owner;
	cb_create do_create;
	cb_dispatch do_dispatch;
	cb_add_fd do_add_fd;
	cb_remove_fd do_remove_fd;
	cd_destory do_destory;
};

//����io_event_type_������Ӧ��ioģ�͵ķ�ʽ����selectָ������ʵ�ַ�ʽ����select 
//��epool�����epool��ֻ����linux��ʹ�ã�
net_io_event_t* nio_event_create(enum io_event_type io_event_type_, net_log_t* net_log_ ,net_connection_t* conn_array)
{
}

//����io�߳̽����¼�����
void nio_event_dispatch(net_io_event_t*self)
{
	self->do_dispatch(self->owner);
}

int nio_event_add_fd(net_io_event_t*self,net_connection_t* conn_ptr)
{
	return self->do_add_fd(self->owner,conn_ptr);
}

int nio_event_remove_fd(net_io_event_t*self,net_connection_t* conn_ptr)
{
	return self->do_remove_fd(self->owner,conn_ptr);
}

//����net_io_event_t���ر�ioģ����������io�߳�
void nio_event_destory(net_io_event_t*self)
{
	self->do_destory(self->owner);
}