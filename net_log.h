#ifndef net_log_h
#define net_log_h

#include <stdlib.h>

typedef enum log_level_ 
{
	LOG_WARN,
	LOG_DEBUG,
	LOG_INFO,
	LOG_EXCEPTION,
	LOG_ERROR
}log_level_t;


typedef struct net_log_ net_log_t;

typedef void (*callback_t)(net_log_t* self,log_level_t log_level,char* format,va_list arg_ptr);

net_log_t* nlog_create();

//���ļ������Ĭ�ϵ���־���stderr����ʧ�ܷ���-1
int nlog_open(net_log_t* self,const char* file_path);

//��������ļ�������ر��ļ������ʧ�ܷ���-1�����û�д��ļ������ùرպ��������ú���ʧ�ܷ���-1
int nlog_close(net_log_t* self);

void nlog_destory(net_log_t** self_ptr);

//����log����ļ��𣬲�������־����С�����õļ���ʱ����־������ԡ�Ĭ�ϼ���Ϊ�������е���־��Ϣ
void nlog_set_level(net_log_t* self,log_level_t log_level);

void nlog_log(net_log_t* self,log_level_t log_level,char* format,...);

//����log�Ļص�������������־����ʱ���ص��˺�������û�����ûص�����ʱ����ϵͳĬ�ϵĺ������д���
void nlog_set_callback(net_log_t* self,callback_t log);



#endif