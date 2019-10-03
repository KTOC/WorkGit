/*
This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

		1. The origin of this software must not be misrepresented; you must not
		claim that you wrote the original software. If you use this software
		in a product, an acknowledgment in the product documentation would be
		appreciated but is not required.

		2. Altered source versions must be plainly marked as such, and must not be
		misrepresented as being the original software.

		3. This notice may not be removed or altered from any source
		distribution.
*/

#if !defined(UBMP_H)
#define UBMP_H

#define AUXLAYER_WIDTH (1920)
#define AUXLAYER_HEIGHT (720)
#define AUXLAYER_SIZE (AUXLAYER_WIDTH * AUXLAYER_HEIGHT * 4)

typedef unsigned char BYTE ;
typedef unsigned short WORD;
typedef unsigned int DWORD;
typedef int LONG;

typedef struct BMPFileHead_t {
    WORD bfType;          /* ˵���ļ������� */
    DWORD bfSize;         /* ˵���ļ��Ĵ�С�����ֽ�Ϊ��λ */
    WORD bfReserved1;     /* ����������Ϊ0 */
    WORD bfReserved2;     /* ����������Ϊ0 */
    DWORD bfOffsetBytes;  /* ˵����BITMAPFILEHEADER�ṹ��ʼ��ʵ�ʵ�ͼ������֮����ֽ�ƫ���� */
}BMPFileHead;             //14�ֽ�,����sizeof���㳤��ʱΪ16�ֽ�


typedef struct BMPHeaderInfo_t {
    DWORD biSize;           /* ˵���ṹ�������ֽ��� */
    LONG biWidth;           /* ������Ϊ��λ˵��ͼ��Ŀ�� */
    LONG biHeight;          /* ������Ϊ��λ˵��ͼ��ĸ߶� */
    WORD biPlanes;          /* ˵��λ����������Ϊ1 */
    WORD biBitCount;        /* ˵��λ��/���أ�1��2��4��8��24 */
    DWORD biCompression;    /* ˵��ͼ���Ƿ�ѹ����ѹ������BI_RGB��BI_RLE8��BI_RLE4��BI_BITFIELDS */
    DWORD biSizeImage;      /* ���ֽ�Ϊ��λ˵��ͼ���С��������4��������*/
    LONG biXPixelsPerMeter; /*Ŀ���豸��ˮƽ�ֱ��ʣ�����/�� */
    LONG biYPixelsPerMeter; /*Ŀ���豸�Ĵ�ֱ�ֱ��ʣ�����/�� */
    DWORD biClrUsed;        /* ˵��ͼ��ʵ���õ�����ɫ�������Ϊ0������ɫ��Ϊ2��biBitCount�η� */
    DWORD biClrImportant;   /*˵����ͼ����ʾ����ҪӰ�����ɫ��������Ŀ�������0����ʾ����Ҫ��*/
}BMPHeaderInfo;             //40�ֽ�


typedef struct  RGB_t{
    BYTE rgbBlue;     /*ָ����ɫ����*/
    BYTE rgbGreen;    /*ָ����ɫ����*/
    BYTE rgbRed;      /*ָ����ɫ����*/
    BYTE rgbReserved; /*������ָ��Ϊ0*/
}RGB;

/*
typedef struct serial_s{
	char type[16];//0:camera 1:radar_r 2:radar_m 3:radar_l
	int idx;//0:camera 1:radar_r 2:radar_m 3:radar_l
} serial_t;

typedef struct sensor_s{
	char type[16];//0:camera 1:radar_r 2:radar_m 3:radar_l
	int idx;//0:camera 1:radar_r 2:radar_m 3:radar_l
	int status;
} sensor_t;

sensor_t sensor;
*/

typedef struct bmp_img_s{
    unsigned char *line_dest;
    unsigned char *line_src;
    
    unsigned char *carmodel_dest;
    unsigned char *carmodel_src;
	
    unsigned char *radar_dest;
	
    unsigned char *radar_r_g_dest;
    unsigned char *radar_m_g_dest;
    unsigned char *radar_l_g_dest;
    unsigned char *radar_r_o_dest;
    unsigned char *radar_m_o_dest;
    unsigned char *radar_l_o_dest;
    unsigned char *radar_r_r_dest;
    unsigned char *radar_m_r_dest;
    unsigned char *radar_l_r_dest;

    unsigned char *radar_src;	
	
    unsigned char *radar_r_g_src;
    unsigned char *radar_m_g_src;
    unsigned char *radar_l_g_src;
    unsigned char *radar_r_o_src;
    unsigned char *radar_m_o_src;
    unsigned char *radar_l_o_src;
    unsigned char *radar_r_r_src;
    unsigned char *radar_m_r_src;
    unsigned char *radar_l_r_src;

    unsigned char line_path[32];
    unsigned char carmodel_path[32];	
    unsigned char radar_r_path[32];
    unsigned char radar_m_path[32];
    unsigned char radar_l_path[32];

    int line_idx;
    int carmodel_idx;
	
    int radar_r_idx;
    int radar_m_idx;
    int radar_l_idx;
	
    int line_h;
    int line_w;
    
    int carmodel_h;
    int carmodel_w;

    int radar_r_g_h;
    int radar_m_g_h;
    int radar_l_g_h;  
    int radar_r_o_h;
    int radar_m_o_h;
    int radar_l_o_h; 
    int radar_r_r_h;
    int radar_m_r_h;
    int radar_l_r_h; 

    int radar_r_g_w;
    int radar_m_g_w;
    int radar_l_g_w;  
    int radar_r_o_w;
    int radar_m_o_w;
    int radar_l_o_w; 
    int radar_r_r_w;
    int radar_m_r_w;
    int radar_l_r_w; 
  
    int rgb_bit;
    int argb_bit;
} bmp_img_t;


int init_picture(void);
int alloc_memery(void); 
int free_memery(void);
//int clear_cache(int screen_id, void *data,int data_w, int data_h, int p_byte);

int	analysis_auxiliary_line_pictures(const char *path, void *base);
int analysis_carmodel_pictures(const char *path, void *base);
int	analysis_radar_r_g_pictures(const char *path, void *base);
int	analysis_radar_m_g_pictures(const char *path, void *base);
int	analysis_radar_l_g_pictures(const char *path, void *base);
int	analysis_radar_r_o_pictures(const char *path, void *base);
int	analysis_radar_m_o_pictures(const char *path, void *base);
int	analysis_radar_l_o_pictures(const char *path, void *base);
int	analysis_radar_r_r_pictures(const char *path, void *base);
int	analysis_radar_m_r_pictures(const char *path, void *base);
int	analysis_radar_l_r_pictures(const char *path, void *base);


int copy_to_base(unsigned char *base, unsigned char *src, int src_w, int src_h, int point_w, int point_h);
int radar_copy_to_base(unsigned char *base, unsigned char *src, int src_w, int src_h, int point_w, int point_h);
int copy_to_dest(unsigned char *dest, unsigned char *src, int dest_w, int dest_h, int src_w, int src_h, int point_w, int point_h);
int rgb_to_argb(unsigned char *dest, unsigned char *src, int dest_w, int dest_h);
int car_model_rgb_to_argb(unsigned char *dest, unsigned char *src, int dest_w, int dest_h);

#endif /*defined(UBMP_H)*/
