/******************************************************************************
* Copyright (C) 2015 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
******************************************************************************/

#ifndef XPFW_IPI_MANAGER_H_
#define XPFW_IPI_MANAGER_H_

#include "xstatus.h"
#include "xpfw_default.h"
#include "xpfw_module.h"
#include "xipipsu.h"
#include "xparameters.h"

#define XPFW_IPI_MASK_COUNT XIPIPSU_MAX_TARGETS
extern u32 IpiMaskList[XPFW_IPI_MASK_COUNT];

#define XPFW_IPI_MAX_MSG_LEN XIPIPSU_MAX_MSG_LEN

#define IPI_PMU_0_IER_APU_MASK	  XPAR_XIPIPS_TARGET_PSU_CORTEXA53_0_CH0_MASK
#define IPI_PMU_0_IER_RPU_0_MASK  XPAR_XIPIPS_TARGET_PSU_CORTEXR5_0_CH0_MASK
#define IPI_PMU_0_IER_RPU_1_MASK  XPAR_XIPIPS_TARGET_PSU_CORTEXR5_1_CH0_MASK
/**
 * Initialize the IPI driver instance
 * This should be called in the core init
 */
s32 XPfw_IpiManagerInit(void);

/**
 * Write a message to IPI Message Buffer
 * @param ModPtr is the pointer to module that is sending the message
 * @param DestCpuMask is mask for the destination CPU
 * @param MsgPtr is pointer to the buffer containing the message to be sent
 * @param MsgLen is the number of 32-bit words to be sent
 * @return XST_SUCCESS if success
 *         XST_FAILURE if failure
 */
s32 XPfw_IpiWriteMessage(const XPfw_Module_t *ModPtr, u32 DestCpuMask, u32 *MsgPtr, u32 MsgLen);

/**
 * Write a message to IPI Response Buffer
 * This function is preferably called from with in a IPI interrupt handler to send a response
 * for that IPI request
 * @param ModPtr is the pointer to module that is sending the message
 * @param DestCpuMask is mask for the destination CPU
 * @param MsgPtr is pointer to the buffer containing the message to be sent
 * @param MsgLen is the number of 32-bit words to be sent
 * @return XST_SUCCESS if success
 *         XST_FAILURE if failure
 */
s32 XPfw_IpiWriteResponse(const XPfw_Module_t *ModPtr, u32 DestCpuMask, u32 *MsgPtr, u32 MsgLen);

/**
 * Read Message buffer contents (Used only by Core)
 * @param SrcCpuMask is mask for the Source CPU
 * @param MsgPtr is pointer to the buffer to which message is to be retrieved
 * @param MsgLen is the number of 32-bits to be retrieved
 * @return XST_SUCCESS if IPI ID of the module matches and the message is read into buffer
 *         XST_FAILURE in case of an error
 */
s32 XPfw_IpiReadMessage(u32 SrcCpuMask, u32 *MsgPtr, u32 MsgLen);

/**
 * Read Response buffer contents
 * @param ModPtr is the pointer to module that is requesting the message
 * @param SrcCpuMask is mask for the Source CPU
 * @param MsgPtr is pointer to the buffer to which message is to be retrieved
 * @param MsgLen is the number of 32-bits to be retrieved
 * @return XST_SUCCESS if the message is read into buffer
 *         XST_FAILURE if a mismatch in IPI ID or failure to read message
 */
s32 XPfw_IpiReadResponse(const XPfw_Module_t *ModPtr, u32 SrcCpuMask, u32 *MsgPtr, u32 MsgLen);

/**
 * Trigger an IPI interrupt to a target processor
 *
 * @param DestCpuMask is the mask corresponding to Dest CPU
 *
 * @return XST_SUCCESS if IPI was triggered
 *         XST_FAILURE if an error occurred while triggering
 */
s32 XPfw_IpiTrigger(u32 DestCpuMask);

#endif /* XPFW_IPI_MANAGER_H_ */
