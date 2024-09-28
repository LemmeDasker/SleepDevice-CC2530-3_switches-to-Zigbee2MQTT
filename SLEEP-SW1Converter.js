const {} = require('zigbee-herdsman-converters/lib/modernExtend');
const fz = require('zigbee-herdsman-converters/converters/fromZigbee');
const tz = require('zigbee-herdsman-converters/converters/toZigbee');
const exposes = require('zigbee-herdsman-converters/lib/exposes');
const reporting = require('zigbee-herdsman-converters/lib/reporting');
const ota = require('zigbee-herdsman-converters/lib/ota');
const utils = require('zigbee-herdsman-converters/lib/utils');
const globalStore = require('zigbee-herdsman-converters/lib/store');
const e = exposes.presets;
const ea = exposes.access;

const definition = {
    zigbeeModel: ['Home-switch'], // The model ID from: Device with modelID 'lumi.sens' is not supported.
    model: 'Home-switch', // Vendor model number, look on the device for a model number
    vendor: 'SLEEP-SW1', // Vendor of the device (only used for documentation and startup logging)
    description: 'FlemmingsZigbees', // Description of the device, copy from vendor site. (only used for documentation and startup logging)
    fromZigbee: [fz.command_on_state, fz.command_off_state, fz.battery ], // We will add this later
    toZigbee: [], // Should be empty, unless device can be controlled (e.g. lights, switches).
    exposes: [e.switch()], // Defines what this device exposes, used for e.g. Home Assistant discovery and in the frontend
};

module.exports = definition;
