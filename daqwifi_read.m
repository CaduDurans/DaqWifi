% ----------------------------------------------------------------------
% DAQ-Duino: Matlab side code. Make sure NodeMCU side is up and running.
% Authors: Carlos Eduardo Durans Nogueira (cednogueira@gmail.com) and 
% Prof. Antonio Silveira (asilveira@ufpa.br)
%   Laboratory of Control and Systems, UFPA (lacos.ufpa.br)
% ----------------------------------------------------------------------
% daqWifi_read  Single-shot acquisition by A/D conversion of a single
%               sample from the analog input in use.
%
%   Example:
%
%     y=daqwifi_read(url);
%
%         Stores to y a single sample from the analog channel in use. 
%         The range of the analog input is 0V to 3.3V.

function [y]=daqwifi_read(url),

 options=weboptions('Timeout',12); % Espera resposta de 12 segundos

    [y] = str2num(webread(url,options) );