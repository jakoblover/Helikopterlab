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

A_P = [0 1 0; 0 0 0; 0 0 0];
B_P = [0 0 ; 0 k_1 ; k_2 0];
C_P = [1 0 0; 0 0 1];

%---------Proportional-Integrator regulator matrices----------%
A_PI = [0 1 0 0 0; 0 0 0 0 0; 0 0 0 0 0; 1 0 0 0 0; 0 0 1 0 0];
B_PI = [0 0 ; 0 k_1 ; k_2 0; 0 0; 0 0];
C_PI = [0 0 1 0 0; 0 0 1 0 0];

%---------Observer matrices----------%
A_obs = [0 1 0 0 0 0; 0 0 0 0 0 0; 0 0 0 1 0 0; 0 0 0 0 0 0; 0 0 0 0 0 1; k_3 0 0 0 0 0];
B_obs = [0 0 ; 0 k_1 ; 0 0; k_2 0; 0 0; 0 0];
C_obs = [0 0 1 0 0 0; 0 0 0 0 1 0];

R = diag([10 1000]);
Q_P = diag([10000 10000 1000]); 
Q_PI = diag([100 1000 1000 100000 10000]); %pitch, pitch rate, elevation rate, pitch integral, elevation integral
K_P = lqr(A_P, B_P, Q_P, R);
K_PI = lqr(A_PI, B_PI, Q_PI, R);
P_PI = inv(C_P*inv(B_P*K_PI(:,1:3) - A_P) * B_P);

system_poles = eig(A_P-B_P*K_P);
system_poles_max_magnitude = max(abs(eig(A_P-B_P*K_P)))*20;
obsv_poles_angle = [-pi*(1/8) -pi*(3/40) -pi*(1/40) pi*(1/40) pi*(3/40) pi*(1/8)];
obsv_poles = -system_poles_max_magnitude*exp(1i*obsv_poles_angle);

L = place(A_obs',C_obs',obsv_poles)';

A_LC = A_obs - (L*C_obs);
