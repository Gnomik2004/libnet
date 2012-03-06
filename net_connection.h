
#pragma once
//#ifndef net_connection_h
//#define net_connection_h

#include "net_log.h"
#include "net_lock.h"

#include "net_def.h"
#include "net_buffer.h"

typedef struct net_connection_   net_connection_t;
typedef struct net_conn_manager_ net_conn_manager_t;

typedef void (*nconn_event_in)(net_connection_t* self);
typedef void (*nconn_event_out)(net_connection_t* self);

//connection ��Ҫ����session ��linker��ص�Ԫ��

//��Ҫ����appid �������ع���ģ�飬ʹ��߱���¼��ǰ�����Ƿ�Ϊ�������Էǵ���ÿ��app_id ��һ��ר�е����ȶ��У��Ը��ؾ�����й���
//
struct net_connection_ 
{
  int connection_status;
  struct net_connection_* next;
  struct net_connection_* prev;
  net_log_t* net_log;
  fd_t fd;
  net_buffer_t* read_buf;//default size is NET_DEFAULT_READ_BUF_SIZE
  int id;
  nconn_event_in read_fun;
  nconn_event_out write_fun;
  //int burden;//�����и��ؾ���Ŀͻ��˵ĸ���ѹ����¼
  //nconn_event_in on_event_in;
  //void* key;//ͨ���ⲿ����ͬʱҲ��Ҫ�ⲿ�ͷţ��󶨵�key���Է�������ڻص�������

  // read_buf
  //read callback
  //write callback
  //close callback
  //connect notify
  
};

#define STATUS_IDLE        0x00
#define STATUS_OPEN        0x01
#define STATUS_REGISTE     0x02
#define STATUS_CLOSE       0x80
#define STATUS_ALIVE       0x7f //�뵱ǰ״̬�����㣬�����Ϊ0 ��Ϊalive״̬




//��ʼ��connection���飬����connection�����������γ���������net_connection����
//�ĵ�һ��ΪԤ��free connection �����ͷָ��
net_conn_manager_t* nconnection_create(int max_connection_count,net_log_t* net_log_ptr);

//��free connection����ı�ͷ��ȡ��һ��������ʼ��һЩ��item�ĳ�Ա����
net_connection_t* nconnection_get(net_conn_manager_t* self);

//��item�Żص�free connection������β��������item��һЩ��Ա������ԭ
void nconnection_free(net_conn_manager_t* self,net_connection_t* item);

void nconnections_destory(net_conn_manager_t* self);

void nconnections_dump(net_conn_manager_t* self);

//#endif