#ifndef net_base_msg_h
#define net_base_msg_h

//��Ϣ��Ҫ���ü���


 
#define COMMON_HEADER 	unsigned int msg_len;/*��������ͷ����msg����*/                                          \
	                    unsigned short msg_type;/*���й涨60000-65536����ϢΪϵͳ�������Ϣ*/					 \
	                    unsigned short dest_addr;																\
						unsigned short source_addr;																\
						unsigned short app_addr;																\
						unsigned short flag;/*����վλʹ��*/													  \
						char more:1;/*���ڴ���Ϣ�ķ���ʱ����Ҫ���в�֣���Ϣ����С����Ϣͨ�����Ƶ����ֵ����*/	 \
						/*����Ϊ1�Ǳ�ʾ������Ϣû�н������*/														\
						char compress:1;/*���ݰ���data���Ƿ�ѹ��*/											  \
						char debug:1/*debug״̬����Ϣ��ȫ����¼*/                                                \
                        char log:1/*log ״̬����Ϣ������¼�����ڻطŻ����ݻָ�*/                                 \
                        /*������λ�����ڱ���ʹ��*/																 \
						unsigned char data_offset/*�������ƫ��λ�ã�16+data_offset*/						   \
	//��Ҫ��֤��Ϣ����˳����	

typedef struct net_base_msg_
{
	COMMON_HEADER;
}net_base_msg_t;

enum base_msg_type 
{
	HEARTBEAT = 60000,
	OPEN,
	CLOSE
};

typedef struct net_heartbeat_msg_
{
	COMMON_HEADER;
	short cpu_usage;
	short memery_usage;
	unsigned int request_delay;
	unsigned int wait_task;
}net_heartbeat_msg_t;

typedef struct net_open_msg_
{
	COMMON_HEADER;
	short max_instance;//���ʵ�����������max_instance Ϊ1������ΪΨһʵ��
	short max_load;//�����ֵ�����������ֵʱ�����Ŵ����µ�ʵ��
	short app_id;
	unsigned char app_server_name_len;//�������Ϊ0��ʾ������ʵ��
	char app_server_name[1];//app ��������'\0'��β

}net_open_msg_t;

typedef struct net_close_msg_
{
	COMMON_HEADER;
}net_close_msg_t;

typedef struct net_app_id_msg_
{
	COMMON_HEADER;
	short app_id;//app_id Ϊ 0 ��ʾû���ҵ���Ӧ�ķ���
}net_app_name_msg_t;

typedef struct net_dest_error_msg_
{
	COMMON_HEADER;
	short dest;
}net_app_name_msg_t;

//���msg��������
#define nmsg_data(self) (((char*)(self))+((net_base_msg_t*)(self)->data_offset)+16)

//���msg��������ĳ���
#define nmsg_len (self) (((net_base_msg_t*)(self)->msg_len)-(net_base_msg_t*)(self)->data_offset-16)


#endif