seno=iddata(seno_d,seno_v,0.02);
T_seno=getTrend(seno);
T_seno.OutputOffset = 34.64097;
seno_data = detrend(seno,T_seno);
plot(seno_data)