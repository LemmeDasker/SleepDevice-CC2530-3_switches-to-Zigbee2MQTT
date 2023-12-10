//#include <stdio.h>
#include <stdlib.h>

#include "zcl.h"
#include "zcl_genericapp.h"
#include "bdb_interface.h"
#include "hal_adc.h"

#include "battery_reporting.h"

afAddrType_t zclGenericApp_Batt_DstAddr;

void zclGenericApp_ReportBatt(uint8 value)
{
  uint8 MeasuredValue = value;
  
  const uint8 NUM_ATTRIBUTES = 1;
  zclReportCmd_t *pReportCmd;
  pReportCmd = osal_mem_alloc(sizeof(zclReportCmd_t) + (NUM_ATTRIBUTES * sizeof(zclReport_t)));
  if (pReportCmd != NULL) {
    pReportCmd->numAttr = NUM_ATTRIBUTES;

    pReportCmd->attrList[0].attrID = ATTRID_POWER_CFG_BATTERY_PERCENTAGE_REMAINING;
    pReportCmd->attrList[0].dataType = ZCL_DATATYPE_UINT8;
    pReportCmd->attrList[0].attrData = (void *)(&MeasuredValue);

    zclGenericApp_Batt_DstAddr.addrMode = (afAddrMode_t)Addr16Bit;
    zclGenericApp_Batt_DstAddr.addr.shortAddr = 0x0000;
    zclGenericApp_Batt_DstAddr.endPoint = GENERICAPP_ENDPOINT;

    zcl_SendReportCmd(GENERICAPP_ENDPOINT, &zclGenericApp_Batt_DstAddr,
                      ZCL_CLUSTER_ID_GEN_POWER_CFG, pReportCmd,
                      ZCL_FRAME_CLIENT_SERVER_DIR, TRUE, bdb_getZCLFrameCounter());
  }

  osal_mem_free(pReportCmd);
}


void zclGenericApp_ReadADC(void)
{
uint16 ADC_value = 0;
uint16 accumulator = 0;
uint16 value = 0;
float voltage = 0.0;
uint8 percent = 0;


uint16 min = 270;       // minimum voltage = 0%
uint16 max = 300;       // maximum voltage = 100%

int i = 0;
while (i < 10) {
  /* Clear ADC interrupt flag */
  ADCIF = 0;
  /* Do the conversion */
  ADCCON3 = (HAL_ADC_REF_125V | HAL_ADC_RESOLUTION_10 | HAL_ADC_CHN_VDD3);
  /* Wait for the conversion to finish */
  while ( !ADCIF );
  /* Get the result */
  value = ADCL;
  value |= ((uint16) ADCH) << 8;
  /* Adjust for 10 bit resolution */
  value >>= 6;
  accumulator = accumulator + value;
  i++;
}

ADC_value = accumulator / 10;            // find average of 10 samples
//printf("ADC_value = %d\n", ADC_value);

voltage = (1.15*ADC_value)/511*3;        // convert to voltage - etc.3.0587
//printf("Volt = %f\n", voltage);

voltage = voltage + 0.15;                // compensate for ADC measurement vs.actual battery value
//printf("Volt = %f\n", voltage);  

value = (int)(voltage * 100);            // convert to simpel voltage - etc.318
//printf("Voltage in INT = %d\n", value);    

if (value >= max) {value = max;}         // keep value within max range
if (value <= min) {value = min;}         // keep value within min range
//printf("Voltage in min-max range = %d\n", value);

percent = (uint8)(((value - min) * 100) / (max - min)); // Beregning af procentdel
percent = percent - (percent % 5);                      // Afrunding til nærmeste 5%
//printf("Percent = %d\n", percent);

percent = percent * 2; // adjust to Zigbee2MQTT percent reader
//printf("Percent = %d\n", percent); 

zclGenericApp_ReportBatt(percent);
}