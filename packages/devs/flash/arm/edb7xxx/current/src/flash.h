//==========================================================================
//
//      flash.h
//
//      Flash programming - device constants, etc.
//
//==========================================================================
//####COPYRIGHTBEGIN####
//                                                                          
// -------------------------------------------                              
// The contents of this file are subject to the Red Hat eCos Public License 
// Version 1.1 (the "License"); you may not use this file except in         
// compliance with the License.  You may obtain a copy of the License at    
// http://www.redhat.com/                                                   
//                                                                          
// Software distributed under the License is distributed on an "AS IS"      
// basis, WITHOUT WARRANTY OF ANY KIND, either express or implied.  See the 
// License for the specific language governing rights and limitations under 
// the License.                                                             
//                                                                          
// The Original Code is eCos - Embedded Configurable Operating System,      
// released September 30, 1998.                                             
//                                                                          
// The Initial Developer of the Original Code is Red Hat.                   
// Portions created by Red Hat are                                          
// Copyright (C) 1998, 1999, 2000 Red Hat, Inc.                             
// All Rights Reserved.                                                     
// -------------------------------------------                              
//                                                                          
//####COPYRIGHTEND####
//==========================================================================
//#####DESCRIPTIONBEGIN####
//
// Author(s):    gthomas
// Contributors: gthomas
// Date:         2000-07-26
// Purpose:      
// Description:  
//              
//####DESCRIPTIONEND####
//
//==========================================================================

#ifndef _FLASH_HWR_H_
#define _FLASH_HWR_H_

#define FLASH_Read_ID      0x90909090
#define FLASH_Read_Status  0x00700070
#define FLASH_Clear_Status 0x50505050
#define FLASH_Status_Ready 0x00800080  // Only low 8 bits
#define FLASH_Program      0x40404040
#define FLASH_Block_Erase  0x20202020
#define FLASH_Confirm      0xD0D0D0D0
#define FLASH_Reset        0xFFFFFFFF

#define FLASH_BLOCK_SIZE   0x20000
#define FLASH_BOOT_BLOCK_SIZE   0x4000

#define FLASH_Intel_code   0x89

#endif  // _FLASH_HWR_H_
