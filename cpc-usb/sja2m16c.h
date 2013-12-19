#ifndef SJA2M16C_H
#define SJA2M16C_H

#include "cpc.h"
    
#define BAUDRATE_TOLERANCE_PERCENT      1
#define SAMPLEPOINT_TOLERANCE_PERCENT   5
#define SAMPLEPOINT_UPPER_LIMIT        88
    
// M16C parameters
    typedef struct FIELD_C0CONR {
	
	
	
	


	
	
	
	


	
	


	
	


#define SJA_TSEG1  ((pParams->btr1 & 0x0f)+1)
#define SJA_TSEG2  (((pParams->btr1 & 0x70)>>4)+1)
#define SJA_BRP    ((pParams->btr0 & 0x3f)+1)
#define SJA_SJW    ((pParams->btr0 & 0xc0)>>6)
#define SJA_SAM    ((pParams->btr1 & 0x80)>>7)




#endif	/* 