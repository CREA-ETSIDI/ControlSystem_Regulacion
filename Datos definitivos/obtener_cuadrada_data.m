cuadrada=iddata(cuadrada_d,cuadrada_v,0.02);
T_cuadrada=getTrend(cuadrada);
T_cuadrada.OutputOffset = 37.46774;
cuadrada_data = detrend(cuadrada,T_cuadrada);
plot(cuadrada_data)