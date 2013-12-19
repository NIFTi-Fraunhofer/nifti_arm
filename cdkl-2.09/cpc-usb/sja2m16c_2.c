/****************************************************************************
*                                                                            
*      Copyright (c) 2003,2004 by EMS Dr. Thomas Wuensche              
*                                                                            
*                  - All rights reserved -                                   
*                                                                            
* This code is provided "as is" without warranty of any kind, either         
* expressed or implied, including but not limited to the liability           
* concerning the freedom from material defects, the fitness for parti-       
* cular purposes or the freedom of proprietary rights of third parties.      
*                                                                            
*****************************************************************************
* Module name.: cpcusb
*****************************************************************************
* Include file: cpc.h                                                      
*****************************************************************************
* Project.....: Windows Driver Development Kit                               
* Filename....: sja2m16c.cpp                                             
* Authors.....: (GU) Gerhard Uttenthaler
*               (CS) Christian Schoett
*****************************************************************************
* Short descr.: converts baudrate between SJA1000 and M16C    
*****************************************************************************
* Description.: handles the baudrate conversion from SJA1000 parameters to
*               M16C parameters
*****************************************************************************
* Address     : EMS Dr. Thomas Wuensche                                      
*               Sonnenhang 3                                                 
*               D-85304 Ilmmuenster                                          
*               Tel. : +49-8441-490260                                       
*               Fax. : +49-8441-81860                                        
*               email: support@ems-wuensche.com
*****************************************************************************
*                            History                                         
*****************************************************************************
* Version  Date        Auth Remark                                       
*                                                                            
* 01.00    ??          GU   - initial release
* 01.10    ??????????  CS   - adapted to fit into the USB Windows driver
* 02.00    18.08.2004  GU   - improved the baudrate calculating algorithm
*                           - implemented acceptance filtering
* 02.10    10.09.2004  CS   - adapted to fit into the USB Windows driver
*****************************************************************************
*                            ToDo's                                          
*****************************************************************************
*/  
    
/****************************************************************************/ 
/*     I N C L U D E S
*/ 
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>
#include <linux/module.h>
#include <linux/poll.h>
#include <linux/version.h>
#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,39))
#include <linux/smp_lock.h>
#endif
#include <linux/completion.h>
#include <asm/uaccess.h>
#include <linux/usb.h>
    
#include "../include/cpc.h"
#include "../include/cpc_int.h"
#include "cpcusb.h"
    
#include "sja2m16c.h"
    
/*********************************************************************/ 
int baudrate_m16c(int clk, int brp, int pr, int ph1, int ph2) 
{
	
							    ph1 + 1 + ph2 +
							    1);



/*********************************************************************/ 
int samplepoint_m16c(int brp, int pr, int ph1, int ph2) 
{
	
						  ph2 + 1);



/****************************************************************************
* Function.....: SJA1000_TO_M16C_BASIC_Params
*                                                                      
* Task.........: This routine converts SJA1000 CAN btr parameters into M16C
*                parameters based on the sample point and the error. In 
*                addition it converts the acceptance filter parameters to 
*                suit the M16C parameters
*                                                                      
* Parameters...: None
*                                                                      
* Return values: None
*
* Comments.....: 
*****************************************************************************
*                History
*****************************************************************************
* 19.01.2005  CS   - modifed the conversion of SJA1000 filter params into
*                    M16C params. Due to compatibility reasons with the 
*                    older 82C200 CAN controller the SJA1000 
****************************************************************************/ 
int SJA1000_TO_M16C_BASIC_Params(CPC_MSG_T * in) 
{
	
	
	
	int *samplepoint_error;	// BRP[0..15], PR[0..7], PH1[0..7], PH2[0..7]
	int baudrate_error_merk;
	
	
	
	
	
	
	
	
	
	
	
	    // we have to convert the parameters into M16C parameters
	    CPC_SJA1000_PARAMS_T * pParams;
	
	    // check if the type is CAN parameters and if we have to convert the given params
	    if (in->type != CPC_CMD_T_CAN_PRMS
		|| in->msg.canparams.cc_type != SJA1000)
		
	
	    (CPC_SJA1000_PARAMS_T *) & in->msg.canparams.cc_params.sja1000;
	
	
	
	
	
	
	
	
	
#ifdef _DEBUG_OUTPUT_CAN_PARAMS
	    info("acc_code0: %2.2Xh\n", acc_code0);
	
	
	
	
	
	
	
	
#endif	/* 
	    
		 (baudrate_error =
		  (int *) vmalloc(sizeof(int) * 16 * 8 * 8 * 8 * 5))) {
		
		
	
	
	      (samplepoint_error =
	       (int *) vmalloc(sizeof(int) * 16 * 8 * 8 * 8 * 5))) {
		
		
		
	
	
	
	
	    16000000 / 2 / SJA_BRP / (1 + SJA_TSEG1 + SJA_TSEG2);
	
	    100 * (1 + SJA_TSEG1) / (1 + SJA_TSEG1 + SJA_TSEG2);
	
		
		
		
	
	
#ifdef _DEBUG_OUTPUT_CAN_PARAMS
	    info("\nStarting SJA CAN params\n");
	
	
	
	      pParams->btr1);
	
	      sjaBaudrate % 1000);
	
	
	
#endif	/* 
	    
	
	
	    // calculate errors for all baudrates
	    index = 0;
	
		
			
				
					
						
						    100 *
						    abs(baudrate_m16c
							(clk, brp, pr, ph1,
							 ph2) -
							sjaBaudrate) /
						    sjaBaudrate;
						
						    abs(samplepoint_m16c
							(brp, pr, ph1,
							 ph2) -
							sjaSamplepoint);
						
#if 0
						    info
						    ("Baudrate      : %d kBaud\n",
						     baudrate_m16c(clk,
								   brp, pr,
								   ph1,
								   ph2));
						
						    ("Baudrate Error: %d\n",
						     baudrate_error
						     [index]);
						
						    ("Sample P Error: %d\n",
						     samplepoint_error
						     [index]);
						
						    ("clk           : %d\n",
						     clk);
						
#endif	/* 
						    index++;
					
				
			
		
	
	
	    // mark all baudrate_error entries which are outer limits
	    index = 0;
	
		
			
				
					
						
						      >
						      BAUDRATE_TOLERANCE_PERCENT)
						     ||
						     
						       [index] >
						       SAMPLEPOINT_TOLERANCE_PERCENT)
						     ||
						     
						       (brp, pr, ph1,
							ph2) >
						       SAMPLEPOINT_UPPER_LIMIT))
						{
							
							    [index] = -1;
						
						    if (((1 + pr + 1 +
							  ph1 + 1 + ph2 +
							  1) < 8)
							||
							((1 + pr + 1 +
							  ph1 + 1 + ph2 +
							  1) > 25)) {
							
							    [index] = -1;
						
						
#if 0
						    else {
							
							    ("Baudrate      : %d kBaud\n",
							     baudrate_m16c
							     (clk, brp, pr,
							      ph1, ph2));
							
							    ("Baudrate Error: %d\n",
							     baudrate_error
							     [index]);
							
							    ("Sample P Error: %d\n",
							     samplepoint_error
							     [index]);
						
						
#endif	/* 
						    index++;
					
				
			
		
	
	
	    // find list of minimum of baudrate_error within unmarked entries
	    clk_merk = brp_merk = pr_merk = ph1_merk = ph2_merk = 0;
	
	
	
		
			
				
					
						
						     != -1) {
							
							     [index] <
							     baudrate_error_merk)
							{
								
								    =
								    baudrate_error
								    [index];
								
								    brp;
								
								    pr;
								
								    ph1;
								
								    ph2;
								
								    clk;
								
#if 0
								    info
								    ("brp: %2.2Xh pr: %2.2Xh ph1: %2.2Xh ph2: %2.2Xh\n",
								     brp,
								     pr,
								     ph1,
								     ph2);
								
								    ("Baudrate      : %d kBaud\n",
								     baudrate_m16c
								     (clk,
								      brp,
								      pr,
								      ph1,
								      ph2));
								
								    ("Baudrate Error: %d\n",
								     baudrate_error
								     [index]);
								
								    ("Sample P Error: %d\n",
								     samplepoint_error
								     [index]);
								
#endif	/* 
							}
						
						
					
				
			
		
	
	
		
		
		
		
	
	
	    // setting m16c CAN parameter
	    c0con.bc0con.brp = brp_merk;
	
	
	
	
#ifdef _DEBUG_OUTPUT_CAN_PARAMS
	    info("\nResulting M16C CAN params\n");
	
	
	
	      c1con.bc1con.ph2 + 1);
	
	      c0con.bc0con.brp + 1);
	
	      c0con.bc0con.sam);
	
	
	       baudrate_m16c(clk_merk, c0con.bc0con.brp, c0con.bc0con.pr,
			     c1con.bc1con.ph1, c1con.bc1con.ph2) / 1000,
	       
			      c1con.bc1con.ph1, c1con.bc1con.ph2) % 1000);
	
	      samplepoint_m16c(c0con.bc0con.brp, c0con.bc0con.pr,
			       c1con.bc1con.ph1, c1con.bc1con.ph2));
	
	
#endif	/* 
	    
	
	
	
	
	
	
	
	
	
	    acc_code0;
	
	
//      info("code0: 0x%2.2X, code1: 0x%2.2X\n", out->msg.canparams.cc_params.m16c_basic.acc_std_code0, out->msg.canparams.cc_params.m16c_basic.acc_std_code1);
	    
	
	    (unsigned char) tmpAccCode;
	
	    (unsigned char) (tmpAccCode >> 8);
	
//      info("code0: 0x%2.2X, code1: 0x%2.2X\n", out->msg.canparams.cc_params.m16c_basic.acc_std_code0, out->msg.canparams.cc_params.m16c_basic.acc_std_code1);
	    
	    ~acc_mask0;
	
	    ~acc_mask1;
	
//      info("mask0: 0x%2.2X, mask1: 0x%2.2X\n", out->msg.canparams.cc_params.m16c_basic.acc_std_mask0, out->msg.canparams.cc_params.m16c_basic.acc_std_mask1);
	    
	
//      info("tmpAccMask: 0x%4.4X\n", tmpAccMask);
	    out->msg.canparams.cc_params.m16c_basic.acc_std_mask0 =
	    (unsigned char) ~tmpAccMask;
	
	    (unsigned char) ~(tmpAccMask >> 8);
	
//      info("mask0: 0x%2.2X, mask1: 0x%2.2X\n", out->msg.canparams.cc_params.m16c_basic.acc_std_mask0, out->msg.canparams.cc_params.m16c_basic.acc_std_mask1);
	    
	    (unsigned char) tmpAccCode;
	
	    (unsigned char) (tmpAccCode >> 8);
	
	
	
	    (unsigned char) ~tmpAccMask;
	
	    (unsigned char) ~(tmpAccMask >> 8);
	
	    ~acc_mask2;
	
	    ~acc_mask3;
	
	
	


