// Copyright (c) 2021-2022 FlyByWire Simulations
// Copyright (c) 2021-2022 Synaptic Simulations
//
// SPDX-License-Identifier: GPL-3.0

import { MathUtils } from '@flybywiresim/fbw-sdk';

export interface FlightPlanPerformanceData {
  v1: number;

  vr: number;

  v2: number;

  databaseTransitionAltitude: number;

  databaseTransitionLevel: number;

  pilotTransitionAltitude: number;

  pilotTransitionLevel: number;

  get transitionAltitude(): AltitudeValue;

  get transitionAltitudeIsFromDatabase(): boolean;

  get transitionLevel(): AltitudeValue;

  get transitionLevelIsFromDatabase(): boolean;

  costIndex: number;

  cruiseFlightLevel: number;

  pilotTropopause: AltitudeValue;

  defaultTropopause: AltitudeValue;

  get tropopause(): AltitudeValue;

  get tropopauseIsPilotEntered(): boolean;

  // THR RED

  /**
   * THR RED pilot entry
   */
  pilotThrustReductionAltitude: AltitudeValue;

  /**
   * THR RED from NAV database
   */
  defaultThrustReductionAltitude: AltitudeValue;

  get thrustReductionAltitude(): AltitudeValue;

  get thrustReductionAltitudeIsPilotEntered(): boolean;

  // ACC

  /**
   * ACC pilot entry
   */
  pilotAccelerationAltitude: AltitudeValue;

  /**
   * ACC from NAV database
   */
  defaultAccelerationAltitude: AltitudeValue;

  get accelerationAltitude(): AltitudeValue;

  get accelerationAltitudeIsPilotEntered(): boolean;

  // EO ACC

  /**
   * EO ACC pilot entry
   */
  pilotEngineOutAccelerationAltitude: AltitudeValue;

  /**
   * EO ACC from NAV database
   */
  defaultEngineOutAccelerationAltitude: AltitudeValue;

  get engineOutAccelerationAltitude(): AltitudeValue;

  get engineOutAccelerationAltitudeIsPilotEntered(): boolean;

  // MISSED THR RED

  /**
   * Missed THR RED pilot entry
   */
  pilotMissedThrustReductionAltitude: AltitudeValue;

  /**
   * Missed THR RED from NAV database
   */
  defaultMissedThrustReductionAltitude: AltitudeValue;

  get missedThrustReductionAltitude(): AltitudeValue;

  get missedThrustReductionAltitudeIsPilotEntered(): boolean;

  // MISSED ACC

  /**
   * Missed ACC pilot entry
   */
  pilotMissedAccelerationAltitude: AltitudeValue;

  /**
   * Missed ACC from NAV database
   */
  defaultMissedAccelerationAltitude: AltitudeValue;

  get missedAccelerationAltitude(): AltitudeValue;

  get missedAccelerationAltitudeIsPilotEntered(): boolean;

  // MISSED EO ACC

  /**
   * Missed EO ACC pilot entry
   */
  pilotMissedEngineOutAccelerationAltitude: AltitudeValue;

  /**
   * Missed EO ACC from NAV database
   */
  defaultMissedEngineOutAccelerationAltitude: AltitudeValue;

  get missedEngineOutAccelerationAltitude(): AltitudeValue;

  get missedEngineOutAccelerationAltitudeIsPilotEntered(): boolean;

  clone(): this;
}

export type FlightPlanPerformanceDataProperties = Omit<FlightPlanPerformanceData, 'clone'>;

type VSpeedValue = number | undefined;

type AltitudeValue = Feet | undefined;

type CostIndexValue = number | undefined;

// TODO this should remain in fbw-a32nx/ once FMS is moved to fbw-common

export class A320FlightPlanPerformanceData implements FlightPlanPerformanceData {
  public clone(): this {
    const cloned = new A320FlightPlanPerformanceData();

    cloned.v1 = this.v1;
    cloned.vr = this.vr;
    cloned.v2 = this.v2;

    cloned.pilotThrustReductionAltitude = this.pilotThrustReductionAltitude;
    cloned.defaultThrustReductionAltitude = this.defaultThrustReductionAltitude;

    cloned.pilotAccelerationAltitude = this.pilotAccelerationAltitude;
    cloned.defaultAccelerationAltitude = this.defaultAccelerationAltitude;

    cloned.pilotEngineOutAccelerationAltitude = this.pilotEngineOutAccelerationAltitude;
    cloned.defaultEngineOutAccelerationAltitude = this.defaultEngineOutAccelerationAltitude;

    cloned.pilotMissedThrustReductionAltitude = this.pilotMissedThrustReductionAltitude;
    cloned.defaultMissedThrustReductionAltitude = this.defaultMissedThrustReductionAltitude;

    cloned.pilotMissedAccelerationAltitude = this.pilotMissedAccelerationAltitude;
    cloned.defaultMissedAccelerationAltitude = this.defaultMissedAccelerationAltitude;

    cloned.pilotMissedEngineOutAccelerationAltitude = this.pilotMissedEngineOutAccelerationAltitude;
    cloned.defaultMissedEngineOutAccelerationAltitude = this.defaultMissedEngineOutAccelerationAltitude;

    cloned.databaseTransitionAltitude = this.databaseTransitionAltitude;
    cloned.pilotTransitionAltitude = this.pilotTransitionAltitude;

    cloned.databaseTransitionLevel = this.databaseTransitionLevel;
    cloned.pilotTransitionLevel = this.pilotTransitionLevel;

    cloned.cruiseFlightLevel = this.cruiseFlightLevel;
    cloned.costIndex = this.costIndex;
    cloned.pilotTropopause = this.pilotTropopause;
    cloned.defaultTropopause = this.defaultTropopause;

    return cloned as this;
  }

  /**
   * Cruise FL
   */
  cruiseFlightLevel: AltitudeValue = undefined;

  /**
   * Cost index
   */
  costIndex: CostIndexValue = undefined;

  /**
   * Tropopause altitude in feet entered by the pilot, undefined if not entered
   */
  pilotTropopause: AltitudeValue = undefined;

  /**
   * Default tropopause altitude in feet
   */
  defaultTropopause: AltitudeValue = 36090;

  get tropopause() {
    const rawAlt = this.pilotTropopause ?? this.defaultTropopause;
    return rawAlt !== undefined ? MathUtils.round(rawAlt, -1) : undefined;
  }

  get tropopauseIsPilotEntered() {
    return this.pilotTropopause !== undefined;
  }

  /**
   * V1 speed
   */
  v1: VSpeedValue = undefined;

  /**
   * VR speed
   */
  vr: VSpeedValue = undefined;

  /**
   * V2 speed
   */
  v2: VSpeedValue = undefined;

  // THR RED

  /**
   * THR RED pilot entry
   */
  pilotThrustReductionAltitude: AltitudeValue = undefined;

  /**
   * THR RED from NAV database
   */
  defaultThrustReductionAltitude: AltitudeValue = undefined;

  /**
   * THR RED from pilot if entered, otherwise from database
   */
  get thrustReductionAltitude() {
    const rawAlt = this.pilotThrustReductionAltitude ?? this.defaultThrustReductionAltitude;
    return rawAlt !== undefined ? MathUtils.round(rawAlt, -1) : undefined;
  }

  /**
   * Whether THR RED is from the database
   */
  get thrustReductionAltitudeIsPilotEntered() {
    return this.pilotThrustReductionAltitude !== undefined;
  }

  // ACC

  /**
   * ACC pilot entry
   */
  pilotAccelerationAltitude: AltitudeValue = undefined;

  /**
   * ACC from NAV database
   */
  defaultAccelerationAltitude: AltitudeValue = undefined;

  /**
   * ACC from pilot if entered, otherwise from database
   */
  get accelerationAltitude() {
    const rawAlt = this.pilotAccelerationAltitude ?? this.defaultAccelerationAltitude;
    return rawAlt !== undefined ? MathUtils.round(rawAlt, -1) : undefined;
  }

  /**
   * Whether ACC is from the database
   */
  get accelerationAltitudeIsPilotEntered() {
    return this.pilotAccelerationAltitude !== undefined;
  }

  // EO ACC

  /**
   * EO ACC pilot entry
   */
  pilotEngineOutAccelerationAltitude: AltitudeValue = undefined;

  /**
   * EO ACC from NAV database
   */
  defaultEngineOutAccelerationAltitude: AltitudeValue = undefined;

  /**
   * EO ACC from pilot if entered, otherwise from database
   */
  get engineOutAccelerationAltitude() {
    const rawAlt = this.pilotEngineOutAccelerationAltitude ?? this.defaultEngineOutAccelerationAltitude;
    return rawAlt !== undefined ? MathUtils.round(rawAlt, -1) : undefined;
  }

  /**
   * Whether EO ACC is from the database
   */
  get engineOutAccelerationAltitudeIsPilotEntered() {
    return this.pilotEngineOutAccelerationAltitude !== undefined;
  }

  // MISSED THR RED

  /**
   * Missed THR RED pilot entry
   */
  pilotMissedThrustReductionAltitude: AltitudeValue = undefined;

  /**
   * Missed THR RED from NAV database
   */
  defaultMissedThrustReductionAltitude: AltitudeValue = undefined;

  /**
   * Missed THR RED from pilot if entered, otherwise from database
   */
  get missedThrustReductionAltitude() {
    const rawAlt = this.pilotMissedThrustReductionAltitude ?? this.defaultMissedThrustReductionAltitude;
    return rawAlt !== undefined ? MathUtils.round(rawAlt, -1) : undefined;
  }

  /**
   * Whether missed THR RED is from the database
   */
  get missedThrustReductionAltitudeIsPilotEntered() {
    return this.pilotMissedThrustReductionAltitude !== undefined;
  }

  // MISSED ACC

  /**
   * Missed ACC pilot entry
   */
  pilotMissedAccelerationAltitude: AltitudeValue = undefined;

  /**
   * Missed ACC from NAV database
   */
  defaultMissedAccelerationAltitude: AltitudeValue = undefined;

  /**
   * Missed ACC from pilot if entered, otherwise from database
   */
  get missedAccelerationAltitude() {
    const rawAlt = this.pilotMissedAccelerationAltitude ?? this.defaultMissedAccelerationAltitude;
    return rawAlt !== undefined ? MathUtils.round(rawAlt, -1) : undefined;
  }

  /**
   * Whether missed ACC is from the database
   */
  get missedAccelerationAltitudeIsPilotEntered() {
    return this.pilotMissedAccelerationAltitude !== undefined;
  }

  // MISSED EO ACC

  /**
   * Missed EO ACC pilot entry
   */
  pilotMissedEngineOutAccelerationAltitude: AltitudeValue = undefined;

  /**
   * Missed EO ACC from NAV database
   */
  defaultMissedEngineOutAccelerationAltitude: AltitudeValue = undefined;

  /**
   * Missed EO ACC from pilot if entered, otherwise from database
   */
  get missedEngineOutAccelerationAltitude() {
    const rawAlt = this.pilotMissedEngineOutAccelerationAltitude ?? this.defaultMissedEngineOutAccelerationAltitude;
    return rawAlt !== undefined ? MathUtils.round(rawAlt, -1) : undefined;
  }

  /**
   * Whether missed EO ACC is from the database
   */
  get missedEngineOutAccelerationAltitudeIsPilotEntered() {
    return this.pilotMissedEngineOutAccelerationAltitude !== undefined;
  }

  /**
   * TRANS ALT from NAV database
   */
  databaseTransitionAltitude: AltitudeValue = undefined;

  /**
   * TRANS ALT from pilot entry
   */
  pilotTransitionAltitude: AltitudeValue = undefined;

  /**
   * TRANS ALT from pilot if entered, otherwise from database
   */
  get transitionAltitude() {
    const rawAlt = this.pilotTransitionAltitude ?? this.databaseTransitionAltitude;
    return rawAlt !== undefined ? MathUtils.round(rawAlt, -1) : undefined;
  }

  /**
   * Whether TRANS ALT is from the database
   */
  get transitionAltitudeIsFromDatabase() {
    return this.pilotTransitionAltitude === undefined;
  }

  /**
   * TRANS LVL from NAV database
   */
  databaseTransitionLevel: AltitudeValue = undefined;

  /**
   * TRANS LVL from pilot entry
   */
  pilotTransitionLevel: AltitudeValue = undefined;

  /**
   * TRANS LVL from pilot if entered, otherwise from database
   */
  get transitionLevel() {
    const rawLevel = this.pilotTransitionLevel ?? this.databaseTransitionLevel;
    return rawLevel !== undefined ? MathUtils.round(rawLevel, 0) : undefined;
  }

  /**
   * Whether TRANS LVL is from the database
   */
  get transitionLevelIsFromDatabase() {
    return this.pilotTransitionLevel === undefined;
  }

  serialize(): SerializedFlightPlanPerformanceData {
    return {
      cruiseFlightLevel: this.cruiseFlightLevel,
      costIndex: this.costIndex,
      pilotTropopause: this.pilotTropopause,
      defaultTropopause: this.defaultTropopause,
      v1: this.v1,
      vr: this.vr,
      v2: this.v2,
      pilotThrustReductionAltitude: this.pilotThrustReductionAltitude,
      defaultThrustReductionAltitude: this.defaultThrustReductionAltitude,
      pilotAccelerationAltitude: this.pilotAccelerationAltitude,
      defaultAccelerationAltitude: this.defaultAccelerationAltitude,
      pilotEngineOutAccelerationAltitude: this.pilotEngineOutAccelerationAltitude,
      defaultEngineOutAccelerationAltitude: this.defaultEngineOutAccelerationAltitude,
      pilotMissedThrustReductionAltitude: this.pilotMissedThrustReductionAltitude,
      defaultMissedThrustReductionAltitude: this.defaultMissedThrustReductionAltitude,
      pilotMissedAccelerationAltitude: this.pilotMissedAccelerationAltitude,
      defaultMissedAccelerationAltitude: this.defaultMissedAccelerationAltitude,
      pilotMissedEngineOutAccelerationAltitude: this.pilotMissedEngineOutAccelerationAltitude,
      defaultMissedEngineOutAccelerationAltitude: this.defaultMissedEngineOutAccelerationAltitude,
      databaseTransitionAltitude: this.databaseTransitionAltitude,
      pilotTransitionAltitude: this.pilotTransitionAltitude,
      databaseTransitionLevel: this.databaseTransitionLevel,
      pilotTransitionLevel: this.pilotTransitionLevel,
    };
  }
}

export interface SerializedFlightPlanPerformanceData {
  cruiseFlightLevel: number | undefined;
  costIndex: number | undefined;
  defaultTropopause: number;
  pilotTropopause: number | undefined;

  v1: number | undefined;

  vr: number | undefined;

  v2: number | undefined;

  pilotThrustReductionAltitude: number | undefined;
  defaultThrustReductionAltitude: number | undefined;

  pilotAccelerationAltitude: number | undefined;
  defaultAccelerationAltitude: number | undefined;

  pilotEngineOutAccelerationAltitude: number | undefined;
  defaultEngineOutAccelerationAltitude: number | undefined;

  pilotMissedThrustReductionAltitude: number | undefined;
  defaultMissedThrustReductionAltitude: number | undefined;

  pilotMissedAccelerationAltitude: number | undefined;
  defaultMissedAccelerationAltitude: number | undefined;

  pilotMissedEngineOutAccelerationAltitude: number | undefined;
  defaultMissedEngineOutAccelerationAltitude: number | undefined;

  databaseTransitionAltitude: number | undefined;
  pilotTransitionAltitude: number | undefined;

  databaseTransitionLevel: number | undefined;
  pilotTransitionLevel: number | undefined;
}
