
module DE2_Media_Computer (
	// Inputs
	CLOCK_50,
	CLOCK_27,
	EXT_CLOCK,
	KEY,
	SW,

	//  Communication
	UART_RXD,

/*****************************************************************************/
	// Bidirectionals
	GPIO_0,
	GPIO_1,

	// Memory (SRAM)
	SRAM_DQ,
	
	//Flash
	FL_DQ,
	
	// Memory (SDRAM)
	DRAM_DQ,
	
	// PS2 Port
	PS2_CLK,
	PS2_DAT,
	
	// Char LCD 16x2
	LCD_DATA,
	
/*****************************************************************************/
	// Outputs
	
	// 	Simple
	HEX0,
	HEX1,
	HEX2,
	HEX3,
	HEX4,
	HEX5,
	HEX6,
	HEX7,
	
	// 	Memory (SRAM)
	SRAM_ADDR,

	SRAM_CE_N,
	SRAM_WE_N,
	SRAM_OE_N,
	SRAM_UB_N,
	SRAM_LB_N,
	
	//  Communication
	UART_TXD,
	
	// Memory (SDRAM)
	DRAM_ADDR,
	
	DRAM_BA_1,
	DRAM_BA_0,
	DRAM_CAS_N,
	DRAM_RAS_N,
	DRAM_CLK,
	DRAM_CKE,
	DRAM_CS_N,
	DRAM_WE_N,
	DRAM_UDQM,
	DRAM_LDQM,
	
	// VGA
	VGA_CLK,
	VGA_HS,
	VGA_VS,
	VGA_BLANK,
	VGA_SYNC,
	VGA_R,
	VGA_G,
	VGA_B,
	
	//Flash
	FL_ADDR,
	FL_CE_N,
	FL_OE_N,
	FL_RST_N,
	FL_WE_N,

	// Char LCD 16x2
	LCD_ON,
	LCD_BLON,
	LCD_EN,
	LCD_RS,
	LCD_RW,
);

/*****************************************************************************
 *                           Parameter Declarations                          *
 *****************************************************************************/


/*****************************************************************************
 *                             Port Declarations                             *
 *****************************************************************************/
// Inputs
input				CLOCK_50;
input				CLOCK_27;
input				EXT_CLOCK;
input		[3:0]	KEY;
input		[17:0]	SW;


//  Communication
input				UART_RXD;

// Bidirectionals
inout		[35:0]	GPIO_0;
inout		[35:0]	GPIO_1;

// 	Memory (SRAM)
inout		[15:0]	SRAM_DQ;

//  Memory (SDRAM)
inout		[15:0]	DRAM_DQ;

//  PS2 Port
inout				PS2_CLK;
inout				PS2_DAT;

//  Char LCD 16x2
inout		[ 7: 0]	LCD_DATA;

// Flash
inout 	[ 7: 0]  FL_DQ; 

// Outputs

// 	Simple
output		[6:0]	HEX0;
output		[6:0]	HEX1;
output		[6:0]	HEX2;
output		[6:0]	HEX3;
output		[6:0]	HEX4;
output		[6:0]	HEX5;
output		[6:0]	HEX6;
output		[6:0]	HEX7;

// 	Memory (SRAM)
output		[17:0]	SRAM_ADDR;

output				SRAM_CE_N;
output				SRAM_WE_N;
output				SRAM_OE_N;
output				SRAM_UB_N;
output				SRAM_LB_N;

//  Communication
output				UART_TXD;

//  Memory (SDRAM)
output		[11:0]	DRAM_ADDR;

output				DRAM_BA_1;
output				DRAM_BA_0;
output				DRAM_CAS_N;
output				DRAM_RAS_N;
output				DRAM_CLK;
output				DRAM_CKE;
output				DRAM_CS_N;
output				DRAM_WE_N;
output				DRAM_UDQM;
output				DRAM_LDQM;

//  VGA
output				VGA_CLK;
output				VGA_HS;
output				VGA_VS;
output				VGA_BLANK;
output				VGA_SYNC;
output		[ 9: 0]	VGA_R;
output		[ 9: 0]	VGA_G;
output		[ 9: 0]	VGA_B;

//  Char LCD 16x2
output				LCD_ON;
output				LCD_BLON;
output				LCD_EN;
output				LCD_RS;
output				LCD_RW;

//  Flash
output 		[21: 0]	FL_ADDR;
output 				FL_CE_N;
output				FL_OE_N;
output				FL_RST_N;
output				FL_WE_N;


/*****************************************************************************
 *                 Internal Wires and Registers Declarations                 *
 *****************************************************************************/
// Internal Wires

wire clk_25;

// Internal Registers

// State Machine Registers

/*****************************************************************************
 *                         Finite State Machine(s)                           *
 *****************************************************************************/


/*****************************************************************************
 *                             Sequential Logic                              *
 *****************************************************************************/


/*****************************************************************************
 *                            Combinational Logic                            *
 *****************************************************************************/

// Output Assignments
assign GPIO_0[ 0]	= 1'bZ;
assign GPIO_0[ 2]	= 1'bZ;
assign GPIO_0[16]	= 1'bZ;
assign GPIO_0[18]	= 1'bZ;
assign GPIO_1[ 0]	= 1'bZ;
assign GPIO_1[ 2]	= 1'bZ;
assign GPIO_1[16]	= 1'bZ;
assign GPIO_1[18]	= 1'bZ;

assign ENET_CLK = clk_25;

/*****************************************************************************
 *                              Internal Modules                             *
 *****************************************************************************/
nios_system NiosII (
	// 1) global signals:
	.clk									(CLOCK_50),
	.clk_27									(CLOCK_27),
	.reset_n								(1'b1),
	
	.sys_clk								(),
	.vga_clk								(clk_25),
	.sdram_clk								(DRAM_CLK),
	.audio_clk								(AUD_XCK),

	// the_Char_LCD_16x2
	.LCD_DATA_to_and_from_the_Char_LCD_16x2	(LCD_DATA),
	.LCD_ON_from_the_Char_LCD_16x2			(LCD_ON),
	.LCD_BLON_from_the_Char_LCD_16x2		(LCD_BLON),
	.LCD_EN_from_the_Char_LCD_16x2			(LCD_EN),
	.LCD_RS_from_the_Char_LCD_16x2			(LCD_RS),
	.LCD_RW_from_the_Char_LCD_16x2			(LCD_RW),

	// the_HEX3_HEX0
	.HEX0_from_the_HEX3_HEX0				(HEX0),
	.HEX1_from_the_HEX3_HEX0				(HEX1),
	.HEX2_from_the_HEX3_HEX0				(HEX2),
	.HEX3_from_the_HEX3_HEX0				(HEX3),
	
	// the_HEX7_HEX4
	.HEX4_from_the_HEX7_HEX4				(HEX4),
	.HEX5_from_the_HEX7_HEX4				(HEX5),
	.HEX6_from_the_HEX7_HEX4				(HEX6),
	.HEX7_from_the_HEX7_HEX4				(HEX7),
	
	// the_PS2_Port
	.PS2_CLK_to_and_from_the_PS2_Port		(PS2_CLK),
	.PS2_DAT_to_and_from_the_PS2_Port		(PS2_DAT),

	// the_Pushbuttons
	.KEY_to_the_Pushbuttons					(KEY[3:0]),
	
	// the_SDRAM
	.zs_addr_from_the_SDRAM					(DRAM_ADDR),
	.zs_ba_from_the_SDRAM					({DRAM_BA_1, DRAM_BA_0}),
	.zs_cas_n_from_the_SDRAM				(DRAM_CAS_N),
	.zs_cke_from_the_SDRAM					(DRAM_CKE),
	.zs_cs_n_from_the_SDRAM					(DRAM_CS_N),
	.zs_dq_to_and_from_the_SDRAM			(DRAM_DQ),
	.zs_dqm_from_the_SDRAM					({DRAM_UDQM, DRAM_LDQM}),
	.zs_ras_n_from_the_SDRAM				(DRAM_RAS_N),
	.zs_we_n_from_the_SDRAM					(DRAM_WE_N),
	
	// the_SRAM
	.SRAM_DQ_to_and_from_the_SRAM			(SRAM_DQ),
	.SRAM_ADDR_from_the_SRAM				(SRAM_ADDR),
	.SRAM_LB_N_from_the_SRAM				(SRAM_LB_N),
	.SRAM_UB_N_from_the_SRAM				(SRAM_UB_N),
	.SRAM_CE_N_from_the_SRAM				(SRAM_CE_N),
	.SRAM_OE_N_from_the_SRAM				(SRAM_OE_N),
	.SRAM_WE_N_from_the_SRAM				(SRAM_WE_N),
	
	// the_Slider_switches
	.SW_to_the_Slider_Switches				(SW),

	// the_VGA_Controller
	.VGA_CLK_from_the_VGA_Controller		(VGA_CLK),
	.VGA_HS_from_the_VGA_Controller			(VGA_HS),
	.VGA_VS_from_the_VGA_Controller			(VGA_VS),
	.VGA_BLANK_from_the_VGA_Controller		(VGA_BLANK),
	.VGA_SYNC_from_the_VGA_Controller		(VGA_SYNC),
	.VGA_R_from_the_VGA_Controller			(VGA_R),
	.VGA_G_from_the_VGA_Controller			(VGA_G),
	.VGA_B_from_the_VGA_Controller			(VGA_B),
	
	// the Flash
	.flash_ADDR                             (FL_ADDR),
   .flash_CE_N                             (FL_CE_N),
   .flash_OE_N                             (FL_OE_N),
   .flash_WE_N                             (FL_WE_N),
   .flash_RST_N                            (FL_RST_N),
   .flash_DQ                               (FL_DQ),
);

endmodule

