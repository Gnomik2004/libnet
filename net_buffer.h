#ifndef net_buffer_h
#define net_buffer_h

#include <stdlib.h>
#include "net_err.h"

//���ڹ���buffer�ĺ���ʹ�õ�Ƶ�ʱȽϸߣ����Խ���ʵ�ַ���ͷ�ļ������������ڱ�������������
typedef struct net_buffer_
{
	char* data;
	int len;
	char* tmp_data;
	int tmp_len;
	int begin_pos;
	int end_pos;

}net_buffer_t;

net_buffer_t* nbuf_create(int size)
{
	net_buffer_t* self = (net_buffer_t*)malloc(sizeof(net_buffer_t));
	self->begin_pos = self->end_pos = 0;
	self->len = 0;
	self->tmp_data = NULL;
	self->data = (char*)malloc(sizeof(char)*size);
	return self;
}

char* nbuf_data(net_buffer_t* self)
{
	return self->data+self->begin_pos;
}

int nbuf_size(net_buffer_t* self)
{
	return self->end_pos-self->end_pos;
}
//�����Ϣ�峤�ȴ���bufʣ���С���򻺴�����Ҫ���û������Ĵ�С
//������һ����Ҫ��ȡ�Ļ���������Ϊ����Ϣ�峤��-nbuf_size��
//��ʹ������Ϣ����Ҫ����nbuf_clear,����������ԭΪԭ��ȱʡdata
int nbuf_remain_size(net_buffer_t* self)
{
	return self->len-self->end_pos;
}
//���ڴ�����dataֱ����Ϊһ���µ�msg�������ڴ治��Ҫ�ͷ�
void nbuf_clear(net_buffer_t* self)
{
	char* tmp;
	self->begin_pos = self->end_pos = 0;
	self->data = self->tmp_data;
}

char* nbuf_reset(net_buffer_t* self,int size)
{
	char* tmp;
	int len = self->end_pos-self->begin_pos;
	self->tmp_len = self->len;
	self->tmp_data = (char*)malloc(sizeof(char)*size);
	memcpy(self->tmp_data,self->data+self->begin_pos,len);
	self->begin_pos = 0;
	self->end_pos = len;
	self->len = size;
	tmp = self->data;
	self->data = self->tmp_data;
	self->tmp_data = tmp;
}

void nbuf_product(net_buffer_t* self,int size)
{
	net_assert(nbuf_remain_size(self)>=size);
	self->end_pos +=size;
}

void nbuf_consume(net_buffer_t* self,int size)
{
	net_assert(nbuf_size(self)<=size);
	self->begin_pos +=size;
	if(self->begin_pos == self->end_pos)
		self->begin_pos = self->end_pos = 0;
}

void nbuf_destory(net_buffer_t** self)
{
	free((*self)->data);
	free(*self);
	*self = NULL;
}

#endif