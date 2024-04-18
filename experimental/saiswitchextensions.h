/**
 * Copyright (c) 2018 Microsoft Open Technologies, Inc.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License"); you may
 *    not use this file except in compliance with the License. You may obtain
 *    a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
 *
 *    THIS CODE IS PROVIDED ON AN *AS IS* BASIS, WITHOUT WARRANTIES OR
 *    CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT
 *    LIMITATION ANY IMPLIED WARRANTIES OR CONDITIONS OF TITLE, FITNESS
 *    FOR A PARTICULAR PURPOSE, MERCHANTABILITY OR NON-INFRINGEMENT.
 *
 *    See the Apache Version 2.0 License for specific language governing
 *    permissions and limitations under the License.
 *
 *    Microsoft would like to thank the following companies for their review and
 *    assistance with these files: Intel Corporation, Mellanox Technologies Ltd,
 *    Dell Products, L.P., Facebook, Inc., Marvell International Ltd.
 *
 * @file    saiswitchextensions.h
 *
 * @brief   This module defines switch extensions of the Switch Abstraction Interface (SAI)
 */

#ifndef __SAISWITCHEXTENSIONS_H_
#define __SAISWITCHEXTENSIONS_H_

#include <saiswitch.h>
#include <saitypes.h>

/**
 * @brief SAI switch attribute extensions.
 *
 * @flags free
 */
typedef enum _sai_switch_attr_extensions_t
{
    SAI_SWITCH_ATTR_EXTENSIONS_RANGE_START = SAI_SWITCH_ATTR_END,

    /**
     * @brief Maximum number of meter buckets per ENI.
     *
     * @type sai_uint32_t
     * @flags READ_ONLY
     */
    SAI_SWITCH_ATTR_DASH_CAPS_MAX_METER_BUCKET_COUNT_PER_ENI = SAI_SWITCH_ATTR_EXTENSIONS_RANGE_START,

    SAI_SWITCH_ATTR_EXTENSIONS_RANGE_END

} sai_switch_attr_extensions_t;

#endif /* __SAISWITCHEXTENSIONS_H_ */
