%% Project Introdection:
%   This project is developed to design some signal filters based on digital
% signal processing.

%% Produce and sample digital signal
f1 = 10;
f2 = 20;
f3 = 100;
f4 = 200;          % so the fc = f4 = 200
%% Experiment 1 (Choosing samling frequency fs >= 2fc)
fs = 400;          % sampling frequency
[N1, xn1] = ProduceSamplingSignal(f1, f2, f3, f4, fs);
%% Experiment 2 (Choosing samling frequency fs < 2fc)
fs = 300;          % sampling frequency
[N2, xn2] = ProduceSamplingSignal(f1, f2, f3, f4, fs);