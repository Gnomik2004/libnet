#include "net_log.h"

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>



struct net_log_ 
{
  int log_level;
  FILE* file_handle;
  void* handle;
  int started;
  callback_t log;
  //���������Ϣ����
};

#define LOG_MAX_STRING_LEN 256
static const char* log_level_str [] ={"[WARN]","[DEBUG]","[INFO]","[EXCEPTION]","[ERROR]"};

static void nlog_log_(net_log_t* self,log_level_t log_level,char* format,va_list arg_ptr)
{
	if(self->log_level>log_level||log_level>LOG_ERROR)
	 return;
	else
	{
    time_t curtime = time (NULL);
    struct tm *loctime = localtime (&curtime);
    char formatted [30];
    strftime (formatted, 30, "%Y-%m-%d %H:%M:%S ", loctime);
    fprintf(self->file_handle,"%s %s:",log_level_str[log_level],formatted);
    vfprintf (self->file_handle,format, arg_ptr);
    fprintf(self->file_handle,"\n");
    fflush (self->file_handle);
	}
	
}


net_log_t* nlog_create()
{
	net_log_t* self = (net_log_t*)malloc(sizeof(net_log_t));
	self->file_handle = stderr;
	self->log_level = LOG_WARN;
	self->started =1;
	self->log = nlog_log_;
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

void nlog_warn_log(net_log_t* self,char* format,...)
{
  va_list arg_ptr;
  va_start(arg_ptr, format);
  self->log(self,LOG_WARN,format,arg_ptr);
  va_end(arg_ptr);
}

void nlog_debug_log(net_log_t* self,char* format,...)
{
  va_list arg_ptr;
  va_start(arg_ptr, format);
  self->log(self,LOG_DEBUG,format,arg_ptr);
  va_end(arg_ptr);
}

void nlog_info_log(net_log_t* self,char* format,...)
{
  va_list arg_ptr;
  va_start(arg_ptr, format);
  self->log(self,LOG_INFO,format,arg_ptr);
  va_end(arg_ptr);
}

void nlog_exception_log(net_log_t* self,char* format,...)
{
  va_list arg_ptr;
  va_start(arg_ptr, format);
  self->log(self,LOG_EXCEPTION,format,arg_ptr);
  va_end(arg_ptr);
}

void nlog_error_log(net_log_t* self,char* format,...)
{
  va_list arg_ptr;
  va_start(arg_ptr, format);
  self->log(self,LOG_ERROR,format,arg_ptr);
  va_end(arg_ptr);
}
