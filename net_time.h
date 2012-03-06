#ifndef net_time_h
#define net_time_h

#include <stdint.h>

typedef struct net_timer_ net_timer_t;
typedef struct timer_task_ timer_task_t;

typedef void (*timer_callback)(void* arg);
typedef void (*free_callback)(void* arg);

net_timer_t* ntimer_create();

//���һ����ʱ�����ڶ�ʱ���Ļص�ֻ�ᱻִ��һ��
//������arg ��Ҫ�������ڻص��������ͷ��ڴ�
//����ֵ��timer_task_t,�������ΪNULL��ʾ��Ӷ�ʱ��ʧ��
timer_task_t* ntimer_expires_at(net_timer_t* self,int millisecond,timer_callback callback,void* arg);

//ȡ��task_id��Ӧ������
//����趨�Ķ�ʱ���ѱ�ִ���򷵻�-1�����򷵻�0
int ntimer_cannel(net_timer_t* self,timer_task_t*  task_ptr,free_callback callback);


void ntimer_destory(net_timer_t** self_ptr,free_callback callback);

int64_t ntime();

#endif