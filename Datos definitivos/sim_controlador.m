modelo=tf(m4);
controlador=tf(C_extra);
modelo_c=feedback(modelo*controlador,1);
step(modelo_c)