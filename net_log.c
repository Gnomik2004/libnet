#include "net_log.h"
#include "net_thread.h"
#include "net_queue.h"

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>



struct net_log_ 
{
  int log_level;
  FILE* file_handle;
  queue_t* msg_queue;
  void* handle;
  int started;
  callback_t log;
  //���������Ϣ����
};

#define LOG_MAX_STRING_LEN 256
static const char* log_level_str [] ={"[WARN]","[DEBUG]","[INFO]","[EXCEPTION]","[ERROR]"};



static void log_loop(void* arg)
{
	net_log_t* net_log = (net_log_t*)arg;
	while(net_log->started)
	{
		void* log_str=nqueue_sync_pop(net_log->msg_queue);
	    fprintf(net_log->file_handle,(const char*)log_str);
		fflush(net_log->file_handle);
		free(log_str);
	}
	nthread_join(net_log->handle);
}

static void nlog_log_(net_log_t* self,log_level_t log_level,char* format,va_list arg_ptr)
{
	if(self->log_level>log_level||log_level>LOG_ERROR)
	 return;
	else
	{
		//ƴ���ַ���
		char* log_str = (char*)malloc(LOG_MAX_STRING_LEN);
		char tmp_str[100];
		time_t t = time( 0 ); 
		
	    sprintf(tmp_str,"%s %s",log_level_str[log_level],ctime(&t));
		strcat(tmp_str,format);
		vsprintf(log_str,tmp_str,arg_ptr);
		va_end(arg_ptr);
		
		if(log_level==LOG_ERROR)//LOG_ERRORֱ���������
		{
			fprintf(self->file_handle,log_str);
			fflush(self->file_handle);
			free(log_str);
		}
		else//�����ݷ�������н��д���
			nqueue_sync_push(self->msg_queue,log_str);
	}
	
}


net_log_t* nlog_create()
{
	net_log_t* self = (net_log_t*)malloc(sizeof(net_log_t));
	self->file_handle = stderr;
	self->log_level = LOG_WARN;
	self->msg_queue = nqueue_create(1);
	self->started =1;
	self->log = nlog_log_;
	self->msg_queue = nqueue_create(1);
	self->handle = nthread_create(log_loop,self);
	return self;
}

//���ļ������Ĭ�ϵ���־���stderr����ʧ�ܷ���-1
int nlog_open(net_log_t* self,const char* file_path)
{
	FILE* file = fopen(file_path,"a+");
	if(file ==NULL)
		return -1;
	self->file_handle = file;
	return 0;
}

//��������ļ�������ر��ļ������ʧ�ܷ���-1�����û�д��ļ������ùرպ��������ú���ʧ�ܷ���-1
int nlog_close(net_log_t* self)
{
	if(self->file_handle!=NULL&&self->file_handle!=stderr)
		return fclose(self->file_handle);
	return -1;
}

void nlog_destory(net_log_t** self_ptr)
{
	nlog_close(*self_ptr);
	free(*self_ptr);
	*self_ptr = NULL;
}

//����log����ļ��𣬲�������־����С�����õļ���ʱ����־������ԡ�Ĭ�ϼ���Ϊ�������е���־��Ϣ
void nlog_set_level(net_log_t* self,log_level_t log_level)
{
	self->log_level = log_level;
}

void nlog_log(net_log_t* self,log_level_t log_level,char* format,...)
{
	va_list arg_ptr;
	va_start(arg_ptr, format);
	self->log(self,log_level,format,arg_ptr);
	va_end(arg_ptr);
}


//����log�Ļص�������������־����ʱ���ص��˺�������û�����ûص�����ʱ����ϵͳĬ�ϵĺ������д���
void nlog_set_callback(net_log_t* self,callback_t log)
{
	self->log = log;
}