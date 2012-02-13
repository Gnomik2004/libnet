#ifndef net_h
#define net_h 

typedef struct net_context_ net_context_t;

net_context_t* net_create_context();

void net_destory_context(net_context_t** context_ptr_ptr);

//��������

//������ͬ��chanel�������ݴ���

/////////////////////////net msg ��غ����Ĵ���////////////////////////////////////////////////
//sizeΪ��Ϣ��ĳ��ȣ���������Ϣͷ������������չ��Ϣͷ��ͷ��
void* net_msg_create(int size);


void* net_msg_data(void* msg);

//�����Ϣ��ĳ��ȣ���������Ϣͷ������Ϣ����չͷ��
int   net_msg_size();

//��msg�����ü���-1�������ǰ�����ü���Ϊ0 ������msg
void  net_msg_close(void** msg);

//����Ϣ�����ü�����count(���ڵ�ǰʹ������Ϣû�г����ڲ�ͬ�߳��еĳ�������û�ж����ü����ϼ���)
void  net_msg_increase_ref(void** msg,int count);

void  net_msg_set_exheader(void* msg,void* data,int len);

//������չ��Ϣͷ��lenΪ��չ��Ϣͷ�ĳ���
void* net_msg_exheader(void* msg,int* len);

/////////////////////�������õ���ز���//////////////////////////////////////////////






#endif