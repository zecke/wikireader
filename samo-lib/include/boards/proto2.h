#ifndef WIKIREADER_PROTO2_H
#define WIKIREADER_PROTO2_H

#define DISPLAY_INVERTED	1
#define EEPROM_SST25VF040	1

static inline int board_revision(void)
{
	return 2;
}

/* this is the board support file for caiaq's 2nd prototype */

static inline void init_pins(void)
{
	/* P85: LCD_CS, P83: TFT_CTL1 */
	REG_P8_IOC8 = 0x28;
	REG_P8_03_CFP = 0x3f;
	REG_P8_45_CFP = 0x03;

	/* P65-67: SPI */
	REG_P6_47_CFP = 0x54;

	/* Serial interface */
	REG_P0_03_CFP = 0x05;

	/* LCD controller */
	REG_P8_03_CFP = 0x15;
	REG_P9_47_CFP = 0x55;

	/* board specific things */
	/* P13 & P14: debug LEDs */
	REG_P1_IOC1 = 0x18;
	/* SDCARD power */
	REG_P3_IOC3 = 0x0f;
	/* SDCARD CS# */
	REG_P5_03_CFP = 0x01;

	REG_MISC_PUP6 = (1 << 5);

	/* P50 & P52: CS lines */
	REG_P5_IOC5 = 0x07;

	/* use P64 and NMI pins for hardware watchdog logic */
	REG_P6_IOC6 = 0x18;
	REG_P6_P6D = 0x08;
	REG_P6_P6D = 0x18;
}

#ifdef INCLUDED_FROM_KERNEL
static inline void power_off(void)
{
	/* switch off condition: P64 high, P63 low */
	REG_P6_P6D = 0x10;
}

static inline void prepare_keys(void)
{
	/* initial comparison is all buttons open */
	REG_KINTCOMP_SCPK0 = 0x00;

	/* enable mask for three buttons */
	REG_KINTCOMP_SMPK0 = 0x07;

	/* select P60/P61/P62 */
	REG_KINTSEL_SPPK01 = 0x04;

	/* only interested in KINT0 source */
	REG_INT_EK01_EP0_3 = 0x10;
}

static inline unsigned char get_key_state(void)
{
	return REG_P6_P6D & 0x7;
}
#endif

/* MRS command address for burst length=1, CAS latency = 2 */
#define MRSREG		(*(volatile unsigned char *) 0x10000442)
#define RAMDUMMY	(*(volatile unsigned char *) 0x10000000)

/* setup for ESMT M52S128168A */

static inline void init_ram(void)
{
	int i;

	/* P20-P27 functions */
	REG_P2_03_CFP = 0x55;
	REG_P2_47_CFP = 0x55;
	REG_P5_03_CFP |= 0x80;

	/* P85 */
	REG_P8_45_CFP &= 0x03;

	/* disable write protection of clock registers */
	REG_CMU_PROTECT = 0x96;

	/* switch on SDRAM clk */
	REG_CMU_GATEDCLK0 |= 0x78;

	/* re-enable write protection of clock registers */
	REG_CMU_PROTECT = 0x00;

	/* enable SDRAMC application core */
	REG_SDRAMC_APP = 0x8000000b;

	/* set up SDRAM controller */
	/* 8M x 16 bits x 1, minimal possible timing */
	REG_SDRAMC_CTL = 0x22;

	/* disable RAM self-refresh, ... */
	REG_SDRAMC_REF = 0x8c | (0 << 23) | (0x7f << 16);

	/* SDRAM command sequence */
	for (i = 0; i < 4; i++) {
		REG_SDRAMC_INI = 0x12;	/* PALL */
		RAMDUMMY = 0x0;		/* dummy write */
	}

	for (i = 0; i < 4; i++) {
		REG_SDRAMC_INI = 0x11;	/* INIREF */
		RAMDUMMY = 0x0;		/* dummy write */
	}

	REG_SDRAMC_INI = 0x14;	/* INIMRS */
	MRSREG = 0x0;		/* dummy write */

	/* exit RAM setup mode */
	REG_SDRAMC_INI = 0x10;
}

#define enable_card_power()  do { REG_P3_P3D |=	 (1 << 3); } while(0)
#define disable_card_power() do { REG_P3_P3D &= ~(1 << 3); } while(0)

#define SDCARD_CS_LO()	do { REG_P5_P5D &= ~(1 << 0); } while (0)
#define SDCARD_CS_HI()	do { REG_P5_P5D |=  (1 << 0); } while (0)
#define EEPROM_WP_HI()	do {} while (0)

#define AVDD_MILLIVOLTS	       2700
#define ADC_SERIES_RESISTOR_K  220
#define ADC_SHUNT_RESISTOR_K   1000


#endif /* WIKIREADER_PROTO2_H */

