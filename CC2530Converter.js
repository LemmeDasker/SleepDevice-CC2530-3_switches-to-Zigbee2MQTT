const fz = require('zigbee-herdsman-converters/converters/fromZigbee');
const tz = require('zigbee-herdsman-converters/converters/toZigbee');
const exposes = require('zigbee-herdsman-converters/lib/exposes');
const reporting = require('zigbee-herdsman-converters/lib/reporting');
const extend = require('zigbee-herdsman-converters/lib/extend');
const e = exposes.presets;
const ea = exposes.access;

const definition = {
    zigbeeModel: ['Home-switch'], // The model ID from: Device with modelID 'lumi.sens' is not supported.
    model: 'SLEEP-SW3', // Vendor model number, look on the device for a model number
    vendor: 'SLEEP-SW3', // Vendor of the device (only used for documentation and startup logging)
    description: 'Smart-Hjemmet', // Description of the device, copy from vendor site. (only used for documentation and startup logging)
    fromZigbee: [fz.command_on_state, fz.command_off_state, fz.battery], // We will add this later fz.battery
    toZigbee: [], // Should be empty, unless device can be controlled (e.g. lights, switches).
    exposes: [e.switch().withEndpoint('1'), e.switch().withEndpoint('2'), e.switch().withEndpoint('3')], // Defines what this device exposes, used for e.g. Home Assistant discovery and in the frontend
    meta: {multiEndpoint: true},
    endpoint: (device) => {
        return {'1': 1, '2': 2, '3': 3};	
	},
};

module.exports = definition;
