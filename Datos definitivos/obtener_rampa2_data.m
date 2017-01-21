rampa2=iddata(rampa2_d,rampa2_v,0.02);
T_rampa2=getTrend(rampa2);
T_rampa2.OutputOffset = 41.85502;
rampa2_data = detrend(rampa2,T_rampa2);
plot(rampa2_data)