/**************************************************************************
*
* Copyright (C) 2006 Steve Karg <skarg@users.sourceforge.net>
*
* Permission is hereby granted, free of charge, to any person obtaining
* a copy of this software and associated documentation files (the
* "Software"), to deal in the Software without restriction, including
* without limitation the rights to use, copy, modify, merge, publish,
* distribute, sublicense, and/or sell copies of the Software, and to
* permit persons to whom the Software is furnished to do so, subject to
* the following conditions:
*
* The above copyright notice and this permission notice shall be included
* in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*
*********************************************************************/
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include "config_bacnet.h"
#include "txbuf.h"
#include "bacdef.h"
#include "bacdcode.h"
#include "timesync.h"
#include "handlers.h"

#if PRINT_ENABLED
    #include "debug_msg.h"
#endif


/** @file h_ts.c  Handles TimeSync requests. */

#if PRINT_ENABLED
static void show_bacnet_date_time(
    BACNET_DATE * bdate,
    BACNET_TIME * btime)
{
    /* show the date received */
    H_DEBUG_MSG("%u", (unsigned) bdate->year);
    H_DEBUG_MSG("/%u", (unsigned) bdate->month);
    H_DEBUG_MSG("/%u", (unsigned) bdate->day);
    /* show the time received */
    H_DEBUG_MSG(" %02u", (unsigned) btime->hour);
    H_DEBUG_MSG(":%02u", (unsigned) btime->min);
    H_DEBUG_MSG(":%02u", (unsigned) btime->sec);
    H_DEBUG_MSG(".%02u", (unsigned) btime->hundredths);
    H_DEBUG_MSG("");
}
#endif

void handler_timesync(
    uint8_t * service_request,
    uint16_t service_len,
    BACNET_ADDRESS * src)
{
    int len = 0;
    BACNET_DATE bdate;
    BACNET_TIME btime;

    (void) src;
    (void) service_len;
    len =
        timesync_decode_service_request(service_request, service_len, &bdate,
        &btime);
    if (len > 0) {
#if PRINT_ENABLED
        H_DEBUG_VMSG("Received TimeSyncronization Request");
        show_bacnet_date_time(&bdate, &btime);
#else
        /* FIXME: set the time? */
#endif
    }

    return;
}

void handler_timesync_utc(
    uint8_t * service_request,
    uint16_t service_len,
    BACNET_ADDRESS * src)
{
    int len = 0;
    BACNET_DATE bdate;
    BACNET_TIME btime;

    (void) src;
    (void) service_len;
    len =
        timesync_decode_service_request(service_request, service_len, &bdate,
        &btime);
    if (len > 0) {
#if PRINT_ENABLED
        H_DEBUG_VMSG("Received TimeSyncronization Request");
        show_bacnet_date_time(&bdate, &btime);
#endif
        /* FIXME: set the time? */
    }

    return;
}
