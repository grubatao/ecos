//==========================================================================
//
//      devs_eth_arm_olpce2294.inl
//
//      OLPCE2294 ethernet I/O definitions
//
//==========================================================================
//####ECOSGPLCOPYRIGHTBEGIN####
// -------------------------------------------
// This file is part of eCos, the Embedded Configurable Operating System.
// Copyright (C) 1998, 1999, 2000, 2001, 2002 Red Hat, Inc.
// Copyright (C) 2008 eCosCentric Limited
//
// eCos is free software; you can redistribute it and/or modify it under
// the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 or (at your option) any later version.
//
// eCos is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
// for more details.
//
// You should have received a copy of the GNU General Public License along
// with eCos; if not, write to the Free Software Foundation, Inc.,
// 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA.
//
// As a special exception, if other files instantiate templates or use macros
// or inline functions from this file, or you compile this file and link it
// with other works to produce a work based on this file, this file does not
// by itself cause the resulting work to be covered by the GNU General Public
// License. However the source code for this file must still be made available
// in accordance with section (3) of the GNU General Public License.
//
// This exception does not invalidate any other reasons why a work based on
// this file might be covered by the GNU General Public License.
// -------------------------------------------
//####ECOSGPLCOPYRIGHTEND####
//==========================================================================
//#####DESCRIPTIONBEGIN####
//
// Author(s):     Sergei Gavrikov
// Contributors:  Sergei Gavrikov
// Date:          2008-08-31
// Purpose:       OLPCE2294 ethernet definitions
// Description:
//
//####DESCRIPTIONEND####
//
//========================================================================*/

#include <cyg/hal/hal_intr.h>
#include <cyg/hal/hal_if.h>

#ifdef CYGPKG_REDBOOT
# include <pkgconf/redboot.h>
# ifdef CYGSEM_REDBOOT_FLASH_CONFIG
#  include <redboot.h>
#  include <flash_config.h>
# endif
#endif

#ifdef __WANT_CONFIG
//#define DEBUG 0xf

// This is done by reading the low order byte first
#define CS_IN( _b_, _o_, _d_)                                   \
    CYG_MACRO_START                                             \
    cyg_uint8 x, y;                                             \
    HAL_READ_UINT8 ((cyg_addrword_t)(_b_)+(_o_), x);            \
    _d_ = x;                                                    \
    HAL_READ_UINT8 ((cyg_addrword_t)(_b_)+(_o_)+1, y);          \
    _d_ |= y << 8;                                              \
    CYG_MACRO_END

// This is done by writing the low order byte first
#define CS_OUT( _b_, _o_, _d_)                                  \
    CYG_MACRO_START                                             \
    HAL_WRITE_UINT8 ((cyg_addrword_t)(_b_)+(_o_), _d_);         \
    HAL_WRITE_UINT8 ((cyg_addrword_t)(_b_)+(_o_)+1, (_d_) >> 8);\
    CYG_MACRO_END

#endif // __WANT_CONFIG

#ifdef __WANT_DEVS

#ifdef CYGPKG_DEVS_ETH_ARM_OLPCE2294_ETH0

#ifndef CYGSEM_DEVS_ETH_ARM_OLPCE2294_ETH0_SET_ESA
#if defined(CYGPKG_REDBOOT) && defined(CYGSEM_REDBOOT_FLASH_CONFIG)
RedBoot_config_option("Set " CYGDAT_DEVS_ETH_ARM_OLPCE2294_ETH0_NAME " network hardware address [MAC]",
                      eth0_esa,
                      ALWAYS_ENABLED, true,
                      CONFIG_BOOL, false
    );
RedBoot_config_option(CYGDAT_DEVS_ETH_ARM_OLPCE2294_ETH0_NAME " network hardware address [MAC]",
                      eth0_esa_data,
                      "eth0_esa", true,
                      CONFIG_ESA, 0
    );
#endif // CYGPKG_REDBOOT && CYGSEM_REDBOOT_FLASH_CONFIG

# ifdef CYGSEM_HAL_VIRTUAL_VECTOR_SUPPORT
// Note that this section *is* active in an application, outside RedBoot,
// where the above section is not included.

#  include <cyg/hal/hal_if.h>

#  ifndef CONFIG_ESA
#   define CONFIG_ESA (6)
#  endif
#  ifndef CONFIG_BOOL
#   define CONFIG_BOOL (1)
#  endif

cyg_bool
_olpce2294_provide_eth0_esa(struct cs8900a_priv_data* cpd)
{
    cyg_bool set_esa;
    int ok;
    ok = CYGACC_CALL_IF_FLASH_CFG_OP( CYGNUM_CALL_IF_FLASH_CFG_GET,
                                      "eth0_esa", &set_esa, CONFIG_BOOL);
    if (ok && set_esa) {
        ok = CYGACC_CALL_IF_FLASH_CFG_OP( CYGNUM_CALL_IF_FLASH_CFG_GET,
                                          "eth0_esa_data", 
                                          cpd->esa, CONFIG_ESA);
    }
    return ok && set_esa;
}

# endif // CYGSEM_HAL_VIRTUAL_VECTOR_SUPPORT
#endif // ! CYGSEM_DEVS_ETH_ARM_OLPCE2294_ETH0_SET_ESA

static cs8900a_priv_data_t cs8900a_eth0_priv_data = {
    base : (cyg_addrword_t) 0x82000000,
    interrupt : CYGNUM_HAL_INTERRUPT_NONE,
#ifdef CYGSEM_DEVS_ETH_ARM_OLPCE2294_ETH0_SET_ESA
    esa : CYGDAT_DEVS_ETH_ARM_OLPCE2294_ETH0_ESA,
    hardwired_esa : true,
#else
    hardwired_esa : false,
# ifdef CYGSEM_HAL_VIRTUAL_VECTOR_SUPPORT
    provide_esa : &_olpce2294_provide_eth0_esa,
# else
    provide_esa : NULL,
# endif
#endif
};

ETH_DRV_SC(cs8900a_sc,
           &cs8900a_eth0_priv_data, // Driver specific data
           CYGDAT_DEVS_ETH_ARM_OLPCE2294_ETH0_NAME,
           cs8900a_start,
           cs8900a_stop,
           cs8900a_control,
           cs8900a_can_send,
           cs8900a_send,
           cs8900a_recv,
           cs8900a_deliver,     // "pseudoDSR" called from fast net thread
           cs8900a_poll,        // poll function, encapsulates ISR and DSR
           cs8900a_int_vector);

NETDEVTAB_ENTRY(cs8900a_netdev,
                "cs8900a_" CYGDAT_DEVS_ETH_ARM_OLPCE2294_ETH0_NAME,
                cs8900a_init,
                &cs8900a_sc);

#endif // CYGPKG_DEVS_ETH_ARM_OLPCE2294_ETH0

#endif // __WANT_DEVS

// indent: --indent-level4 -br -nut; vim: expandtab tabstop=4 shiftwidth=4
//--------------------------------------------------------------------------
// EOF devs_eth_arm_olpce2294.inl

