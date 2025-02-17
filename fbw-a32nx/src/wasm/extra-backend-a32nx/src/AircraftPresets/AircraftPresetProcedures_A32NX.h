// Copyright (c) 2023 FlyByWire Simulations
// SPDX-License-Identifier: GPL-3.0

#ifndef FLYBYWIRE_AIRCRAFT_AIRCRAFTPRESETPROCEDURES_A32NX_H
#define FLYBYWIRE_AIRCRAFT_AIRCRAFTPRESETPROCEDURES_A32NX_H

#include "AircraftPresets/PresetProceduresDefinition.h"
#include "AircraftPresets/ProcedureStep.h"

/**
 * A32NX specific aircraft procedures definition.
 *
 * @see AircraftProceduresDefinition
 */
class AircraftPresetProcedures_A32NX {
 public:
  const inline static PresetProceduresDefinition aircraftProcedureDefinition{
      // clang-format off
      // @formatter:off

      .POWERED_CONFIG_ON {
        // SOP: PRELIMINARY COCKPIT PREPARATION
        ProcedureStep{"BAT1 On",                  1010, false, 1000, "(L:A32NX_OVHD_ELEC_BAT_1_PB_IS_AUTO)",                 "1 (>L:A32NX_OVHD_ELEC_BAT_1_PB_IS_AUTO)"},
        ProcedureStep{"BAT2 On",                  1020, false, 3000, "(L:A32NX_OVHD_ELEC_BAT_2_PB_IS_AUTO)",                 "1 (>L:A32NX_OVHD_ELEC_BAT_2_PB_IS_AUTO)"},

        ProcedureStep{"EXT PWR On",               1030, false, 3000, "(L:A32NX_OVHD_APU_MASTER_SW_PB_IS_ON) "
                                                                     "(L:A32NX_OVHD_APU_MASTER_SW_PB_IS_ON) && "
                                                                     "(L:A32NX_ENGINE_STATE:1) 1 == || "
                                                                     "(L:A32NX_ENGINE_STATE:2) 1 == || "
                                                                     "(A:EXTERNAL POWER ON:1, BOOL) ||",                     "(A:EXTERNAL POWER ON:1, BOOL) ! if{ 1 (>K:TOGGLE_EXTERNAL_POWER) }"},

        // if no Ext Pwr is available we start the APU here with a bat only fire test
        ProcedureStep{"APU Fire Test On",         1035, false, 2000, "(L:A32NX_ELEC_AC_1_BUS_IS_POWERED)",                   "1 (>L:A32NX_FIRE_TEST_APU)"},
        ProcedureStep{"APU Fire Test Off",        1036, false, 2000, "(L:A32NX_ELEC_AC_1_BUS_IS_POWERED)",                   "0 (>L:A32NX_FIRE_TEST_APU)"},
        ProcedureStep{"APU Master On",            1040, false, 3000, "(L:A32NX_ELEC_AC_1_BUS_IS_POWERED)",                   "1 (>L:A32NX_OVHD_APU_MASTER_SW_PB_IS_ON)"},
        ProcedureStep{"APU Start On",             1050, false, 1000, "(L:A32NX_OVHD_APU_MASTER_SW_PB_IS_ON) ! "
                                                                     "(L:A32NX_OVHD_APU_START_PB_IS_AVAILABLE) ||",          "1 (>L:A32NX_OVHD_APU_START_PB_IS_ON)"},

        ProcedureStep{"Waiting on AC BUS Availability", 1060, true,  2000, "",                                               "(L:A32NX_ELEC_AC_1_BUS_IS_POWERED)"},

        // SOP: COCKPIT PREPARATION
        ProcedureStep{"Crew Oxy On",              1120, false, 1000, "(L:PUSH_OVHD_OXYGEN_CREW) 0 ==",                       "0 (>L:PUSH_OVHD_OXYGEN_CREW)"},
        ProcedureStep{"GND CTL On",               1110, false, 1000, "(L:A32NX_ENGINE_STATE:1) 1 == "
                                                                     "(L:A32NX_ENGINE_STATE:2) 1 == || "
                                                                     "(L:A32NX_RCDR_GROUND_CONTROL_ON) 1 == ||",             "1 (>L:A32NX_RCDR_GROUND_CONTROL_ON)"},
        ProcedureStep{"CVR Test On",              1115, false, 5000, "(L:A32NX_AIRCRAFT_PRESET_CVR_TEST_DONE)",              "1 (>L:A32NX_RCDR_TEST)"},
        ProcedureStep{"CVR Test Off",             1116, false, 2000, "(L:A32NX_AIRCRAFT_PRESET_CVR_TEST_DONE)",              "0 (>L:A32NX_RCDR_TEST) 1 (>L:A32NX_AIRCRAFT_PRESET_CVR_TEST_DONE)"},

        ProcedureStep{"ADIRS 1 Nav",              1080, false, 500,  "(L:A32NX_OVHD_ADIRS_IR_1_MODE_SELECTOR_KNOB) 1 ==",    "1 (>L:A32NX_OVHD_ADIRS_IR_1_MODE_SELECTOR_KNOB)"},
        ProcedureStep{"ADIRS 2 Nav",              1090, false, 500,  "(L:A32NX_OVHD_ADIRS_IR_2_MODE_SELECTOR_KNOB) 1 ==",    "1 (>L:A32NX_OVHD_ADIRS_IR_2_MODE_SELECTOR_KNOB)"},
        ProcedureStep{"ADIRS 3 Nav",              1100, false, 1500, "(L:A32NX_OVHD_ADIRS_IR_3_MODE_SELECTOR_KNOB) 1 ==",    "1 (>L:A32NX_OVHD_ADIRS_IR_3_MODE_SELECTOR_KNOB)"},

        ProcedureStep{"Strobe Auto",              2122, false, 50,   "(L:LIGHTING_STROBE_0) 1 ==",                           "0 (>L:STROBE_0_AUTO) 0 (>K:STROBES_OFF)"},
        ProcedureStep{"Strobe Auto",              2122, false, 1000, "(L:LIGHTING_STROBE_0) 1 ==",                           "1 (>L:STROBE_0_AUTO) 0 (>K:STROBES_ON)"},
        ProcedureStep{"Nav & Logo Lt On",         1070, false, 1000, "(A:LIGHT LOGO, Bool) (A:LIGHT NAV, Bool) &&",          "1 (>K:2:LOGO_LIGHTS_SET) 1 (>K:2:NAV_LIGHTS_SET)"},

        ProcedureStep{"SEAT BELTS On",            2140, false, 1000, "(A:CABIN SEATBELTS ALERT SWITCH:1, BOOL)",             "(A:CABIN SEATBELTS ALERT SWITCH:1, BOOL) ! if{ 1 (>K:CABIN_SEATBELTS_ALERT_SWITCH_TOGGLE) }"},
        ProcedureStep{"NO SMOKING Auto",          1130, false, 1000, "(L:XMLVAR_SWITCH_OVHD_INTLT_NOSMOKING_POSITION) 1 ==", "1 (>L:XMLVAR_SWITCH_OVHD_INTLT_NOSMOKING_POSITION)"},
        ProcedureStep{"EMER EXT Lt Arm",          1140, false, 1000, "(L:XMLVAR_SWITCH_OVHD_INTLT_EMEREXIT_POSITION) 1 ==",  "1 (>L:XMLVAR_SWITCH_OVHD_INTLT_EMEREXIT_POSITION)"},

        // For the fire tests the FWC needs to be initialized
        // The correct variables to wait for are: A32NX_FWS_FWC_1_NORMAL and A32NX_FWS_FWC_2_NORMAL. But
        // as these are only on Exp this first iteration uses A32NX_FWC_FLIGHT_PHASE which also work on>
        // master and is equivalent for this specific purpose. Will be changed when the FWC is on master.
        ProcedureStep{"Waiting on FWC Initialization", 1065, true,  5000, "",                                           "(L:A32NX_FWC_FLIGHT_PHASE)"},
        ProcedureStep{"Waiting...",                    9999, false, 5000, "(L:A32NX_AIRCRAFT_PRESET_FWC_INIT_DONE)",    "1 (>L:A32NX_AIRCRAFT_PRESET_FWC_INIT_DONE)"},

        // APU fire test
        ProcedureStep{"APU Fire Test On",         1035, false, 2000, "(L:A32NX_AIRCRAFT_PRESET_FIRE_TEST_APU_DONE)",    "1 (>L:A32NX_FIRE_TEST_APU)"},
        ProcedureStep{"APU Fire Test Off",        1036, false, 2000, "(L:A32NX_AIRCRAFT_PRESET_FIRE_TEST_APU_DONE)",    "0 (>L:A32NX_FIRE_TEST_APU) 1 (>L:A32NX_AIRCRAFT_PRESET_FIRE_TEST_APU_DONE)"},

        // After fire test we start the APU
        ProcedureStep{"APU Master On",            1041, false, 3000, "(L:A32NX_ENGINE_STATE:1) 1 == "
                                                                     "(L:A32NX_ENGINE_STATE:2) 1 == && "
                                                                      "(L:A32NX_OVHD_APU_MASTER_SW_PB_IS_ON) 1 == ||",  "1 (>L:A32NX_OVHD_APU_MASTER_SW_PB_IS_ON)"},
        ProcedureStep{"APU Start On",             1051, false, 1000, "(L:A32NX_OVHD_APU_MASTER_SW_PB_IS_ON) ! "
                                                                     "(L:A32NX_OVHD_APU_START_PB_IS_AVAILABLE) ||",     "1 (>L:A32NX_OVHD_APU_START_PB_IS_ON)"},

        // ENG fire test
        ProcedureStep{"ENG 1 Fire Test On",       2002, false, 2000, "(L:A32NX_AIRCRAFT_PRESET_FIRE_TEST_ENG1_DONE)",   "1 (>L:A32NX_FIRE_TEST_ENG1)"},
        ProcedureStep{"ENG 1 Fire Test Off",      2003, false, 2000, "(L:A32NX_AIRCRAFT_PRESET_FIRE_TEST_ENG1_DONE)",   "0 (>L:A32NX_FIRE_TEST_ENG1) 1 (>L:A32NX_AIRCRAFT_PRESET_FIRE_TEST_ENG1_DONE)"},
        ProcedureStep{"ENG 2 Fire Test On",       2004, false, 2000, "(L:A32NX_AIRCRAFT_PRESET_FIRE_TEST_ENG2_DONE)",   "1 (>L:A32NX_FIRE_TEST_ENG2)"},
        ProcedureStep{"ENG 2 Fire Test Off",      2005, false, 2000, "(L:A32NX_AIRCRAFT_PRESET_FIRE_TEST_ENG2_DONE)",   "0 (>L:A32NX_FIRE_TEST_ENG2) 1 (>L:A32NX_AIRCRAFT_PRESET_FIRE_TEST_ENG2_DONE)"},

        ProcedureStep{"Waiting on APU Availability", 1150, true,  2000, "",                                             "(L:A32NX_OVHD_APU_MASTER_SW_PB_IS_ON) ! (L:A32NX_OVHD_APU_START_PB_IS_AVAILABLE) ||"},
        ProcedureStep{"APU Bleed On",                1160, false, 1000, "(L:A32NX_OVHD_APU_MASTER_SW_PB_IS_ON) ! "
                                                                        "(L:A32NX_OVHD_PNEU_APU_BLEED_PB_IS_ON) ||",    "1 (>L:A32NX_OVHD_PNEU_APU_BLEED_PB_IS_ON)"}
      },

      .POWERED_CONFIG_OFF = {
        ProcedureStep{"NO SMOKING Off",        1170, false, 1000, "(L:XMLVAR_SWITCH_OVHD_INTLT_NOSMOKING_POSITION) 2 ==", "2 (>L:XMLVAR_SWITCH_OVHD_INTLT_NOSMOKING_POSITION)"},
        ProcedureStep{"EMER EXT Lt Off",       1180, false, 1500, "(L:XMLVAR_SWITCH_OVHD_INTLT_EMEREXIT_POSITION) 2 ==",  "2 (>L:XMLVAR_SWITCH_OVHD_INTLT_EMEREXIT_POSITION)"},
        ProcedureStep{"GND CTL Off",           1200, false, 1000, "(L:A32NX_RCDR_GROUND_CONTROL_ON) 0 ==",                "0 (>L:A32NX_RCDR_GROUND_CONTROL_ON)"},
        ProcedureStep{"SEAT BELTS Off",        2200, false, 2000, "(A:CABIN SEATBELTS ALERT SWITCH:1, BOOL) !",           "(A:CABIN SEATBELTS ALERT SWITCH:1, BOOL) if{ 1 (>K:CABIN_SEATBELTS_ALERT_SWITCH_TOGGLE) }"},
        ProcedureStep{"Strobe Off",            2121, false, 1000, "(L:LIGHTING_STROBE_0) 2 ==",                           "0 (>L:STROBE_0_AUTO) 0 (>K:STROBES_OFF)"},
        ProcedureStep{"Nav & Logo Lt Off",     1240, false, 500,  "(A:LIGHT LOGO, Bool) ! (A:LIGHT NAV, Bool) ! &&",      "0 (>K:2:LOGO_LIGHTS_SET) 0 (>K:2:NAV_LIGHTS_SET)"},
        ProcedureStep{"Crew Oxy Off",          1190, false, 1000, "(L:PUSH_OVHD_OXYGEN_CREW) 1 ==",                       "1 (>L:PUSH_OVHD_OXYGEN_CREW)"},
        ProcedureStep{"ADIRS 3 Off",           1210, false, 500,  "(L:A32NX_OVHD_ADIRS_IR_3_MODE_SELECTOR_KNOB) 0 ==",    "0 (>L:A32NX_OVHD_ADIRS_IR_3_MODE_SELECTOR_KNOB)"},
        ProcedureStep{"ADIRS 2 Off",           1220, false, 500,  "(L:A32NX_OVHD_ADIRS_IR_2_MODE_SELECTOR_KNOB) 0 ==",    "0 (>L:A32NX_OVHD_ADIRS_IR_2_MODE_SELECTOR_KNOB)"},
        ProcedureStep{"ADIRS 1 Off",           1230, false, 1000, "(L:A32NX_OVHD_ADIRS_IR_1_MODE_SELECTOR_KNOB) 0 ==",    "0 (>L:A32NX_OVHD_ADIRS_IR_1_MODE_SELECTOR_KNOB)"},
        ProcedureStep{"APU Bleed Off",         1250, false, 1500, "(L:A32NX_OVHD_PNEU_APU_BLEED_PB_IS_ON) 0 ==",          "0 (>L:A32NX_OVHD_PNEU_APU_BLEED_PB_IS_ON)"},
        ProcedureStep{"APU Master Off",        1260, false, 2000, "(L:A32NX_OVHD_APU_MASTER_SW_PB_IS_ON) 0 ==",           "0 (>L:A32NX_OVHD_APU_MASTER_SW_PB_IS_ON)"},
        ProcedureStep{"EXT PWR Off",           1270, false, 3000, "(A:EXTERNAL POWER ON:1, BOOL) !",                      "(A:EXTERNAL POWER ON:1, BOOL) if{ 1 (>K:TOGGLE_EXTERNAL_POWER) }"},
        ProcedureStep{"BAT2 Off",              1280, false, 100,  "(L:A32NX_OVHD_ELEC_BAT_2_PB_IS_AUTO) 0 ==",            "0 (>L:A32NX_OVHD_ELEC_BAT_2_PB_IS_AUTO)"},
        ProcedureStep{"BAT1 Off",              1290, false, 1000, "(L:A32NX_OVHD_ELEC_BAT_1_PB_IS_AUTO) 0 ==",            "0 (>L:A32NX_OVHD_ELEC_BAT_1_PB_IS_AUTO)"},
        ProcedureStep{"AC BUS Off Check",      1300, true,  2000, "",                                                     "(L:A32NX_ELEC_AC_1_BUS_IS_POWERED) !"},
        ProcedureStep{"CVR Test Reset",        1117, false, 0,    "",                                                     "0 (>L:A32NX_AIRCRAFT_PRESET_CVR_TEST_DONE)"},
        ProcedureStep{"APU Fire Test Reset",   1037, false, 0,    "",                                                     "0 (>L:A32NX_AIRCRAFT_PRESET_FIRE_TEST_APU_DONE)"},
        ProcedureStep{"ENG 1 Fire Test Reset", 2006, false, 0,    "",                                                     "0 (>L:A32NX_AIRCRAFT_PRESET_FIRE_TEST_ENG1_DONE)"},
        ProcedureStep{"ENG 2 Fire Test Reset", 2007, false, 0,    "",                                                     "0 (>L:A32NX_AIRCRAFT_PRESET_FIRE_TEST_ENG2_DONE)"},
        ProcedureStep{"FWC Init Reset",        1066, false, 0,    "",                                                     "0 (>L:A32NX_AIRCRAFT_PRESET_FWC_INIT_DONE)"}
      },

      .PUSHBACK_CONFIG_ON = {
        // SOP: BEFORE PUSHBACK OR START
        ProcedureStep{"EXT PWR Off",             2000, false, 3000, "(A:EXTERNAL POWER ON:1, BOOL) !",               "(A:EXTERNAL POWER ON:1, BOOL) if{ 1 (>K:TOGGLE_EXTERNAL_POWER) }"},
        ProcedureStep{"Beacon On",               2130, false, 2000, "(A:LIGHT BEACON, Bool)",                        "0 (>K:BEACON_LIGHTS_ON)"},
        ProcedureStep{"FUEL PUMP 2 On",          2010, false, 100,  "(A:FUELSYSTEM PUMP SWITCH:2, Bool)",            "2 (>K:FUELSYSTEM_PUMP_ON)"},
        ProcedureStep{"FUEL PUMP 5 On",          2020, false, 500,  "(A:FUELSYSTEM PUMP SWITCH:5, Bool)",            "5 (>K:FUELSYSTEM_PUMP_ON)"},
        ProcedureStep{"FUEL VALVE 9 On",         2030, false, 100,  "(A:FUELSYSTEM VALVE SWITCH:9, Bool)",           "9 (>K:FUELSYSTEM_VALVE_OPEN)"},
        ProcedureStep{"FUEL VALVE 10 On",        2040, false, 500,  "(A:FUELSYSTEM VALVE SWITCH:10, Bool)",          "10 (>K:FUELSYSTEM_VALVE_OPEN)"},
        ProcedureStep{"FUEL PUMP 3 On",          2050, false, 100,  "(A:FUELSYSTEM PUMP SWITCH:3, Bool)",            "3 (>K:FUELSYSTEM_PUMP_ON)"},
        ProcedureStep{"FUEL PUMP 6 On",          2060, false, 2000, "(A:FUELSYSTEM PUMP SWITCH:6, Bool)",            "6 (>K:FUELSYSTEM_PUMP_ON)"},
        // next step will keep a slgitht delay as the A32NX otherwise often did not start up the ENG2 in step 3010
        ProcedureStep{"Cockpit Door Locked",     2110, false, 2000, "(L:A32NX_COCKPIT_DOOR_LOCKED) 1 ==",            "1 (>L:A32NX_COCKPIT_DOOR_LOCKED)", true},
        ProcedureStep{"Await ADIRS 1 Alignment", 2150, true,  2000, "",                                              "(L:A32NX_ADIRS_ADIRU_1_STATE) 2 =="},
        ProcedureStep{"Await ADIRS 2 Alignment", 2160, true,  2000, "",                                              "(L:A32NX_ADIRS_ADIRU_2_STATE) 2 =="},
        ProcedureStep{"Await ADIRS 3 Alignment", 2170, true,  2000, "",                                              "(L:A32NX_ADIRS_ADIRU_3_STATE) 2 =="},
      },

      .PUSHBACK_CONFIG_OFF = {
        ProcedureStep{"Cockpit Door open",    2250, false, 2000, "(L:A32NX_COCKPIT_DOOR_LOCKED) 0 ==",                "0 (>L:A32NX_COCKPIT_DOOR_LOCKED)"},
        ProcedureStep{"Fuel Pump 2 Off",      2260, false,  100, "(A:FUELSYSTEM PUMP SWITCH:2, Bool) !",              "2 (>K:FUELSYSTEM_PUMP_OFF)"},
        ProcedureStep{"Fuel Pump 5 Off",      2270, false,  500, "(A:FUELSYSTEM PUMP SWITCH:5, Bool) !",              "5 (>K:FUELSYSTEM_PUMP_OFF)"},
        ProcedureStep{"Fuel Valve 9 Off",     2280, false,  100, "(A:FUELSYSTEM VALVE SWITCH:9, Bool) !",             "9 (>K:FUELSYSTEM_VALVE_CLOSE)"},
        ProcedureStep{"Fuel Valve 10 Off",    2290, false,  500, "(A:FUELSYSTEM VALVE SWITCH:10, Bool) !",            "10 (>K:FUELSYSTEM_VALVE_CLOSE)"},
        ProcedureStep{"Fuel Pump 3 Off",      2300, false,  100, "(A:FUELSYSTEM PUMP SWITCH:3, Bool) !",              "3 (>K:FUELSYSTEM_PUMP_OFF)"},
        ProcedureStep{"Fuel Pump 6 Off",      2310, false, 1000, "(A:FUELSYSTEM PUMP SWITCH:6, Bool) !",              "6 (>K:FUELSYSTEM_PUMP_OFF)"},
        ProcedureStep{"Beacon Off",           2190, false, 1000, "(A:LIGHT BEACON, Bool) !",                          "0 (>K:BEACON_LIGHTS_OFF)"},
      },

      .TAXI_CONFIG_ON = {
        // SOP: ENGINE START
        ProcedureStep{"ENG MODE SEL START",   3000, false, 3000,  "(L:A32NX_ENGINE_STATE:1) 1 == "
                                                                  "(L:A32NX_ENGINE_STATE:2) 1 == && ",                "2 (>K:TURBINE_IGNITION_SWITCH_SET2) "
                                                                                                                      "2 (>K:TURBINE_IGNITION_SWITCH_SET1)"},
        ProcedureStep{"ENG 2 On",             3010, false, 60000, "(A:FUELSYSTEM VALVE OPEN:2, Bool)",                "2 (>K:FUELSYSTEM_VALVE_OPEN)"},
        ProcedureStep{"Await ENG 2 Avail",    3020, true,  5000,  "",                                                 "(L:A32NX_ENGINE_STATE:2) 1 =="},
        ProcedureStep{"ENG 1 On",             3030, false, 60000, "(A:FUELSYSTEM VALVE OPEN:1, Bool)",                "1 (>K:FUELSYSTEM_VALVE_OPEN)"},
        ProcedureStep{"Await ENG 1 Avail",    3040, true,  5000,  "",                                                 "(L:A32NX_ENGINE_STATE:1) 1 =="},
        // SOP: AFTER START
        ProcedureStep{"ENG MODE SEL Norm",    3050, false, 3000,  "",                                                 "1 (>K:TURBINE_IGNITION_SWITCH_SET1) "
                                                                                                                      "1 (>K:TURBINE_IGNITION_SWITCH_SET2) "},
        ProcedureStep{"APU Bleed Off",        3060, false, 2000,  "(L:A32NX_OVHD_PNEU_APU_BLEED_PB_IS_ON) 0 ==",      "0 (>L:A32NX_OVHD_PNEU_APU_BLEED_PB_IS_ON)"},
        ProcedureStep{"APU Master Off",       3070, false, 2000,  "(L:A32NX_OVHD_APU_MASTER_SW_PB_IS_ON) 0 ==",       "0 (>L:A32NX_OVHD_APU_MASTER_SW_PB_IS_ON)"},
        ProcedureStep{"Spoiler Arm",          3090, false, 2000,  "(L:A32NX_SPOILERS_ARMED) 1 ==",                    "1 (>K:SPOILERS_ARM_SET)"},
        ProcedureStep{"Rudder Trim Reset",    3100, false, 2000,  "(A:RUDDER TRIM, Radians) 0 ==",                    "0 (>K:RUDDER_TRIM_SET)"},
        ProcedureStep{"Flaps 1",              3110, false, 3000,  "(L:A32NX_FLAPS_HANDLE_INDEX) 1 ==",                "1 (>L:A32NX_FLAPS_HANDLE_INDEX)"},
        // SOP: TAXI
        ProcedureStep{"NOSE Lt Taxi",         3120, false, 1000,  "(A:CIRCUIT SWITCH ON:20, Bool)",                   "0 (>L:LIGHTING_LANDING_1) (A:CIRCUIT SWITCH ON:20, Bool) ! if{ 20 (>K:ELECTRICAL_CIRCUIT_TOGGLE)"},
        ProcedureStep{"RWY TURN OFF Lt L On", 3130, false, 0,     "(A:CIRCUIT SWITCH ON:21, Bool)",                   "(A:CIRCUIT SWITCH ON:21, Bool) ! if{ 21 (>K:ELECTRICAL_CIRCUIT_TOGGLE)"},
        ProcedureStep{"RWY TURN OFF Lt R On", 3140, false, 2000,  "(A:CIRCUIT SWITCH ON:22, Bool)",                   "(A:CIRCUIT SWITCH ON:22, Bool) ! if{ 22 (>K:ELECTRICAL_CIRCUIT_TOGGLE)"},
        ProcedureStep{"PWS Auto",             2070, false, 1000,  "(L:A32NX_SWITCH_RADAR_PWS_POSITION) 1 ==",         "1 (>L:A32NX_SWITCH_RADAR_PWS_POSITION)"},
        ProcedureStep{"Transponder On",       2080, false, 1000,  "(L:A32NX_TRANSPONDER_MODE) 1 ==",                  "1 (>L:A32NX_TRANSPONDER_MODE)"},
        ProcedureStep{"ATC ALT RPTG On",      2090, false, 1000,  "(L:A32NX_SWITCH_ATC_ALT) 1 ==",                    "1 (>L:A32NX_SWITCH_ATC_ALT)"},
        ProcedureStep{"TCAS TRAFFIC Abv",     2100, false, 2000,  "(L:A32NX_SWITCH_TCAS_TRAFFIC_POSITION) 2 ==",      "2 (>L:A32NX_SWITCH_TCAS_TRAFFIC_POSITION)"},
        ProcedureStep{"Autobrake Max",        3080, false, 2000,  "(L:A32NX_AUTOBRAKES_ARMED_MODE) 3 ==",             "3 (>L:A32NX_AUTOBRAKES_ARMED_MODE_SET)"},
        ProcedureStep{"TERR ON ND Capt. On",  3080, false, 2000,  "(L:A32NX_EFIS_TERR_L_ACTIVE) 1 ==",                "1 (>L:A32NX_EFIS_TERR_L_ACTIVE)"},
        ProcedureStep{"T.O Config",           3085, false, 200,   "",                                                 "1 (>L:A32NX_BTN_TOCONFIG)"},
        ProcedureStep{"T.O Config",           3085, false, 2000,  "",                                                 "0 (>L:A32NX_BTN_TOCONFIG)"},
      },

      .TAXI_CONFIG_OFF = {
        ProcedureStep{"TERR ON ND Capt. Off",  3080, false, 2000, "(L:A32NX_EFIS_TERR_L_ACTIVE) 0 ==",           "0 (>L:A32NX_EFIS_TERR_L_ACTIVE)"},
        ProcedureStep{"Autobrake Off",         3180, false, 2000, "(L:A32NX_AUTOBRAKES_ARMED_MODE) 0 ==",        "0 (>L:A32NX_AUTOBRAKES_ARMED_MODE_SET)"},
        ProcedureStep{"TCAS TRAFFIC Abv",      2240, false, 1000, "(L:A32NX_SWITCH_TCAS_TRAFFIC_POSITION) 2 ==", "2 (>L:A32NX_SWITCH_TCAS_TRAFFIC_POSITION)"},
        ProcedureStep{"ATC ALT RPTG Off",      2230, false, 1000, "(L:A32NX_SWITCH_ATC_ALT) 1 ==",               "1 (>L:A32NX_SWITCH_ATC_ALT)"},
        ProcedureStep{"Transponder Off",       2220, false, 1000, "(L:A32NX_TRANSPONDER_MODE) 0 ==",             "0 (>L:A32NX_TRANSPONDER_MODE)"},
        ProcedureStep{"PWS Off",               2210, false, 1000, "(L:A32NX_SWITCH_RADAR_PWS_POSITION) 0 ==",    "0 (>L:A32NX_SWITCH_RADAR_PWS_POSITION)"},
        ProcedureStep{"RWY TURN OFF Lt L Off", 3160, false, 0,    "(A:CIRCUIT SWITCH ON:21, Bool) !",            "(A:CIRCUIT SWITCH ON:21, Bool) if{ 21 (>K:ELECTRICAL_CIRCUIT_TOGGLE)"},
        ProcedureStep{"RWY TURN OFF Lt R Off", 3170, false, 2000, "(A:CIRCUIT SWITCH ON:22, Bool) !",            "(A:CIRCUIT SWITCH ON:22, Bool) if{ 22 (>K:ELECTRICAL_CIRCUIT_TOGGLE)"},
        ProcedureStep{"NOSE Lt Taxi",          3150, false, 1000, "(A:CIRCUIT SWITCH ON:20, Bool) !",            "2 (>L:LIGHTING_LANDING_1) (A:CIRCUIT SWITCH ON:20, Bool) if{ 20 (>K:ELECTRICAL_CIRCUIT_TOGGLE)"},
        ProcedureStep{"Flaps 0",               3210, false, 2000, "(L:A32NX_FLAPS_HANDLE_INDEX) 0 ==",           "0 (>L:A32NX_FLAPS_HANDLE_INDEX)"},
        ProcedureStep{"Rudder Trim Reset",     3200, false, 2000, "(A:RUDDER TRIM, Radians) 0 ==",               "0 (>K:RUDDER_TRIM_SET)"},
        ProcedureStep{"Spoiler Disarm",        3190, false, 2000, "(L:A32NX_SPOILERS_ARMED) 0 ==",               "0 (>K:SPOILERS_ARM_SET)"},
        ProcedureStep{"ENG 1 Off",             3220, false, 2000, "(A:FUELSYSTEM VALVE OPEN:1, Bool) !",         "1 (>K:FUELSYSTEM_VALVE_CLOSE)"},
        ProcedureStep{"ENG 2 Off",             3230, false, 2000, "(A:FUELSYSTEM VALVE OPEN:2, Bool) !",         "2 (>K:FUELSYSTEM_VALVE_CLOSE)"},
        ProcedureStep{"ENG 1 N1 <3%",          3240, true,  1000, "",                                            "(L:A32NX_ENGINE_N1:1) 3 <"},
        ProcedureStep{"ENG 2 N1 <3%",          3250, true,  1000, "",                                            "(L:A32NX_ENGINE_N1:2) 3 <"}
      },

      .TAKEOFF_CONFIG_ON = {
        // SOP: TAXI
        ProcedureStep{"WX Radar On",       4000, false, 1000, "(L:XMLVAR_A320_WEATHERRADAR_SYS) 0 ==",  "0 (>L:XMLVAR_A320_WEATHERRADAR_SYS)"},
        ProcedureStep{"WX Radar Mode",     4010, false, 1000, "(L:XMLVAR_A320_WEATHERRADAR_MODE) 1 ==", "1 (>L:XMLVAR_A320_WEATHERRADAR_MODE)"},
        // SOP: BEFORE TAKEOFF
        ProcedureStep{"TCAS Switch TA/RA", 4020, false, 2000, "(L:A32NX_SWITCH_TCAS_POSITION) 2 ==",    "2 (>L:A32NX_SWITCH_TCAS_POSITION)"},
        // unfortunately strobe 3-way switch control is weird, so we have to use a workaround and turn it off first
        ProcedureStep{"Strobe On"  ,       2120, false, 50,   "(L:LIGHTING_STROBE_0) 0 ==",             "0 (>L:STROBE_0_AUTO) 0 (>K:STROBES_OFF)"},
        ProcedureStep{"Strobe On",         2120, false, 1000, "(L:LIGHTING_STROBE_0) 0 ==",             "0 (>L:STROBE_0_AUTO) 0 (>K:STROBES_ON)"},
        ProcedureStep{"Cabin Ready",       2125, false, 1000, "",                                       "1 (>L:A32NX_CABIN_READY)"},
        // SOP: TAKE OFF
        ProcedureStep{"NOSE Lt Takeoff",   4030, false, 1000, "(A:CIRCUIT SWITCH ON:17, Bool)",         "(A:CIRCUIT SWITCH ON:17, Bool) ! if{ 17 (>K:ELECTRICAL_CIRCUIT_TOGGLE)"},
        ProcedureStep{"LL Lt L On",        4040, false, 0,    "(A:CIRCUIT SWITCH ON:18, Bool)",         "0 (>L:LIGHTING_LANDING_2) 0 (>L:LANDING_2_RETRACTED) (A:CIRCUIT SWITCH ON:18, Bool) ! if{ 18 (>K:ELECTRICAL_CIRCUIT_TOGGLE)"},
        ProcedureStep{"LL Lt R On",        4050, false, 1000, "(A:CIRCUIT SWITCH ON:19, Bool)",         "0 (>L:LIGHTING_LANDING_3) 0 (>L:LANDING_3_RETRACTED) (A:CIRCUIT SWITCH ON:19, Bool) ! if{ 19 (>K:ELECTRICAL_CIRCUIT_TOGGLE)"},
      },

      .TAKEOFF_CONFIG_OFF = {
        ProcedureStep{"LL Lt L Off",       4060, false, 0,    "(A:CIRCUIT SWITCH ON:18, Bool) ! (L:LANDING_2_RETRACTED) &&",     "2 (>L:LIGHTING_LANDING_2) 1 (>L:LANDING_2_RETRACTED) (A:CIRCUIT SWITCH ON:18, Bool) if{ 18 (>K:ELECTRICAL_CIRCUIT_TOGGLE)"},
        ProcedureStep{"LL Lt R Off",       4070, false, 1000, "(A:CIRCUIT SWITCH ON:19, Bool) ! (L:LANDING_3_RETRACTED) &&",     "2 (>L:LIGHTING_LANDING_3) 1 (>L:LANDING_3_RETRACTED) (A:CIRCUIT SWITCH ON:19, Bool) if{ 19 (>K:ELECTRICAL_CIRCUIT_TOGGLE)"},
        ProcedureStep{"NOSE Lt Takeoff",   4080, false, 2000, "(A:CIRCUIT SWITCH ON:17, Bool) !",                                "(A:CIRCUIT SWITCH ON:17, Bool) if{ 17 (>K:ELECTRICAL_CIRCUIT_TOGGLE)"},
        // unfortunately strobe 3-way switch control is weird, so we have to use a workaround and turn it off first
        ProcedureStep{"Strobe Auto",       2122, false, 50,   "(L:LIGHTING_STROBE_0) 0 == (L:LIGHTING_STROBE_0) 1 == ||",        "0 (>L:STROBE_0_AUTO) 0 (>K:STROBES_OFF)"},
        ProcedureStep{"Strobe Auto",       2122, false, 1000, "(L:A32NX_ENGINE_STATE:1) 0 == (L:A32NX_ENGINE_STATE:2) 0 == && "
                                                              "(L:LIGHTING_STROBE_0) 1 == || ",                                  "1 (>L:STROBE_0_AUTO) 0 (>K:STROBES_ON)"},
        ProcedureStep{"TCAS Switch TA/RA", 4090, false, 1000, "(L:A32NX_SWITCH_TCAS_POSITION) 0 ==",                             "0 (>L:A32NX_SWITCH_TCAS_POSITION)"},
        ProcedureStep{"WX Radar Mode",     4110, false, 1000, "(L:XMLVAR_A320_WEATHERRADAR_MODE) 1 ==",                          "1 (>L:XMLVAR_A320_WEATHERRADAR_MODE)"},
        ProcedureStep{"WX Radar Off",      4100, false, 1000, "(L:XMLVAR_A320_WEATHERRADAR_SYS) 1 ==",                           "1 (>L:XMLVAR_A320_WEATHERRADAR_SYS)"},
      }

      // @formatter:on
      // clang-format on
  };
};

#endif  // FLYBYWIRE_AIRCRAFT_AIRCRAFTPRESETPROCEDURES_A32NX_H
