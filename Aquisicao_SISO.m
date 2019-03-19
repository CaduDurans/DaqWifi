% Autores:  Carlos Eduardo Durans Nogueira
%           Antonio da Silva Silviera

clear all; close all; clc;

u1(1:10)=0; u1(11:200)=1;
nit=length(u2);
Ts = 0.1;
urlin='http://192.168.43.46/input/';
urlout='http://192.168.43.46/output/';

y(1:2)=0;
atraso(1:2)=0;

for k=3:nit,
    y(k)=daqwifi_read(urlin);
    daqwifi_write(urlout,u1(k),Ts);
end

% Plotando resultados
t=0:Ts:(Ts*nit-Ts);
sample=1:nit;

figure(1),
stairs(sample,u1,'b','LineWidth',2); hold;
stairs(sample,y,'r','LineWidth',2);
ylabel('Y(s)'); xlabel('Tempo em segundos');
title('Resultados');
legend('u1','y'); 
ylabel('Saída'); xlabel('Amostras');