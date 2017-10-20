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


%%%%%%%%%%%%%%%%%%% Control system design
A = [0 1 0; 0 0 0; 0 0 0];
B = [0 0 ; 0 k_1 ; k_2 0];
C = [1 0 0; 0 0 1];
Q = diag([1500 500 1000]); %pitch, pitch rate, elevation rate
R = diag([100 10]);%elevation rate, pitch

K = lqr(A,B,Q,R);
P = inv(C*(inv(B*K - A)) * B);
%P = [0 31.6228; 1 0];

