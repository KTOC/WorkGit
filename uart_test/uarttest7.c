#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <termios.h>


#define DEVICE_NAME  "/dev/ttyS7"//device point
 
int set_opt(int fd,int nSpeed, int nBits, char nEvent, int nStop)
{
	 struct termios newtio,oldtio;
	 if  ( tcgetattr( fd,&oldtio)  !=  0) {
	  perror("SetupSerial 1");
	  return -1;
	 }
	 memset( &newtio,0,sizeof( newtio ) );
	 newtio.c_cflag  |=  CLOCAL | CREAD; //CLOCAL:����modem������  CREAD���򿪽�����
	 newtio.c_cflag &= ~CSIZE; //�ַ��������롣ȡֵΪ��CS5��CS6��CS7��CS8
 
	 switch( nBits )
	 {
	 case 7:
	  newtio.c_cflag |= CS7;
	  break;
	 case 8:
	  newtio.c_cflag |= CS8;
	  break;
	 }
 
	 switch( nEvent )
	 {
	 case 'O':
	  newtio.c_cflag |= PARENB; //�������������ż��Ϣ�Լ����뵽��żУ��
	  newtio.c_cflag |= PARODD;  //�����������漰У��
	  newtio.c_iflag |= (INPCK | ISTRIP); // INPACK:����������ż��⣻ISTRIP��ȥ���ڰ�λ
	  break;
	 case 'E':
	  newtio.c_iflag |= (INPCK | ISTRIP);
	  newtio.c_cflag |= PARENB;
	  newtio.c_cflag &= ~PARODD;
	  break;
	 case 'N': 
	  newtio.c_cflag &= ~PARENB;
	  break;
	 }
 
	 switch( nSpeed )
	 {
	 case 2400:
	  cfsetispeed(&newtio, B2400);
	  cfsetospeed(&newtio, B2400);
	  break;
	 case 4800:
	  cfsetispeed(&newtio, B4800);
	  cfsetospeed(&newtio, B4800);
	  break;
	 case 9600:
	  cfsetispeed(&newtio, B9600);
	  cfsetospeed(&newtio, B9600);
	  break;
	 case 115200:
	  cfsetispeed(&newtio, B115200);
	  cfsetospeed(&newtio, B115200);
	  break;
	 case 460800:
	  cfsetispeed(&newtio, B460800);
	  cfsetospeed(&newtio, B460800);
	  break;
	 default:
	  cfsetispeed(&newtio, B9600);
	  cfsetospeed(&newtio, B9600);
	  break;
	 }
 
	 if( nStop == 1 )
	  newtio.c_cflag &=  ~CSTOPB; //CSTOPB:��������ֹͣλ��������һ��
	 else if ( nStop == 2 )
	 newtio.c_cflag |=  CSTOPB;
	 
	 newtio.c_cc[VTIME]  = 0; //VTIME:��cannoicalģʽ��ʱ����ʱ����ʮ��֮һ��λ��λ
	 newtio.c_cc[VMIN] = 0; //VMIN:��canonicalģʽ������С�ַ���
	 tcflush(fd,TCIFLUSH); // �ı�������д�� fd ���õĶ������������������Ч�������ѽ��ܵ�δ��������붼�ڸı䷢��ǰ������
	 if((tcsetattr(fd,TCSANOW,&newtio))!=0) //TCSANOW:�ı���������
	 {
	  perror("com set error");
	  return -1;
	 }
	 printf("set done!\n\r");
	 return 0;
}
 
int main(void)
{
	 int fd1,nset,nread,ret;
	 char buf[100]={"test com data!...........\n"};
	 char buf1[100];
 
	 fd1 = open(DEVICE_NAME, O_RDWR);
	 printf("fd1 = %d\r\n",fd1);
	 if (fd1 == -1) {
		 printf("open device %s error \n",DEVICE_NAME);
	     exit(1);
	 }
	 printf("open  %s success!!\n",DEVICE_NAME);
 
	 nset = set_opt(fd1, 115200, 8, 'N', 1);
	 if (nset == -1) {
		 printf("set device %s error \n",DEVICE_NAME);
	     exit(1);
	 }
	 
	 printf("SET  %s success!!\n",DEVICE_NAME);
	 printf("enter the loop!!\n");
 
	 while(1) { 
	   memset(buf1, 0, sizeof(buf1));
	   ret = write(fd1, buf, 100);
	   if( ret > 0){
	       printf("write success!  wait data receive\n");
	   }
	   nread = read(fd1, buf1, 100);
	   if(nread > 0){
	       printf("redatad: nread = %s\n\n\r", buf1);
	   }
	   sleep(1);
	   //nread = read(fd1, buf1,1);
	   //if(buf1[0] == 'q')
	   //break;
	}
	 
    close(fd1);
    return 0;
}
