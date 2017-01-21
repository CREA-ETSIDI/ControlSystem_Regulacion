rampaneg1=iddata(rampaneg1_d,rampaneg1_v,0.02);
T_rampaneg1=getTrend(rampaneg1);
T_rampaneg1.OutputOffset = 43.56363;
rampaneg1_data = detrend(rampaneg1,T_rampaneg1);
plot(rampaneg1_data)