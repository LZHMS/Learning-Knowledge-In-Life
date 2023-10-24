function [N, xn] = ProduceSamplingSignal(f1, f2, f3, f4, fs)
% ProduceSamplingSignal Function:
%    Function Description: 
%            We want to make a digital signal composed of four frequency
%            components and sample the produced signal.
%    Inputs: f1, f2, f3, f4 means our selected frequency components, fs
%            represents the sampling frequency.
%    Outputs:
%            N: represents the number of sampling points
%            xn: represents the sampled signal

    ts = 1/fs;            % sampling timestep
    t = 0: ts : 0.5;        % samping sequence of discrete sampling points
    t0 = 0: 0.0001: 0.5;    % analog time sequence
    N = 1 / ts;           % samping points
    % Produce digital signal
    xt = cos(2*pi*f1*t0 - pi/6) + 2.0 * cos(4*pi*f2*t0 + pi/3) + ...
         0.4*cos(6*pi*f3*t0 - pi*2/3) + 0.5*cos(8*pi*f4*t0 + pi/3);
    % Sample produced signal
    xn = cos(2*pi*f1*t - pi/6) + 2.0 * cos(4*pi*f2*t + pi/3) + ...
        0.4*cos(6*pi*f3*t - pi*2/3) + 0.5*cos(8*pi*f4*t + pi/3);

    % Visualize produced signal and sampled signal
    figure;
    subplot(2, 1, 1);
    plot(t0, xt);
    txt = title('Time-domain signal $x(t)$');
    set(txt, 'Interpreter', 'latex');
    txt = xlabel('$t/s$');
    set(txt, 'Interpreter', 'latex');
    txt = ylabel('Amplitude');
    set(txt, 'Interpreter', 'latex');
    grid on
    subplot(2, 1, 2);
    stem(t, xn);
    txt = title('Time-domain sampled signal $x(n)$');
    set(txt, 'Interpreter', 'latex');
    txt = ylabel('Amplitude');
    set(txt, 'Interpreter', 'latex');
    txt = xlabel('$N$');
    set(txt, 'Interpreter', 'latex');
    grid on
end