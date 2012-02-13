#include "net_connection.h"
#include "net_buffer.h"

#include <assert.h>
//��ʼ��connection���飬����connection�����������γ���������net_connection����
//�ĵ�һ��ΪԤ��free connection �����ͷָ�� ��2����nextָ��βָ��
net_connection_t* nconnection_create(int max_connection_count)
{
	int i;
	net_connection_t* self = (net_connection_t*)malloc(sizeof(net_connection_t)*max_connection_count);
	assert(max_connection_count>2);
	for(i=2;i<max_connection_count-1;i++)
	{
		self[i].burden = 0;
		self[i].connection_status = STATUS_IDLE ;
		self[i].fd = retired_fd;
		self[i].read_buf = NULL;
		self[i].next = &self[i+1];
	}
	self[i].burden = 0;
	self[i].connection_status = STATUS_IDLE ;
	self[i].fd = retired_fd;
	self[i].read_buf = NULL;
	self[i].next = NULL;
	self[0].next = &self[2];
	self[1].next = &self[i];
	return self;
}


//��free connection����ı�ͷ��ȡ��һ��������ʼ��һЩ��item�ĳ�Ա����
net_connection_t* nconnection_get(net_connection_t* self)
{
	net_connection_t* item =NULL;
	if(self[0].next!=NULL)//self[0].nextΪ�ձ�ʾ�Ѿ�û�п��õ�connection
	{
		item = self[0].next;
		item->connection_status = STATUS_OPEN;
		item->read_buf = nbuf_create(NET_DEFAULT_READ_BUF_SIZE);
		self[0].next = item->next;
	}
	return item;
}

//��item�Żص�free connection������β��������item��һЩ��Ա������ԭ
void nconnection_free(net_connection_t* self,net_connection_t* item)
{
	item->fd = retired_fd;
	assert(item->connection_status==STATUS_CLOSE);
	item->connection_status = STATUS_IDLE;
	nbuf_destory(&item->read_buf);
	self[1].next->next = item;
	self[1].next = item;
}
//��Ҫ�ͷ�����alive��recv_buf
void nconnections_destory(net_connection_t* self)
{
	net_connection_t* item;
	while(item=self[0].next)
	{
		nbuf_destory(&item->read_buf);
		item=item->next;
	}
	free(self);
}


