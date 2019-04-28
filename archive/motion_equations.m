pkg load symbolic;

syms v_i a j t


# t = (j*v_c - (a^2) -j*v_i)/j*a
t = (-3*(a^2)-2*j*v_i + sqrt((a^4) - 4*(a^2)*j*v_i + 8*a*(j^2)*s_c + 4*(j^2)*(v_i^2)))/(2*a*j)


v_a = v_i + (a^2)/(2*j)
s_a = v_i*(a/j) +(a^3)/(6*(j^2))

v_b = v_a + a*t
s_b = s_a + v_a*t + (a*(t^2))/2

v_c = v_b + a*(a/j)-(j*((a/j)^2))/2
#s_c = s_b + v_b*(a/j) + (a*((a/j)^2))/2 -(j*((a/j)^3))/6

#simp_expr = simplify(v_c)


#t = (-3*(a^2)-2*j*v_i + sqrt((a^4) - 4*(a^2)*j*v_i + 8*a*(j^2)*s_c + 4*(j^2)*(v_i^2)))/(2*a*j)
v_c = v_b + a*(a/j)-(j*((a/j)^2))/2

simp_expr = simplify(v_c)
