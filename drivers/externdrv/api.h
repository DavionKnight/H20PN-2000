/*
 *
 * @file		api.h
 * @author	Tianzhy <tianzy@huahuan.com>
 * @date		2013-8-15
 * @modif   zhangjj<zhangjj@huahuan.com>
 */
#ifndef __CE_API_H__
#define __CE_API_H__


//#define DEBUG
#ifdef DEBUG
#define cdebug(format, arg...)		\
    printf(format , ## arg);        \
    printf("\n")
#else
#define cdebug(format, arg...)
#endif

//add by zhangjj for 1604
#define FPGADRVDIR	"/dev/spidev0.0"


#define SPI_IOC_MAGIC			'k'

#define SPI_IOC_OPER_FPGA		    _IOW(SPI_IOC_MAGIC, 5, __u8)
#define SPI_IOC_OPER_FPGA_DONE		_IOW(SPI_IOC_MAGIC, 6, __u8)
#define SPI_IOC_OPER_DPLL		    _IOW(SPI_IOC_MAGIC, 7, __u8)
#define SPI_IOC_OPER_DPLL_DONE		_IOW(SPI_IOC_MAGIC, 8, __u8)
//add end

#define DELAY_COUNT 100
// offset of the fpga 
#define FPGA_WREN_OFFSET  		0x00;   // write enable , flap  is valid
#define FPGA_RDEN_OFFSET  		0x02;   // read enable,  flap is valid
#define FPGA_ADDR_OFFSET  		0x04;   // set the slave address and reg address
#define FPGA_WRDATA_OFFSET  	0x06;   // write data
#define FPGA_RDDATA_OFFSET  	0x08;   // read data
#define FPGA_EN_OFFSET     	    0x0a;   // read/write/write data flag


/*struct used for the infomation*/
struct bdinfo_{
    int RJ45100M_num;
    int SFP100M_num;
    int RJ451G_num;
    int SFP1G_num;
    int XFP10G_num;
    int total_num;
};

struct bdinfo_ bdinfo_port_num;

struct sfpinfo_{
    int txdis_state;
    int txdis_changed;
    int mo_state;
    int mo_changed;
    int txfault_state;
    int txfault_changed;
    int rxlos_state;
    int rxlos_changed;
};

struct sfpinfo_ce{
  int txdis_state;
  int txdis_changed;
  int mo_state;
  int mo_changed;
  int txfault_state;
  int txfault_changed;
  int rxlos_state;
  int rxlos_changed;
};


struct sfpxfpenvinfo_ {
    char vendorName[16];
    char vendorPN[16];
    char vendorRev[16];
    char vendorSerialNo[16];
    char date[16];
    char transceiverType[16];
    char connectorType[16];
    char opticalType[32];
    char lineCoding[64];
    char nominalBitRate[32];
    char linkLength[16];
    char waveLength[16];
    char maxBitRateMargin[16];
    char minBitRateMargin[16];

    char temperature[16];
    char vccVoltage[16];
    char TXBiasCurrent[16];
    char TXOutputPower[16];
    char RXInputPower[16];	

};
/* struct to read and write to fpga*/
struct fpga_msg 
{
    unsigned short addr;       //register address to read or write

    unsigned char  flags;      //read or write flag; 0: read, 1:write

    unsigned short len;        //length to read or write

    unsigned char  buf[2];       //buffer to store the data
};

struct fpga_rdwr_data
{
    struct fpga_msg *msgs;
    int nmsgs;      //step to implement an action, it needs 5 steps to read sfp informaion, etc.
};


//typedef struct _sdm_ce_fan_running_info
struct sdm_ce_fan_running_info
{
	int           FanID;
  int           HwState ;
//	int           *SubUnitHwState;
	int           SubUnitHwState[8];
//	int           *RunSpeed;
	int           RunSpeed[8];
	int           Voltage; 
	int           Intensity; 
} ;

//typedef struct _sdm_ce_power_running_info
struct sdm_ce_power_running_info 
{
	int             PowerID; 
	int             HwState;
	int 		VoltageIn ;
	int    	IntensityIn ;
	int 		VoltageOut ;
	int    	IntensityOut ;
} ;


/************************************************
 *��ȡ�����¶�(TMP101)
 *����:
 *����ֵ:	-1 �쳣����, value:�¶�ֵ
 ************************************************/
int  getTemperature(short *temp);      // Ŀǰ�¶�Ϊ����ֵ
//int getTemperature(float *temprature);


/************************************************
 *��ȡrtc��������2013 9 4 17 21 10
 *����:		��ͨ��int time[6];����ֵ
 *����ֵ:	0 �������أ� -1 �쳣����
 ************************************************/
int rtc_get_time(int *piYear, int *piMonth,  int *piDay, 
        int *piHour, int *piMinute, int *piSecond);

/************************************************
 *����rtc��������2013 9 4 17 21 10
 *��:rtc_set_time(2013,9,4,17,21 10)
 *����ֵ:	0 �������أ� -1 �쳣����
 ************************************************/
int rtc_set_time(int  iYear, int  iMonth,  int  iDay,
        int  iHour, int  iMinute, int  iSecond) ;

/************************************************
 *ͨ��rctʱ������ϵͳʱ��
 *����:
 *����ֵ:	0 �������أ� -1 �쳣����
 ************************************************/
int rtc_recover_systime();


/*******************************************
 * ��ȡEEPROM���ݵ�buffer---��ʼ��ʱ����һ��
 * ����: 	
 * ����ֵ:	0 �������أ� -1 �쳣����
 ********************************************/
int boardinfo_init(void);

/* ��ȡϵͳ���� Ŀǰ�Ѿ������ֵΪ*/
#define CONFIG_H20PN_1610       00  /* only 4GE + 4FX */
#define CONFIG_H20PN_1611	01  /* 4GE+4FX+8E1 */
#define CONFIG_H20PN_1612	02  /* */
#define CONFIG_H20PN_1613	03  /* 4GE+4GE+2STM1 */
#define CONFIG_H20PN_1841_4E1	04  /* 2GE + 2GX + 4E1 */
#define CONFIG_H20PN_1822_2GX	05  /* 4GE + 2GX */

#define CONFIG_H18CE_2404B	16

#define CONFIG_H18CE_2404C    	19

#define CONFIG_H20PN_1660	22 /* 4x10GE + 24GE */
#define CONFIG_H20PN_1664	23 /* only 16GE */
#define CONFIG_H20PN_1663	24 /* only 24GE no 10GE */

#if 0
/*******************************************
 * ��buffer����DeviceName---��ʼ��ʱ����һ��
 * ����:    
 * ����ֵ:  0 �������أ� -1 �쳣����
 ********************************************/
int getDeviceFromEeprom(void);

/*******************************************
 * ��buffer����VendorName---��ʼ��ʱ����һ��
 * ����:    
 * ����ֵ:  0 �������أ� -1 �쳣����
 ********************************************/
int getVendorFromEeprom(void);
#endif

/***************************************************
 * ��EEPROM��ȡ������	
 * ����:    
 * ����ֵ:  boardTypeValue --�������Ͳο�����궨��
 **************************************************/
int get_bdtype(void);

/*******************************************
 * ��EEPROM��ȡverdor name
 * ����:    ptr:vendor name
 * ����ֵ:  ����ֵ:	0 �������أ� -1 �쳣����
 ********************************************/
int get_vendor_name(unsigned char *ptr);

/*******************************************
 * ��EEPROM��ȡ������
 * ����:    ptr: device name
 * ����ֵ:  ����ֵ:	0 �������أ� -1 �쳣����
 ********************************************/
int get_device_name(unsigned char *ptr);

/**********************************************************
 * EEPROMд����
 * ����:    addr:Ŀ�ĵ�ַ��buf:��д���buf��len:buf length
 * ����ֵ:  ����ֵ:	0 �������أ� -1 �쳣����
 **********************************************************/
int EepromWrite(unsigned short addr,unsigned char *buf, unsigned short len);

/**********************************************************
 * EEPROM������
 * ����:	addr:EEPROM��ַ��buf:������buf��len:buf length
 * ����ֵ:	����ֵ: 0 �������أ� -1 �쳣����
 **********************************************************/
int EepromRead(unsigned short addr,unsigned char *buf, unsigned short len);


/*******************************************
 * ��ȡ��ģ����λ��los��txdis����Ϣ
 * ����: 	port: 1-20  ptr:��ģ����Ϣ
 * ����ֵ:	0 �������أ� -1 �쳣����
 ********************************************/
int get_sfpinfo_by_port(int port, struct sfpinfo_ce *ptr);

/*********************************************
 *�ӻ������л�ȡ��ģ����Ϣ
 *����ʵ����get_sfpEnvInfo_by_port_from_sxfp��ͬ
 *********************************************/
int get_sfpEnvInfo_by_port(int port, struct sfpxfpenvinfo_ *ptr);

/*********************************************
 *��sfp/xfpģ����ֱ�ӻ�ȡ��ģ����Ϣ
 *����: 	port: 1-20  sfpPtr: ��ģ����Ϣ
 *����ֵ: 	0 �������أ� -1 �쳣����
 *********************************************/
int get_sfpEnvInfo_by_port_from_sxfp(int port, struct sfpxfpenvinfo_ *sfpPtr);

//int get_bdinfo_port_num(struct bdinfo_ *ptr);

/***************************************************
 *b"000"	ֱ����Դ�̣�-48V/12V��75W���޵�Դ���
 *b"001"	ֱ����Դ�̣�-48V/12V��75W������Դ���
 *b"010"	reserve
 *b"011"	reserve
 *b"100"	������Դ�̣�~220V/12V��75W���޵�Դ���
 *b"101"	������Դ�̣�~220V/12V��75W������Դ���
 *b"110"	reserve
 *b"111"	����λ
 ***************************************************/
/****************************************************
 * ��ȡ��Դ״̬
 * ����:	pwrState: ��Դ״̬ �ο��ϱ�
 * ����ֵ:  0 �������أ� -1 �쳣����
 ****************************************************/
int  getPowerState(unsigned short *pwrState);

/***************************************************************
 * ��ȡ��Դ��Ϣ(0: ok ;  1:fail)----�ýӿ���ʱ�����ã�FPGA��pwr��IIC��û�н�
 * Power B state			Power A state
 * ����ֵ:  0 �������أ� -1 �쳣����
 ***************************************************************/
int  getPowerInfo(int index, struct sdm_ce_power_running_info *pwrInfo);

/*******************************************
 * ��ȡ������λ״̬
 * ����: fan: 0-��λ	1-����λ
 * ����ֵ:  0 �������أ� -1 �쳣����
 *******************************************/
int  getFanState(unsigned short *fan);

/*******************************************
 * ��ȡ����״̬
 * ����: 	index: for 1604c this value fixed 1
 			fan: ������Ϣ
 * ����ֵ:  0 �������أ� -1 �쳣����
 *******************************************/
int  getFanInfo(int index, struct sdm_ce_fan_running_info *fan);

/***************************************
 * ���ȿ�������
 * ����:	1-ON  0-OFF
 * ����ֵ:  0 �������أ� -1 �쳣����
 ***************************************/
int  enableFan(const short on_off);

/***************************************************
 * ���ø澯ָʾ��
 * ����:    led_type: unused 
 *			led_color: 1-OFF	2-ON
 * ����ֵ:  0 �������أ� -1 �쳣����
 ***************************************************/
int setAlarmLed(int led_type, int led_color);


/****************************************
 * ����ָʾ��
 * ����:	led_color: 1: OFF	2: ON
 * ����ֵ��	0 ����  -1 ����
 ****************************************/
int setNorLed( int led_color);

#if 0
/********************************************************
 *�˿ڳ�ʼ��������Ҫ����sfp_app_global_init����
 *
 ********************************************************/
void swtichport_api_init();


/********************************************************
 *sfp��ʼ������Ҫ��swtichport_api_init֮���ʼ��
 *
 ********************************************************/
int sfp_app_global_init(void);


/********************************************************
 * ��ȡ�������е�image�ţ�1 or 2
 ********************************************************/
//int readRunningImage(void);
#endif

/***************************************
        type 					value
#define TYPE_IMAGE   	1	 	1 or 2
#define TYPE_KERNEL1 	2		0 or 1 1��ʾ��Ч��0��ʾ��Ч
#define TYPE_RAMFS1 	3		0 or 1
#define TYPE_DTB1		4		0 or 1
#define TYPE_APP1		5		0 or 1
#define TYPE_KERNEL2 	6		0 or 1
#define TYPE_RAMFS2 	7		0 or 1
#define TYPE_DTB2		8		0 or 1
#define TYPE_APP2		9		0 or 1
 ***************************************/
 
/**********************************************
*�޸�EEPROM ��ģ����Ч��� 
*������type:�ο��ϱ� value:�ο��ϱ�
*����ֵ��0 ����  -1 ����
***********************************************/
int writeImageFlag(int type, int value);

/**********************************************
*��ȡEEPROM ��ģ����Ч��� 
*������type:�ο��ϱ� value:�ο��ϱ�
*����ֵ��0 ����  -1 ����
***********************************************/
int readImageFlag(int type, int *value);

/*printf function, used for debug */
void pdata(unsigned char *pdata, int count);

/**********************************************
*FPGA���ݶ�ȡ
*������fd:�豸������  msg:��ַ��buf����Ϣ  step:��д����
*����ֵ��1 ����  -1 ����
***********************************************/
int read_fpga_data(int fd, struct fpga_msg *msg, int step);

/**********************************************
*FPGA����д��
*������fd:�豸������  msg:��ַ��buf����Ϣ  step:��д����
*����ֵ��1 ����  -1 ����
***********************************************/
int write_fpga_data(int fd, struct fpga_msg *msg, int step);

#endif  //endif __API_H__
