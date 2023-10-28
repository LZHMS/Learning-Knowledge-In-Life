function xn = ProduceSamplingSignal(f1, f2, f3, fs, Np)
% Function Description: 
%        We want to make a digital signal composed of three frequency
%        components and sample the produced signal.
% Inputs: 
%        f1, f2, f3: means our selected frequency components, fs
%            represents the sampling frequency.
%        Np: means the number of periods.
% Outputs:
%        xn: represents the sampled signal.

    period = 1/f1;        % the period of analog signal(assuming f1 is the minimal)
    T = Np*period;         % sampling time-domain window(several periods)
    Ts = 1 / fs;          % sampling timestep
    t0 = 0: Ts : T;       % samping sequence of discrete sampling points
    t = 0: 0.0001: T;     % analog time sequence

    % Step I: Produce digital signal
    xt = cos(2*pi*f1*t) + cos(2*pi*f2*t) + cos(2*pi*f3*t);
    % Step II: Sample produced signal
    xn = cos(2*pi*f1*t0) + cos(2*pi*f2*t0) + cos(2*pi*f3*t0);

    % Step III: Visualize produced signal and sampled signal
    figure;
    subplot(2, 1, 1);
    plot(t, xt);
    txt = title('Time-domain signal $x(t)$');
    set(txt, 'Interpreter', 'latex');
    txt = xlabel('$t/s$');
    set(txt, 'Interpreter', 'latex');
    txt = ylabel('Amplitude');
    set(txt, 'Interpreter', 'latex');
    grid on

    subplot(2, 1, 2);
    stem(t0, xn);
    txt = title('Time-domain sampled signal $x(n)$');
    set(txt, 'Interpreter', 'latex');
    txt = ylabel('Amplitude');
    set(txt, 'Interpreter', 'latex');
    txt = xlabel('$N$');
    set(txt, 'Interpreter', 'latex');
    grid on
end