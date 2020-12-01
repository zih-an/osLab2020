/*
* Filename : ipc.h
* copyright : (C) 2006 by zhonghonglie
* Function : 声明 IPC 机制的函数原型和全局变量
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/msg.h>

#define BUFSZ 256
//建⽴或获取 ipc 的⼀组函数的原型说明
int get_ipc_id(char *proc_file,key_t key);

// 函数建⽴⼀个具有 n 个字节 的共享内存区
char *set_shm(key_t shm_key,int shm_num,int shm_flag);

//  函数建⽴⼀个消息队列
int set_msq(key_t msq_key,int msq_flag);

// 函数建⽴⼀个具有 n 个信号灯的信号量
int set_sem(key_t sem_key,int sem_val,int sem_flag);

// 信号灯上的down/up 操作  -> 阻塞/唤醒
int down(int sem_id);
int up(int sem_id);


/*信号灯控制⽤的共同体*/
typedef union semuns {
    int val;
} Sem_uns;

/* 消 息 结 构 体 */
typedef struct msgbuf {
    long mtype;
    char mtext[1];
} Msg_buf;

//⽣产消费者共享缓冲区即其有关的变量
key_t buff_key;
int buff_num;  // real 共享缓冲区大小（可任给大小）
char *buff_ptr;  // real 共享缓冲区  == set_shm(buff_key, buf_num, ...) -> 开辟空间

//⽣产者放产品位置的共享指针
key_t pput_key;
int pput_num;  // 指针数
int *pput_ptr;  // real 生产者放产品的位置  == set_shm(pput_key, pput_num, ...) -> 开辟空间

//消费者取产品位置的共享指针
key_t cget_key;
int cget_num;
int *cget_ptr;

//⽣产者有关的信号量
key_t prod_key;
key_t pmtx_key;
int prod_sem;  // ⽣产者同步信号灯
int pmtx_sem;  // ⽣产者互斥信号灯

//消费者有关的信号量
key_t cons_key;
key_t cmtx_key;
int cons_sem;  // 消费者同步信号灯
int cmtx_sem;  // 消费者互斥信号灯

int sem_val;  // 各信号灯初值 -> 一个tmp过渡量
int sem_flg;
int shm_flg;
