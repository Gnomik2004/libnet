#ifndef net_broker_h
#define net_broker_h

typedef struct net_broker_ net_broker_t;

net_broker_t* nbroker_create(int thread_count,int max_connection_count);

void nbroker_start(net_broker_t* self,int port);

void nbroker_close(net_broker_t* self);

void nbroker_destory(net_broker_t** self_ptr);

void nbroker_send(net_broker_t* self,void* data);

//�յ���Ϣ�Ļص�����

//��Ҫ���е�¼��֤
//��Ҫ�鿴appid���б�
//��Ҫ�鿴��ǰ����app �����״̬
//�����ݷ�����־�Ĵ���


//������������app_id ����Ϣ
//�������з���app_id ����Ϣ
//������������source ����Ϣ
void set_filter



#endif