% FOR HELICOPTER NR 3-10
% This file contains the initialization for the helicopter assignment in
% the course TTK4115. Run this file before you execute QuaRC_ -> Build 
% to build the file heli_q8.mdl.

% Oppdatert høsten 2006 av Jostein Bakkeheim
% Oppdatert høsten 2008 av Arnfinn Aas Eielsen
% Oppdatert høsten 2009 av Jonathan Ronen
% Updated fall 2010, Dominik Breu
% Updated fall 2013, Mark Haring
% Updated spring 2015, Mark Haring


%%%%%%%%%%% Calibration of the encoder and the hardware for the specific
%%%%%%%%%%% helicopter
Joystick_gain_x = 1;
Joystick_gain_y = -1;


%%%%%%%%%%% Physical constants
g = 9.81; % gravitational constant [m/s^2]
l_c = 0.46; % distance elevation axis to counterweight [m]
l_h = 0.66; % distance elevation axis to helicopter head [m]
l_p = 0.175; % distance pitch axis to motor [m]
m_c = 1.92; % Counterweight mass [kg]
m_p = 0.72; % Motor mass [kg]
k_f = (1/(6.3*0.66))*((2*m_p*g*l_h)-(m_c*g*l_c));

l_1 = l_p*k_f;
l_2 = g*(l_c*m_c - 2*m_p * l_h);
l_3 = l_h * k_f;
l_4 = - l_h * k_f;

j_p = 2*m_p*l_p^2;
j_e = m_c * l_c^2 + 2*m_p*l_h^2;
j_lambda = m_c*l_c^2 + 2*m_p*(l_h^2 + l_p^2);

k_1 = l_1 /j_p;
k_2 = l_3 / j_e;
k_3 = (-l_4*l_2) / (j_lambda * l_3);
%w_n = 0.35;

%k_pp = k_1/w_n^2;
%k_pd = (2/w_n)*k_pp;

k_pp = 8;
k_pd = 10;

k_pt = 10;


A = [0 1 0 0 0; 0 0 0 0 0; 0 0 0 0 0; 1 0 0 0 0; 0 0 1 0 0];
B = [0 0 ; 0 k_1 ; k_2 0; 0 0; 0 0];
C = [1 0 0; 0 0 1];
Q = diag([100 1000 100 100000 10000]); %pitch, pitch rate, elevation rate, pitch integral, elevation integral
R = diag([10 1000]);
K = lqr(A,B,Q,R);

%C_ctrl = [B A*B (A*A)*B];
%D = zeros(2,2);

%f = K(1,3);
%g = K(2,1);
%h = K(2,2); 

%sys = ss(A,B,C,D);
%controll = rank(ctrb(sys));
%controll = rank(C);
% P utrekna fra formel i slides
%P = inv(C*(inv(B*K - A)) * B);
P = [0 31.6228; 1 0];

A_obs = [0 1 0 0 0 0; 0 0 0 0 0 0; 0 0 0 1 0 0; 0 0 0 0 0 0; 0 0 0 0 0 1; k_3 0 0 0 0 0];
C_obs = [1 0 0 0 0 0; 0 0 1 0 0 0; 0 0 0 0 1 0];

CA1 = C_obs * A_obs;
CA2 = C_obs * A_obs * A_obs;
CA3 = C_obs * A_obs * A_obs * A_obs;
CA4 = C_obs * A_obs * A_obs * A_obs * A_obs;
CA5 = C_obs * A_obs * A_obs * A_obs * A_obs * A_obs;v 

O = [C_obs;CA1;CA2;CA3;CA4;CA5];

controll = rank(O);
