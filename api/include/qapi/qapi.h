/* Copyright (c) 2011-2015.  Qualcomm Atheros, Inc.
All rights reserved.

Qualcomm Atheros Confidential and Proprietary.

*/

#ifndef __QAPI_H__ // [
#define __QAPI_H__

/**
 * @file qapi.h
 *
 * @brief QAPI interface definition
 *
 * @details This file provides the base type definitions used by the QAPI.
 *          This includes the basic integer types (based on stdint.h and
 *          stddef.h) and a basic boolean type.
 */

/*-------------------------------------------------------------------------
 * Include Files
 * ----------------------------------------------------------------------*/
#include "qapi_types.h"
#include "qapi_status.h"

#ifdef QAPI_USE_LPW // [
  #include "qapi_lpw.h"
#endif // ] ifdef QAPI_USE_LPW

#ifdef QAPI_USE_BLE // [
  #include "qapi_ble.h"
#endif // ] ifdef QAPI_USE_BLE

#ifdef QAPI_USE_WLAN // [
  #include "qapi_wlan.h"
#endif // ] ifdef QAPI_USE_WLAN

#ifdef QAPI_USE_LPW // [
  #include "qapi_lpw.h"
#endif // ] ifdef QAPI_USE_LPW

#ifdef QAPI_USE_I2C_MASTER // [
  #include "qapi_i2c_master.h"
#endif // ] ifdef QAPI_USE_I2C_MASTER

#ifdef QAPI_USE_SPI_MASTER // [
  #include "qapi_spi_master.h"
#endif // ] ifdef QAPI_USE_SPI_MASTER

#ifdef QAPI_USE_PWM // [
  #include "qapi_pwm.h"
#endif // ] ifdef QAPI_USE_PWM

#ifdef QAPI_USE_TLMM // [
  #include "qapi_tlmm.h"
#endif // ] ifdef QAPI_USE_TLMM

#ifdef QAPI_USE_GPIOINT // [
  #include "qapi_gpioint.h"
#endif // ] ifdef QAPI_USE_GPIOINT

#ifdef QAPI_USE_ERR_SERVICES // [
  #include "qapi_fatal_err.h"
#endif // ] ifdef QAPI_USE_ERR_SERVICES

#ifdef QAPI_USE_DIAG_CLI // [
  #include "qapi_diag_cli.h"
#endif // ] ifdef QAPI_USE_DIAG_CLI

#ifdef QAPI_USE_DIAG_MSG // [
  #include "qapi_diag_msg.h"
#endif // ] ifdef QAPI_USE_DIAG_MSG

#ifdef QAPI_USE_TSENS // [
  #include "qapi_tsens.h"
#endif // ] ifdef QAPI_USE_TSENS

#ifdef QAPI_USE_ADC // [
  #include "qapi_adc.h"
#endif // ] ifdef QAPI_USE_ADC

#ifdef QAPI_USE_UART // [
  #include "qapi_uart.h"
#endif // ] ifdef QAPI_USE_UART

#ifdef QAPI_USE_KPD // [
  #include "qapi_kpd.h"
#endif // ] ifdef QAPI_USE_KPD

//#define QAPI_USE_PMU
#ifdef QAPI_USE_PMU // [
  #include "qapi_pmu.h"
#endif // ] ifdef QAPI_USE_PMU

//#define QAPI_USE_CLK
#ifdef QAPI_USE_CLK // [
  #include "qapi_clk.h"
#endif // ] ifdef QAPI_USE_CLK

#ifdef QAPI_USE_OMSM
  #include "qapi_om_smem.h"
#endif

#ifdef QAPI_USE_OMTM // [
  #include "qapi_omtm.h"
#endif // ] ifdef QAPI_USE_OMTM

#ifdef QAPI_USE_SPM // [
  #include "qapi_spm.h"
#endif // ] ifdef QAPI_USE_SPM

#ifdef QAPI_USE_SLP // [
  #include "qapi_slp.h"
#endif // ] ifdef QAPI_USE_SLP

#ifdef QAPI_USE_FILESYSTEM // [
  #include "qapi_fs.h"
#endif // ] ifdef QAPI_USE_FILESYSTEM

#ifdef QAPI_USE_HEAP // [
  #include "qapi_heap.h"
#endif // ] ifdef QAPI_USE_HEAP

#ifdef QAPI_USE_MOM // [
  #include "qapi_mom.h"
#endif // ] ifdef QAPI_USE_MOM

/*-------------------------------------------------------------------------
 * Function Declarations and Documentation
 * ----------------------------------------------------------------------*/

/* Function Definitions to be added later */

#endif // ] #ifndef __QAPI_H__
