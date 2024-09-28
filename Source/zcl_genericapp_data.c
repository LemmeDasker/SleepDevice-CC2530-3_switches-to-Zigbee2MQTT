/**************************************************************************************************
  Filename:       zcl_genericapp_data.c
  Revised:        $Date: 2014-05-12 13:14:02 -0700 (Mon, 12 May 2014) $
  Revision:       $Revision: 38502 $


  Description:    Zigbee Cluster Library - sample device application.


  Copyright 2006-2014 Texas Instruments Incorporated. All rights reserved.

  IMPORTANT: Your use of this Software is limited to those specific rights
  granted under the terms of a software license agreement between the user
  who downloaded the software, his/her employer (which must be your employer)
  and Texas Instruments Incorporated (the "License").  You may not use this
  Software unless you agree to abide by the terms of the License. The License
  limits your use, and you acknowledge, that the Software may not be modified,
  copied or distributed unless embedded on a Texas Instruments microcontroller
  or used solely and exclusively in conjunction with a Texas Instruments radio
  frequency transceiver, which is integrated into your product.  Other than for
  the foregoing purpose, you may not use, reproduce, copy, prepare derivative
  works of, modify, distribute, perform, display or sell this Software and/or
  its documentation for any purpose.

  YOU FURTHER ACKNOWLEDGE AND AGREE THAT THE SOFTWARE AND DOCUMENTATION ARE
  PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED,
  INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY, TITLE,
  NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT SHALL
  TEXAS INSTRUMENTS OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER CONTRACT,
  NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR OTHER
  LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
  INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE
  OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT
  OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
  (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

  Should you have any questions regarding your right to use this Software,
  contact Texas Instruments Incorporated at www.TI.com.
**************************************************************************************************/

/*********************************************************************
 * INCLUDES
 */
#include "ZComDef.h"
#include "OSAL.h"
#include "AF.h"
#include "ZDConfig.h"

#include "zcl.h"
#include "zcl_general.h"
#include "zcl_ha.h"
#include "zcl_genericapp.h"

/* GENERICAPP_TODO: Include any of the header files below to access specific cluster data
#include "zcl_poll_control.h"
#include "zcl_electrical_measurement.h"
#include "zcl_diagnostic.h"
#include "zcl_meter_identification.h"
#include "zcl_appliance_identification.h"
#include "zcl_appliance_events_alerts.h"
#include "zcl_power_profile.h"
#include "zcl_appliance_control.h"
#include "zcl_appliance_statistics.h"
#include "zcl_hvac.h"
*/


/*********************************************************************
 * CONSTANTS
 */

#define GENERICAPP_DEVICE_VERSION     0
#define GENERICAPP_FLAGS              0

#define GENERICAPP_HWVERSION          1
#define GENERICAPP_ZCLVERSION         2
#define GENERICAPP_APPVERSION         1
#define GENERICAPP_STACKVERSION       1

/*********************************************************************
 * TYPEDEFS
 */

/*********************************************************************
 * MACROS
 */

/*********************************************************************
 * GLOBAL VARIABLES
 */

// Global attributes
const uint16 zclGenericApp_clusterRevision_all = 0x0001; 

// Basic Cluster
const uint8 zclGenericApp_ManufacturerName[] = { 9, 'S','L','E','E','P','-','S','W','1' };
const uint8 zclGenericApp_ModelId[] = { 11, 'H','o','m','e','-','s','w','i','t','c','h' };
const uint8 zclGenericApp_PowerSource = POWER_SOURCE_BATTERY;
uint8 zclGenericApp_DeviceEnable = DEVICE_ENABLED;
uint8 zclGenericApp_PowerConfiguration_BatteryPercentageRemaining = 0;

// Identify Cluster
uint16 zclGenericApp_IdentifyTime = 0;

// On/Off Cluster
uint8  zclGenericApp_OnOff = 0;

/* GENERICAPP_TODO: declare attribute variables here. If its value can change,
 * initialize it in zclGenericApp_ResetAttributesToDefaultValues. If its
 * value will not change, initialize it here.
 */

#if ZCL_DISCOVER
CONST zclCommandRec_t zclGenericApp_Cmds[] =
{
  {
    ZCL_CLUSTER_ID_GEN_BASIC,
    COMMAND_BASIC_RESET_FACT_DEFAULT,
    CMD_DIR_SERVER_RECEIVED
  },

};

CONST uint8 zclCmdsArraySize = ( sizeof(zclGenericApp_Cmds) / sizeof(zclGenericApp_Cmds[0]) );
#endif // ZCL_DISCOVER

/*********************************************************************
 * ATTRIBUTE DEFINITIONS - Uses REAL cluster IDs
 */
CONST zclAttrRec_t zclGenericApp_Attrs[] =
{
  // *** General Basic Cluster Attributes ***
  {ZCL_CLUSTER_ID_GEN_BASIC, {ATTRID_BASIC_MANUFACTURER_NAME, ZCL_DATATYPE_CHAR_STR, ACCESS_CONTROL_READ, (void *)zclGenericApp_ManufacturerName}},
  {ZCL_CLUSTER_ID_GEN_BASIC, {ATTRID_BASIC_MODEL_ID, ZCL_DATATYPE_CHAR_STR, ACCESS_CONTROL_READ,(void *)zclGenericApp_ModelId}},
  {ZCL_CLUSTER_ID_GEN_BASIC, {ATTRID_BASIC_POWER_SOURCE, ZCL_DATATYPE_ENUM8, ACCESS_CONTROL_READ, (void *)&zclGenericApp_PowerSource}},
  {ZCL_CLUSTER_ID_GEN_BASIC, {ATTRID_BASIC_DEVICE_ENABLED, ZCL_DATATYPE_BOOLEAN, (ACCESS_CONTROL_READ | ACCESS_CONTROL_WRITE), (void *)&zclGenericApp_DeviceEnable}},

  {ZCL_CLUSTER_ID_GEN_POWER_CFG, {ATTRID_POWER_CFG_BATTERY_PERCENTAGE_REMAINING, ZCL_DATATYPE_UINT8, ACCESS_REPORTABLE | ACCESS_CONTROL_READ, (void *)&zclGenericApp_PowerConfiguration_BatteryPercentageRemaining}},
  
#ifdef ZCL_IDENTIFY
  // *** Identify Cluster Attribute ***
  {ZCL_CLUSTER_ID_GEN_IDENTIFY, {ATTRID_IDENTIFY_TIME, ZCL_DATATYPE_UINT16, (ACCESS_CONTROL_READ | ACCESS_CONTROL_WRITE), (void *)&zclGenericApp_IdentifyTime}},
  {ZCL_CLUSTER_ID_GEN_IDENTIFY, {ATTRID_CLUSTER_REVISION, ZCL_DATATYPE_UINT16, ACCESS_CONTROL_READ | ACCESS_CLIENT, (void *)&zclGenericApp_clusterRevision_all}},
#endif

  // *** On / Off Switch Configuration Cluster *** //
  //{ZCL_CLUSTER_ID_GEN_ON_OFF_SWITCH_CONFIG, {ATTRID_ON_OFF_SWITCH_TYPE, ZCL_DATATYPE_ENUM8, ACCESS_CONTROL_READ, (void *)&zclGenericApp_OnOffSwitchType}},
  //{ZCL_CLUSTER_ID_GEN_ON_OFF_SWITCH_CONFIG, {ATTRID_ON_OFF_SWITCH_ACTIONS, ZCL_DATATYPE_ENUM8, ACCESS_CONTROL_READ | ACCESS_CONTROL_WRITE, (void *)&zclGenericApp_OnOffSwitchActions}},
  //{ZCL_CLUSTER_ID_GEN_ON_OFF_SWITCH_CONFIG, {ATTRID_CLUSTER_REVISION, ZCL_DATATYPE_UINT16, ACCESS_CONTROL_READ, (void *)&zclGenericApp_clusterRevision_all}},

  // *** On / Off Cluster *** //
  {ZCL_CLUSTER_ID_GEN_ON_OFF, {ATTRID_ON_OFF, ZCL_DATATYPE_BOOLEAN, ACCESS_CONTROL_READ, (void *)&zclGenericApp_OnOff}},
  {ZCL_CLUSTER_ID_GEN_ON_OFF, {ATTRID_CLUSTER_REVISION, ZCL_DATATYPE_UINT16, ACCESS_CONTROL_READ | ACCESS_CLIENT, (void *)&zclGenericApp_clusterRevision_all}},

 };

uint8 CONST zclGenericApp_NumAttributes = ( sizeof(zclGenericApp_Attrs) / sizeof(zclGenericApp_Attrs[0]) );

/*********************************************************************
 * SIMPLE DESCRIPTOR
 */
// This is the Cluster ID List and should be filled with Application
// specific cluster IDs.
const cId_t zclGenericApp_InClusterList[] =
{
  ZCL_CLUSTER_ID_GEN_BASIC,
  ZCL_CLUSTER_ID_GEN_IDENTIFY,
  
  // GENERICAPP_TODO: Add application specific Input Clusters Here. 
  //       See zcl.h for Cluster ID definitions
  
};
#define ZCLGENERICAPP_MAX_INCLUSTERS   (sizeof(zclGenericApp_InClusterList) / sizeof(zclGenericApp_InClusterList[0]))


const cId_t zclGenericApp_OutClusterList[] =
{
  ZCL_CLUSTER_ID_GEN_BASIC,
  ZCL_CLUSTER_ID_GEN_POWER_CFG,
  ZCL_CLUSTER_ID_GEN_IDENTIFY,
  ZCL_CLUSTER_ID_GEN_ON_OFF
 
  // GENERICAPP_TODO: Add application specific Output Clusters Here. 
  //       See zcl.h for Cluster ID definitions
};
#define ZCLGENERICAPP_MAX_OUTCLUSTERS  (sizeof(zclGenericApp_OutClusterList) / sizeof(zclGenericApp_OutClusterList[0]))

//const cId_t zclGenericApp_OutClusterList2[] =
//{
//  ZCL_CLUSTER_ID_GEN_BASIC,
//  ZCL_CLUSTER_ID_GEN_IDENTIFY,
//  ZCL_CLUSTER_ID_GEN_ON_OFF
// 
//  // GENERICAPP_TODO: Add application specific Output Clusters Here. 
//  //       See zcl.h for Cluster ID definitions
//};
//#define ZCLGENERICAPP_MAX_OUTCLUSTERS2  (sizeof(zclGenericApp_OutClusterList2) / sizeof(zclGenericApp_OutClusterList2[0]))



SimpleDescriptionFormat_t zclGenericApp_SimpleDesc =
{
  GENERICAPP_ENDPOINT,                  //  int Endpoint;
  ZCL_HA_PROFILE_ID,                     //  uint16 AppProfId;
  // GENERICAPP_TODO: Replace ZCL_HA_DEVICEID_ON_OFF_LIGHT with application specific device ID
  ZCL_HA_DEVICEID_ON_OFF_SWITCH,  //  uint16 AppDeviceId; 
  GENERICAPP_DEVICE_VERSION,            //  int   AppDevVer:4;
  GENERICAPP_FLAGS,                     //  int   AppFlags:4;
  ZCLGENERICAPP_MAX_INCLUSTERS,         //  byte  AppNumInClusters;
  (cId_t *)zclGenericApp_InClusterList, //  byte *pAppInClusterList;
  ZCLGENERICAPP_MAX_OUTCLUSTERS,        //  byte  AppNumInClusters;
  (cId_t *)zclGenericApp_OutClusterList //  byte *pAppInClusterList;
};
//SimpleDescriptionFormat_t zclGenericApp_SimpleDesc2 =
//{
//  GENERICAPP_ENDPOINT2,                  //  int Endpoint;
//  ZCL_HA_PROFILE_ID,                     //  uint16 AppProfId;
//  // GENERICAPP_TODO: Replace ZCL_HA_DEVICEID_ON_OFF_LIGHT with application specific device ID
//  ZCL_HA_DEVICEID_ON_OFF_SWITCH,  //  uint16 AppDeviceId; 
//  GENERICAPP_DEVICE_VERSION,            //  int   AppDevVer:4;
//  GENERICAPP_FLAGS,                     //  int   AppFlags:4;
//  ZCLGENERICAPP_MAX_INCLUSTERS,         //  byte  AppNumInClusters;
//  (cId_t *)zclGenericApp_InClusterList, //  byte *pAppInClusterList;
//  ZCLGENERICAPP_MAX_OUTCLUSTERS2,        //  byte  AppNumInClusters;
//  (cId_t *)zclGenericApp_OutClusterList2 //  byte *pAppInClusterList;
//};
//SimpleDescriptionFormat_t zclGenericApp_SimpleDesc3 =
//{
//  GENERICAPP_ENDPOINT3,                  //  int Endpoint;
//  ZCL_HA_PROFILE_ID,                     //  uint16 AppProfId;
//  // GENERICAPP_TODO: Replace ZCL_HA_DEVICEID_ON_OFF_LIGHT with application specific device ID
//  ZCL_HA_DEVICEID_ON_OFF_SWITCH,  //  uint16 AppDeviceId; 
//  GENERICAPP_DEVICE_VERSION,            //  int   AppDevVer:4;
//  GENERICAPP_FLAGS,                     //  int   AppFlags:4;
//  ZCLGENERICAPP_MAX_INCLUSTERS,         //  byte  AppNumInClusters;
//  (cId_t *)zclGenericApp_InClusterList, //  byte *pAppInClusterList;
//  ZCLGENERICAPP_MAX_OUTCLUSTERS2,        //  byte  AppNumInClusters;
//  (cId_t *)zclGenericApp_OutClusterList2 //  byte *pAppInClusterList;
//};


// Added to include ZLL Target functionality
#if defined ( BDB_TL_INITIATOR ) || defined ( BDB_TL_TARGET )
bdbTLDeviceInfo_t tlGenericApp_DeviceInfo =
{
  GENERICAPP_ENDPOINT,                  //uint8 endpoint;
  ZCL_HA_PROFILE_ID,                    //uint16 profileID;
  // GENERICAPP_TODO: Replace ZCL_HA_DEVICEID_ON_OFF_LIGHT with application specific device ID
  ZCL_HA_DEVICEID_ON_OFF_SWITCH,  //uint16 deviceID;
  GENERICAPP_DEVICE_VERSION,            //uint8 version;
  GENERICAPP_NUM_GRPS                   //uint8 grpIdCnt;
};
#endif

/*********************************************************************
 * GLOBAL FUNCTIONS
 */

/*********************************************************************
 * LOCAL FUNCTIONS
 */
  
void zclGenericApp_ResetAttributesToDefaultValues(void)
{
//  int i;
//  
//  zclGenericApp_LocationDescription[0] = 16;
//  for (i = 1; i <= 16; i++)
//  {
//    zclGenericApp_LocationDescription[i] = ' ';
//  }
//  
//  zclGenericApp_PhysicalEnvironment = PHY_UNSPECIFIED_ENV;
//  zclGenericApp_DeviceEnable = DEVICE_ENABLED;
//  
//#ifdef ZCL_IDENTIFY
//  zclGenericApp_IdentifyTime = 0;
//#endif
//  
//  /* GENERICAPP_TODO: initialize cluster attribute variables. */
}

/****************************************************************************
****************************************************************************/


