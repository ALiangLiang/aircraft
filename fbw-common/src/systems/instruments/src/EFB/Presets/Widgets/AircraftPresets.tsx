// Copyright (c) 2023-2024 FlyByWire Simulations
// SPDX-License-Identifier: GPL-3.0

/* eslint-disable max-len */
import React, { useState } from 'react';
import { useSimVar } from '@flybywiresim/fbw-sdk';
import { Toggle, t, ScrollableContainer, PromptModal, useModals } from '@flybywiresim/flypad';

import { useViewListenerEvent } from '../../Utils/listener';

export const AircraftPresets = () => {
  // Aircraft presets are handled by a backend WASM module. This frontend will
  // use the LVAR A32NX_AIRCRAFT_PRESET_LOAD to signal the backend that the user
  // requests a preset to be loaded.
  // The backend will reset the LVAR to 0 when done.
  // As long as the LVAR is >0, the backend is still applying the preset.
  // If the LVAR is set to 0 before the backend is finished, applying, the preset
  // will be stopped by the backend.
  // A32NX_AIRCRAFT_PRESET_LOAD_EXPEDITE is a LVAR to expedite the loading of the preset
  // by skipping the delay between steps.

  const [simOnGround] = useSimVar('SIM ON GROUND', 'number', 200);
  const [loadPresetVar, setLoadPresetVar] = useSimVar('L:A32NX_AIRCRAFT_PRESET_LOAD', 'number', 200);
  const [loadPresetsExpedite, setLoadPresetsExpedite] = useSimVar(
    'L:A32NX_AIRCRAFT_PRESET_LOAD_EXPEDITE',
    'number',
    250,
  );

  const { showModal } = useModals();

  // State to store the loading progress and the current step description
  const [loadPresetProgress, setLoadPresetProgress] = useState(0);
  const [currentStepDescription, setCurrentStepDescription] = useState('');

  // Callback function to update the loading progress from the WASM module
  const onProgressUpdateFromWasm = (data: string) => {
    const [progressPercentage, currentStep] = data.split(';');
    setLoadPresetProgress(parseFloat(progressPercentage));
    setCurrentStepDescription(currentStep);
  };

  // Register the callback function to receive the loading progress from the WASM module
  useViewListenerEvent('JS_LISTENER_COMM_BUS', 'AIRCRAFT_PRESET_WASM_CALLBACK', onProgressUpdateFromWasm);

  // These need to align with the IDs in the Presets C++ WASM.
  // WASM: src/presets/src/Aircraft/AircraftProcedures.h
  const AircraftPresetsList: { index: number; name: string }[] = [
    { index: 1, name: `${t('Presets.AircraftStates.ColdDark')}` }, // 'Cold & Dark' },
    { index: 2, name: `${t('Presets.AircraftStates.Powered')}` },
    { index: 3, name: `${t('Presets.AircraftStates.ReadyPushback')}` },
    { index: 4, name: `${t('Presets.AircraftStates.ReadyTaxi')}` },
    { index: 5, name: `${t('Presets.AircraftStates.ReadyTakeoff')}` },
  ];

  // Sets the LVAR to tell the wasm to load the preset into the aircraft
  const handleLoadPreset = (presetID: number) => {
    showModal(
      <PromptModal
        title={`${AircraftPresetsList[presetID - 1].name}`}
        bodyText={t('Presets.AircraftStates.ConfirmationDialogMsg')}
        onConfirm={() => setLoadPresetVar(presetID)}
      />,
    );
  };

  // Called by the cancel button to stop and cancel loading of a preset
  const handleCancel = () => {
    setLoadPresetVar(0);
  };

  return (
    <div className="h-content-section-reduced border-theme-accent mt-4 space-y-4 rounded-lg border-2 p-4">
      <div className="border-theme-accent flex h-20 flex-row items-center justify-center space-x-2 rounded-md border-2 p-2">
        {loadPresetVar ? (
          <>
            <div className="bg-theme-accent h-full w-full content-center justify-center overflow-hidden rounded-md">
              <span className="h-1/2 pl-3 pt-1 text-xl">
                {t('Presets.AircraftStates.CurrentProcedureStep')}: {currentStepDescription}
              </span>
              <div
                className="bg-theme-highlight h-1/2"
                style={{ width: `${loadPresetProgress * 100}%`, transition: 'width 0.1s ease' }}
              />
            </div>

            <div
              className="border-theme-highlight bg-theme-highlight text-theme-body hover:bg-theme-body hover:text-theme-highlight flex h-full items-center rounded-md border-2 px-4 transition duration-100"
              onClick={() => handleCancel()}
            >
              {t('Presets.AircraftStates.Cancel')}
            </div>
          </>
        ) : (
          <>
            {simOnGround
              ? t('Presets.AircraftStates.SelectAPresetToLoad')
              : t('Presets.AircraftStates.TheAircraftMustBeOnTheGroundToLoadAPreset')}
          </>
        )}
      </div>

      <ScrollableContainer innerClassName="space-y-4" height={42}>
        {AircraftPresetsList.map(({ index, name }) => (
          <div
            key={index}
            className={`border-theme-accent bg-theme-accent text-theme-text hover:bg-theme-highlight hover:text-theme-body flex h-24 items-center justify-center rounded-md border-2 transition duration-100 ${(!simOnGround || (loadPresetVar && loadPresetVar !== index)) && 'pointer-events-none opacity-50'}`}
            onClick={() => handleLoadPreset(index)}
          >
            {name}
          </div>
        ))}
      </ScrollableContainer>

      <div className="border-theme-accent mt-14 rounded-md border-2 px-4 py-1">
        <div className="flex h-10 flex-row items-center">
          <div className="pr-3">{t('Presets.AircraftStates.ExpediteLoading')}</div>
          <Toggle value={!!loadPresetsExpedite} onToggle={(value) => setLoadPresetsExpedite(value ? 1 : 0)} />
        </div>
      </div>
    </div>
  );
};
