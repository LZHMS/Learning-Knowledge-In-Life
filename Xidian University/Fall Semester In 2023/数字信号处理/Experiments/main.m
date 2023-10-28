%% Project Introdection:
%   This project is developed to design some signal filters based on digital
% signal processing.
clear, close all;
%% Produce and sample digital signal
f1 = 10;
f2 = 20;
f3 = 30;      % so the fc = f3 = 30Hz
Np = 3;      % number of periods for time-domain window
%% Experiment 1 (Choosing samling frequency fs = 3fc (fs > 2fs))
fs = 90;          % sampling frequency
xn1 = ProduceSamplingSignal(f1, f2, f3, fs, Np);
DFTAnalysis(xn1, fs);

%% Experiment 2 (Choosing samling frequency fs = 2fc)
fs = 60;          % sampling frequency
xn2 = ProduceSamplingSignal(f1, f2, f3, fs, Np);
DFTAnalysis(xn2, fs);

%% Experiment 3 (Choosing samling frequency fs < 2fc)
fs = 40;          % sampling frequency
xn3 = ProduceSamplingSignal(f1, f2, f3, fs, Np);
DFTAnalysis(xn3, fs);

