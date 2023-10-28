function DFTAnalysis(xn, fs)
% Function Description:
%       This function calculates the DFT[x(n)] and do spectral analysis.
% Inputs:
%       xn: digital discrete signal
%       fs: sampling frequency
% Outputs:
%       No return

    N = length(xn);    % number of sampling points
    df = fs / N;       % spectral resolution
    f = (0:N-1)*df;    % tranverse to the frequncy sequence

    % DFT using FFT algorithm
    Xk = fft(xn, N);   
    % Tranverse to the real amplitude
    RM = 2*abs(Xk)/N;

    % Amplitude-Frequency Characteristics
    figure;
    subplot(3,1,1);
    stem(f, RM,'.');
    txt = title('Amplitude-Frequency Characteristics');
    set(txt, 'Interpreter', 'latex');
    txt = xlabel('f/Hz');
    set(txt, 'Interpreter', 'latex');
    txt = ylabel('Amplitude');
    set(txt, 'Interpreter', 'latex');
    grid on;

    % Outline of Amplitude-Frequency Characteristics
    subplot(3,1,2);
    plot(f, RM);
    txt = title('Outline of Amplitude-Frequency Characteristics');
    set(txt, 'Interpreter', 'latex');
    txt = xlabel('f/Hz');
    set(txt, 'Interpreter', 'latex');
    txt = ylabel('Amplitude');
    set(txt, 'Interpreter', 'latex');
    grid on;

    % Phase-Frequency Characteristics
    subplot(3,1,3);
    stem(f, angle(Xk),'.'); 
    line([(N-1)*df, 0],[0,0]);
    txt = title('Phase-Frequency Characteristics');
    set(txt, 'Interpreter', 'latex');
    txt = xlabel('f/Hz');
    set(txt, 'Interpreter', 'latex');
    txt = ylabel('Phase');
    set(txt, 'Interpreter', 'latex');
    grid on;
end

