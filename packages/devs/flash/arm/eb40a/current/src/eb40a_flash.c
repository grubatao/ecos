//==========================================================================
//
//      eb40a_flash.c
//
//      Flash programming for Atmel device on Atmel EB40A board
//
//==========================================================================
// ####ECOSGPLCOPYRIGHTBEGIN####                                            
// -------------------------------------------                              
// This file is part of eCos, the Embedded Configurable Operating System.   
// Copyright (C) 1998, 1999, 2000, 2001, 2002 Free Software Foundation, Inc.
//
// eCos is free software; you can redistribute it and/or modify it under    
// the terms of the GNU General Public License as published by the Free     
// Software Foundation; either version 2 or (at your option) any later      
// version.                                                                 
//
// eCos is distributed in the hope that it will be useful, but WITHOUT      
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or    
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License    
// for more details.                                                        
//
// You should have received a copy of the GNU General Public License        
// along with eCos; if not, write to the Free Software Foundation, Inc.,    
// 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.            
//
// As a special exception, if other files instantiate templates or use      
// macros or inline functions from this file, or you compile this file      
// and link it with other works to produce a work based on this file,       
// this file does not by itself cause the resulting work to be covered by   
// the GNU General Public License. However the source code for this file    
// must still be made available in accordance with section (3) of the GNU   
// General Public License v2.                                               
//
// This exception does not invalidate any other reasons why a work based    
// on this file might be covered by the GNU General Public License.         
// -------------------------------------------                              
// ####ECOSGPLCOPYRIGHTEND####                                              
//==========================================================================
//#####DESCRIPTIONBEGIN####
//
// Author(s):    jskov, tdrury
// Contributors: jskov, nickg
// Date:         2002-07-08
// Purpose:      
// Description:  
//              
//####DESCRIPTIONEND####
//
//==========================================================================


// The EB40 can either contain a AT49LV1604 or a AT49LV1614. For now we just
// treat both as a 1614.

#define CYGHWR_DEVS_FLASH_ATMEL_AT49LV1614A
#define CYGNUM_FLASH_INTERLEAVE	(1)
#define CYGNUM_FLASH_WIDTH      (16)
#define CYGNUM_FLASH_SERIES	(1)
#define CYGNUM_FLASH_BASE 	(0x01000000u)

#include "cyg/io/flash_at49xxxx.inl"


// ------------------------------------------------------------------------
// EOF eb40a_flash.c
