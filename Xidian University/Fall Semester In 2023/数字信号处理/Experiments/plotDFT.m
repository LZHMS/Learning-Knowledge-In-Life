function [F, Fi] = plotDFT(xn, N, fs) %Xn 为被变换离散信号
    figure;
    subplot(3, 1, 1)
    plotTime(N, xn, 1);
    Xk = fft(xn);
    
    F = abs(Xk)*2/N;        %幅频特性
    Fi = angle(Xk);         %相频特性
    Nn = floor((N-1)/2);    %有效点
    f = (0:Nn)*fs/N ;       %横坐标 频率HZ
    F = F(1:Nn+1);          %幅值(仅取有用点Nn个点)
    Fi = Fi(1:Nn+1);        %相位(仅取有用点Nn个点)
    Fi = unwrap(Fi);
    Fi = Fi/pi;
    
    subplot(3,1,2);
    stem(f, F);
    title('DFT的幅频特性');
    xlabel('f/Hz');
    ylabel('幅值');
    grid on;
    
    subplot(3,1,3);
    plot(f, Fi);
    title('DFT的相频特性');
    xlabel('f/Hz');
    ylabel('相位/pi');
    grid on;
 
end

