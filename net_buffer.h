#ifndef net_buffer_h
#define net_buffer_h

#include <stdlib.h>
#include "net_err.h"

//���ڹ���buffer�ĺ���ʹ�õ�Ƶ�ʱȽϸߣ����Խ���ʵ�ַ���ͷ�ļ������������ڱ�������������
typedef struct net_buffer_
{
	char* data;
	int base_len;
	char* tmp_data;
	int len;
	int begin_pos;
	int end_pos;

}net_buffer_t;

net_buffer_t* nbuf_create(int size);

#define nbuf_data(self) ((self)->data+(self)->begin_pos)
#define nbuf_size(self) ((self)->end_pos-(self)->begin_pos)
#define nbuf_tailer(self) ((self)->data+(self)->end_pos)
#define nbuf_space_size(self) ((self)->len-(self)->end_pos)

//���ڴ�����dataֱ����Ϊһ���µ�msg�������ڴ治��Ҫ�ͷ�,ֱ�����ⲿ�ͷ�
void nbuf_clear(net_buffer_t* self);

char* nbuf_reset(net_buffer_t* self,int size);

void nbuf_product(net_buffer_t* self,int size);

void nbuf_consume(net_buffer_t* self,int size);

void nbuf_destory(net_buffer_t** self);

static void s_dump(char *buffer, int sz) ;

void nbuf_dump(net_buffer_t* self);



#endif