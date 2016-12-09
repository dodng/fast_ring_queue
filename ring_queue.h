#include <assert.h>
#include <string.h>

typedef unsigned char u_char;

#define CAN_WRITE 0x00
#define CAN_READ 0x01
#define READING 0x02
#define WRITING 0x03

typedef struct tag
{
	u_char tag_value;
}TAG;


class Ring_Queue
{
	public:
		Ring_Queue(int nmemb,int size):_nmemb(nmemb),_size(size)
										 ,_read_now(0),_write_now(0)
	{
		if ( nmemb <= 0 || size <=0 )
		{
			assert(0);
		}
		_queue_p = NULL;
		_queue_p = new u_char[ nmemb * (sizeof(TAG) + size)];
		memset(_queue_p,0,nmemb * (sizeof(TAG) + size));

	}
		~Ring_Queue()
		{
			if (_queue_p) delete []_queue_p;

		}
		u_char * SOLO_Read()
		{
			u_char * g_p = 0;
			TAG * tag_p = 0;
			u_char *user_data = 0;

			g_p = queue_peek_nth(_queue_p,_read_now);
			tag_p = (TAG *)g_p;
			if (tag_p->tag_value == CAN_READ)
			{
				user_data = (u_char *)g_p + sizeof(TAG);
				tag_p->tag_value = READING;
			}
			return user_data;
		}
		void SOLO_Read_Over()
		{
			u_char * g_p = 0;
			TAG * tag_p = 0;

			g_p = queue_peek_nth(_queue_p,_read_now);
			tag_p = (TAG *)g_p;
			if (tag_p->tag_value == READING)
			{
				tag_p->tag_value = CAN_WRITE;
				_read_now = (_read_now + 1)% _nmemb;
			}
		}
		u_char * SOLO_Write()
		{
			u_char * g_p = 0;
			TAG * tag_p = 0;
			u_char *user_data = 0;

			g_p = queue_peek_nth(_queue_p,_write_now);
			tag_p = (TAG *)g_p;
			if (tag_p->tag_value == CAN_WRITE)
			{  
				user_data = (u_char *)g_p + sizeof(TAG);
				tag_p->tag_value = WRITING;
			}                
			return user_data;
		}
		void SOLO_Write_Over()
		{
			u_char * g_p = 0;
			TAG * tag_p = 0;

			g_p = queue_peek_nth(_queue_p,_write_now);
			tag_p = (TAG *)g_p;
			if (tag_p->tag_value == WRITING)
			{
				tag_p->tag_value = CAN_READ;
				_write_now = (_write_now + 1)% _nmemb;
			}
		}
	private:
		u_char *queue_peek_nth(u_char *queue_p,int pos)
		{
			u_char *rst = 0;
			if (queue_p && pos < _nmemb)
			{
				rst = queue_p + pos * (sizeof(TAG) + _size);
			}
			return rst;
		}
		u_char * _queue_p;
		int _nmemb;
		int _size;
		volatile int _read_now;
		volatile int _write_now;
};
