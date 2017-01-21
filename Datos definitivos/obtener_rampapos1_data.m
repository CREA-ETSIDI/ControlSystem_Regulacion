rampapos1=iddata(rampapos1_d,rampapos1_v,0.02);
T_rampapos1=getTrend(rampapos1);
T_rampapos1.OutputOffset = 31.76684;
rampapos1_data = detrend(rampapos1,T_rampapos1);
plot(rampapos1_data)