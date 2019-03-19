% ----------------------------------------------------------------------
% DAQWiFi: Matlab side code. Make sure NodeMCU side is up and running.
% Authors: Carlos Eduardo Durans Nogueira (cednogueira@gmail.com) and 
% Prof. Antonio Silveira (asilveira@ufpa.br)
%   Laboratory of Control and Systems, UFPA (lacos.ufpa.br)
% ----------------------------------------------------------------------
% daqWifi_write  Updates the DaqDuino PWM output in use.
%
%     daqwifi_write(url,u1,Ts) sets u Volts, where u range is 0V to 3.3V,
%     and Ts is the sampling time (a delay) given in seconds.

function []=daqwifi_write(url,u1,Ts),
    global s;
                  
    webwrite(url,'u1',num2str(u1)); % Sends u(k) as a string

    pause(Ts); % Sampling time interval