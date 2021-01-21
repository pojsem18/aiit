
close all;
clear all;
clc;

global DEBUG_ECG;
DEBUG_ECG = 1;      %set this variable to 1 to show debug figures and information

fs = 360;               %sample rate of ecg signal
load 100;               %load ecg signals from database
ecg_wave = ecg(:,1)';
time = 0:1/fs:(length(ecg_wave)-1)*1/fs;

%4.2.1 - 4.2.6
[r_peaks1, p_wave, t_wave] = ecg_rdetect(ecg_wave, fs);           %use 2 times differentation method
% r_peaks2 = ecg_rdetect(ecg_wave, fs, 0.04);                        %use threshold method

% %4.2.7
% %define a template containing the qrs complex
% n_samples_qr = 0.05 * fs;
% n_samples_rs = 0.15 * fs;
% ecg_qrs_template = ecg_wave(r_peaks1(1) - n_samples_qr : r_peaks1(1) + n_samples_rs);    % use first qrs complex in signal ecg_wave as template
% 
% %4.2.8
% qrs_sig = ecg_qrsdetect(ecg_wave, ecg_qrs_template, 0.4);
